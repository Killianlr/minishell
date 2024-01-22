/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_free.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fserpe <fserpe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 16:19:12 by fserpe            #+#    #+#             */
/*   Updated: 2024/01/22 19:20:34 by fserpe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_cmd_2(t_cmd *cmd)
{
	if (cmd->line)
	{
		free_tab(cmd->line);
	}
	if (cmd->hdoc)
		unlink(".heredoc_tmp");
	if (cmd->fd_in > 0)
	{
		close(cmd->fd_in);
	}
	if (cmd->fd_out > 0)
		close(cmd->fd_out);
	free(cmd);
}

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	if (!cmd)
		return ;
	tmp = cmd->next;
	while (tmp)
	{
		if (cmd)
			free_cmd_2(cmd);
		cmd = tmp;
		tmp = cmd->next;
	}
	if (cmd)
		free_cmd_2(cmd);
}

t_cmd	*end_of_pars(t_pars *pars, t_cmd *cmd)
{
	t_cmd	*tmp;
	t_cmd	*first;

	free(pars->av);
	free(pars);
	if (!cmd)
		return (NULL);
	tmp = cmd->next;
	first = cmd;
	while (tmp)
	{
		if (cmd->hdoc)
			cmd->fd_in = open(".heredoc_tmp", O_RDONLY);
		cmd = cmd->next;
		tmp = cmd;
	}
	if (cmd)
	{
		if (cmd->hdoc)
		{
			cmd->fd_in = open(".heredoc_tmp", O_RDONLY);
		}
	}
	return (first);
}

int	ft_error(char *msg, int ret)
{
	if (msg)
		ft_printf("%s\n", msg);
	return (ret);
}
