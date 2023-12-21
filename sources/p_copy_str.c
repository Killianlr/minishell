/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_copy_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 10:32:14 by fserpe            #+#    #+#             */
/*   Updated: 2023/12/21 13:48:06 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*copy_str_4(t_pars *pars, t_cs *data, char *buf)
{
	buf = ms_strjoin(buf, get_var_env(pars, pars->i), 3);
	if (!buf)
		return (NULL);
	data->y = ft_strlen(buf);
	return (buf);
}

char	*copy_str_3(t_pars *pars, t_cs *data, char *buf)
{
	if (is_quote(pars->av[pars->i]) && quote_is_closed(pars, pars->i))
	{
		data->quote = handle_quotes(pars, pars->i);
		if (!data->quote)
			return (NULL);
		if (!ms_strjoin_size(buf, data->quote, data->size))
			return (NULL);
		data->y = ft_strlen(buf);
		if (quote_is_closed(pars, pars->i) > 0)
			pars->i = quote_is_closed(pars, pars->i);
		else
			return (ft_strdup(""));
	}
	return (buf);
}

char	*copy_str_2(t_pars *pars, t_cs *data, char *buf)
{
	while (pars->av[pars->i] && !is_sep(pars->av[pars->i])
		&& !is_whitespace(pars->av[pars->i]))
	{
		if (is_quote(pars->av[pars->i]) && quote_is_closed(pars, pars->i))
		{
			buf = copy_str_3(pars, data, buf);
			if (!buf)
				return (NULL);
		}
		else if (is_var_env(pars->av[pars->i]))
		{
			buf = copy_str_4(pars, data, buf);
			if (!buf)
				return (NULL);
		}
		else if (!is_quote(pars->av[pars->i]) && !is_var_env(pars->av[pars->i])
			&& !is_sep(pars->av[pars->i]) && !is_whitespace(pars->av[pars->i]))
		{
			buf[data->y] = pars->av[pars->i];
			data->y++;
		}
		pars->i++;
	}
	buf[data->y] = 0;
	return (buf);
}

char	*copy_str(t_pars *pars)
{
	t_cs	*data;
	char	*buf;

	data = malloc(sizeof(t_cs));
	if (!data)
		return (NULL);
	data->size = size_for_line(pars);
	buf = ft_calloc((data->size + 1), sizeof(char));
	if (!buf)
		return (NULL);
	data->y = 0;
	data->quote = NULL;
	while (pars->av[pars->i] && is_whitespace(pars->av[pars->i]))
		pars->i++;
	buf = copy_str_2(pars, data, buf);
	free (data);
	return (buf);
}
