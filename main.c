#include "./pipex.h"

void child_process(t_clarg *clarg, t_lcmd *header, int fd[2], char **envp)
{
    close(fd[0]);
    if(header->next != NULL)
    {
        if(dup2(fd[1], STDOUT_FILENO) == -1)
            cleanup(clarg, DUP2, NULL);
    }
    else if (header->next == NULL)
    {
        if(dup2(clarg->outfile_fd, STDOUT_FILENO) == -1)
            cleanup(clarg, DUP2, NULL);
    }
    close(fd[1]);
    close(clarg->outfile_fd);
    if (execve(header->path_cmd, header->cmd, envp) == -1)
        cleanup(clarg, EXECVE, NULL);
}

void pipex(t_clarg *clarg, char **envp)
{
    int fd[2];
    pid_t pid;
    t_lcmd *header;

    header = clarg->cmds_header;
    if (dup2(clarg->infile_fd, STDIN_FILENO) == -1)
        cleanup(clarg, DUP2, NULL);
    close(clarg->infile_fd); //to avoid duplicates
    while (header != NULL)
    {
        if (pipe(fd) == -1)
            cleanup(clarg, PIPE, NULL);
        pid = fork();
        if (pid == -1)
            cleanup(clarg, FORK, NULL);
        if (pid == 0)
            child_process(clarg, header, fd, envp);
        close(fd[1]); //parent process won't be writing
        if (dup2(fd[0], STDIN_FILENO) == -1)
            cleanup(clarg, DUP2, NULL);
        wait(NULL); //handle error?
        close(fd[0]);
        header = header->next;
    }
}

/* envp is array of pointers where each element is an environment variable.
We're interested in the PATH variable (executables directories). */
int main(int argc, char **argv, char **envp)
{
    t_clarg *clarg;

    clarg = NULL;
    if (argc != 5)
        cleanup(clarg, WRNG_ARGS, NULL); //could have called handle_error directly
    fill_clarg(argc, argv, envp, &clarg);
    clarg->cmds_header = fill_lcmd(clarg, argc, argv);
    pipex(clarg, envp);
    cleanup(clarg, "succes!", NULL);
    return 0;
}


/*checker t_clarg + t_lcmd structs are parsed
    printf("infile fd is: %d\n", clarg->infile_fd);
    printf("outfile fd is: %d\n", clarg->outfile_fd);
    while (*(clarg->path_all) != NULL)
    {
        printf("path is: %s\n", *(clarg->path_all));
        (clarg->path_all)++;
    }
    while (clarg->cmds_header != NULL)
    {
        printf("Path: %s\n", clarg->cmds_header->path_cmd);
        printf("Command: ");
        for (int i = 0; clarg->cmds_header->cmd[i]; i++) {
            printf("%s ", clarg->cmds_header->cmd[i]);
        }
        printf("\n\n");
        clarg->cmds_header = clarg->cmds_header->next;
    }*/