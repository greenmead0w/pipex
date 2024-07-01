/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 10:58:47 by mzuloaga          #+#    #+#             */
/*   Updated: 2024/07/01 10:59:25 by mzuloaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex.h"

t_lcmd	*create_node(char *path_cmd, char **cmd)
{
	t_lcmd	*new_node;

	new_node = malloc(sizeof(struct s_lcmd));
	if (new_node == NULL)
		return (NULL);
	new_node->path_cmd = path_cmd;
	new_node->cmd = cmd;
	new_node->next = NULL;
	return (new_node);
}

//adds node to the bottom of the list
void	add_node(t_lcmd **lst, t_lcmd *new_node)
{
	t_lcmd	*temp;

	if (lst == NULL || new_node == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new_node;
		return ;
	}
	temp = *lst;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new_node;
}