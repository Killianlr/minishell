/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_get_in_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 15:35:44 by kle-rest          #+#    #+#             */
/*   Updated: 2024/01/21 18:40:30 by flavian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_in_env_4(char *ret, t_gie *data)
{
	ret = data->buf;
	free(data);
	return (ret);
}

char	*get_in_env_3(char **env, char *str, t_gie *data)
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

char	*get_in_env_2(char **env, char *str, t_gie *data, char *ret)
{
	while (env[data->i])
	{
		data->y = 0;
		data->j = 0;
		if (!env_strncmp(env[data->i], str, ft_strlen(str)))
		{
			get_in_env_3(env, str, data);
			free(str);
			return (get_in_env_4(ret, data));
		}
		data->i++;
	}
	return (ret);
}

char	*incr_str(char *str)
{
	char	*ret;
	int		i;
	int		y;

	if (!str)
		return (NULL);
	ret = malloc(sizeof(char) * ft_strlen(str));
	if (!ret)
		return (NULL);
	i = 1;
	y = 0;
	while (str[i])
		ret[y++] = str[i++];
	ret[y] = 0;
	free(str);
	return (ret);
}

char	*get_in_env(char **env, char *str, int ret_val)
{
	t_gie	*data;
	char	*ret;
	int		set;

	set = 0;
	ret = is_ret_val(str, ret_val);
	if (ret && !str[1])
		return (ret);
	else
	{
		str = incr_str(str);
		set = 1;
	}
	data = malloc(sizeof(t_gie));
	if (!data)
		return (NULL);
	data->i = 0;
	data->buf = NULL;
	ret = get_in_env_2(env, str, data, ret);
	if (!ret)
	{
		free(data);
		if (str[0])
		{
			free(str);
			return (NULL);
		}
		else
			return (ms_strjoin("$", str, 2));
	}
	else if (ret && set)
	{
		free(data);
		ret = strjoin_env(ret, str, (ft_strlen(ret) + ft_strlen(str)));
		return (ret);
	}
	return (ret);
}
