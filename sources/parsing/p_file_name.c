/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_file_name.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:07:04 by fserpe            #+#    #+#             */
/*   Updated: 2024/01/21 13:52:11 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	len_for_file_name(t_pars *pars, t_ffn *data)
{
	while (pars->av[data->y] && !is_whitespace(pars->av[data->y])
		&& !ft_find_sep_val(pars->av[data->y]))
	{
		if (is_quote(pars->av[data->y]))
		{
			data->quote = handle_quotes(pars->av, data->y);
			data->len += ft_strlen(data->quote);
			free(data->quote);
			data->y = end_quote(pars->av, data->y);
		}
		data->len++;
		data->y++;
	}
	return (data->len);
}

char	*find_file_name_2(t_pars *pars, int i, t_ffn *data, char *ret)
{
	while (pars->av[i] && !is_whitespace(pars->av[i])
		&& !ft_find_sep_val(pars->av[i]))
	{
		if (is_quote(pars->av[i]))
		{
			data->quote = handle_quotes(pars->av, i);
			if (!data->quote)
				return (NULL);
			if (!ms_strj_s(ret, data->quote, data->len))
				return (NULL);
			data->y = ft_strlen(ret);
			i = end_quote(pars->av, i) + 1;
			if (!pars->av[i])
				break ;
		}
		ret[data->y++] = pars->av[i++];
	}
	ret[data->y] = 0;
	return (ret);
}

char	*find_file_name(t_pars *pars, int i)
{
	t_ffn	*data;
	char	*ret;

	data = malloc(sizeof(t_ffn));
	if (!data)
		return (NULL);
	data->quote = NULL;
	while (pars->av[i] && (ft_find_sep_val(pars->av[i]) > 1
			|| is_whitespace(pars->av[i])))
		i++;
	if (!pars->av[i])
	{
		free(data);
		return (0);
	}
	data->len = 0;
	data->y = i;
	len_for_file_name(pars, data);
	ret = ft_calloc(data->len + 1, 1);
	if (!ret)
		return (NULL);
	data->y = 0;
	ret = find_file_name_2(pars, i, data, ret);
	free(data);
	return (ret);
}
