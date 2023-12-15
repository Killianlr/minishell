/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_count.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:03:27 by flavian           #+#    #+#             */
/*   Updated: 2023/12/15 11:49:56 by flavian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_sep(char *str)
{
	int	i;
	int	count;
	int	status;

	i = 0;
	count = 0;
	status = is_quote(str[i]);
	while (str[i])
	{
		if (status > 0 && is_quote(str[i]) == status)
			status = 0;
		else if (is_quote(str[i]) > 0)
			status = is_quote(str[i]);
		if (is_sep(str[i]) && !is_sep(str[i + 1]) && status == 0)
			count++;
		i++;
	}
	count++;
	return (count);
}

int	count_word(t_pars *pars)
{
	int	count;

	int	 i;
	int	set;
	int	quote_s;

	count = 0;
	set = 0;
	quote_s = 0;
	i = pars->i;
	while (pars->av[i])
	{

		if (is_sep(pars->av[i]) && quote_s == 0)
			break;
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
	int	count;
	char	*var_env;
	int	i;

	count = 0;
	var_env = NULL;
	i = pars->i;
	while (pars->av[i] && (is_sep(pars->av[i]) || is_whitespace(pars->av[i])))
		i++;
	while (pars->av[i] && ft_isprint(pars->av[i]) && !is_whitespace(pars->av[i]))
	{
		if (is_$(pars->av[i]))
		{
			var_env = get_$(pars);
			count += ft_strlen(var_env) - 1;
			i = after_$(pars) - 1;
		}
		count++;
		i++;
	}

	return (count);
}