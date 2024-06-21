 
#include "./pipex.h"
 /* 
 1- print errors function
 2 - clean up function
 3- free_array function (ft_split)
 4- free linked list
 */

/*if errno is not set, it prints "success" after custom message, 
because of that adding else condition*/
void *handle_error(const char *message) {
    if (errno != 0) {
        perror(message);
    } else { // errno is not set (for cases where PATH variable has not been found, for example)
        // Call write or ft_printf to stdrerror
        write(2, message, ft_strlen(message));
        write(2, "\n", 1);
    }
    exit(EXIT_FAILURE); //same as exit(1)?
}

//frees **
void free_cmd_array(char **cmd) 
{
    int i; 

    i = 0;
    if (cmd != NULL) 
    {
        while (cmd[i] != NULL)
        {
            free(cmd[i]);
            i++;           
        }
        free(cmd);
    }
}

//frees linked list
void free_lcmd_list(t_lcmd *head) 
{
    t_lcmd *temp;
    while (head != NULL) 
    {
        temp = head;
        head = head->next;
        free_cmd_array(temp->cmd);
        free(temp->path_cmd);
        free(temp);
    }
}

//calls handle error at the end
//cleanup()

