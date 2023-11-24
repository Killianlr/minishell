/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 15:01:37 by flavian           #+#    #+#             */
/*   Updated: 2023/11/24 14:55:38 by flavian          ###   ########.fr       */
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
	free(tab[i]);
}

void	free_all(s_cmd *cmd)
{
	s_cmd	*tmp;

	tmp = cmd;
	while (tmp)
	{
		free_tab(tmp->line);
		free(tmp);
		tmp = cmd->next;
		cmd = cmd->next;
	}
}

int	main(int ac, char **av)
{
	s_cmd	*cmd;
	
	if (ac <= 1)
		return (0);
	cmd = NULL;
	cmd = parsing(av[1]);
	printf("LA\n");
	printf("cmd = %s\n", cmd->line[0]);
	free_all(cmd);
	return (1);
}