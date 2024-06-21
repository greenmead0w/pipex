#include "./pipex.h"

/*
1- parsing struct with every command line argument
2- parsing specifically commands
*/



//get path to cmd executable
char *	get_cmd_path(t_clarg *clarg, char *cmd)
{
	char	*path_cmd;
    char *end;
	char **path_iter;

    end = ft_strjoin("/", cmd); // "/ls"
	printf("end is: %s\n", end);
    if (end == NULL)
		handle_error(STR_JOIN); //cleanup function missing 
	path_iter = clarg->path_all;
	printf("path_all is: %p\n", clarg->path_all);
	printf("path_iter is: %p\n", path_iter);
	while (*path_iter != NULL)
	{
		path_cmd = ft_strjoin(*path_iter, end);
		printf("path_cmd is: %s\n", path_cmd);
		if (path_cmd == NULL)
		{
			free(end);
			handle_error(STR_JOIN); //cleanup function missing
		}
		if (access(path_cmd, X_OK) == 0)
		{
			printf("found!\n");
			free(end);
			return (path_cmd);
		}
		free(path_cmd);
		path_iter++;
	}
	free(end);
	return (handle_error(NO_CMD_PATH)); //cleanup function missing
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
			return (handle_error(SPLIT_COMMAND)); //cleanup function missing
		path_cmd = get_cmd_path(clarg, *cmd); // gets full path to executable
		//if path_cmd == null
			//
		new_node = create_node(path_cmd, cmd);
		//if new_node == null
			//
		add_node(&cmds, new_node);
		i++; 
	}
	return (cmds);
}


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
    ptr->path_all = ft_split(*envp + 5, ':'); // +5 done not to copy "PATH="
    if (ptr->path_all == NULL || *(ptr->path_all) == NULL)
        handle_error(SPLIT); // cleanup function missing
    return (ptr);
}
