/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_hdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fserpe <fserpe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 14:33:41 by fserpe            #+#    #+#             */
/*   Updated: 2024/01/19 16:37:01 by fserpe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_fd(t_cmd *cmd)
{
	if (cmd->fd_in < 0 || cmd->fd_out < 0)
		return (0);
	return (1);
}

int	end_quote(char *str, int l)
{
	int		target;
	int		i;

	target = 0;
	i = l;
	if (count_quote(str) % 2 != 0)
		return (ft_error("Error 1, quote unclosed", 0));
	else
	{
		while (str[i])
		{
			if (target == 0 && is_quote(str[i]) > 0)
				target = is_quote(str[i]);
			else if (target > 0 && target == is_quote(str[i]))
				return (i);
			i++;
		}
	}
	return (0);
}

int	get_here_doc_2(char *av, int fd, char *buf)
{
	while (1)
	{
		write(1, "> ", 3);
		buf = get_next_line(0, 0);
		if (!buf)
		{
			printf("Minishell: warning: here-document delimited ");
			printf("by end-of-file (wanted `%s')\n", av);
			break ;
		}
		if (!ms_strcmp(av, buf, ft_strlen(av)))
		{
			free(buf);
			break ;
		}
		write(fd, buf, ft_strlen(buf));
		free(buf);
	}
	close(fd);
	return (fd);
}

int	get_here_doc(char *av, int fd, t_cmd *cmd)
{
	char	*buf;

	buf = NULL;
	if (!cmd->hdoc)
		fd = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	else
	{
		printf("LA\n");
		unlink(".heredoc_tmp");
		fd = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0000644);
		return (get_here_doc_2(av, fd, buf));
	}
	if (fd < 0)
		return (0);
	return (get_here_doc_2(av, fd, buf));
}
