/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:03:27 by flavian           #+#    #+#             */
/*   Updated: 2023/12/11 18:08:34 by flavian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


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

int	count_word(char *str, int i)
{
	int	count;
	int	set;
	int	quote_s;

	count = 0;
	set = 0;
	quote_s = 0;
	while (str[i] )
	{
		if (is_sep(str[i]) && quote_s == 0)
			break;
		else if (is_quote(str[i]) && quote_s == 0)
			quote_s = is_quote(str[i]);
		else if (is_whitespace(str[i]) && quote_s == 0)
			set = 0;
		else if (set == 0 && quote_s == 0)
		{
			count++;
			set = 1;
		}
		else if (is_quote(str[i]) == quote_s)
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



int	count_char(char *str, int i, t_bui *blts)
{
	int	count;
	char	*var_env;

	count = 0;
	var_env = NULL;
	while (str[i] && (is_sep(str[i]) || is_whitespace(str[i])))
		i++;
	while (str[i] && ft_isprint(str[i]) && !is_whitespace(str[i]))
	{
		if (is_$(str[i]))
		{
			var_env = get_$(str, i, blts);
			count += ft_strlen(var_env) - 1;
			i = after_$(str, i) - 1;
		}
		count++;
		i++;
	}
	return (count);
}