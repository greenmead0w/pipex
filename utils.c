#include "./pipex.h"


t_lcmd *create_node(char *path_cmd, char **cmd)
{
    t_lcmd *new_node = malloc(sizeof(struct s_lcmd));
    if (!new_node)
        return (handle_error(MALLOC)) ; //clean up function missing
    new_node->path_cmd = path_cmd;
    new_node->cmd = cmd;
    new_node->next = NULL;
    return new_node;
}

//adds node to the bottom of the list
void add_node(t_lcmd **lst, t_lcmd *new_node)
{
    t_lcmd *temp;
    
    if (lst == NULL || new_node == NULL)
        return;
    if (*lst == NULL) // no node in the linked list
    {
        *lst = new_node;
        return;
    }
    temp = *lst;
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = new_node;
}