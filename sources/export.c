/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 11:18:16 by kle-rest          #+#    #+#             */
/*   Updated: 2024/01/14 10:58:31 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	add_val_export_next(t_gc *garbage, char *arg)
{
	char	*tmp;

	if (check_arg_should_be_define(arg))
	{
		tmp = ft_strjoin(arg, "=");
		if (!tmp)
			return (1);
		if (new_var_w_value(garbage->blts, tmp))
			return (1);
		free(tmp);
	}
	else if (it_is_an_equal(arg))
	{
		if (new_var_w_value(garbage->blts, arg))
			return (1);
	}
	else
	{
		if (new_name_var(garbage->blts, arg))
			return (1);
	}
	return (0);
}

int	add_var_export(t_gc *garbage, char *arg)
{
	int		val;

	if (!ft_strncmp("PWD", arg, ft_size_var_env(arg)))
		garbage->blts->upwd = 0;
	if (!ft_strncmp("OLDPWD", arg, ft_size_var_env(arg)))
		garbage->blts->uoldpwd = 0;
	val = check_var_exist(garbage->blts->exp, arg);
	if (!val)
		return (0);
	else if (val <= ft_strlen_tab(garbage->blts->exp))
	{
		if (update_var(garbage->blts, arg, val))
			return (1);
	}
	else
	{
		if (add_val_export_next(garbage, arg))
			return (1);
	}
	garbage->blts->exp = ft_sort_tab(garbage->blts->exp);
	return (0);
}

int	update_export_next(char c, int j, int pid)
{
	if (j > 0)
		return (0);
	if ((!ft_isalpha(c) && c != '=')
		|| (!j && c == '='))
	{
		if (pid)
			printf("minishell: export: `%c': not a valid identifier\n", c);
		return (1);
	}
	if (c == '=')
		return (1);
	return (0);
}

int	update_export(t_gc *garbage, char **args, int pid)
{
	int	i;
	int	j;

	i = 1;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if (update_export_next(args[i][j], j, pid))
			{
				if (!pid)
					exit_free(garbage, 1);
				break ;
			}
			j++;
		}
		if (j == (int)ft_strlen(args[i]) || args[i][j] == '=')
		{
			if (add_var_export(garbage, args[i]))
				return (1);
		}
		i++;
	}
	return (0);
}

int	set_export(t_bui *blts)
{
	blts->exp = ft_sort_tab_n_add_dbq(blts->env);
	if (!blts->exp)
	{
		free_blts(blts);
		return (1);
	}
	return (0);
}
