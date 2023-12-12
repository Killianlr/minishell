
#include "../includes/minishell.h"

int		clear_or_exit(char **str)
{
	if (!str)
		return (0);
	if (!ft_strncmp("clear history", str[0], 14))
		rl_clear_history();
    if (!ft_strncmp("exit", str[0], 4) && ft_strlen(str[0]) == 4)
        return (1);
	else
		return (0);
}

int	is_builtins(t_gc *garbage, char **args)
{
	if (!args)
		return (0);
	if (ft_env(garbage, args))
		return (1);
	if (ft_pwd(garbage, args))
		return (1);
	if (ft_export(garbage, args))
		return (1);
	if (ft_unset(garbage, args))
		return (1);
	return (0);
}

t_gc	*in_minishell()
{
	t_gc	*garbage;

	garbage = malloc(sizeof(t_gc));
	if (!garbage)
		return (NULL);
	garbage->blts = set_builtins();
	if (!garbage->blts)
	{
		free(garbage);
		return (NULL);
	}
	while (1)
	{
		garbage->args = NULL;
		garbage->line = ft_prompt();
		if ((int)ft_strlen(garbage->line))
			garbage->args = ft_split(garbage->line, ' ');
		free(garbage->line);
		if (clear_or_exit(garbage->args))
			break ;
		if (is_builtins(garbage, garbage->args))
			break ;
		free_tab(garbage->args);
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
