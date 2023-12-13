/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_is.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fserpe <fserpe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:01:34 by flavian           #+#    #+#             */
/*   Updated: 2023/12/13 14:03:33 by fserpe           ###   ########.fr       */
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
	if (c == '<' || c == '>' || c == '|') 
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
	int	status;
	int	set;
	int	i;
	int y;
	

	i = 0;
	y = 0;
	set = 0;
	status = is_quote(str[i]);
	while (str[i])
	{
			printf("status = %d\n", status);
		if (is_quote(str[i]) && status == 0)
			status = is_quote(str[i]);
		else if (is_quote(str[i]) == status && status > 0)
			status = 0;
		else if (str[i] == '<' && str[i + 1] == '<' && status == 0)
		{
			set = 1;
			buf = malloc(sizeof(char) * (ft_strlen(str) - (i + 1) + 2));
			if (!buf)
				return (NULL);
			i += 2;
			if (is_whitespace(str[i]) && str[i + 1])
				i++;
			while (is_printable(str[i]))
				buf[y++] = str[i++];
			if (!str[i])
				break ;
		}
		i++;
	}
	printf("i in  ishdoc = %d\n", i);
	if (set == 0)
		return (NULL);
	buf[y] = 0;
	return (buf);
}