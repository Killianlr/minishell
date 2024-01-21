/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:20:01 by kle-rest          #+#    #+#             */
/*   Updated: 2024/01/21 13:53:51 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	char	*var_name;

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

char	**ft_sort_tab(char **tabl)
{
	int	i;

	i = 0;
	while (i < ft_strlen_tab(tabl) - 1)
	{
		if (ft_strcmp(tabl[i], tabl[i + 1]) > 0)
		{
			ft_swap(&tabl[i], &tabl[i + 1]);
			i = 0;
		}
		i++;
	}
	return (tabl);
}

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
