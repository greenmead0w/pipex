/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 10:50:29 by mzuloaga          #+#    #+#             */
/*   Updated: 2024/07/01 10:54:51 by mzuloaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex.h"

/*if errno is not set, it prints "success" after custom message, 
because of that adding else condition*/
void	*handle_error(const char *message)
{
	if (errno != 0)
		perror(message);
	else
	{
		write(2, message, ft_strlen(message));
		write(2, "\n", 1);
	}
	exit(1);
}

/*
char *** because you want to free every string in array, 
free the pointer to the array (cmd)
and set it to NULL to avoid it becoming a dangling pointer 
(a pointer that points to memory
that no longer exists because it has been freed).
*** because you pass by reference
*/
void	free_split(char ***cmd)
{
	int	i;

	i = 0;
	if (cmd == NULL || *cmd == NULL)
		return ;
	while ((*cmd)[i] != NULL)
	{
		free((*cmd)[i]);
		i++;
	}
	free(*cmd);
	*cmd = NULL;
}

//frees linked list
void	free_lcmd_list(t_lcmd *head)
{
	t_lcmd	*temp;

	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free_split(&(temp->cmd));
		free(temp->path_cmd);
		free(temp);
	}
}

//flag only non-null when ft_strjoin returns null
void	*cleanup(t_clarg *clarg, char *message)
{
	
	if (clarg != NULL)
	{
		close(clarg->infile_fd);
		close(clarg->outfile_fd);
		free_split(&(clarg->path_all));
		if (clarg->cmds_header != NULL)
			free_lcmd_list(clarg->cmds_header);
		free(clarg);
	}
	if (ft_strncmp(message, END, ft_strlen(message)) != 0)
		handle_error(message);
	return (0);
}