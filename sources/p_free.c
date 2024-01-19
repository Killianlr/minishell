/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_free.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fserpe <fserpe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 16:19:12 by fserpe            #+#    #+#             */
/*   Updated: 2024/01/19 16:53:09 by fserpe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void	print_cmd(t_cmd *cmd)
// {
// 	t_cmd	*tmp;

// 	if (!cmd)
// 		return ;
// 	tmp = cmd->next;
// 	while (tmp)
// 	{
// 		if (cmd->line)
// 		{
// 			for (int i = 0; cmd->line[i]; i++)
// 				printf("line[i] = %s[%i]\n", cmd->line[i], i);			
// 		}
// 		cmd = cmd->next;
// 		tmp = cmd;
// 	}
// 	if (cmd)
// 	{
// 		if (cmd->line)
// 		{
// 			for (int i = 0; cmd->line[i]; i++)
// 				printf("line[i] = %s[%i]\n", cmd->line[i], i);			
// 		}
// 	}
// }

void	free_cmd_2(t_cmd *cmd)
{
	if (cmd->line)
		free_tab(cmd->line);
	if (cmd->hdoc)
		unlink(".heredoc_tmp");
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

	tmp = cmd->next;
	first = cmd;
	while (tmp)
	{
		if (cmd->hdoc)
			open(".heredoc_tmp", O_RDONLY);
		cmd = cmd->next;
		tmp = cmd;
	}
	if (cmd)
	{
		if (cmd->hdoc)
			open(".heredoc_tmp", O_RDONLY);
	}
	free(pars->av);
	free(pars);
	return (first);
}

int	ft_error(char *msg, int ret)
{
	if (msg)
		ft_printf("%s\n", msg);
	return (ret);
}
