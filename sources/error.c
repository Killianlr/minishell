
#include "../includes/minishell.h"

void    ft_cmd_not_find(char **paths, char *cmd, t_gc *garbage, t_exec *ex)
{
    write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found\n", 21);
    free_tab(paths);
    close(ex->tube[0]);
    write(ex->tube[1], "42", 4);
    close(ex->tube[1]);
    exit_child(garbage);
}

void    exit_child(t_gc *garbage)
{
    free_all(garbage);
    exit(1);
}