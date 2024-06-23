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

int main(int argc, char **argv) 
{
    const char *string = " ";
    char **result = ft_split(string, ' ');
    while (*result != NULL)
    {
        printf("result is: %s\n", *result);
        result++;
    }
    printf("result is: %s\n", *result);
    return (0);
}*/
