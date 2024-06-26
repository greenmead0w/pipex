#include "./mandatory/pipex.h"

void child_process(t_clarg *clarg, t_lcmd *header, int fd[2], char **envp)
{
    close(fd[0]);
    if(header->next != NULL)
    {
        if(dup2(fd[1], STDOUT_FILENO) == -1)
            cleanup(clarg, DUP2);
    }
    else if (header->next == NULL)
    {
        if(dup2(clarg->outfile_fd, STDOUT_FILENO) == -1)
            cleanup(clarg, DUP2);
    }
    close(fd[1]);
    close(clarg->outfile_fd);
    if (execve(header->path_cmd, header->cmd, envp) == -1)
        cleanup(clarg, EXECVE);
}

void pipex(t_clarg *clarg, char **envp)
{
    int fd[2];
    pid_t pid;
    t_lcmd *header;

    header = clarg->cmds_header;
    if (dup2(clarg->infile_fd, STDIN_FILENO) == -1)
        cleanup(clarg, DUP2);
    close(clarg->infile_fd); //to avoid duplicates
    while (header != NULL)
    {
        if (pipe(fd) == -1)
            cleanup(clarg, PIPE);
        pid = fork();
        if (pid == -1)
            cleanup(clarg, FORK);
        if (pid == 0)
            child_process(clarg, header, fd, envp);
        close(fd[1]); //parent process won't be writing
        if (dup2(fd[0], STDIN_FILENO) == -1)
            cleanup(clarg, DUP2);
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
        cleanup(clarg, WRNG_ARGS); //could have called handle_error directly
    fill_clarg(argc, argv, envp, &clarg);
    clarg->cmds_header = fill_lcmd(clarg, argc, argv);
    pipex(clarg, envp);
    cleanup(clarg, END);
    return 0;
}