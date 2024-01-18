/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:37:05 by kle-rest          #+#    #+#             */
/*   Updated: 2024/01/18 23:37:18 by flavian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_tab(char **tableau)
{
	int	i;

	i = 0;
	if (!tableau)
		return ;
	printf(" in free_tab\n");
	if (tableau)
	{
		while (tableau[i])
		{
			printf("here\n");
			free(tableau[i]);
			i++;
		}
	}
	printf("out of free_tab\n");
	free(tableau);
}

void	free_blts(t_bui *blts)
{
	free_tab(blts->env);
	free_tab(blts->exp);
	free(blts->pwd);
}

void	free_all(t_gc *garbage)
{
	if (!garbage)
		return ;
	if (garbage->s_cmd)
		free_cmd(garbage->s_cmd);
	free_blts(garbage->blts);
	free(garbage->blts);
	// if (garbage->fd_hdoc)
	// 	unlink(".heredoc_tmp");
	free(garbage);
	close_standard_fd();
}

void	free_cmd(s_cmd *cmd)
{
	s_cmd *tmp;

	if (!cmd)
		return ;
	tmp = cmd->next;
	while (tmp)
	{
		if (cmd->line)
			free_tab(cmd->line);
		free(cmd);
		cmd = cmd->next;
		tmp = cmd;
	}
	if (cmd->line)
		free_tab(cmd->line);
	free(cmd);
}

void	exit_free(t_gc *garbage, int exival)
{
	free_all(garbage);
	exit(exival);
}

void	exit_child(t_gc *garbage, int exival)
{
	free_all(garbage);
	exit(exival);
}

void	close_standard_fd(void)
{
	close(0);
	close(1);
	close(2);
}