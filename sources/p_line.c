/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_line.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 11:44:50 by flavian           #+#    #+#             */
/*   Updated: 2024/01/06 21:02:54 by flavian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	size_for_line_3(t_pars *pars, t_sfl *data, int ret_val)
{
	data->tmp = get_var_env(pars, data->i, ret_val);
	data->count += (int)ft_strlen(data->tmp);
	free(data->tmp);
	while (pars->av[data->i + 1] && !is_whitespace(pars->av[data->i + 1])
		&& !is_sep(pars->av[data->i + 1]) && !is_quote(pars->av[data->i + 1]))
		data->i++;
}

void	size_for_line_2(t_pars *pars, t_sfl *data, int ret_val)
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
			size_for_line_3(pars, data, ret_val);
		else if (is_sep(pars->av[data->i]) || is_whitespace(pars->av[data->i]))
			break ;
		data->i++;
	}
}

int	size_for_line(t_pars *pars, int ret_val)
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
	size_for_line_2(pars, data, ret_val);
	ret = data->count;
	free(data);
	return (ret);
}

char	**get_line(t_pars *pars, int ret_val)
{
	t_sl	data;
	char	**buf;

	data.word_count = count_word(pars);
	if (!data.word_count)
		return (strduptab(pars));
	buf = malloc(sizeof(char *) * (data.word_count + 1));
	if (!buf)
		return (NULL);
	data.y = 0;
	while (pars->av[pars->i] && data.y < data.word_count)
	{
		while (pars->av[pars->i] && is_whitespace(pars->av[pars->i]))
			pars->i++;
		buf[data.y] = copy_str(pars, ret_val);
		if (!buf[data.y])
		{
			free_pars_tab(buf);	
			return (NULL);
		}
		data.y++;
	}
	buf[data.y] = NULL;
	return (buf);
}
