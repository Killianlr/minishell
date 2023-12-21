/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_quote.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fserpe <fserpe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:06:01 by flavian           #+#    #+#             */
/*   Updated: 2023/12/21 14:42:17 by fserpe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_quote(t_pars *pars)
{
	int	i;
	int	s_count;
	int	d_count;

	i = 0;
	s_count = 0;
	d_count = 0;
	while (pars->av[i])
	{
		if (is_quote(pars->av[i]) == 1)
			s_count++;
		if (is_quote(pars->av[i]) == 2)
			d_count++;
		i++;
	}
	if (s_count % 2 != 0 || d_count % 2 != 0)
		return (1);
	return (s_count + d_count);
}

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
			{
				target = is_quote(pars->av[i]);
				i++;
			}
			if (target > 0 && target == is_quote(pars->av[i]))
				return (i);
			i++;
		}
	}
	return (0);
}

void	handle_quote_3(t_pars *pars, t_hq *data)
{
	data->i++;
	while (pars->av[data->i] && data->i < data->end
		&& is_quote(pars->av[data->i]) != 2)
	{
		if (is_var_env(pars->av[data->i]))
		{
			data->buf = ms_strjoin(data->buf, get_var_env(pars, data->i), 3);
			if (!data->buf)
				return ;
			data->y = ft_strlen(data->buf);
			data->i = after_var_env(pars, data->i);
			if (data->i < 0)
				return ;
		}
		if (is_quote(pars->av[data->i]) == 2)
		{
			data->buf[data->y] = 0;
			return ;
		}
		data->buf[data->y++] = pars->av[data->i++];
	}
}

void	handle_quote_2(t_pars *pars, t_hq *data)
{
	if (is_quote(pars->av[data->i]) == 1)
	{
		data->i++;
		if (pars->av[data->i] == '$' && pars->av[data->i + 1] == '?')
		{
			free(data->buf);
			data->buf = ft_strdup("'$?'");
			return ;
		}
		while (pars->av[data->i] && data->i < data->end)
			data->buf[data->y++] = pars->av[data->i++];
	}
	else if (is_quote(pars->av[data->i]) == 2)
		handle_quote_3(pars, data);
	if (!data->buf)
		return ;
	data->buf[data->y] = 0;
}

char	*handle_quotes(t_pars *pars, int l)
{
	t_hq	*data;
	char	*ret;

	ret = NULL;
	data = malloc(sizeof(t_hq));
	if (!data)
		return (NULL);
	data->i = l;
	data->end = quote_is_closed(pars, data->i);
	if (data->end == 0)
		return (NULL);
	while (pars->av[data->i] && !is_quote(pars->av[data->i]))
		data->i++;
	data->buf = malloc(sizeof(char) * (data->end - data->i + 1));
	if (!data->buf)
		return (NULL);
	data->buf[0] = 0;
	data->y = 0;
	handle_quote_2(pars, data);
	if (!data->buf)
		return (NULL);
	ret = data->buf;
	free(data);
	return (ret);
}
