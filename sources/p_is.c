/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_is.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:01:34 by flavian           #+#    #+#             */
/*   Updated: 2023/12/17 17:44:43 by flavian          ###   ########.fr       */
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
	if ((c != '\n' && c > 9 && c < 14) || c == ' ')
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

int	is_var_env(char c)
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
	char	*tmp;
	int		set;
	int		size;
	int		i;

	size = 0;
	set = 0;
	tmp = NULL;
	i = pars->i;
	while (pars->av[i] && is_whitespace(pars->av[i]))
		i++;
	if (pars->av[i] == '<' && pars->av[i + 1] == '<')
		i += 2;
	else
		return (0);
	while (pars->av[i])
	{
		if (set == is_quote(pars->av[i]) && set > 0)
		{
			set = 0;
			i++;
		}
		if (is_quote(pars->av[i]) && set == 0)
		{
			set = is_quote(pars->av[i]);
			tmp = handle_quotes(pars);
			size += (int) ft_strlen(tmp);
			i++;
			while (is_quote(pars->av[i]) && set > 0)
				i++;
		}
		if (is_whitespace(pars->av[i]))
			i++;
		if (is_printable(pars->av[i]) && !is_sep(pars->av[i])
			&& !is_quote(pars->av[i]))
		{
			size++;
			i++;
		}
		if (is_sep(pars->av[i]))
		{
			free(tmp);
			return (size);
		}
	}
	if (tmp)
		free(tmp);
	return (size);
}

char	*is_here_doc(t_pars *pars)
{
	char	*buf;
	char	*tmp;
	int		status;
	int		set;
	int		y;
	int		size;
	int		i;

	y = 0;
	set = 0;
	tmp = NULL;
	i = pars->i;
	status = is_quote(pars->av[i]);
	while (pars->av[i] && is_whitespace(pars->av[i]))
		i++;
	while (pars->av[i])
	{
		if (is_quote(pars->av[i]) && status == 0)
			status = is_quote(pars->av[i]);
		else if (is_quote(pars->av[i]) == status && status > 0)
			status = 0;
		else if (pars->av[i] == '<' && pars->av[i + 1] == '<' && status == 0)
		{
			set = 1;
			size = size_for_malloc_del(pars);
			buf = malloc(sizeof(char) * (size + 1));
			if (!buf)
				return (NULL);
			i += 2;
			while (pars->av[i] && is_whitespace(pars->av[i]) && pars->av[i + 1])
			{
				i++;
			}
			if (is_quote(pars->av[i]))
				return (handle_quotes(pars));
			while (is_printable(pars->av[i])
				&& !is_sep(pars->av[i]) && y < size)
			{
				if (is_quote(pars->av[i]))
				{
					tmp = handle_quotes(pars);
					buf = ms_strjoin(buf, tmp, 1);
					y += (int) ft_strlen(tmp);
					i += (int) ft_strlen(tmp);
					free(tmp);
				}
				buf[y++] = pars->av[i++];
			}
			if (!pars->av[i] || is_sep(pars->av[i])
				|| is_whitespace(pars->av[i]))
				break ;
		}
		i++;
	}
	if (set == 0)
		return (NULL);
	buf[y] = 0;
	return (buf);

}