# include <unistd.h> //write, read, access, dup, dup2, execve, fork, pipe, unlink
#include <sys/wait.h> //wait, waitpid
# include <fcntl.h> //open, close
# include <stdlib.h> // malloc, free 
# include <stdio.h> // perror
#include <errno.h>
#include "./pipex_libft/libft.h"
//to add, libft

//LIST OF ERRORS TO PRINT

#define WRNG_ARGS "Errror: invalid arguments. Usage: ./pipex infile cmd1 cmd2 outfile"
#define MALLOC "Error: malloc"
#define INFILE "Error: infile failure" //errno will specify type of infile error (no file, no permission, etc.)
#define OUTFILE "Error: outfile failure" //errno will specify
#define NO_PATH "Error: no path found"
#define SPLIT "Error: ft_split function" //to be modified, why is ft_split erroring?
#define SPLIT_COMMAND "Error: ft_split function or command not found" // to be modified
#define STR_JOIN "Error: ft_strjoin function" //to be modified


//struct including data about infile, outfile, cmds and PATH env
typedef struct s_clarg
{
	int		infile_fd;
	int		outfile_fd;
    struct s_lcmd	*cmds_header;
	char	**path_all;
}				t_clarg;

//struct of a node making up a linked list 
typedef struct s_lcmd
{
	char *path_cmd;
	char **cmd;
	struct s_lcmd *next;
}	t_lcmd;

//errors.c
void handle_error(const char * message);

//parsing.c
t_clarg *fill_clarg(int argc, char **argv, char **envp);

