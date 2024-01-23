/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:37:05 by kle-rest          #+#    #+#             */
/*   Updated: 2024/01/23 12:52:07 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	if (tableau)
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
	get_next_line(0, 1);
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

void	ms_strjoin_free(char *s1, char *s2, int status)
{
	if (status == 1)
		free(s1);
	else if (status == 2)
		free(s2);
	else if (status == 3)
	{
		free(s1);
		free(s2);
	}
}
