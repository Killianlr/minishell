/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_hdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 17:35:39 by flavian           #+#    #+#             */
/*   Updated: 2023/12/20 23:31:11 by flavian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int	get_here_doc_2(char *av, int fd, char *buf)
{
	while (1)
	{
		write(1, "> ", 3);
		buf = get_next_line(0, 0);
		if (!buf)
			return (-1);
		if (!ms_strcmp(av, buf, ft_strlen(av)))
		{
			free(buf);
			break ;
		}
		write(fd, buf, ft_strlen(buf));
		write(fd, "\n", 1);
		free(buf);
	}
	free(av);
	return (fd);
}

int	get_here_doc(char *av, int fd)
{
	char	*buf;

	buf = NULL;
	if (fd <= 0)
		fd = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	else
	{
		close(fd);
		unlink(".heredoc_tmp");
		fd = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0000644);;
	}
	if (fd < 0)
		return (0);
	return (get_here_doc_2(av, fd, buf));
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

int		scan_av_for_hdoc(t_pars *pars, int fd_hdoc)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(pars->av);
	while (pars->av[i])
	{
		if (is_sep(pars->av[i]) == 1 && len - (i + 4) > 0)
		{
			if (is_sep(pars->av[i + 1]) == 2
				&& is_sep(pars->av[i + 2]) == 2 && !is_sep(pars->av[i + 3]))
			{
				fd_hdoc = get_here_doc(get_del_hdoc(pars, i), fd_hdoc);
				return (fd_hdoc);
			}
		}
		else if (is_sep(pars->av[i]) == 2 && len - (i + 3) > 0)
		{
			if (is_sep(pars->av[i + 1]) == 2 && !is_sep(pars->av[i + 2]))
			{
				fd_hdoc = get_here_doc(get_del_hdoc(pars, i), fd_hdoc);
				return (fd_hdoc);
			}
		}
		i++;
	}
	return (fd_hdoc);
}
