/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fserpe <fserpe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:17:12 by flavian           #+#    #+#             */
/*   Updated: 2023/12/11 11:17:25 by fserpe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mspars.h"


void	print_cmd(t_cmd *cmd)
{
	while (cmd->next)
	{
		for (int i = 0; cmd->line[i]; i++)
			printf("line = %s\n", cmd->line[i]);
		printf("sep = %s\n", cmd->sep);
		
		cmd = cmd->next;
	}
	for (int y = 0; cmd->line[y]; y++)
		printf("line = %s\n", cmd->line[y]);
	printf("sep = %s\n", cmd->sep);
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

void	free_parsing(t_cmd *cmd)
{
	t_cmd	*tmp;


	if (!cmd)
		return ;
	tmp = cmd->next;
	while (tmp)
	{
		free_pars_tab(cmd->line);
		free(cmd->sep);
		free(cmd);
		cmd = tmp;
		tmp = cmd->next;
	}
	free_pars_tab(cmd->line);
	free(cmd->sep);
	free(cmd);
}