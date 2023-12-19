/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_hdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fserpe <fserpe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 11:47:42 by flavian           #+#    #+#             */
/*   Updated: 2023/12/19 17:46:13 by fserpe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
			tmp = handle_quotes(pars, i);
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

char	*get_here_doc(char *av)
{
	int		doc;
	int		set;
	char	*buf;
	char	*ret;

	buf = NULL;
	ret = NULL;
	doc = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (doc < 0)
		return (NULL);
	set = 0;
	while (1)
	{
		write(1, "> ", 3);
		buf = get_next_line(0, 0);
		if (!buf)
			return (NULL);
		if (!ms_strcmp(av, buf, ft_strlen(av)))
		{
			free(buf);
			break ;
		}
		write(doc, buf, ft_strlen(buf));
		write(doc, "\n", 1);
		if (set == 0)
		{
			ret = ms_strjoin(ret, buf, 2);
			set = 1;
		}
		else if (set > 0)
			ret = ms_strjoin(ret, buf, 3);
	}
	get_next_line(0, 1);
	close(doc);
	// unlink(".heredoc_tmp");
	free(av);
	return (ret);
}

char	*handle_quotes_hdoc(t_pars *pars, int l)
{
	char	*buf;
	int		end;
	int		y;
	int		i;

	i = l;
	while (pars->av[i] && !is_quote(pars->av[i]))
		i++;
	end = quote_is_closed(pars, i);
	if (end == 0)
		return (NULL);
	buf = malloc(sizeof(char) * (end - i + 1));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	y = 0;
	if (is_quote(pars->av[i]))
	{
		i++;
		while (pars->av[i] && i < end)
			buf[y++] = pars->av[i++];
	}
	buf[y] = 0;
	return (buf);
}

int	size_for_del(t_pars *pars, int l)
{
	int		i;
	int		count;
	char	*quote;

	i = l;
	count = 0;
	quote = NULL;
	while (pars->av[i])
	{
		if ((is_whitespace(pars->av[i]) || is_sep(pars->av[i])))
			break ;
		else if (is_quote(pars->av[i]))
		{
			quote = handle_quotes_hdoc(pars, i);
			count += (int)ft_strlen(quote);
			free(quote);
			i = quote_is_closed(pars, i);
		}
		if (is_printable(pars->av[i]) && !is_quote(pars->av[i])
			&& !is_sep(pars->av[i]))
			count++;
		i++;
	}
	return (count);
}

char	*get_del_hdoc(t_pars *pars)
{
	int		i;
	int		y;
	char	*quote;
	int		size;
	char	*ret;

	i = pars->i;
	while (pars->av[i] && is_whitespace(pars->av[i]))
		i++;
	if (!pars->av[i])
		return (NULL);
	while (is_sep(pars->av[i]) || is_whitespace(pars->av[i]))
		i++;
	size = size_for_del(pars, i);
	quote = NULL;
	printf("size = %d\n", size);
	ret = malloc(sizeof(char) * (size + 1));
	if (!ret)
		return (NULL);
	ret[0] = 0;
	y = 0;
	while (pars->av[i] && y < size)
	{
		if (is_sep(pars->av[i]) || is_whitespace(pars->av[i]))
			break ;
		if (is_quote(pars->av[i]))
		{
			quote = handle_quotes(pars, i);
			if (!quote)
				return (NULL);
			if (!ms_strjoin_size(ret, quote, size))
				return (NULL);
			y = ft_strlen(ret);
			i = quote_is_closed(pars, i);
		}
		if (is_printable(pars->av[i]) && !is_sep(pars->av[i])
			&& !is_quote(pars->av[i]))
			ret[y++] = pars->av[i++];
	}
	ret[y] = 0;
	return (ret);
}
