# include "../include/minishell.h"

void print_error(const char *msg) {
    fprintf(stderr, "Error: %s\n", msg);
}

int my_exit(t_list *ncd, int *n) {
    // Extract the build information from the linked list node
    t_mini *node = (t_mini *)ncd->content;
    
    // Check if the command is an exit command (no arguments)
    *n = !ncd->next;
    
    // Print "exit" if it's an exit command
    if (*n) {
        printf("exit\n");
    }
    
    // Check if there are no arguments
    if (!node->toks || !node->toks[1]) {
        return 0;
    }
    
    // Declare an array to store the exit status and parse the argument
    long status[2];
    status[1] = atoi(node->toks[1]);
    
    // Check for invalid numeric argument
    if (status[1] == 0 && node->toks[1][0] != '0') {
        print_error("Numeric argument required");
        return 255;
    } else if (node->toks[2]) {
        // Check for too many arguments
        *n = 0;
        print_error("Too many arguments for exit");
        return 1;
    }

    // Ensure the exit status wraps around modulo 256
    status[0] %= 256 + 256 * (status[0] < 0);
    
    // Return the exit status
    return (int)status[0];
}

/*int main(void)
{
    t_build sample_build = {
        .full_cmd = (char *[]){"exit", "42", NULL},
        .full_path = "/bin/exit",
        .infile = 0,
        .outfile = 1
    };

    t_list *sample_node = malloc(sizeof(t_list));
    sample_node->next = NULL;
    sample_node->content = &sample_build;

    int n = 0;
    int exit_status = mini_exit(sample_node, &n);

    if (n)
    {
        printf("Exit command detected.\n");
        printf("Exit status: %d\n", exit_status);
    }
    else
    {
        printf("Not an exit command.\n");
    }

    free(sample_node);

    return 0;
}*/