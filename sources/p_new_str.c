/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_new_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 20:02:54 by flavian           #+#    #+#             */
/*   Updated: 2024/01/12 20:57:40 by flavian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		size_for_new_str(t_pars *pars, int ret_val)
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

char	*new_str(t_pars *pars, int ret_val)
{
	char	*ret;
	int		len;
	int		i;
	int		y;
	int		set;

	len = size_for_new_str(pars, ret_val) + 1;
	ret = ft_calloc(len, 1);
	if (!ret)
		return (NULL);
	ret[0] = 0;
	i = 0;
	y = 0;
	set = 0;
	while (pars->av[i])
	{
		if (pars->av[i] == 39 && set == 0)
			set = 1;
		else if (pars->av[i] == 39 && set == 1)
			set = 0;
		if (pars->av[i] == '$' && !set)
		{
			if (!ms_strjoin_size(ret, get_var_env(pars, i , ret_val), len))
				return (NULL);
			y = ft_strlen(ret);
			while (pars->av[i] && (!is_whitespace(pars->av[i]) &&
				!is_sep(pars->av[i]) && !is_quote(pars->av[i])))
				i++;
		}
		else if (pars->av[i])
			ret[y++] = pars->av[i++];
	}
	ret[y] = 0;
	pars->av = ret;
	return (ret);
}
