/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 13:42:15 by kle-rest          #+#    #+#             */
/*   Updated: 2024/01/14 11:04:17 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_buitlins_next(t_gc *garbage, char **args)
{
	int	i;

	i = 0;
	i = ft_unset(garbage, args, 0);
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
	if (!args || !garbage->line)
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

int	ft_pwd(t_gc *garbage, char **args)
{
	char	*pwd;

	if (!garbage->line)
		return (0);
	if (!ft_strncmp(args[0], "pwd", 4))
	{
		garbage->ret = 0;
		pwd = get_pwd();
		if (!pwd)
		{
		garbage->ret = 1;
			return (1);
		}
		printf("%s\n", pwd);
		free(pwd);
		return (2);
	}
	return (0);
}
