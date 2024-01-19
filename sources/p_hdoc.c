/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_hdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 14:33:41 by fserpe            #+#    #+#             */
/*   Updated: 2024/01/19 15:50:55 by kle-rest         ###   ########.fr       */
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