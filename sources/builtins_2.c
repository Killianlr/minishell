/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fserpe <fserpe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 13:50:08 by kle-rest          #+#    #+#             */
/*   Updated: 2024/01/14 15:26:20 by fserpe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_echo_2(t_gc *garbage, char **args)
{
	if (!garbage->line)
		return (0);
	if (!ft_strncmp(args[0], "echo", ft_strlen(args[0])))
	{
		garbage->ret = 0;
		return (2);
	}
	return (0);
}

int	option_echo(char *tiret_n)
{
	int	i;

	i = 0;
	if (!tiret_n[i])
		return (1);
	if (tiret_n[i] != '-')
		return (1);
	i++;
	while (tiret_n[i] && tiret_n[i] == 'n')
		i++;
	if (i == (int)ft_strlen(tiret_n))
		return (0);
	else
		return (1);
}

int	ft_echo(t_gc *garbage, char **args)
{
	int	e;
	int	i;

	e = 0;
	i = 1;
	if (!garbage->line)
		return (0);
	if (!ft_strncmp(args[0], "echo", ft_strlen(args[0])))
	{
		while (args[i] && !option_echo(args[i]))
		{
			i++;
			e = 1;
		}
		i = loop_echo_write(args, i, garbage);
		if (args[i] && !ft_strncmp(args[i], "$?", 4))
			ft_putnbr_fd(garbage->ret, STDOUT_FILENO);
		else
			write(STDOUT_FILENO, args[i], ft_strlen(args[i]));
		if (!e)
			write(STDOUT_FILENO, "\n", 1);
		garbage->ret = 0;
		return (2);
	}
	return (0);
}

int	ft_cd_2(t_gc *garbage, char **args)
{
	if (!ft_strncmp(args[0], "cd", 3))
	{
		garbage->ret = 0;
		if (!args[1])
			return (2);
		if (chdir(args[1]))
		{
			garbage->ret = 1;
			garbage->go = 0;
			return (2);
		}
		else
		{
			if (cd_set_pwd(garbage->blts))
			{
				garbage->ret = 2;
				return (1);
			}
		}
		return (2);
	}
	return (0);
}

int	ft_cd(t_gc *garbage, char **args)
{
	if (!garbage->line)
		return (0);
	if (!ft_strncmp(args[0], "cd", 3))
	{
		garbage->ret = 0;
		if (!args[1])
			return (2);
		if (chdir(args[1]))
		{
			printf("minishell: cd: %s: No such file or directory\n", args[1]);
			garbage->ret = 1;
			garbage->go = 0;
			return (2);
		}
		else
		{
			if (cd_set_pwd(garbage->blts))
			{
				garbage->ret = 2;
				return (1);
			}
		}
		return (2);
	}
	return (0);
}
