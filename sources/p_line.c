/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_line.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 11:44:50 by flavian           #+#    #+#             */
/*   Updated: 2023/12/19 22:32:44 by flavian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	size_for_line_3(t_pars *pars, t_sfl *data)
{
	data->tmp = get_var_env(pars, data->i);
	data->count += (int)ft_strlen(data->tmp);
	free(data->tmp);
	while (pars->av[data->i + 1] && !is_whitespace(pars->av[data->i + 1])
		&& !is_sep(pars->av[data->i + 1]) && !is_quote(pars->av[data->i + 1]))
		data->i++;
}


void	size_for_line_2(t_pars *pars, t_sfl *data)
{
	while (pars->av[data->i])
	{
		if (is_quote(pars->av[data->i]))
		{
			data->quote = handle_quotes(pars, data->i);
			data->count += (int)ft_strlen(data->quote);
			free(data->quote);
			data->i = quote_is_closed(pars, data->i);
			if (data->i == 0)
				return ;
		}
		else if (is_printable(pars->av[data->i]) && !is_sep(pars->av[data->i])
			&& !is_quote(pars->av[data->i]) && !is_var_env(pars->av[data->i]))
			data->count++;
		else if (is_var_env(pars->av[data->i]))
			size_for_line_3(pars, data);
		else if (is_sep(pars->av[data->i]) || is_whitespace(pars->av[data->i]))
			break ;
		data->i++;
	}

}

int	size_for_line(t_pars *pars)
{
	t_sfl	*data;
	int		ret;

	data = malloc(sizeof(t_sfl));
	if (!data)
		return (-1);
	data->i = pars->i;
	data->count = 0;
	data->quote = NULL;
	data->tmp = NULL;
	size_for_line_2(pars, data);
	ret = data->count;
	free(data);
	return (ret);
}

char	*copy_str(t_pars *pars)
{
	int		y;
	char	*buf;
	char	*quote;
	int		size;

	size = size_for_line(pars);
	buf = ft_calloc((size + 1), sizeof(char));
	if (!buf)
		return (NULL);
	y = 0;
	quote = NULL;
	while (pars->av[pars->i] && is_whitespace(pars->av[pars->i]))
		pars->i++;
	while (pars->av[pars->i] && !is_sep(pars->av[pars->i])
		&& !is_whitespace(pars->av[pars->i]))
	{
		if (is_quote(pars->av[pars->i]) && quote_is_closed(pars, pars->i))
		{
			quote = handle_quotes(pars, pars->i);
			if (!quote)
				return (NULL);
			if (!ms_strjoin_size(buf, quote, size))
				return (NULL);
			y = ft_strlen(buf);
			if (quote_is_closed(pars, pars->i) > 0)
				pars->i = quote_is_closed(pars, pars->i);
			else
				return (ft_strdup(""));
		}
		else if (is_var_env(pars->av[pars->i]))
		{
			buf = ms_strjoin(buf, get_var_env(pars, pars->i), 3);
			if (!buf)
				return (NULL);
			y = ft_strlen(buf);
			break ;
		}
		else if (!is_quote(pars->av[pars->i]) && !is_var_env(pars->av[pars->i])
			&& !is_sep(pars->av[pars->i]) && !is_whitespace(pars->av[pars->i]))
		{
			buf[y] = pars->av[pars->i];
			y++;
		}
		pars->i++;
	}
	buf[y] = 0;
	return (buf);
}

char	**get_line(t_pars *pars)
{
	char	**buf;
	int		y;
	int		word_count;

	word_count = count_word(pars);
	if (!word_count)
		return (strduptab(pars));
	buf = malloc(sizeof(char *) * (word_count + 1));
	if (!buf)
		return (NULL);
	y = 0;
	while (pars->av[pars->i] && word_count > 0)
	{
		while (pars->av[pars->i] && is_whitespace(pars->av[pars->i]))
			pars->i++;
		buf[y] = copy_str(pars);
		if (!buf[y])
			return (NULL);
		y++;
		word_count--;
	}
	buf[y] = NULL;
	return (buf);
}
