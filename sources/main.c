/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 15:01:37 by flavian           #+#    #+#             */
/*   Updated: 2023/11/28 13:34:11 by flavian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_all(s_cmd *cmd)
{
	s_cmd	*tmp;


	if (!cmd)
		return ;
	tmp = cmd->next;
	while (tmp)
	{
		free_tab(cmd->line);
		free(cmd);
		cmd = tmp;
		tmp = cmd->next;
	}
	free_tab(cmd->line);
		free(cmd);
}

int	main(int ac, char **av)
{
	s_cmd	*cmd;
	
	if (ac <= 1)
		return (0);
	cmd = NULL;
	cmd = parsing(av[1]);
	free_all(cmd);
	return (1);
}