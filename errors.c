 
#include "./pipex.h"
 /* 
 1- print errors function
 2 - clean up function
 */

/*if errno is not set, it prints "success" after custom message, 
because of that adding else condition*/
void handle_error(const char *message) {
    if (errno != 0) {
        perror(message);
    } else { // errno is not set (for cases where PATH variable has not been found, for example)
        // Call write or ft_printf to stdrerror
        write(2, message, ft_strlen(message));
        write(2, "\n", 1);
    }
    exit(EXIT_FAILURE); //same as exit(1)?
}

//calls handle error at the end
//cleanup()

