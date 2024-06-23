#include "./pipex.h"

//writes input from here_doc to a newly created infile using get next line
int heredoc_to_infile(t_clarg *clarg)
{
	int new_fd;
	char *line;

    new_fd = open("infile.txt", O_RDWR | O_CREAT, 0666);
	if (new_fd == -1)
		cleanup(clarg, HD_INFILE, NULL);
    while (1) 
	{
		line = get_next_line(STDIN_FILENO);
		if (line == NULL)
			break;
        if (ft_strncmp(line, clarg->hd_delimeter, ft_strlen(clarg->hd_delimeter)) == 0)
		{
			free(line);
			break;
		}
		write(new_fd, line, ft_strlen(line));
		free(line);
    }
	close(new_fd);
    new_fd = open("infile.txt", O_RDONLY);
	if (new_fd == -1)
		cleanup(clarg, HD_INFILE, NULL);
	return new_fd;
}

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
    if (clarg->hd_delimeter == NULL) //bonus
		i = 2; //bonus
	else //bonus
		i = 3; //bonus
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


/*fills struct with command line arguments: outfile fd, env_path and 
nulls cmds_header and hd_delimeter
infile_fd set to -2 to act as sentinel in case cleanup is called (prevents cleanup 
errors)
*/
void fill_clarg(int argc, char **argv, char **envp, t_clarg **clarg) 
{
    *clarg = malloc(sizeof(struct s_clarg));
    if (*clarg == NULL)
        cleanup(*clarg, MALLOC, NULL);
    (*clarg)->cmds_header = NULL;
	(*clarg)->hd_delimeter = NULL; //bonus
	(*clarg)->infile_fd = -2; //bonus, sentinel value
    (*clarg)->outfile_fd = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0666); //WHY APPEND?
    if ((*clarg)->outfile_fd == -1)
        cleanup(*clarg, OUTFILE, NULL);
    while (*envp && ft_strncmp(*envp, "PATH", 4))
        envp++;
    if (*envp == NULL)
        cleanup(*clarg, NO_PATH, NULL);
    (*clarg)->path_all = ft_split(*envp + 5, ':'); // +5 done not to copy "PATH="
    if ((*clarg)->path_all == NULL || *((*clarg)->path_all) == NULL)
        cleanup(*clarg, SPLIT, NULL);
}
