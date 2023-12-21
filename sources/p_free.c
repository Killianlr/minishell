/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_free.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fserpe <fserpe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:17:12 by flavian           #+#    #+#             */
/*   Updated: 2023/12/21 11:19:42 by fserpe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_cmd(t_arg *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return ;
// 	while (cmd->next)
// 	{
// 		while (cmd->line[i])
// 			ft_printf("line = %s\n", cmd->line[i++]);
// 		ft_printf("sep = %s\n", cmd->sep);
// 		if (cmd->next)
// 			cmd = cmd->next;
// 	}
// 	i = 0;
// 	while (cmd->line[i])
// 		ft_printf("line = %s\n", cmd->line[i++]);
// 	ft_printf("sep = %s\n", cmd->sep);
}

void	free_pars_tab(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	ft_error(char *msg, int ret)
{
	if (msg)
		ft_printf("%s\n", msg);
	return (ret);
}

void	free_parsing(t_arg *cmd)
{
	t_arg	*tmp;

	if (!cmd)
		return ;
	tmp = cmd->next;
	while (tmp)
	{
		if (cmd->line)
			free_pars_tab(cmd->line);
		if (cmd->sep)
			free(cmd->sep);
		free(cmd);
		cmd = tmp;
		tmp = cmd->next;
	}
	if (cmd->line)
		free_pars_tab(cmd->line);
	if (cmd->sep)
		free(cmd->sep);
	free(cmd);
}
