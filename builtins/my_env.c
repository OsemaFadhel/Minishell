# include "../include/minishell.h"

char *get_env(char *var, char **envp, int n) {
    int i = 0;

    while (envp[i] != NULL) {
        if (n < 0) {
            if (strncmp(envp[i], var, strlen(var)) == 0) {
                // If a match is found, get the substring after the equal sign
                char *value = strchr(envp[i], '=');
                if (value != NULL) {
                    return value + 1; // Return the substring after the equal sign
                }
            }
        } else {
            // If n is non-negative, compare the first n characters
            if (strncmp(envp[i], var, n) == 0) {
                // If a match is found, get the substring after the equal sign
                char *value = strchr(envp[i], '=');
                if (value != NULL) {
                    return value + 1; // Return the substring after the equal sign
                }
            }
        }
        i++;
    }

    // Return NULL if the environment variable is not found
    return NULL;
}

/*int main() {
    char *env[] = {"VAR1=value1", "VAR2=value2", "VAR3=value3", NULL};
    char *result = get_env("VAR2", env, -1);
    if (result != NULL) {
        printf("Environment variable value: %s\n", result);
    } else {
        printf("Environment variable not found\n");
    }
    return 0;
}*/


char **set_env(char *var, char *value, char **envp, int n) {
    if (n < 0) {
        n = strlen(var);
    }

    // Create auxiliary strings by joining the variable name and value with '='
    char *new_entry = malloc(strlen(var) + strlen(value) + 2);
    strcpy(new_entry, var);
    strcat(new_entry, "=");
    strcat(new_entry, value);

    // Count the number of entries in the original environment variable array
    int count = 0;
    while (envp[count] != NULL) {
        count++;
    }

    // Create a new environment variable array with one additional entry
    char **new_envp = malloc((count + 2) * sizeof(char *));
    if (new_envp == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Copy the original environment variable entries to the new array using a while loop
    int i = 0;
    while (i < count) {
        new_envp[i] = strdup(envp[i]);
        if (new_envp[i] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
        i++;
    }

    // Add the new entry to the new environment variable array
    new_envp[count] = new_entry;
    new_envp[count + 1] = NULL;

    return new_envp;
}


/*int main() {
    char *env[] = {"VAR1=Value1", "VAR2=Value2", NULL};
    char **new_env = set_env("VAR3", "Value3", env, -1);
    int i = 0;
    while (new_env[i] != NULL) {
        printf("%s\n", new_env[i]);
        i++;
    }
    i = 0;
    while (new_env[i] != NULL) {
        free(new_env[i]);
        i++;
    }
    free(new_env);

    return 0;
}*/