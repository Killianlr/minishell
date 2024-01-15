/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_hdoc_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 23:28:28 by flavian           #+#    #+#             */
/*   Updated: 2024/01/15 14:57:32 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	size_for_del(t_pars *pars, int l)
{
	int		i;
	int		count;
	char	*quote;

	i = l;
	count = 0;
	quote = NULL;
	while (pars->av[i])
	{
		if ((is_whitespace(pars->av[i]) || is_sep(pars->av[i])))
			break ;
		else if (is_quote(pars->av[i]))
		{
			quote = handle_quotes_hdoc(pars, i);
			count += (int)ft_strlen(quote);
			free(quote);
			i = quote_is_closed(pars, i);
		}
		if (is_printable(pars->av[i]) && !is_quote(pars->av[i])
			&& !is_sep(pars->av[i]))
			count++;
		i++;
	}
	return (count);
}

char	*get_del_hdoc_2(t_pars *pars, t_gdh *data, char *ret)
{
	while (pars->av[data->i] && data->y < data->size)
	{
		if (is_sep(pars->av[data->i]) || is_whitespace(pars->av[data->i]))
			break ;
		if (is_quote(pars->av[data->i]))
		{
			data->quote = handle_quotes(pars, data->i);
			if (!data->quote)
				return (NULL);
			if (!ms_strj_s(ret, data->quote, data->size))
				return (NULL);
			data->y = ft_strlen(ret);
			data->i = quote_is_closed(pars, data->i);
		}
		if (is_printable(pars->av[data->i]) && !is_sep(pars->av[data->i])
			&& !is_quote(pars->av[data->i]))
			ret[data->y++] = pars->av[data->i++];
	}
	ret[data->y] = 0;
	free(data);
	return (ret);
}

char	*get_del_hdoc(t_pars *pars, int l)
{
	t_gdh	*data;
	char	*ret;

	data = malloc(sizeof(t_gdh));
	if (!data)
		return (NULL);
	data->i = l;
	while (pars->av[data->i] && is_whitespace(pars->av[data->i]))
		data->i++;
	if (!pars->av[data->i])
		return (NULL);
	while (is_sep(pars->av[data->i]) || is_whitespace(pars->av[data->i]))
		data->i++;
	data->size = size_for_del(pars, data->i);
	data->quote = NULL;
	ret = malloc(sizeof(char) * (data->size + 1));
	if (!ret)
		return (NULL);
	ret[0] = 0;
	data->y = 0;
	return (get_del_hdoc_2(pars, data, ret));
}
