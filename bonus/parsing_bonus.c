/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 09:54:34 by mzuloaga          #+#    #+#             */
/*   Updated: 2024/07/01 10:45:40 by mzuloaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex_bonus.h"

//writes input from here_doc to a newly created infile using get next line
int	heredoc_to_infile(t_clarg *clarg)
{
	int		new_fd;
	char	*line;

	new_fd = open("karaket.txt", O_RDWR | O_CREAT | O_APPEND, 0666);
	if (new_fd == -1)
		cleanup(clarg, INFILE);
	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (line == NULL)
			break ;
		if (ft_strncmp(line, clarg->hd_delim, ft_strlen(clarg->hd_delim))
			== 0 && line[ft_strlen(clarg->hd_delim)] == '\n')
		{
			free(line);
			break ;
		}
		write(new_fd, line, ft_strlen(line));
		free(line);
	}
	close(new_fd);
	new_fd = open("karaket.txt", O_RDONLY);
	if (new_fd == -1)
		perror("new_file");
	return (new_fd);
}

//get path to cmd executable, result to be stored in t_lcmd struct
char	*get_cmd_path(t_clarg *clarg, char *cmd)
{
	char	*path_cmd;
	char	*end;
	char	**path_iter;

	end = ft_strjoin("/", cmd);
	if (end == NULL)
		return (NULL);
	path_iter = clarg->path_all;
	while (*path_iter++ != NULL)
	{
		path_cmd = ft_strjoin(*path_iter, end);
		if (path_cmd == NULL)
		{
			free(end);
			return (NULL);
		}
		if (access(path_cmd, X_OK) == 0)
		{
			free(end);
			return (path_cmd);
		}
		free(path_cmd);
	}
	free(end);
	return (NULL);
}

/*fills struct t_lcmd and adds to linked list for as many cmds as there are
cmd stores cmd + cmd args
cmds is the returning variable, a pointer to head of cmd linked list*/
t_lcmd	*process_command(t_clarg *clarg, char *arg, t_lcmd *cmds)
{
	char	**cmd;
	char	*path_cmd;
	t_lcmd	*new_node;

	if (*arg == '\0')
	{
		free_lcmd_list(cmds);
		perror("Error: null command");
		return (NULL);
	}
	cmd = ft_split(arg, ' ');
	if (cmd == NULL || *cmd == NULL)
		return ((t_lcmd *)cleanup(clarg, SPLIT_COMMAND));
	path_cmd = get_cmd_path(clarg, *cmd);
	if (path_cmd == NULL)
	{
		free_lcmd_list(cmds);
		free_split(&cmd);
		return ((t_lcmd *)cleanup(clarg, NO_CMD_PATH));
	}
	new_node = create_node(path_cmd, cmd);
	if (new_node == NULL)
		return ((t_lcmd *)cleanup(clarg, MALLOC));
	add_node(&cmds, new_node);
	return (cmds);
}

/*router to process_command
cmds is the returning variable, a pointer to the head of the linked list
*/
t_lcmd	*fill_lcmd(t_clarg *clarg, int argc, char **argv)
{
	t_lcmd	*cmds;
	int		i;

	cmds = NULL;
	if (clarg->hd_delim == NULL)
		i = 2;
	else
		i = 3;
	while (i < argc - 1)
	{
		cmds = process_command(clarg, argv[i], cmds);
		if (cmds == NULL)
			return (NULL);
		i++;
	}
	return (cmds);
}

/*fills struct with command line arguments: outfile fd, env_path and 
cmds_header and hd_delimeter initialized to null
infile_fd set to -2 to act as sentinel in case cleanup is called 
(prevents cleanup errors)
*/
void	fill_clarg(int argc, char **argv, char **envp, t_clarg **clarg)
{
	*clarg = malloc(sizeof(struct s_clarg));
	if (*clarg == NULL)
		cleanup(*clarg, MALLOC);
	(*clarg)->cmds_header = NULL;
	(*clarg)->hd_delim = NULL;
	(*clarg)->infile_fd = -2;
	if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])))
		(*clarg)->outfile_fd = open(argv[argc - 1], O_CREAT
			| O_RDWR | O_TRUNC, 0666);
	else
		(*clarg)->outfile_fd = open(argv[argc - 1], O_CREAT
			| O_RDWR | O_APPEND, 0666);	
	if ((*clarg)->outfile_fd == -1)
		cleanup(*clarg, OUTFILE);
	while (*envp && ft_strncmp(*envp, "PATH", 4))
		envp++;
	if (*envp == NULL)
		cleanup(*clarg, NO_PATH);
	(*clarg)->path_all = ft_split(*envp + 5, ':');
	if ((*clarg)->path_all == NULL || *((*clarg)->path_all) == NULL)
		cleanup(*clarg, SPLIT);
}
