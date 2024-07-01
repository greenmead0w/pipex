/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 11:04:52 by mzuloaga          #+#    #+#             */
/*   Updated: 2024/07/01 11:11:18 by mzuloaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h> //write, read, access, dup, dup2, execve, fork, pipe, unlink
#include <sys/wait.h> //wait, waitpid
#include <fcntl.h> //open, close
#include <stdlib.h> // malloc, free 
#include <stdio.h> // perror
#include <errno.h>
#include "./pipex_libft/libft.h"

//List of errors to print

#define WRNG_ARGS \
"Errror: invalid arguments. Usage:./pipex infile cmd1 cmd2 \
outfile OR ./pipex here_doc DELIMITER cmd1 cmd2 outfile"
#define MALLOC "Error: malloc"
#define INFILE "Error: infile failure" //errno will specify type of infile error
#define HD_INFILE "Error: here_doc infile failure"
#define OUTFILE "Error: outfile failure" //errno will specify
#define NO_PATH "Error: no path found"
#define SPLIT "Error: ft_split function"
#define SPLIT_COMMAND "Error: ft_split function or command not found"
#define NO_CMD_PATH "Error: no command executable path found"
#define DUP2 "Error: dup2 function"
#define PIPE "Error: pipe function"
#define FORK "Error: fork function"
#define EXECVE "Error: execve function"
#define UNLINK "Error: unlink function"
#define WAIT "Error: wait function"
#define END "Success is:"

//struct including data about infile, outfile, cmds and PATH env
typedef struct s_clarg
{
	int				infile_fd;
	int				outfile_fd;
	struct s_lcmd	*cmds_header;//pointer to head of the cmds data linked list
	char			**path_all;
}				t_clarg;

//struct of a node making up a linked list 
typedef struct s_lcmd
{
	char			*path_cmd; //full path to executable
	char			**cmd; // command and its arguments
	struct s_lcmd	*next;
}	t_lcmd;

//errors.c
void	*handle_error(const char *message);
void	free_split(char ***cmd);
void	free_lcmd_list(t_lcmd *head);
void	*cleanup(t_clarg *clarg, char *message, char *flag);

//parsing.c
void	fill_clarg(int argc, char **argv, char **envp, t_clarg **clarg);
t_lcmd	*fill_lcmd(t_clarg *clarg, int argc, char **argv);
char	*get_cmd_path(t_clarg *clarg, char *cmd);
//ADD CODE HERE!

//utils.c
t_lcmd	*create_node(char *path_cmd, char **cmd);
void	add_node(t_lcmd **lst, t_lcmd *new_node);