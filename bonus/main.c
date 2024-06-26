/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 09:46:00 by mzuloaga          #+#    #+#             */
/*   Updated: 2024/06/26 10:20:43 by mzuloaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex.h"

/*
executes cmd and writes output to pipe or outfile depending on if its last cmd 
or not
*/
void	child_process(t_clarg *clarg, t_lcmd *header, int fd[2], char **envp)
{
	close(fd[0]);
	if (header->next != NULL)
	{
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			cleanup(clarg, DUP2);
	}
	else if (header->next == NULL)
	{
		if (dup2(clarg->outfile_fd, STDOUT_FILENO) == -1)
			cleanup(clarg, DUP2);
	}
	close(fd[1]);
	close(clarg->outfile_fd);
	if (execve(header->path_cmd, header->cmd, envp) == -1)
		cleanup(clarg, EXECVE);
}

/* each cmd executes a child process and a pipe between parent and child is
created every time. as many pipes as cmds

closes every duplicate file descriptor and those that the process
is not going to use
*/
void	pipex(t_clarg *clarg, char **envp)
{
	int		fd[2];
	pid_t	pid;
	t_lcmd	*header;

	header = clarg->cmds_header;
	if (dup2(clarg->infile_fd, STDIN_FILENO) == -1)
		cleanup(clarg, DUP2);
	close(clarg->infile_fd);
	while (header != NULL)
	{
		if (pipe(fd) == -1)
			cleanup(clarg, PIPE);
		pid = fork();
		if (pid == -1)
			cleanup(clarg, FORK);
		if (pid == 0)
			child_process(clarg, header, fd, envp);
		close(fd[1]);
		if (dup2(fd[0], STDIN_FILENO) == -1)
			cleanup(clarg, DUP2);
		if (wait(NULL) == -1)
			cleanup(clarg, WAIT);
		close(fd[0]);
		header = header->next;
	}
}

/* envp is array of pointers where each element is an environment variable.
 PATH variable (executables directories) important envp for us. 
 
 main checks validates args, checks if here_doc feature being used, 
 fills structs and executes pipe*/
int	main(int argc, char **argv, char **envp)
{
	t_clarg	*clarg;

	clarg = NULL;
	if (argc < 5)
		cleanup(clarg, WRNG_ARGS);
	if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) == 0)
	{
		if (argc < 6)
			cleanup(clarg, WRNG_ARGS);
		fill_clarg(argc, argv, envp, &clarg);
		clarg->hd_delim = argv[2];
		clarg->infile_fd = heredoc_to_infile(clarg);
	}
	else
	{
		fill_clarg(argc, argv, envp, &clarg);
		clarg->infile_fd = open(argv[1], O_RDONLY);
		if (clarg->infile_fd == -1)
			cleanup(clarg, INFILE);
	}
	clarg->cmds_header = fill_lcmd(clarg, argc, argv);
	pipex(clarg, envp);
	cleanup(clarg, END);
	return (0);
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