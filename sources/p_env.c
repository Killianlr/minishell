/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 11:49:41 by flavian           #+#    #+#             */
/*   Updated: 2023/12/19 11:51:51 by flavian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	after_var_env(t_pars *pars, int i)
{
	int	y;

	y = i;
	if (!pars->av || y < 0)
		return (0);
	while (pars->av[y] && !is_whitespace(pars->av[y])
		&& !is_sep(pars->av[y]) && !is_quote(pars->av[y]))
		y++;
	if (!pars->av[y])
		return (-1);
	return (y);
}

char	*get_in_env(char **env, char *str)
{
	char	*buf;
	int		i;
	int		y;
	int		j;

	if (!env[0] || !str)
		return (NULL);
	i = 0;
	buf = NULL;
	while (env[i])
	{
		y = 0;
		j = 0;
		if (!ft_strncmp(env[i], str, ft_strlen(str)))
		{
			y += ft_strlen(str) + 1;
			if (env[i][y - 1] != '=')
				break ;
			buf = malloc(sizeof(char) * (ft_strlen(env[i]) - y + 1));
			if (!buf)
				return (NULL);
			buf[0] = 0;
			while (env[i][y])
				buf[j++] = env[i][y++];
			buf[j] = 0;
			free(str);
			return (buf);
		}
		i++;
	}
	return (ms_strjoin("$", str, 2));
}

char	*get_var_env(t_pars *pars, int i)
{
	char	*buf;
	int		y;
	int		j;

	while (pars->av[i] && !is_var_env(pars->av[i]))
		i++;
	if (!pars->av[i])
		return (NULL);
	if (pars->av[i + 1])
		i++;
	y = 0;
	j = i;
	while (pars->av[i] && !is_whitespace(pars->av[i])
		&& !is_sep(pars->av[i]) && !is_quote(pars->av[i]))
	{
		y++;
		i++;
	}
	buf = malloc(sizeof(char) * y + 1);
	if (!buf)
		return (NULL);
	buf[0] = 0;
	y = 0;
	while (pars->av[j] && !is_whitespace(pars->av[j])
		&& !is_sep(pars->av[j]) && !is_quote(pars->av[j]))
		buf[y++] = pars->av[j++];
	buf[y] = 0;
	buf = get_in_env(pars->env, buf);
	return (buf);
}