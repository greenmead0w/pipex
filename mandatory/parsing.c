#include "./pipex.h"

//get path to cmd executable
char *	get_cmd_path(t_clarg *clarg, char *cmd)
{
	char	*path_cmd;
    char *end;
	char **path_iter;

    end = ft_strjoin("/", cmd); // "/ls"
    if (end == NULL)
		return ((char *)cleanup(clarg, STR_JOIN, NULL)); //cleanup function missing 
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
	return ((char *)cleanup(clarg, NO_CMD_PATH, NULL));
}

/*fills struct t_lcmd for as many cmds as there are*/
t_lcmd	*fill_lcmd(t_clarg *clarg, int argc, char **argv)
{
	char	**cmd; // part of t_lcmd struct, stores command + command args
	t_lcmd	*cmds; //returning variable, pointer to head of command linked list
	t_lcmd *new_node;
	char *path_cmd;
    int i;

	cmds = NULL;
    i = 2;
	while (i < argc -1)
	{
		cmd = ft_split(argv[i], ' '); 
		if (cmd == NULL || *cmd == NULL) //ft_split("",' ') returns pointer to {NULL}, segfault if ft_split(NULL, ' ') (maybe need to modify ft_split for this case)
			return ((t_lcmd *)cleanup(clarg, SPLIT_COMMAND, NULL)); 
		path_cmd = get_cmd_path(clarg, *cmd); // gets full path to executable
		new_node = create_node(path_cmd, cmd);
		if (new_node == NULL)
			return((t_lcmd *)cleanup(clarg, MALLOC, NULL));
		add_node(&cmds, new_node);
		i++; 
	}
	return (cmds);
}


/*fills struct with command line arguments: infile and outfile fds, env_path
*/
void fill_clarg(int argc, char **argv, char **envp, t_clarg **clarg) 
{
    *clarg = malloc(sizeof(struct s_clarg));
    if (*clarg == NULL)
        cleanup(*clarg, MALLOC, NULL); // cleanup function missing
    (*clarg)->cmds_header = NULL;
    (*clarg)->infile_fd = open(argv[1], O_RDONLY);
    if ((*clarg)->infile_fd == -1) // can fail because no infile found, or infile has no read permissions
        cleanup(*clarg, INFILE, NULL); // cleanup function missing
    (*clarg)->outfile_fd = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0777);
    if ((*clarg)->outfile_fd == -1)
        cleanup(*clarg, OUTFILE, NULL); // cleanup function missing
    while (*envp && ft_strncmp(*envp, "PATH", 4))
        envp++;
    if (*envp == NULL)
        cleanup(*clarg, NO_PATH, NULL); // cleanup function missing
    (*clarg)->path_all = ft_split(*envp + 5, ':'); // +5 done not to copy "PATH="
    if ((*clarg)->path_all == NULL || *((*clarg)->path_all) == NULL)
        cleanup(*clarg, SPLIT, NULL); // cleanup function missing
}
