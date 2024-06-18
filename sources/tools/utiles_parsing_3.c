/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles_parsing_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 12:13:40 by kle-rest          #+#    #+#             */
/*   Updated: 2024/01/23 12:22:53 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	loop_in_loop_ns(t_pars *pars, t_sfns *data)
{
	while (pars->av[data->i + 1] && (!is_whitespace(pars->av[data->i + 1])
			&& !is_sep(pars->av[data->i + 1])
			&& !is_quote(pars->av[data->i + 1])))
		data->i++;
}

int	loop_size_4_new_str(t_pars *pars, t_sfns *data, int ret_val, int size)
{
	while (pars->av[data->i])
	{
		if (pars->av[data->i] == '$' && data->set != 1)
		{
			data->set = set_quote_new_str(pars, data->i, data->set);
			data->var_env = get_var_env(pars, data->i, ret_val);
			if (data->var_env)
			{
				size += (int) ft_strlen(data->var_env) - 1;
				free(data->var_env);
				loop_in_loop_ns(pars, data);
			}
			else
			{
				size++;
				data->i++;
			}
		}
		size++;
		data->i++;
	}
	return (size);
}

char	*check_sep_count(char *str)
{
	int	i;
	int	sep_val;
	int	set;

	i = 0;
	sep_val = 0;
	set = 0;
	return (check_sep_count_2(str, i, sep_val, set));
}

void	unlink_hdoc(t_cmd *cmd)
{
	unlink(".heredoc_tmp");
	cmd->hdoc = 0;
}
