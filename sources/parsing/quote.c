/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:06:01 by flavian           #+#    #+#             */
/*   Updated: 2023/12/11 18:07:51 by flavian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	quote_is_closed(char *str, int i)
{
	char target;

	target = str[i];
	if (!str || i < 0 || !is_quote(target))
		return (0);
	if (str[i + 1])
		i++;
	else
	{
		// ft_printf("Error 1, quote unclosed\n");
		return (0);
	}
	while (str[i])
	{
		if (str[i] == target)
			return (i);
		i++;
	}
	// ft_printf("Error 2, quote unclosed\n");
	return (0);
}

char	*handle_quotes(char * str, int i)
{
	char	*buf;
	int		end;
	int		y;

	end = quote_is_closed(str, i);
	if (end == 0)
		return (NULL);
	buf = malloc(sizeof(char) * (end - i + 1));
	if (!buf)
		return (NULL);
	y = 0;
	i++;
	while (str[i] && i < end)
		buf[y++] = str[i++];
	buf[y] = 0;
	return (buf);
}