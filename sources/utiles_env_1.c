/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 13:53:35 by kle-rest          #+#    #+#             */
/*   Updated: 2024/01/09 14:57:03 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	remove_quote_next(char *str)
{
	int	i;
	int	q;

	i = 0;
	q = 0;
	while (str[i])
	{
		if (str[i] == '"')
			q++;
		i++;
	}
	return (q);
}

char	*remove_quote(char *str)
{
	int		i;
	int		q;
	char	*dest;

	i = 0;
	q = remove_quote_next(str);
	dest = malloc(sizeof(char) * (ft_strlen(str) - q + 1));
	if (!dest)
		return (NULL);
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

int	update_env_next(t_bui *blts, char *oldpwd)
{
	int	e;
	int	i;

	e = 0;
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

int	update_env(t_bui *blts)
{
	int		i;
	char	*oldpwd;

	i = 0;
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
		}
		i++;
	}
	if (update_env_next(blts, oldpwd))
		return (1);
	return (0);
}
