/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 10:55:00 by mzuloaga          #+#    #+#             */
/*   Updated: 2024/07/01 11:10:58 by mzuloaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex.h"

//get path to cmd executable
char	*get_cmd_path(t_clarg *clarg, char *cmd)
{
	char	*path_cmd;
	cha		*end;
	char	**path_iter;

	end = ft_strjoin("/", cmd);
	if (end == NULL)
		return ((char *)cleanup(clarg, STR_JOIN, NULL));
	path_iter = clarg->path_all;
	while (*path_iter != NULL)
	{
		path_cmd = ft_strjoin(*path_iter, end);
		if (path_cmd == NULL)
			return ((char *)cleanup(clarg, STR_JOIN, end));
		if (access(path_cmd, X_OK) == 0)
		{
			free(end);
			return (path_cmd);
		}
		free(path_cmd);
		path_iter++;
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
	i = 2;
	while (i < argc - 1)
	{
		cmds = process_command(clarg, argv[i], cmds);
		if (cmds == NULL)
			return (NULL);
		i++;
	}
	return (cmds);
}

/*fills struct with command line arguments: infile and outfile fds, env_path
*/
void	fill_clarg(int argc, char **argv, char **envp, t_clarg **clarg)
{
	*clarg = malloc(sizeof(struct s_clarg));
	if (*clarg == NULL)
		cleanup(*clarg, MALLOC, NULL);
	(*clarg)->cmds_header = NULL;
	(*clarg)->infile_fd = open(argv[1], O_RDONLY);
	if ((*clarg)->infile_fd == -1)
		cleanup(*clarg, INFILE, NULL);
	(*clarg)->outfile_fd = open(argv[argc - 1],
			O_CREAT | O_RDWR | O_TRUNC, 0777);
	if ((*clarg)->outfile_fd == -1)
		cleanup(*clarg, OUTFILE, NULL);
	while (*envp && ft_strncmp(*envp, "PATH", 4))
		envp++;
	if (*envp == NULL)
		cleanup(*clarg, NO_PATH, NULL);
	(*clarg)->path_all = ft_split(*envp + 5, ':');
	if ((*clarg)->path_all == NULL || *((*clarg)->path_all) == NULL)
		cleanup(*clarg, SPLIT, NULL);
}