# include <unistd.h> //write, read, access, dup, dup2, execve, fork, pipe, unlink
#include <sys/wait.h> //wait, waitpid
# include <fcntl.h> //open, close
# include <stdlib.h> // malloc, free 
# include <stdio.h> // perror
#include <errno.h>
#include "./pipex_libft/libft.h"

/*int heredoc_to_infile(char *delimiter)
{
	int new_fd;
	char *line = NULL;

    new_fd = open("karaket.txt", O_RDWR | O_CREAT |O_TRUNC, 0666);
    if (new_fd == -1) 
    {
        perror("new_fd");
        return -1;
    }

while (1) 
{
    line = get_next_line(STDIN_FILENO);
    if (line == NULL)
        break;
    if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0 && line[ft_strlen(delimiter)] == '\n') 
    {
        free(line);
        break;
    }
    write(new_fd, line, ft_strlen(line));
    free(line);
}
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
    return (0);
}*/
