/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_free.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:17:12 by flavian           #+#    #+#             */
/*   Updated: 2024/01/03 16:44:13 by kle-rest         ###   ########.fr       */
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
	// while (cmd->next)
	// {
	// 	while (cmd->line[i])
	// 		ft_printf("line = %s\n", cmd->line[i++]);
	// 	ft_printf("sep = %s\n", cmd->sep);
	// 	if (cmd->next)
	// 		cmd = cmd->next;
	// }
	// i = 0;
	// while (cmd->line[i])
	// 	ft_printf("line = %s\n", cmd->line[i++]);
	// ft_printf("sep = %s\n", cmd->sep);
}

void	free_pars_tab(char **arr)
{
	int	i;

	i = 0;
	if (!arr[i])
		return ;
	while (arr[i])
	{
		printf("arr[%d] %s\n", i, arr[i]);
		free(arr[i]);
		i++;
	}
	if (arr)
		free(arr);
	printf("---------H-------\n");
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
	printf("------A-----\n");
	printf("cmd->line[0] = %s\n", cmd->line[0]);
	while (tmp)
	{
	printf("tmp->line[0] = %s\n", tmp->line[0]);
		if (cmd->line)
			free_pars_tab(cmd->line);
	printf("------B-----\n");
		if (cmd->sep)
			free(cmd->sep);
	printf("------C-----\n");
		free(cmd);
	printf("------D-----\n");
		cmd = tmp;
		tmp = cmd->next;
	}
	if (cmd->line)
		free_pars_tab(cmd->line);
	printf("------E-----\n");
	if (cmd->sep)
		free(cmd->sep);
	printf("------F-----\n");
	free(cmd);
	printf("------G-----\n");
}
