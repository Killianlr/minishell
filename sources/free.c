/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fserpe <fserpe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:37:05 by kle-rest          #+#    #+#             */
/*   Updated: 2024/01/19 16:54:34 by fserpe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_tab(char **tableau)
{
	int	i;

	i = 0;
	if (!tableau)
		return ;
	if (tableau)
	{
		while (tableau[i])
		{
			free(tableau[i]);
			i++;
		}
	}
	free(tableau);
}

void	free_blts(t_bui *blts)
{
	free_tab(blts->env);
	free_tab(blts->exp);
	free(blts->pwd);
}

void	free_all(t_gc *garbage)
{
	if (!garbage)
		return ;
	if (garbage->s_cmd)
		free_cmd(garbage->s_cmd);
	free_blts(garbage->blts);
	free(garbage->blts);
	free(garbage);
	close_standard_fd();
}

void	close_standard_fd(void)
{
	close(0);
	close(1);
	close(2);
}
