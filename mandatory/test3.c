#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

/*size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	length;
	size_t	i;

	length = ft_strlen(src);
	i = 0;
	if (dstsize == 0)
		return (length);
	while (i < dstsize - 1 && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (length);
}


static size_t	ft_count_substrings(const char *s, char c)
{
	size_t	count;
	int		in_substring;

	count = 0;
	in_substring = 0;
	while (*s != '\0')
	{
		if (*s == c)
			in_substring = 0;
		else
		{
			if (in_substring == 0)
			{
				in_substring = 1;
				count++;
			}
		}
		s++;
	}
	return (count);
}

static size_t	ft_count_char(const char *s, char c)
{
	size_t	count;

	count = 0;
	while (s[count] != c && s[count] != '\0')
		count++;
	return (count);
}

static char	**ft_free(char **pointer, size_t substrings)
{
	size_t	i;

	i = 0;
	while (i < substrings)
	{
		free(pointer[i]);
		++i;
	}
	free(pointer);
	return (NULL);
}

char	**ft_split(const char *s, char c)
{
	char	**pointer;
	size_t	substrings;
	size_t	i;
	size_t	substr_length;

	i = 0;
	substr_length = 0;
	substrings = ft_count_substrings(s, c);
	pointer = malloc(sizeof(char *) * (substrings + 1));
	if (pointer == NULL)
		return (NULL);
	while (i < substrings)
	{
		while (*s == c)
			s++;
		substr_length = ft_count_char(s, c);
		pointer[i] = malloc(sizeof(char) * (substr_length + 1));
		if (pointer[i] == NULL)
			return (ft_free(pointer, i));
		ft_strlcpy(pointer[i], s, substr_length + 1);
		s += substr_length;
		i++;
	}
	pointer[i] = NULL;
	return (pointer);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (s1[i] != s2[i] || s1[i] == '\0' || s2[i] == '\0')
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		i++;
	}
	return (0);
}

void	*ft_calloc(size_t count, size_t size)
{
	size_t	blocksize;
	void	*result;
	size_t	i;

	blocksize = count * size;
	result = malloc(blocksize);
	i = 0;
	if (result != NULL)
	{
		while (i < blocksize)
		{
			((unsigned char *)result)[i] = '\0';
			i++;
		}
	}
	return (result);
}

void	*ft_memcpy(void *dest, const void *src, size_t count)
{
	size_t	i;

	i = 0;
	if (src == NULL && dest == NULL)
		return (NULL);
	while (i < count)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dest_length;
	size_t	src_length;

	i = 0;
	dest_length = ft_strlen(dst);
	src_length = ft_strlen(src);
	if (dstsize == 0)
		return (src_length);
	if (dstsize < dest_length)
		return (src_length + dstsize);
	while (dest_length + i < dstsize - 1 && src[i] != '\0')
	{
		dst[dest_length + i] = src[i];
		i++;
	}
	dst[dest_length + i] = '\0';
	return (dest_length + src_length);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	s1_length;
	size_t	s2_length;
	char	*result;

	if (s1 != NULL && s2 != NULL)
	{
		s1_length = ft_strlen(s1);
		s2_length = ft_strlen(s2);
		result = ft_calloc(s1_length + s2_length +1, sizeof(char));
		if (result != NULL)
		{
			ft_memcpy(result, s1, s1_length);
			ft_strlcat(result, s2, s1_length + s2_length + 1);
			return (result);
		}
	}
	return (NULL);
}

int main(int argc, char **argv, char **envp)
{
    //find PATH variable
    while (*envp != NULL && ft_strncmp(*envp, "PATH", 4) != 0)
        envp++;
    printf("%s\n", *envp);
    //split PATH variable
    char **path = ft_split(*envp + 5, ':');
    printf("-----------------------\n");
    char **ptr = path;
    while (*ptr != NULL)
    {
        printf("%s\n", *ptr);
        ptr++;
    }
    printf("-----------------------\n");
    //find full_path to cmd
    char *full_path = NULL;
    char *cmd = ft_strjoin("/", argv[1]);
    printf("%s\n", cmd);
    while (*path != NULL)
    {
        full_path = ft_strjoin(*path, cmd);
        if (access(full_path, X_OK) != -1)
            return (printf("%s\n", full_path));
        path++;
    }

    return 0;
}

int main(int argc, char **argv, char **envp)
{
	int i = 0;
	while (envp && ft_strncmp(*envp, "PATH", 4))
	{
		printf("envp %d is: %s\n", i, *envp);
		i++;
		*envp++;
	}
	return (0);
}*/

/*int main(int argc, char **argv)
{
	int i = 2;
	while (--argc>2)
	{
		printf("argv %d is: %s", i, *argv);
		i++;
	}
	return 0;
}*/