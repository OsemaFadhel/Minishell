#include "../include/minishell.h"

int is_valid_identifier_char(char c)
{
    return (c == '_' || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'));
}

// Function to check if a string is a valid identifier
int is_valid_identifier2(const char *str)
{
    if (!str || !is_valid_identifier_char(str[0]))
        return 0;

    for (int i = 1; str[i] != '\0'; i++)
    {
        if (!is_valid_identifier_char(str[i]) && str[i] != '=')
            return 0;
    }

    return 1;
}

// Function to set or update an environment variable
void env_set_env(t_mini *mini, const char *name, const char *value)
{
    char **env = mini->env;

    // Iterate through the environment variables
    for (int i = 0; env[i] != NULL; i++)
    {
        // Check if the variable matches the given name
        if (ft_strncmp(env[i], name, ft_strlen(name)) == 0 && env[i][ft_strlen(name)] == '=')
        {
            // Update the existing variable
            free(env[i]);
            char *new_var = ft_strjoin(name, "=");
            env[i] = ft_strjoin(new_var, value);
            free(new_var);
            return;
        }
    }

    // If the variable doesn't exist, add a new one
    char *new_var = ft_strjoin(name, "=");
    char *new_entry = ft_strjoin(new_var, value);
    free(new_var);

    // Count the number of existing environment variables
    int env_count = 0;
    while (env[env_count] != NULL)
        env_count++;

    // Allocate memory for the new environment
    char **new_env = (char **)malloc((env_count + 2) * sizeof(char *));

    // Copy the existing environment variables
    for (int i = 0; i < env_count; i++)
        new_env[i] = ft_strdup(env[i]);

    // Add the new variable
    new_env[env_count] = ft_strdup(new_entry);
    new_env[env_count + 1] = NULL;

    // Free the old environment and update the global variable
    ft_free_array(env);
    mini->env = new_env;

    free(new_entry);
}

// Function to get the value of an environment variable
char *env_get_value(t_mini *mini, const char *name)
{
    char **env = mini->env;

    // Iterate through the environment variables
    for (int i = 0; env[i] != NULL; i++)
    {
        // Check if the variable matches the given name
        if (ft_strncmp(env[i], name, ft_strlen(name)) == 0 && env[i][ft_strlen(name)] == '=')
        {
            // Return the value of the variable
            return ft_strdup(env[i] + ft_strlen(name) + 1);
        }
    }

    // Return NULL if the variable is not found
    return NULL;
}

// Function to print environment variables
static void add_env_var(t_mini *mini, const char *name, const char *value)
{
    char *new_entry;

    if (value)
        new_entry = ft_strjoin(ft_strjoin(name, "="), value);
    else
        new_entry = ft_strjoin(name, "=");

    if (!new_entry)
    {
        perror("ft_strjoin");
        exit(EXIT_FAILURE);
    }

    mini->env = ft_add_str_to_array(mini->env, new_entry);
    free(new_entry);
}

// Function to print environment variables in alphabetical order
void print_vars_sorted(char **envp)
{
    int i, j;
    int count = 0;
    char **tmp = envp;

    // Count the number of environment variables
    while (tmp[count] != NULL)
        count++;

    // Sort the environment variables in alphabetical order
    for (i = 0; i < count - 1; i++)
    {
        for (j = i + 1; j < count; j++)
        {
            if (ft_strcmp(tmp[i], tmp[j]) > 0)
            {
                // Swap tmp[i] and tmp[j]
                char *temp = tmp[i];
                tmp[i] = tmp[j];
                tmp[j] = temp;
            }
        }
    }

    // Print the sorted environment variables
    for (i = 0; i < count; i++)
    {
        ft_putstr_fd("declare -x ", 1);
        int j = 0;
        while (tmp[i][j] != '\0' && tmp[i][j] != '=')
            ft_putchar_fd(tmp[i][j++], 1);

        if (tmp[i][j] == '=')
        {
            if (tmp[i][j + 1] != '\0')
                ft_putstr_fd("=\"", 1);

            j++;
            while (tmp[i][j] != '\0')
                ft_putchar_fd(tmp[i][j++], 1);

            ft_putstr_fd("\"\n", 1);
        }
        else
        {
            ft_putchar_fd('\n', 1);
        }
    }
}

char **ft_add_str_to_array(char **array, const char *str)
{
    int size = 0;
    char **new_array;

    // Count the number of elements in the existing array
    while (array[size] != NULL)
        size++;

    // Allocate memory for the new array
    new_array = (char **)malloc((size + 2) * sizeof(char *));
    if (!new_array)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    // Copy existing elements to the new array
    for (int i = 0; i < size; i++)
    {
        new_array[i] = array[i];
    }

    // Add the new string to the end of the new array
    new_array[size] = strdup(str);
    if (!new_array[size])
    {
        perror("strdup");
        exit(EXIT_FAILURE);
    }

    // Set the last element of the new array to NULL
    new_array[size + 1] = NULL;

    return new_array;
}

// Main export function
int ft_export(t_mini *mini, t_cmds *current_cmd)
{
    int i = 1;

    if (current_cmd->args[i] == NULL)
    {
        // If no arguments are provided, print all environment variables in alphabetical order
        print_vars_sorted(mini->env);
        return 0;
    }

    while (current_cmd->args[i])
    {
        if (!is_valid_identifier2(current_cmd->args[i]))
        {
            ft_putstr_fd("minishell: export: `", STDERR_FILENO);
            ft_putstr_fd(current_cmd->args[i], STDERR_FILENO);
            ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
            g_exit_status = 1;
        }
        else if (ft_strchr(current_cmd->args[i], '='))
        {
            char *var = ft_substr(current_cmd->args[i], 0, ft_strchr(current_cmd->args[i], '=') - current_cmd->args[i]);
            char *value = ft_strchr(current_cmd->args[i], '=') + 1;
            env_set_env(mini, var, value);
            free(var);
        }
        else
        {
            // For export without '=' (e.g., export VAR), set the variable to an empty string
            char *value = env_get_value(mini, current_cmd->args[i]);
            add_env_var(mini, current_cmd->args[i], value);
        }

        i++;
    }

    return 0;
}