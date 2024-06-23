# include <unistd.h> //write, read, access, dup, dup2, execve, fork, pipe, unlink
#include <sys/wait.h> //wait, waitpid
# include <fcntl.h> //open, close
# include <stdlib.h> // malloc, free 
# include <stdio.h> // perror
#include <errno.h>
#include "./pipex_libft/libft.h"


int heredoc_to_infile(char *delimeter)
{
	int new_fd;
	char *line;

    new_fd = open("karaket.txt", O_RDWR | O_CREAT, 0666);
	if (new_fd == -1)
		perror("new_fd");
    while (1) 
	{
		line = get_next_line(STDIN_FILENO);
        if (line == NULL) // Check if line is NULL (end-of-file or error)
            break;
        if (ft_strncmp(line, delimeter, ft_strlen(delimeter)) == 0)
		{
			free(line);
			break;
		}
		write(new_fd, line, ft_strlen(line));
		free(line);
    }
    free(line);
	close(new_fd);
    new_fd = open("karaket.txt", O_RDONLY);
    if (new_fd == -1)
        perror("new_file");
    return new_fd;
}

int main(int argc, char **argv)
{
    int something = argc;
    int fd = heredoc_to_infile(argv[2]);
    printf("fd is: %d\n", fd);
    printf("somethis is: %d\n", something);
    return (0);
}