/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_quote.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fserpe <fserpe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:06:01 by flavian           #+#    #+#             */
/*   Updated: 2023/12/15 16:51:31 by fserpe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	quote_is_closed(t_pars *pars)
{
	char	target;
	int		i;

	i = pars->i;
	while (pars->av[i] && !is_quote(pars->av[i]))
		i++;
	target = pars->av[i];
	if (!pars->av || i < 0 || !is_quote(target))
		return (0);
	if (pars->av[i + 1])
		i++;
	else
	{
		// ft_printf("Error 1, quote unclosed\n");
		return (0);
	}
	while (pars->av[i])
	{
		if (pars->av[i] == target)
			return (i);
		i++;
	}
	// ft_printf("Error 2, quote unclosed\n");
	return (0);
}

char	*handle_quotes(t_pars *pars)
{
	char	*buf;
	int		end;
	int		y;
	int		i;

	end = quote_is_closed(pars);
	if (end == 0)
		return (NULL);
	i = pars->i;
	while (pars->av[i] && !is_quote(pars->av[i]))
		i++;
	buf = malloc(sizeof(char) * (end - i + 1));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	y = 0;
	if (is_quote(pars->av[i]) == 1)
	{
		i++;
		while (pars->av[i] && i < end)
			buf[y++] = pars->av[i++];
	}
	else if (is_quote(pars->av[i]) == 2)
	{
		i++;
		while (pars->av[i] && i < end && is_quote(pars->av[i]) != 2)
		{
			if (is_var_env(pars->av[i]))
			{
				buf = ms_strjoin(buf, get_var_env(pars), 3);
				if (!buf)
					return (NULL);
				y = ft_strlen(buf);
				i = after_var_env(pars);
			}
			if (is_quote(pars->av[i]) == 2)
			{
				buf[y] = 0;
				return (buf);
			}
			buf[y++] = pars->av[i++];
		}
	}
	buf[y] = 0;
	return (buf);
}
