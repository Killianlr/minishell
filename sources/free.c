/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 11:18:21 by kle-rest          #+#    #+#             */
/*   Updated: 2024/01/05 17:46:49 by flavian          ###   ########.fr       */
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

void	free_t_exec(t_exec *ex)
{
	int	i;

	i = 0;
	(void) i;
	free_tab(ex->paths);
	if (ex->outfile)
		free(ex->outfile);
	if (ex->infile)
		free(ex->infile);
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
	// printf("DEBUT DU FREE\n");
	if (!garbage)
		return ;
	free_parsing(garbage->arg);
	free_blts(garbage->blts);
	free(garbage->blts);
	free(garbage);
	// printf("FIN DU PROGRAMME\n");
}
