/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:19:59 by kle-rest          #+#    #+#             */
/*   Updated: 2024/01/19 15:23:37 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_fd(s_cmd *cmd)
{
	if (cmd->fd_in)
	{
		dup2(cmd->fd_in, STDIN_FILENO);
		close(cmd->fd_in);
	}
	if (cmd->fd_out)
	{
		dup2(cmd->fd_out, STDOUT_FILENO);
		close(cmd->fd_out);
	}
}

void	wait_child_status(t_gc *garbage, int pid, int status)
{
	waitpid(pid, &status, 0);
	if (WTERMSIG(status) == 3)
		garbage->ret = 131;
	else if (WTERMSIG(status) == 2)
		garbage->ret = 130;
	else
		garbage->ret = WEXITSTATUS(status);
}

int	ft_lstsize_cmd(s_cmd *lst)
{
	s_cmd	*tmp;
	int		size;

	size = 0;
	if (!lst)
		return (0);
	tmp = lst->next;
	while (tmp)
	{
		lst = lst->next;
		tmp = lst;
		size++;
	}
	if (lst)
		size++;
	return (size);
}
