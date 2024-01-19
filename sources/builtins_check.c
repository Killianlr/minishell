/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fserpe <fserpe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:34:41 by kle-rest          #+#    #+#             */
/*   Updated: 2024/01/19 17:36:30 by fserpe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_buitlins_next(t_gc *garbage, char **args, int pid)
{
	int	i;

	i = 0;
	i = ft_unset(garbage, args, pid);
	if (i == 1)
		exit_free(garbage, 1);
	else if (i == 2)
		return (2);
	i = ft_cd(garbage, args, pid);
	if (i == 1)
		exit_free(garbage, 1);
	else if (i == 2)
		return (2);
	i = ft_echo(garbage, args, pid);
	if (i == 1)
		exit_free(garbage, 1);
	else if (i == 2)
		return (2);
	i = ft_define_var(garbage, args, pid);
	if (i == 1)
		exit_free(garbage, 1);
	else if (i == 2)
		return (2);
	return (0);
}

int	is_builtins(t_gc *garbage, char **args, int pid)
{
	int			i;
	extern int	g_signal;

	i = 0;
	if (!args || !garbage->line)
		return (0);
	if (g_signal)
		garbage->ret = g_signal;
	i = ft_env(garbage, args, pid);
	if (i == 1)
		exit_free(garbage, 1);
	else if (i == 2)
		return (2);
	i = ft_pwd(garbage, args, pid);
	if (i == 1)
		exit_free(garbage, 1);
	else if (i == 2)
		return (2);
	i = ft_export(garbage, args, pid);
	if (i == 1)
		exit_free(garbage, 1);
	else if (i == 2)
		return (2);
	return (is_buitlins_next(garbage, args, pid));
}

void	ft_exit(t_gc *garbage, char **args)
{
	int	i;

	i = 0;
	if (!args[1])
		exit_free(garbage, 0);
	if (args[2])
	{
		printf("exit\n");
		printf("minishell: exit: too many arguments\n");
		exit_free(garbage, 1);
	}
	while (args[1][i])
	{
		if (args[1][i] == '-')
			i++;
		if (!ft_isdigit(args[1][i]))
		{
			printf("exit\n");
			printf("minishell: exit: %s: numeric argument required\n", args[1]);
			exit_free(garbage, 2);
		}
		i++;
	}
	exit_free(garbage, atoi(args[1]));
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	return (s1[i] - s2[i]);
}
