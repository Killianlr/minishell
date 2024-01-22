/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles_env_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 13:53:55 by kle-rest          #+#    #+#             */
/*   Updated: 2024/01/22 18:44:50 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	it_is_an_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	add_var_env(t_bui *blts, char *arg)
{
	int		i;
	char	**new_env;
	int		size_tab;

	i = 0;
	size_tab = ft_strlen_tab(blts->env);
	new_env = malloc(sizeof(char *) * (size_tab + 2));
	if (!new_env)
		return (1);
	while (blts->env[i])
	{
		new_env[i] = blts->env[i];
		i++;
	}
	new_env[i] = remove_quote(arg);
	if (!new_env[i])
		return (1);
	new_env[i + 1] = NULL;
	free(blts->env);
	blts->env = new_env;
	return (0);
}

char	**create_env(char **existing_env)
{
	int		len_tab;
	char	**env;
	int		i;

	len_tab = ft_strlen_tab(existing_env);
	i = 0;
	env = malloc(sizeof(char *) * (len_tab + 1));
	if (!env)
		return (NULL);
	while (existing_env[i])
	{
		env[i] = ft_strdup(existing_env[i]);
		if (!env[i])
			return (NULL);
		i++;
	}
	env[i] = NULL;
	return (env);
}

int	clear_or_exit(char **str)
{
	if (!str || !str[0])
		return (0);
	if (!ft_strncmp("clear", str[0], ft_strlen(str[0])))
	{
		if (str[1])
		{
			if (!ft_strncmp("history", str[1], ft_strlen(str[1])))
				rl_clear_history();
		}
	}
	if (!ft_strncmp("exit", str[0], 4) && ft_strlen(str[0]) == 4)
		return (1);
	else
		return (0);
}

int	is_metac(char c)
{
	if (c == '-')
		return (1);
	if (c == '*')
		return (1);
	if (c == '+')
		return (1);
	if (c == '.')
		return (1);
	if (c == '&')
		return (1);
	if (c == '$')
		return (1);
	if (c == '#')
		return (1);
	if (c == '@')
		return (1);
	if (c == '!')
		return (1);
	return (0);
}
