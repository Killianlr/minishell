/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 11:18:16 by kle-rest          #+#    #+#             */
/*   Updated: 2023/12/14 14:48:49 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	replace_old_exp(t_bui *blts, char *arg_w_db_q)
{
	int		i;
	char	**new_export;
	int		size_tab;

	i = 0;
	if (!arg_w_db_q)
		return (1);
	size_tab = ft_strlen_tab(blts->exp);
	new_export = malloc(sizeof(char *) * (size_tab + 2));
	if (!new_export)
		return (1);
	while (blts->exp[i])
	{
		new_export[i] = blts->exp[i];
		i++;
	}
	new_export[i] = arg_w_db_q;
	new_export[i + 1] = NULL;
	free(blts->exp);
	blts->exp = new_export;
	return (0);
}

int	new_var_w_value(t_bui *blts, char *arg)
{
	char	*var_w_db_q;

	var_w_db_q = add_db_quote(arg);
	if (add_var_env(blts, var_w_db_q))
		return (1);
	if (replace_old_exp(blts, var_w_db_q))
		return (1);
	return (0);
}

int	new_name_var(t_bui *blts, char *arg)
{
	char *var_name;

	printf("arg = %s\n", arg);
	var_name = ft_strdup(arg);
	if (replace_old_exp(blts, var_name))
		return (1);
	return (0);
}

int	check_arg_should_be_define(char *arg)
{
	if (!ft_strncmp(arg, "PWD", ft_strlen(arg)))
		return (1);
	if (!ft_strncmp(arg, "OLDPWD", ft_strlen(arg)))
		return (1);
	return (0);
}

int	add_var_export(t_gc *garbage, char *arg)
{
	int		val;
	char	*tmp;

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
		if (check_arg_should_be_define(arg))
		{
			printf("ici\n");
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
	}
	garbage->blts->exp = ft_sort_tab(garbage->blts->exp);
	return (0);
}

int	update_export(t_gc *garbage, char **args)
{
	int	i;
	int	j;

	i = 1;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if ((!ft_isalpha(args[i][j]) && args[i][j] != '=')
				|| (!j && args[i][j] == '='))
			{
				printf("minishell: export: `%c': not a valid identifier\n", args[i][j]);
				break ;
			}
			if (args[i][j] == '=')
				break ;
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