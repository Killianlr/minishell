/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_hdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fserpe <fserpe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 17:35:39 by flavian           #+#    #+#             */
/*   Updated: 2024/01/12 15:36:05 by fserpe           ###   ########.fr       */
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
		{
			printf("Minishell: warning: here-document delimited by end-of-file (wanted `%s')\n", av);
			break ;
		}
		if (!ms_strcmp(av, buf, ft_strlen(av)))
		{
			free(buf);
			// free(buf);
			break ;
		}
		write(fd, buf, ft_strlen(buf));
		free(buf);
	}
	free(av);
	close(fd);
	return (1);
}

int	get_here_doc(char *av, int fd)
{
	char	*buf;

	buf = NULL;
	if (fd <= 0)
		fd = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	else
	{
		unlink(".heredoc_tmp");
		fd = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0000644);
		return (get_here_doc_2(av, fd, buf));
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

int	scan_av_for_hdoc_2(t_pars *pars, int fd_hdoc, int i)
{
	if (is_sep(pars->av[i + 1]) == 2 && !is_sep(pars->av[i + 2]))
	{
		fd_hdoc = get_here_doc(get_del_hdoc(pars, i), fd_hdoc);
		return (fd_hdoc);
	}
	return (fd_hdoc);
}

int	scan_av_for_hdoc(t_pars *pars, int fd_hdoc)
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
			fd_hdoc = scan_av_for_hdoc_2(pars, fd_hdoc, i);
		i++;
	}
	if (fd_hdoc)
		get_next_line(0, 1);
	return (fd_hdoc);
}
