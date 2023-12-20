/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_count.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:03:27 by flavian           #+#    #+#             */
/*   Updated: 2023/12/19 22:16:53 by flavian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_sep(t_pars *pars)
{
	int	i;
	int	count;
	int	set;

	i = 0;
	count = 0;
	set = 0;
	while (pars->av[i])
	{
		if (is_quote(pars->av[i]) > 0 && quote_is_closed(pars, i) > 0)
			i = quote_is_closed(pars, i);
		if (is_sep(pars->av[i]) && set == 0)
		{
			set = 1;
			count++;
		}
		if ((!is_sep(pars->av[i]) && !is_quote(pars->av[i] && set == 1)
				&& (is_whitespace(pars->av[i]) || is_printable(pars->av[i]))))
			set = 0;
		i++;
	}
	return (count);
}

void	count_word_3(t_pars *pars, t_wc *data)
{
	data->quote = handle_quotes(pars, data->i);
	if (data->set == 0)
	{
		data->count++;
		data->set = 1;
	}
	free(data->quote);
	data->i = quote_is_closed(pars, data->i);
}

int	count_word_2(t_pars *pars, t_wc *data, int count)
{
	while (pars->av[data->i])
	{
		if (is_sep(pars->av[data->i]))
			break ;
		else if (is_whitespace(pars->av[data->i]))
			data->set = 0;
		else if (is_quote(pars->av[data->i]))
			count_word_3(pars, data);
		else if (data->set == 0)
		{
			data->count++;
			data->set = 1;
		}
		data->i++;
	}
	count = data->count;
	free(data);
	return (count);
}

int	count_word(t_pars *pars)
{
	t_wc	*data;
	int		count;

	data = malloc(sizeof(t_wc));
	if (!data)
		return (-1);
	data->count = 0;
	data->set = 0;
	data->quote = NULL;
	data->i = pars->i;
	count = 0;
	return (count_word_2(pars, data, count));
}
