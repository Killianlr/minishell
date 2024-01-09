/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_get_in_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 15:35:44 by kle-rest          #+#    #+#             */
/*   Updated: 2024/01/09 15:39:24 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	quote_is_closed(t_pars *pars, int l)
{
	int		target;
	int		i;

	target = 0;
	i = l;
	if (count_quote(pars) % 2 != 0)
		return (ft_error("Error 1, quote unclosed", 0));
	else
	{
		while (pars->av[i])
		{
			if (target == 0 && is_quote(pars->av[i]) > 0)
				target = is_quote(pars->av[i]);
			else if (target > 0 && target == is_quote(pars->av[i]))
				return (i);
			i++;
		}
	}
	return (0);
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

char	*get_in_env(char **env, char *str, int ret_val)
{
	t_gie	*data;
	char	*ret;

	ret = is_ret_val(str, ret_val);
	if (ret)
		return (ret);
	data = malloc(sizeof(t_gie));
	if (!data)
		return (NULL);
	data->i = 0;
	data->buf = NULL;
	while (env[data->i])
	{
		data->y = 0;
		data->j = 0;
		if (!env_strncmp(env[data->i], str, ft_strlen(str)))
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
