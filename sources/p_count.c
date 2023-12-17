/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_count.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:03:27 by flavian           #+#    #+#             */
/*   Updated: 2023/12/17 17:41:22 by flavian          ###   ########.fr       */
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

int	count_word(t_pars *pars)
{
	int	count;
	int	i;
	int	set;
	int	quote_s;

	count = 0;
	set = 0;
	quote_s = 0;
	i = pars->i;
	while (pars->av[i])
	{
		if (is_sep(pars->av[i]) && quote_s == 0)
			break ;
		else if (is_quote(pars->av[i]) && quote_s == 0)
			quote_s = is_quote(pars->av[i]);
		else if (is_whitespace(pars->av[i]) && quote_s == 0)
			set = 0;
		else if (set == 0 && quote_s == 0)
		{
			count++;
			set = 1;
		}
		else if (is_quote(pars->av[i]) == quote_s && quote_s > 0)
		{
			set = 0;
			quote_s = 0;
		}
		else if (quote_s > 0 && set == 0)
		{
			count++;
			set = 1;
		}
		i++;
	}
	return (count);
}

int	count_char(t_pars *pars)
{
	int		count;
	char	*var_env;
	int		i;

	count = 0;
	var_env = NULL;
	i = pars->i;
	while (pars->av[i] && (is_sep(pars->av[i]) || is_whitespace(pars->av[i])))
		i++;
	while (pars->av[i] && is_printable(pars->av[i])
		&& !is_whitespace(pars->av[i]) && !is_sep(pars->av[i]))
	{
		if (is_var_env(pars->av[i]))
		{
			var_env = get_var_env(pars, i);
			count += ft_strlen(var_env) - 1;
			i = after_var_env(pars, i) - 1;
			if (i < 0)
			{
				free(var_env);
				return (count);
			}
		}
		count++;
		i++;
	}
	free(var_env);
	return (count);
}
