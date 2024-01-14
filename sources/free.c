/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 11:18:21 by kle-rest          #+#    #+#             */
/*   Updated: 2024/01/14 18:50:17 by kle-rest         ###   ########.fr       */
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
	close_files(ex);
	if (ex->outfile)
		free(ex->outfile);
	if (ex->infile)
		free(ex->infile);
	if (ex->pipex)
		free(ex->pipex);
	unlink(".heredoc_tmp");
}

void	free_blts(t_bui *blts)
{
	free_tab(blts->env);
	free_tab(blts->exp);
	free(blts->pwd);
}

void	exit_error(t_gc *garbage)
{
	free_blts(garbage->blts);
	free(garbage->blts);
	free(garbage->line);
	free_parsing(garbage->arg);
	free(garbage);
	exit(0);
}

void	free_all(t_gc *garbage)
{
	if (!garbage)
		return ;
	free_parsing(garbage->arg);
	free_blts(garbage->blts);
	free(garbage->blts);
	if (garbage->fd_hdoc)
		unlink(".heredoc_tmp");
	free(garbage);
}
