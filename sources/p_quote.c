/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_quote.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:06:01 by flavian           #+#    #+#             */
/*   Updated: 2023/12/14 18:25:45 by flavian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	quote_is_closed(t_pars *pars)
{
	char target;

	target = pars->av[pars->i];
	if (!pars->av || pars->i < 0 || !is_quote(target))
		return (0);
	if (pars->av[pars->i + 1])
		pars->i++;
	else
	{
		// ft_printf("Error 1, quote unclosed\n");
		return (0);
	}
	while (pars->av[pars->i])
	{
		if (pars->av[pars->i] == target)
			return (pars->i);
		pars->i++;
	}
	// ft_printf("Error 2, quote unclosed\n");
	return (0);
}

char	*handle_quotes(t_pars *pars)
{
	char	*buf;
	int		end;
	int		y;

	end = quote_is_closed(pars);
	if (end == 0)
		return (NULL);
	buf = malloc(sizeof(char) * (end - pars->i + 1));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	y = 0;
	if (is_quote(pars->av[pars->i]) == 1)
	{
		pars->i++;
		while (pars->av[pars->i] && pars->i < end)
			buf[y++] = pars->av[pars->i++];
	}
	else if (is_quote(pars->av[pars->i]) == 2)
	{
		pars->i++;
		while (pars->av[pars->i] && pars->i < end && is_quote(pars->av[pars->i]) != 2)
		{
			if (is_$(pars->av[pars->i]))
			{
				buf = ms_strjoin(buf, get_$(pars), 3);
				if (!buf)
					return (NULL);
				y = ft_strlen(buf);
				pars->i = after_$(pars);
			}
			if (is_quote(pars->av[pars->i]) == 2)
			{
				buf[y] = 0;
				return (buf);
			}
			buf[y++] = pars->av[pars->i++];
		}
	}
	buf[y] = 0;
	return (buf);
}