#include "./pipex.h"

/*
1- parsing struct with every command line argument
2- parsing specifically commands
*/

//get path to cmd executable
/*char *	get_cmd_path(t_clarg *clarg, char *cmd)
{
	char	*cmd_path;
    char *partial_path;

    partial_path = ft_strjoin("/", cmd); // "/ls"
    if (partial_path == NULL)
        handle_error(STR_JOIN) //cleanup function missing 
	while (*(clarg->path_all) != NULL)
	{
		free(*cmd_path);
		temp = ft_strjoin(clarg->*(clarg-path_all), "/");
		if (!temp)
			return (-2);
		*full_path = ft_strjoin(temp, cmd);
		free(temp);
		if (!full_path)
			return (-2);
		if (access(*full_path, F_OK) == 0)
			break ;
	}
	if (!data->env_path || !data->env_path[i])
	{
		free(*full_path);
		return (-1);
	}
	return (0);
}*/

/*fills struct t_lcmd for as many cmds as there are*/
/*t_lcmd	*fill_lcmd(t_clarg *clarg, int argc, char **argv)
{
	char	**cmd; // part of t_lcmd struct
	t_lcmd	*cmds;
	int		temp;
    int i;

	cmds = NULL;
    i = 2;
	while (i < argc -1)
	{
		clarg->cmds_header = cmds;
		cmd = ft_split(argv[i], ' '); //starts with argv[2]
		if (cmd == NULL || *cmd == NULL)
			return (handle_error(SPLIT_COMMAND)); //cleanup function missing
		get_cmd_path(clarg, *cmd);
		if (!*cmd || temp == -1)
			return (pipex_exit(data, *cmd, CMD_NOT_FOUND, &cmd));
		if (temp == -2)
			return (pipex_exit(data, NULL, NO_MEMORY, &cmd));
		ft_lstadd_back(&cmds, pipex_lstnew(full_path, cmd));
		free(full_path);
	}
	return (cmds);
}*/


/*fills struct with command line arguments: infile and outfile fds, env_path
*/
t_clarg *fill_clarg(int argc, char **argv, char **envp) 
{
    t_clarg *ptr;

    ptr = malloc(sizeof(struct s_clarg));
    if (ptr == NULL)
        handle_error(MALLOC); // cleanup function missing
    ptr->cmds_header = NULL;
    ptr->infile_fd = open(argv[1], O_RDONLY);
    if (ptr->infile_fd == -1) // can fail because no infile found, or infile has no read permissions
        handle_error(INFILE); // cleanup function missing
    ptr->outfile_fd = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0777);
    if (ptr->outfile_fd == -1)
        handle_error(OUTFILE); // cleanup function missing
    while (*envp && ft_strncmp(*envp, "PATH", 4))
        envp++;
    if (*envp == NULL)
        handle_error(NO_PATH); // cleanup function missing
    ptr->path_all = ft_split(*envp, ':');
    if (ptr->path_all == NULL || *(ptr->path_all) == NULL)
        handle_error(SPLIT); // cleanup function missing
    return (ptr);
}
