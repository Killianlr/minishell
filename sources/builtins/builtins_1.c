/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:35:41 by kle-rest          #+#    #+#             */
/*   Updated: 2024/01/21 13:50:42 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_define_var(t_gc *garbage, char **args, int pid)
{
	int	i;
	int	val;
	int	e;

	i = 0;
	e = 0;
	if (!garbage->line || !pid)
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

int	ft_unset(t_gc *garbage, char **args)
{
	if (!garbage->line)
		return (0);
	if (!ft_strncmp(args[0], "unset", 6))
	{
		garbage->ret = 0;
		if (!args[1])
			return (2);
		if (del_var_unset(garbage, args))
		{
			garbage->ret = 1;
			return (1);
		}
		return (2);
	}
	return (0);
}

int	ft_export(t_gc *garbage, char **args, int pid)
{
	int	i;

	i = 0;
	if (!ft_strncmp(args[0], "export", 7))
	{
		garbage->ret = 0;
		if (!args[1] && !pid)
		{
			while (garbage->blts->exp[i])
			{
				printf("declare -x %s\n", garbage->blts->exp[i]);
				i++;
			}
			return (2);
		}
		if (update_export(garbage, args, pid))
		{
			garbage->ret = 1;
			return (1);
		}
		return (2);
	}
	return (0);
}

int	ft_env(t_gc *garbage, char **args, int pid)
{
	if (!garbage->line || pid)
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
