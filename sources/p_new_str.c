/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_new_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 20:02:54 by flavian           #+#    #+#             */
/*   Updated: 2024/01/15 10:51:26 by flavian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	size_for_new_str(t_pars *pars, int ret_val)
{
	char	*var_env;
	int		size;
	int		i;

	size = 0;
	i = 0;
	while (pars->av[i])
	{
		if (pars->av[i] == '$')
		{
			var_env = get_var_env(pars, i, ret_val);
			size += (int) ft_strlen(var_env) - 1;
			free(var_env);
			while (pars->av[i + 1] && (!is_whitespace(pars->av[i + 1]) &&
					!is_sep(pars->av[i + 1]) && !is_quote(pars->av[i + 1])))
				i++;
		}
		size++;
		i++;
	}
	return (size);
}

char	*new_str_end(t_pars *pars, int ret_val, t_ns *data, char *ret)
{
	while (pars->av[data->i])
	{
		if (pars->av[data->i] == 39 && data->set == 0)
			data->set = 1;
		else if (pars->av[data->i] == 39 && data->set == 1)
			data->set = 0;
		if (pars->av[data->i] == '$' && !data->set)
		{
			if (!ms_strjoin_size(ret, get_var_env(pars, data->i, ret_val), data->len))
				return (NULL);
			data->y = ft_strlen(ret);
			while (pars->av[data->i] && (!is_whitespace(pars->av[data->i])
					&& !is_sep(pars->av[data->i]) && !is_quote(pars->av[data->i])))
				data->i++;
		}
		else if (pars->av[data->i])
			ret[data->y++] = pars->av[data->i++];
	}
	ret[data->y] = 0;
	pars->av = ret;
	return (ret);
}


char	*new_str(t_pars *pars, int ret_val)
{
	t_ns	*data;
	char	*ret;

	data = malloc(sizeof(t_ns));
	if (!data)
		return (NULL);
	data->len = size_for_new_str(pars, ret_val) + 1;
	ret = ft_calloc(data->len, 1);
	if (!ret)
		return (NULL);
	ret[0] = 0;
	data->i = 0;
	data->y = 0;
	data->set = 0;
	ret = new_str_end(pars, ret_val, data, ret);
	free(data);
	return (ret);
}
