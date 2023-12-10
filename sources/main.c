/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 15:01:37 by flavian           #+#    #+#             */
/*   Updated: 2023/12/10 11:44:22 by flavian          ###   ########.fr       */
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

void	free_all(t_cmd *cmd)
{
	t_cmd	*tmp;


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
	t_cmd	*cmd;
	
	if (ac <= 1)
		return (0);
	cmd = NULL;
	cmd = parsing(av[1]);
	if (!cmd)
		printf("Error in parsing\n");
	print_cmd(cmd);
	free_parsing(cmd);
	return (1);
}