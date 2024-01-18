/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_quote.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:06:01 by flavian           #+#    #+#             */
/*   Updated: 2024/01/18 20:34:18 by flavian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_quote_2(char *str, t_sq *data)
{
	int	ret;

	ret = 0;
	while (str[data->i])
	{
		if (is_quote(str[data->i]) == 1 && data->set != 2)
		{
			data->s_count++;
			data->set = 1;
		}
		else if (is_quote(str[data->i]) == 2 && data->set != 1)
		{
			data->d_count++;
			data->set = 2;
		}
		if (data->s_count % 2 == 0 && data->d_count % 2 == 0)
			data->set = 0;
		data->i++;
	}
	if (data->s_count % 2 != 0 || data->d_count % 2 != 0)
		return (1);
	ret = data->s_count + data->d_count;
	return (ret);
}

int	count_quote(char *str)
{
	t_sq	*data;
	int		ret;

	ret = 0;
	data = malloc(sizeof(t_sq) * 1);
	if (!data)
		return (0);
	data->i = 0;
	data->set = 0;
	data->s_count = 0;
	data->d_count = 0;
	ret = count_quote_2(str, data);
	free(data);
	return (ret);
}

int	quote_is_closed(char *str, int l)
{
	int		target;
	int		i;

	target = 0;
	i = l;
	if (count_quote(str) % 2 != 0)
		return (ft_error("Error 1, quote unclosed", 0));
	else
	{
		while (str[i])
		{
			if (target == 0 && is_quote(str[i]) > 0)
				target = is_quote(str[i]);
			else if (target > 0 && target == is_quote(str[i]))
				return (i);
			i++;
		}
	}
	return (0);
}

void	handle_quote_3(char *str, t_hq *data)
{
	data->i++;
	while (str[data->i] && data->i < data->end
		&& is_quote(str[data->i]) != 2)
	{
		// if (is_var_env(str[data->i]))
		// {
		// 	data->buf = ms_strjoin(data->buf, get_var_env(str, data->i, 0), 3);
		// 	if (!data->buf)
		// 		return ;
		// 	data->y = ft_strlen(data->buf);
		// 	data->i = after_var_env(str, data->i);
		// 	if (data->i < 0)
		// 		return ;
		// }
		if (is_quote(str[data->i]) == 2)
		{
			data->buf[data->y] = 0;
			return ;
		}
		data->buf[data->y++] = str[data->i++];
	}
}

void	handle_quote_2(char *str, t_hq *data)
{
	if (is_quote(str[data->i]) == 1)
	{
		data->i++;
		while (str[data->i] && data->i < data->end)
			data->buf[data->y++] = str[data->i++];
	}
	else if (is_quote(str[data->i]) == 2)
		handle_quote_3(str, data);
	if (!data->buf)
		return ;
	data->buf[data->y] = 0;
}

char	*handle_quotes(char *str, int l)
{
	t_hq	*data;
	char	*ret;

	ret = NULL;
	data = malloc(sizeof(t_hq));
	if (!data)
		return (NULL);
	data->i = l;
	while (str[data->i] && !is_quote(str[data->i]))
		data->i++;
	data->end = quote_is_closed(str, data->i);
	if (data->end == 0)
		return (NULL);
	data->buf = ft_calloc(data->end - data->i + 1, sizeof(char));
	if (!data->buf)
		return (NULL);
	// data->buf[0] = 0;
	data->y = 0;
	handle_quote_2(str, data);
	if (!data->buf)
		return (NULL);
	ret = data->buf;
	free(data);
	return (ret);
}
