/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 11:19:17 by kle-rest          #+#    #+#             */
/*   Updated: 2023/12/14 13:03:02 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	find_var_in_tab_and_del(char **tabl, char *str)
{
	int	i;
	int	j;
	int	len1;
	int	len2;

	i = 0;
	j = 0;
	while (tabl[j])
	{
		len1 = ft_size_var_env(str);
		len2 = ft_size_var_env(tabl[i]);
		if ((len1 - len2) == 0)
		{
			if (!ft_strncmp(str, tabl[i], len1))
			{
				j++;
				free(tabl[i]);
			}
		}
		if (!tabl[j])
			break;
		tabl[i] = tabl[j];
		i++;
		j++;
	}
	tabl[i] = 0;
	return (0);
}

int	go_to_find_var_and_del(t_bui *blts, char *str)
{
	int	val;

	val = check_var_exist(blts->exp, str);
	if (!ft_strncmp("PWD", str, 3))
		blts->upwd = 1;
	if (!ft_strncmp("OLDPWD", str, 6))
		blts->uoldpwd = 1;
	if (val > ft_strlen_tab(blts->exp))
		return (0);
	else
	{
		find_var_in_tab_and_del(blts->exp, str);
		find_var_in_tab_and_del(blts->env, str);
	}
	return (0);
}

int del_var_unset(t_gc *garbage, char **args)
{
	int i;
	int	j;
	int	e;

	i = 1;
	while (args[i])
	{
		j = 0;
		e = 0;
		while (args[i][j])
		{
			if (!ft_isalpha(args[i][j]))
			{
				printf("minishell: unset: `%s': not a valid identifier\n", args[i]);
				e = 1;
				break ;
			}
			j++;
		}
		if (!e)
			go_to_find_var_and_del(garbage->blts, args[i]);
		i++;
	}
	return (0);
}