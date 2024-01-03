/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 11:18:06 by kle-rest          #+#    #+#             */
/*   Updated: 2023/12/21 18:25:30 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_define_var(t_gc *garbage, char **args)
{
	int	i;
	int	val;
	int	e;

	i = 0;
	e = 0;
	if (!garbage->line)
		return (0);
	while (args[i] && it_is_an_equal(args[i]))
	{
		val = check_var_exist(garbage->blts->exp, args[i]);
		if (val <= ft_strlen_tab(garbage->blts->exp))
		{
			if (update_var(garbage->blts, args[i], val))
				return (1);
		}
		i++;
		e++;
	}
	if (e > 0)
		return (2);
	return (0);
}

int	ft_put_ret_value(t_gc *garbage, char **args)
{
	int		pid;
	char	**paths;
	char	*cmd_tab[2];
	char	*cmd;

	if (!garbage->line)
		return (0);
	if (!ft_strncmp(args[0], "$?", 4))
	{
		pid = fork();
		if (pid == -1)
			return (1);
		if (pid == 0)
		{
			cmd_tab[0] = ft_itoa(garbage->ret);
			cmd_tab[1] = NULL;
			paths = ft_split(find_path(garbage->blts->env), ':');
			cmd = get_cmd(paths, cmd_tab, garbage->blts->env);
			if (!cmd)
			{
				write(2, ": command not found\n", 21);
				write(2, cmd_tab[0], ft_strlen(cmd_tab[0]));
				write(2, "\n", 1);
				free_tab(paths);
				garbage->ret = 127;
				exit(0);
			}
			execve(cmd, cmd_tab, garbage->blts->env);
		}
		return (2);
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
			if (!ft_strncmp(args[i], "$?", 4))
				ft_putnbr_fd(garbage->ret, STDOUT_FILENO);
			else
			{
				write(STDOUT_FILENO, args[i], ft_strlen(args[i]));
				write(STDOUT_FILENO, " ", 1);
				i++;
			}
		}
		if (!ft_strncmp(args[i], "$?", 4))
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
			return (0);
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

int	ft_unset(t_gc *garbage, char **args)
{
	if (!garbage->line)
		return (0);
	if (!ft_strncmp(args[0], "unset", 6))
	{
		garbage->ret = 0;
		if (!args[1])
			return (0);
		if (del_var_unset(garbage, args))
		{
			garbage->ret = 1;
			return (1);
		}
		return (2);
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
		garbage->ret = 0;
		if (!args[1])
		{
			while (garbage->blts->exp[i])
			{
				printf("declare -x %s\n", garbage->blts->exp[i]);
				i++;
			}
			return (2);
		}
		if (update_export(garbage, args))
		{
			garbage->ret = 1;
			return (1);
		}
		return (2);
	}
	return (0);
}

int	ft_env(t_gc *garbage, char **args)
{
	if (!garbage->line)
		return (0);
	if (!ft_strncmp(args[0], "env", 4))
	{
		garbage->ret = 0;
		if (print_env(garbage))
		{
			free_tab(garbage->blts->env);
			free_blts(garbage->blts);
			free(garbage->blts);
			garbage->ret = 1;
			return (1);
		}
		return (2);
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

t_bui	*set_builtins(void)
{
	t_bui		*blts;
	extern char	**environ;

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
