/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 11:18:11 by kle-rest          #+#    #+#             */
/*   Updated: 2024/01/03 13:18:02 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int	set_unexist_env(t_bui *blts)
{
	blts->env = malloc(sizeof(char *) * 3);
	if (!blts->env)
		return (1);
	blts->pwd = get_pwd();
	if (!blts->pwd)
	{
		free(blts->env);
		return (1);
	}
	blts->env[0] = ft_strjoin_fs2("PWD=", get_pwd());
	if (!blts->env[0])
	{
		free_blts(blts);
		return (1);
	}
	blts->env[1] = ft_strdup("SHLVL=1");
	if (!blts->env[1])
	{
		free(blts->env[0]);
		free_blts(blts);
		return (1);
	}
	blts->env[2] = NULL;
	return (0);
}

int	set_env(t_bui *blts)
{
	extern char	**environ;
	int			i;

	i = 0;
	if (!blts->exi_env)
	{
		if (set_unexist_env(blts))
			return (1);
	}
	else
	{
		blts->env = create_env(environ);
		if (!blts->env)
			return (1);
		blts->pwd = get_pwd();
		if (!blts->pwd)
		{
			free(blts->env);
			return (1);
		}
	}
	while (blts->env[i])
	{
		if (!ft_strncmp("OLDPWD", blts->env[i], 6))
		{
			free(blts->env[i]);
			blts->env[i] = ft_strjoin("OLDPWD=", blts->pwd);
			if (!blts->env[i])
				return (1);
		}
		i++;
	}
	return (0);
}

int	update_var_env(t_bui *blts, char *str)
{
	int	i;

	i = check_var_exist(blts->env, str);
	if (i > ft_strlen_tab(blts->env))
	{
		if (add_var_env(blts, str))
			return (1);
	}
	else
	{
		free(blts->env[i]);
		blts->env[i] = remove_quote(str);
		if (!blts->env[i])
			return (1);
	}
	return (0);
}
