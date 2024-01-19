/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:37:05 by kle-rest          #+#    #+#             */
/*   Updated: 2024/01/19 15:59:42 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_tab(char **tableau)
{
	int	i;

	i = 0;
	if (!tableau)
		return ;
	if (tableau)
	{
		while (tableau[i])
		{
			free(tableau[i]);
			i++;
		}
	}
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
	free(garbage);
	close_standard_fd();
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
		{
			if (cmd->line)
				free_tab(cmd->line);
			if (cmd->hdoc)
				unlink(".heredoc_tmp");
			free(cmd);
		}
		cmd = cmd->next;
		tmp = cmd;
	}
	if (cmd)
	{
		if (cmd->line)
			free_tab(cmd->line);
		if (cmd->hdoc)
			unlink(".heredoc_tmp");
		free(cmd);
	}
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
