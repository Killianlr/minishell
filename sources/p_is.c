/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_is.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:01:34 by flavian           #+#    #+#             */
/*   Updated: 2023/12/14 18:43:30 by flavian          ###   ########.fr       */
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

int	size_for_malloc_del(t_pars *pars)
{
	int	size;

	size = 0;
	if (pars->av[pars->i] == '<' && pars->av[pars->i + 1] == '<')
		pars->i += 2;
	else
		return (0);
	while (pars->av[pars->i])
	{
		if (is_whitespace(pars->av[pars->i]))
			pars->i++;
		if (is_printable(pars->av[pars->i]) && !is_sep(pars->av[pars->i]))
		{
			size++;
			pars->i++;
		}
		if (is_sep(pars->av[pars->i]))
			return (size);
	}
	return (size);
}

char	*is_here_doc(t_pars *pars)
{
	char	*buf;
	int	status;
	int	set;
	int y;
	int	size;
	
	y = 0;
	set = 0;
	status = is_quote(pars->av[pars->i]);
	while (pars->av[pars->i])
	{
		if (is_quote(pars->av[pars->i]) && status == 0)
			status = is_quote(pars->av[pars->i]);
		else if (is_quote(pars->av[pars->i]) == status && status > 0)
			status = 0;
		else if (pars->av[pars->i] == '<' && pars->av[pars->i + 1] == '<' && status == 0)
		{
			set = 1;
			size = size_for_malloc_del(pars);
			buf = malloc(sizeof(char) * (size + 1));
			if (!buf)
				return (NULL);
			pars->i += 2;
			while (is_whitespace(pars->av[pars->i]) && pars->av[pars->i + 1])
				pars->i++;
			if (is_quote(pars->av[pars->i]))
				return (handle_quotes(pars));
			while (is_printable(pars->av[pars->i]) && !is_sep(pars->av[pars->i]) && y < size)
				buf[y++] = pars->av[pars->i++];
			if (!pars->av[pars->i] || is_sep(pars->av[pars->i]) || is_whitespace(pars->av[pars->i]))
				break ;
		}
		pars->i++;
	}
	if (set == 0)
		return (NULL);
	buf[y] = 0;
	return (buf);
}