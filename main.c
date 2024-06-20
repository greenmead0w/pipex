#include "./pipex.h"

/*
add errno.h to differentiate errors (for example, when opening a file)
1) create a function to clean up and exit
2) cretae a function to print errors to stderror
3) create a function to fill CLI struct data
4)
*/

/* envp is array of pointers where each element is an environment variable.
We're interested in the PATH variable (executables directories). */
int main(int argc, char **argv, char **envp)
{
    t_clarg *clarg;

    if (argc != 5)
        handle_error(WRNG_ARGS); //cleanup function needs to be implemented first
    clarg = fill_clarg(argc, argv, envp);
    //clarg->cmds_header = fill_command(clarg, argc, argv);
    printf("infile fd is: %d\n", clarg->infile_fd);
    printf("outfile fd is: %d\n", clarg->outfile_fd);
    while (*(clarg->path_all) != NULL)
    {
        printf("path is: %s\n", *(clarg->path_all));
        (clarg->path_all)++;
    }
    return 0;
}

