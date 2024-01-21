/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_new_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fserpe <fserpe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 20:02:54 by flavian           #+#    #+#             */
/*   Updated: 2024/01/21 16:06:36 by fserpe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	size_for_new_str(t_pars *pars, int ret_val)
{
	char	*var_env;
	int		size;
	int		set;
	int		i;

	size = 0;
	i = 0;
	set = 0;
	while (pars->av[i])
	{
		if (is_quote(pars->av[i]) == 1 && set == 0)
			set = 1;
		else if (is_quote(pars->av[i]) == 1 && set == 1)
			set = 0;
		else if (is_quote(pars->av[i]) == 2 && set == 0)
			set = -1;
		else if (is_quote(pars->av[i]) == 2 && set == -1)
			set = 0;
		if (pars->av[i] == '$' && set != 1)
		{
			var_env = get_var_env(pars, i, ret_val);
			if (var_env)
			{
				size += (int) ft_strlen(var_env) - 1;
				free(var_env);
				while (pars->av[i + 1] && (!is_whitespace(pars->av[i + 1])
						&& !is_sep(pars->av[i + 1]) && !is_quote(pars->av[i + 1])))
					i++;
			}
			else
			{
				size++;
				i++;
			}
		}
		size++;
		i++;
	}
	return (size);
}

int	handle_var_env_2(t_pars *pars, int ret_val, t_ns *data, char *ret)
{
	if (!ms_strj_s(ret, get_var_env(pars, data->i, ret_val), data->len))
		return (0);
	data->y = ft_strlen(ret);
	while (pars->av[data->i] && (!is_whitespace(pars->av[data->i])
			&& !is_sep(pars->av[data->i])
			&& !is_quote(pars->av[data->i])))
		data->i++;
	return (1);
}

char	*handle_var_env(t_pars *pars, int ret_val, t_ns *data, char *ret)
{
	while (pars->av[data->i])
	{
		if (pars->av[data->i] == 34 && data->set == 0)
			data->set = -1;
		else if (pars->av[data->i] == 34 && data->set == -1)
			data->set = 0;
		else if (pars->av[data->i] == 39 && data->set == 0)
			data->set = 1;
		else if (pars->av[data->i] == 39 && data->set == 1)
			data->set = 0;
		if (pars->av[data->i] == '$' && data->set != 1)
		{
			if (!handle_var_env_2(pars, ret_val, data, ret))
				return (NULL);
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

	if (!check_sep_count(pars->av))
		return (NULL);
	if (count_quote(pars->av) % 2 != 0)
	{
		printf("Error 1, quote unclosed\n");
		return (NULL);
	}
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
	data->quote = NULL;
	ret = handle_var_env(pars, ret_val, data, ret);
	free(data);
	return (ret);
}
