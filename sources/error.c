
#include "../includes/minishell.h"

void    ft_cmd_not_find(char **paths, char *cmd, t_gc *garbage, t_exec *ex)
{
    (void) ex;
    write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found\n", 21);
    close_standard_fd();
    free_tab(paths);
    free_all(garbage);
    exit(127);
}

void    exit_child(t_gc *garbage, t_exec *ex)
{
    close_standard_fd();
    if (ex->infile || ex->outfile)
            close_files(ex);
    free_all(garbage);
    exit(1);
}