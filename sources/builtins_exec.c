
#include "../includes/minishell.h"

int	is_buitlins_next(t_gc *garbage, char **args)
{
	int	i;

	i = 0;
	i = ft_unset(garbage, args);
	if (i == 1)
		exit_error(garbage);
	else if (i == 2)
		return (2);
	i = ft_cd(garbage, args);
	if (i == 1)
		exit_error(garbage);
	else if (i == 2)
		return (2);
	i = ft_echo(garbage, args);
	if (i == 1)
		exit_error(garbage);
	else if (i == 2)
		return (2);
	i = ft_define_var(garbage, args);
	if (i == 1)
		exit_error(garbage);
	else if (i == 2)
		return (2);
	return (0);
}

int	is_builtins(t_gc *garbage, char **args)
{
	int	i;

	i = 0;
	if (!args)
		return (0);
	i = ft_env(garbage, args);
	if (i == 1)
		exit_error(garbage);
	else if (i == 2)
		return (2);
	i = ft_pwd(garbage, args);
	if (i == 1)
		exit_error(garbage);
	else if (i == 2)
		return (2);
	i = ft_export(garbage, args, 0);
	if (i == 1)
		exit_error(garbage);
	else if (i == 2)
		return (2);
	return (is_buitlins_next(garbage, args));
}