/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_get_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fserpe <fserpe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 16:15:16 by fserpe            #+#    #+#             */
/*   Updated: 2024/01/20 18:32:05 by fserpe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*fill_quote(t_pars *pars, t_fcl *data, char *buf)
{
	data->quote = handle_quotes(pars->av, pars->i);
	if (!data->quote)
	{
		free(buf);
		return (NULL);
	}
	if (!ms_strj_s(buf, data->quote, data->size))
	{
		free(buf);
		return (NULL);
	}
	data->y = ft_strlen(buf);
	if (end_quote(pars->av, pars->i) > 0)
		pars->i = end_quote(pars->av, pars->i);
	else
		return (ft_strdup(""));
	return (buf);
}

char	*fill_cmd_line_loop(t_pars *pars, t_fcl *data, char *ret)
{
	while (pars->av[pars->i] && ft_find_sep_val(pars->av[pars->i]) != 1)
	{
		if (ft_find_sep_val(pars->av[pars->i]) > 1)
			pars->i = new_val_i(pars, pars->i) - 1;
		else if (is_quote(pars->av[pars->i]) && end_quote(pars->av, pars->i))
		{
			ret = fill_quote(pars, data, ret);
			if (!ret)
				return (NULL);
			data->y = ft_strlen(ret);
			if (!pars->av[pars->i])
				break ;
		}
		else if (is_char(pars->av[pars->i]))
		{
			data->set = 1;
			ret[data->y] = pars->av[pars->i];
			data->y++;
		}
		else if (data->set == 1 && !is_char(pars->av[pars->i]))
			break ;
		pars->i++;
	}
	ret[data->y] = 0;
	return (ret);
}

char	*fill_cmd_line(t_pars *pars)
{
	char	*ret;
	t_fcl	*data;

	data = malloc(sizeof(t_fcl));
	data->size = len_for_malloc_line(pars);
	ret = ft_calloc(data->size + 1, 1);
	if (!ret)
		return (NULL);
	data->y = 0;
	data->set = 0;
	ret = fill_cmd_line_loop(pars, data, ret);
	if (!ret || !ret[0])
	{
		free(data);
		free(ret);
		return (NULL);
	}
	free(data);
	return (ret);
}

void	new_val_pars_i(t_pars *pars)
{
	while (pars->av[pars->i] && !is_char(pars->av[pars->i])
		&& ft_find_sep_val(pars->av[pars->i]) != 1)
	{
		if (ft_find_sep_val(pars->av[pars->i]) > 1)
		{
			pars->i = new_val_i(pars, pars->i);
			if (!pars->av[pars->i])
				return ;
		}
		pars->i++;
	}
}

char	**get_cmd_line(t_pars *pars)
{
	char	**ret;
	int		r;
	int		len;

	while (pars->av[pars->i] && (ft_find_sep_val(pars->av[pars->i]) == 1
			|| is_whitespace(pars->av[pars->i])))
		pars->i++;
	len = len_for_malloc_tab(pars);
	ret = malloc(sizeof(char *) * (len + 1));
	if (!ret)
		return (NULL);
	r = 0;
	while (pars->av[pars->i]
		&& ft_find_sep_val(pars->av[pars->i]) != 1 && len)
	{
		ret[r] = fill_cmd_line(pars);
		if (!ret[r])
			break ;
		r++;
		len--;
	}
	new_val_pars_i(pars);
	ret[r] = NULL;
	return (ret);
}
