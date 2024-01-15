/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_copy_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 10:32:14 by fserpe            #+#    #+#             */
/*   Updated: 2024/01/15 14:57:17 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*copy_str_5(t_pars *pars, t_cs *data, char *buf)
{
	if (!is_quote(pars->av[pars->i]) && !is_var_env(pars->av[pars->i])
		&& !is_sep(pars->av[pars->i]) && !is_whitespace(pars->av[pars->i]))
	{
		buf[data->y] = pars->av[pars->i];
		data->y++;
		if (!pars->av[pars->i])
			return (buf);
	}
	pars->i++;
	return (buf);
}

char	*copy_str_4(t_pars *pars, t_cs *data, char *buf, int ret_val)
{
	buf = ms_strjoin(buf, get_var_env(pars, pars->i, ret_val), 3);
	if (!buf)
		return (NULL);
	data->y = ft_strlen(buf);
	while (pars->av[pars->i] && (!is_whitespace(pars->av[pars->i])
			|| !is_sep(pars->av[pars->i])))
		pars->i++;
	return (buf);
}

char	*copy_str_3(t_pars *pars, t_cs *data, char *buf)
{
	data->quote = handle_quotes(pars, pars->i);
	if (!data->quote)
		return (NULL);
	if (!ms_strj_s(buf, data->quote, data->size))
		return (NULL);
	data->y = ft_strlen(buf);
	if (quote_is_closed(pars, pars->i) > 0)
		pars->i = quote_is_closed(pars, pars->i) + 1;
	else
		return (ft_strdup(""));
	return (buf);
}

char	*copy_str_2(t_pars *pars, t_cs *data, char *buf, int ret_val)
{
	while (pars->av[pars->i] && !is_sep(pars->av[pars->i])
		&& !is_whitespace(pars->av[pars->i]))
	{
		if (is_quote(pars->av[pars->i]) && quote_is_closed(pars, pars->i))
		{
			buf = copy_str_3(pars, data, buf);
			if (!buf)
				return (NULL);
			if (!pars->av[pars->i])
				break ;
		}
		else if (is_var_env(pars->av[pars->i]))
		{
			buf = copy_str_4(pars, data, buf, ret_val);
			if (!buf)
				return (NULL);
			if (!pars->av[pars->i])
				break ;
		}
		else
			buf = copy_str_5(pars, data, buf);
	}
	buf[data->y] = 0;
	return (buf);
}

char	*copy_str(t_pars *pars, int ret_val)
{
	t_cs	*data;
	char	*buf;

	data = malloc(sizeof(t_cs));
	if (!data)
		return (NULL);
	data->size = size_for_line(pars, ret_val);
	buf = ft_calloc((data->size + 1), sizeof(char));
	if (!buf)
		return (NULL);
	data->y = 0;
	data->quote = NULL;
	while (pars->av[pars->i] && is_whitespace(pars->av[pars->i]))
		pars->i++;
	buf = copy_str_2(pars, data, buf, ret_val);
	free(data);
	return (buf);
}
