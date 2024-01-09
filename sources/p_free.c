/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_free.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:17:12 by flavian           #+#    #+#             */
/*   Updated: 2024/01/09 14:07:21 by kle-rest         ###   ########.fr       */
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
}

void	free_pars_tab(char **arr)
{
	int	i;

	i = 0;
	if (!arr[i])
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	if (arr)
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
