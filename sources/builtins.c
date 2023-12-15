/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 11:18:06 by kle-rest          #+#    #+#             */
/*   Updated: 2023/12/14 15:05:33 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_put_ret_value(t_gc *garbage, char **args)
{
	if (!garbage->line)
		return (0);
	if (!ft_strncmp(args[0], "$?", 4))
	{
		ft_putnbr_fd(garbage->ret, STDOUT_FILENO);
		write(STDOUT_FILENO, "\n", 1);
	}
	return (0);
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
		if (!ft_strncmp(args[1], "-n", ft_strlen(args[0])))
			e = 1;
		if (e)
		{
			while (args[i] && !ft_strncmp(args[i], "-n", ft_strlen(args[i])))
				i++;
		}
		while (args[i] && args[i + 1])
		{
			write(STDOUT_FILENO, args[i], ft_strlen(args[i]));
			write(STDOUT_FILENO, " ", 1);
			i++;
		}
		write(STDOUT_FILENO, args[i], ft_strlen(args[i]));
		if (!e)
			write(STDOUT_FILENO, "\n", 1);
	}
	return (0);
}

int	ft_cd(t_gc *garbage, char **args)
{
	if (!garbage->line)
		return (0);
	if (!ft_strncmp(args[0], "cd", 3))
	{
		if (!args[1])
			return (0);
		if (chdir(args[1]))
		{
			printf("minishell: cd: %s: No such file or directory\n", args[1]);
			garbage->ret = 1;
			return (0);
		}
		else
		{
			if (cd_set_pwd(garbage->blts))
				return (1);
		}
	}
	return (0);
}

int	ft_unset(t_gc *garbage, char **args)
{
	if (!garbage->line)
		return (0);
	if (!ft_strncmp(args[0], "unset", 6))
	{
		if (!args[1])
			return (0);
		if (del_var_unset(garbage, args))
			return (1);
	}
	return (0);
}

int	ft_export(t_gc *garbage, char **args)
{
	int		i;

	if (!garbage->line)
		return (0);
	i = 0;
	if (!ft_strncmp(args[0], "export", 7))
	{
		if (!args[1])
		{
			while (garbage->blts->exp[i])
			{
				printf("declare -x %s\n", garbage->blts->exp[i]);
				i++;
			}
			return (0);
		}
		if (update_export(garbage, args))
			return (1);
	}
	return (0);
}

int	ft_env(t_gc *garbage, char **args)
{
	if (!garbage->line)
		return (0);
	if (!ft_strncmp(args[0], "env", 4))
	{
		if (print_env(garbage))
		{
			free_tab(garbage->blts->env);
			free_blts(garbage->blts);
			free(garbage->blts);
			return (1);
		}
	}
	return (0);
}

int	ft_pwd(t_gc *garbage, char **args)
{
	char	*pwd;
	if (!garbage->line)
		return (0);
	if (!ft_strncmp(args[0], "pwd", 4))
	{
		pwd = get_pwd();
		if (!pwd)
			return (1);
		printf("%s\n", pwd);
		free(pwd);
	}
	return (0);
}

t_bui   *set_builtins(void)
{
    t_bui       *blts;
	extern char **environ;

	blts = malloc(sizeof(t_bui));
	if (!blts)
		return (NULL);
	blts->uoldpwd = 0;
	blts->upwd = 0;
	blts->exi_env = 1;
	if (!*environ)
		blts->exi_env = 0;
	if (set_env(blts))
	{
		free(blts);
		return (NULL);
	}
	if (set_export(blts))
	{
		free(blts);
		return (NULL);
	}
	return (blts);
}