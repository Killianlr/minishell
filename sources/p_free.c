/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_free.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:17:12 by flavian           #+#    #+#             */
/*   Updated: 2024/01/06 20:05:45 by flavian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_cmd(t_arg *cmd)
{
	int	i;

	i = 0;
	(void) i;
	if (!cmd)
		return ;
	while (cmd->next)
	{
		i = 0;
		while (cmd->line[i])
			ft_printf("line = %s\n", cmd->line[i++]);
		ft_printf("sep = %s\n", cmd->sep);
		ft_printf("prev_sep = %s\n====================================\n", cmd->prev_sep);
		if (cmd->next)
			cmd = cmd->next;
	}
	i = 0;
	while (cmd->line[i])
		ft_printf("line = %s\n", cmd->line[i++]);
	ft_printf("sep = %s\n", cmd->sep);
	ft_printf("prev_sep = %s\n====================================\n", cmd->prev_sep);
}

void	free_pars_tab(char **arr)
{
	int	i;

	i = 0;
	if (!arr[i])
		return ;
	while (arr[i])
	{
		// printf("arr[%d] %s\n", i, arr[i]);
		free(arr[i]);
		i++;
	}
	if (arr)
		free(arr);
	// printf("---------H-------\n");
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
		if (cmd->prev_sep)
			free(cmd->prev_sep);
		free(cmd);
		cmd = tmp;
		tmp = cmd->next;
	}
	if (cmd->line)
		free_pars_tab(cmd->line);
	if (cmd->sep)
		free(cmd->sep);
	if (cmd->prev_sep)
		free(cmd->prev_sep);
	free(cmd);
}
