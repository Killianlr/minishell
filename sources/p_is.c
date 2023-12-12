/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_is.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:01:34 by flavian           #+#    #+#             */
/*   Updated: 2023/12/12 16:23:50 by flavian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int	is_printable(char c)
{
	if (c > 32 && c < 127)
		return (1);
	else
		return (0);
}

int	is_whitespace(char c)
{

	if ((c != '\n' && c > 9 && c < 14 )|| c == ' ')
		return (1);
	else
		return (0);
}

int	is_sep(char c)
{
	if (!c)
		return (0);
	if (c == '<' || c == '>' || c == '|' || c == '\n') 
		return (1);
	return (0);
}

int	is_$(char c)
{
	if (!c)
		return (0);
	if (c == '$') 
		return (1);
	return (0);
}

int	is_quote(char c)
{
	if (!c)
		return (0);
	else if (c == 39)
		return (1);
	else if (c == 34)
		return (2);
	return (0);
}

char	*is_here_doc(char *str)
{
	char	*buf;
	int	i;
	int y;
	

	i = 0;
	y = 0;
	while (str[i])
	{
		if (str[i] == '<' && str[i + 1] == '<')
		{
			buf = malloc(sizeof(char) * (ft_strlen(str) - (i + 1) + 2));
			if (!buf)
				return (NULL);
			// buf[0] = 0;
			i += 2;
			while (str[i])
			{
				if (is_whitespace(str[i]) && str[i + 1])
					i++;
				if (is_printable(str[i]))
					buf[y++] = str[i++];
			}
		}
		i++;
	}
	buf[y] = 0;
	return (buf);
}