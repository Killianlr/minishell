/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_len_mal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fserpe <fserpe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 16:26:45 by fserpe            #+#    #+#             */
/*   Updated: 2024/01/22 20:46:23 by fserpe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	len_for_malloc_tab_2(t_pars *pars, int len, int i, int set)
{
	while (pars->av[i] && ft_find_sep_val(pars->av[i]) != 1)
	{
		if (set == 0 && is_char(pars->av[i]))
		{
			set = 1;
			len++;
		}
		else if (set == 0 && is_quote(pars->av[i]))
		{
			set = 1;
			len++;
			i = end_quote(pars->av, i);
			if (!i)
				return (0);
		}
		else if (set == 0 && ft_find_sep_val(pars->av[i]) > 1)
			i = new_val_i(pars, i) - 1;
		else if ((set == 1 && is_whitespace(pars->av[i]))
			|| ft_find_sep_val(pars->av[i]) > 1)
			set = 0;
		i++;
	}
	return (len);
}

int	len_for_malloc_tab(t_pars *pars)
{
	int	len;
	int	i;
	int	set;

	len = 0;
	set = 0;
	i = pars->i;
	return (len_for_malloc_tab_2(pars, len, i, set));
}

int	len_for_malloc_line_2(t_pars *pars, t_lfmf *data, int len)
{
	while (pars->av[data->i] && ft_find_sep_val(pars->av[data->i]) != 1)
	{
		if (ft_find_sep_val(pars->av[data->i]) > 1)
			data->i = new_val_i(pars, data->i) - 1;
		else if (is_quote(pars->av[data->i]))
		{
			data->quote = handle_quotes(pars->av, data->i);
			len += ft_strlen(data->quote);
			free(data->quote);
			data->i = end_quote(pars->av, data->i);
		}
		else if (is_char(pars->av[data->i]))
		{
			data->set = 1;
			len++;
		}
		else if (data->set == 1 && !is_char(pars->av[data->i]))
			return (len);
		data->i++;
	}
	return (len);
}

int	len_for_malloc_line(t_pars *pars)
{
	t_lfmf	*data;
	int		len;

	data = malloc(sizeof(t_lfmf));
	if (!data)
		return (0);
	data->i = pars->i;
	len = 0;
	data->set = 0;
	data->quote = NULL;
	len = len_for_malloc_line_2(pars, data, len);
	free(data);
	return (len);
}
