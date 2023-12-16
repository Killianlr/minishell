/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_free.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fserpe <fserpe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:17:12 by flavian           #+#    #+#             */
/*   Updated: 2023/12/15 16:48:52 by fserpe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_cmd(t_arg *cmd)
{
	while (cmd->next)
	{
		for (int i = 0; cmd->line[i]; i++)
			printf("line = %s\n", cmd->line[i]);
		printf("sep = %s\n", cmd->sep);
		if (cmd->h_doc)
			printf("h_doc = %s\n", cmd->h_doc);
		cmd = cmd->next;
	}
	for (int y = 0; cmd->line[y]; y++)
		printf("line = %s\n", cmd->line[y]);
	printf("sep = %s\n", cmd->sep);
	if (cmd->h_doc)
		printf("h_doc = %s\n", cmd->h_doc);

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

void	free_parsing(t_arg *cmd)
{
	t_arg	*tmp;

	if (!cmd)
		return ;
	tmp = cmd->next;
	while (tmp)
	{
		free_pars_tab(cmd->line);
		free(cmd->sep);
		if (cmd->h_doc)
			free(cmd->h_doc);
		free(cmd);
		cmd = tmp;
		tmp = cmd->next;
	}
	free_pars_tab(cmd->line);
	free(cmd->sep);
	if (cmd->h_doc)
		free(cmd->h_doc);
	free(cmd);
}