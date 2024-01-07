
#include "../includes/minishell.h"

void    ft_cmd_not_find(char **paths, char *cmd, t_gc *garbage, t_exec *ex)
{
    (void) ex;
    write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found\n", 21);
    free_tab(paths);
    free_all(garbage);
    exit(127);
}

void    exit_child(t_gc *garbage)
{
    free_all(garbage);
    exit(1);
}