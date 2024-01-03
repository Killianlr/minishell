/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 11:18:21 by kle-rest          #+#    #+#             */
/*   Updated: 2024/01/03 15:56:19 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_tab(char **tableau)
{
	int	i;

	i = 0;
	while (tableau && tableau[i])
	{
		free(tableau[i]);
		i++;
	}
	free(tableau);
}

void	free_blts(t_bui *blts)
{
	free_tab(blts->env);
	free_tab(blts->exp);
	free(blts->pwd);
}

void	exit_error(t_gc *garbage)
{
	printf("debut free error\n");
	free_blts(garbage->blts);
	free(garbage->blts);
	free(garbage->line);
	free_parsing(garbage->arg);
	free(garbage);
	printf("fin free error\n");
	exit(0);
}

void	free_all(t_gc *garbage)
{
	printf("DEBUT DU FREE\n");
	if (!garbage)
		return ;
	free_parsing(garbage->arg);
	free_blts(garbage->blts);
	free(garbage->blts);
	free(garbage);
	printf("FIN DU PROGRAMME\n");
}
