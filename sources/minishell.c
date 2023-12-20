
#include "../includes/minishell.h"

int		clear_or_exit(char *str)
{
	if (!str)
		return (0);
	if (!ft_strncmp("clear history", str, 14))
		rl_clear_history();
    if (!ft_strncmp("exit", str, 4) && ft_strlen(str) == 4)
        return (1);
	else
		return (0);
}

int	is_builtins(t_gc *garbage)
{
	if (ft_env(garbage))
		return (1);
	if (ft_pwd(garbage))
		return (1);
	if (ft_export(garbage))
		return (1);
	// if (ft_unset(garbage))
	// 	return (1);
	return (0);
}

t_gc	*in_minishell()
{
	t_gc	*garbage;

	garbage = malloc(sizeof(t_gc));
	if (!garbage)
		return (NULL);
	garbage->fd_hdoc = 0;
	garbage->blts = set_builtins();
	if (!garbage->blts)
	{
		free(garbage);
		return (NULL);
	}
	while (1)
	{
		garbage->arg = NULL;
		garbage->line = ft_prompt();
		if (ft_strlen(garbage->line))
		{
			garbage->arg = main_pars(garbage->line, garbage->blts, garbage);
			// if (!garbage->arg)
			// 	break;
		}
		if (clear_or_exit(garbage->line))
			break ;
		//printf("%s\n", garbage->line); // check prompt (A RETIRER)
		free(garbage->line);
		free_parsing(garbage->arg);
	}
	return (garbage);
}

int main(void)
{
	t_gc	*garbage;

	if (clear_terminal())
		return (1);
	if (signal_init())
		return (1);
	garbage = in_minishell();
	free_all(garbage);
	return (0);
}
