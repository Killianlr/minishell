/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_line.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fserpe <fserpe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 11:44:50 by flavian           #+#    #+#             */
/*   Updated: 2023/12/19 16:36:48 by fserpe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	size_for_line(t_pars *pars)
{
	int		i;
	char	*tmp;
	char	*quote;
	int		count;

	i = pars->i;
	count = 0;
	quote = NULL;
	tmp = NULL;
	while (pars->av[i])
	{
		if (is_quote(pars->av[i]))
		{
			quote = handle_quotes(pars, i);
			count += (int)ft_strlen(quote);
			free(quote);
			i = quote_is_closed(pars, i);
			if (i == 0)
				return (count);
		}
		else if (is_printable(pars->av[i]) && !is_sep(pars->av[i])
			&& !is_quote(pars->av[i]) && !is_var_env(pars->av[i]))
			count++;
		else if (is_var_env(pars->av[i]))
		{
			tmp = get_var_env(pars, i);
			count += (int)ft_strlen(tmp);
			free(tmp);
			while (pars->av[i + 1] && !is_whitespace(pars->av[i + 1])
				&& !is_sep(pars->av[i + 1]) && !is_quote(pars->av[i + 1]))
				i++;
		}
		else if (is_sep(pars->av[i]) || is_whitespace(pars->av[i]))
			break ;
		i++;
	}
	return (count);
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
