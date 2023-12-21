/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 11:18:11 by kle-rest          #+#    #+#             */
/*   Updated: 2023/12/15 14:23:23 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*remove_quote(char *str)
{
	int		i;
	int		q;
	char	*dest;

	i = 0;
	q = 0;
	while (str[i])
	{
		if (str[i] == '"')
			q++;
		i++;
	}
	dest = malloc(sizeof(char) * (ft_strlen(str) - q + 1));
	if (!dest)
		return (NULL);
	i = 0;
	q = 0;
	while (str[i + q])
	{
		while (str[i + q] == '"')
			q++;
		if (!str[i + q])
			break ;
		dest[i] = str[i + q];
		i++;
	}
	dest[i] = 0;
	return (dest);
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

int	update_env(t_bui *blts)
{
	int		i;
	int		e;
	char	*oldpwd;

	i = 0;
	e = 0;
	oldpwd = NULL;
	while (blts->env[i])
	{
		if (!ft_strncmp("PWD", blts->env[i], ft_size_var_env(blts->env[i])))
		{
			oldpwd = ft_strdup(blts->env[i] + 4);
			free(blts->env[i]);
			free(blts->pwd);
			blts->pwd = get_pwd();
			if (!blts->pwd)
				return (1);
			blts->env[i] = ft_strjoin("PWD=", blts->pwd);
			if (!blts->env[i])
				return (1);
			printf("set PWD : %s\n", blts->env[i]);
		}
		i++;
	}
	if (!oldpwd)
	{
		go_to_find_var_and_del(blts, "OLDPWD");
		e = 1;
	}
	if (blts->uoldpwd)
		free(oldpwd);
	i = 0;
	while (blts->env[i] && !e)
	{
		if (!ft_strncmp("OLDPWD", blts->env[i], 6))
		{
			free(blts->env[i]);
			blts->env[i] = ft_strjoin_fs2("OLDPWD=", oldpwd);
			if (!blts->env[i])
				return (1);
		}
		i++;
	}
	return (0);
}

int	print_env(t_gc *garbage)
{
	int	i;

	i = 0;
	while (garbage->blts->env[i])
	{
		printf("%s\n", garbage->blts->env[i]);
		i++;
	}
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
