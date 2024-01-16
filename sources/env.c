/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 11:18:11 by kle-rest          #+#    #+#             */
/*   Updated: 2024/01/09 14:58:38 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int	set_exi_env(char **environ, t_bui *blts)
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
	return (0);
}

int	set_env_oldpwd(t_bui *blts, int i)
{
	if (!ft_strncmp("OLDPWD", blts->env[i], 6))
	{
		free(blts->env[i]);
		blts->env[i] = ft_strjoin("OLDPWD=", blts->pwd);
		if (!blts->env[i])
			return (1);
	}
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
		if (set_exi_env(environ, blts))
			return (1);
	}
	while (blts->env[i])
	{
		if (set_env_oldpwd(blts, i))
			return (1);
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
