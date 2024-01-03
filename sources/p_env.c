/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 11:49:41 by flavian           #+#    #+#             */
/*   Updated: 2024/01/02 14:57:44 by flavian          ###   ########.fr       */
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

char	*get_in_env_3(char *ret, t_gie *data)
{
	ret = data->buf;
	free(data);
	return (ret);
}

char	*get_in_env_2(char **env, char *str, t_gie *data)
{
	data->y += ft_strlen(str) + 1;
	if (env[data->i][data->y - 1] != '=')
		return (NULL);
	data->buf = malloc(sizeof(char) * (ft_strlen(env[data->i]) - data->y + 1));
	if (!data->buf)
		return (NULL);
	data->buf[0] = 0;
	while (env[data->i][data->y])
		data->buf[data->j++] = env[data->i][data->y++];
	data->buf[data->j] = 0;
	return (data->buf);
}

char	*get_in_env(char **env, char *str)
{
	t_gie	*data;
	char	*ret;

	data = malloc(sizeof(t_gie));
	if (!data)
		return (NULL);
	data->i = 0;
	data->buf = NULL;
	ret = NULL;
	while (env[data->i])
	{
		data->y = 0;
		data->j = 0;
		if (!ft_strncmp(env[data->i], str, ft_strlen(str)))
		{
			get_in_env_2(env, str, data);
			free(str);
			return (get_in_env_3(ret, data));
		}
		data->i++;
	}
	free(data);
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
	y = get_var_env_2(pars, i);
	j = i;
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
