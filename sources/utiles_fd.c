/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:05:12 by kle-rest          #+#    #+#             */
/*   Updated: 2024/01/15 14:48:27 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	close_files(t_exec *ex)
{
	int	i;
	int	o;

	i = ex->i;
	o = ex->o;
	if (ex->infile)
	{
		while (i >= 0)
		{
			close(ex->infile[i]);
			i--;
		}
	}
	if (ex->outfile)
	{
		while (o >= 0)
		{
			close(ex->outfile[o]);
			o--;
		}
	}
}

void	close_pipes(t_exec *ex)
{
	int	i;

	i = 0;
	while (i < (2 * ex->nb_pipe))
	{
		close(ex->pipex[i]);
		i++;
	}
}

void	test(t_gc *garbage)
{
	int	fd;

	fd = open(".tmpfile", O_CREAT | O_RDWR, 0000644);
	dup2(fd, STDIN_FILENO);
	close(fd);
	unlink(".tmpfile");
	garbage->rl = 0;
}

void	set_fd_pipe(t_exec *ex, t_gc *garbage)
{
	if (garbage->rl == 1)
	{
		test(garbage);
		return ;
	}
	if (ex->idx == 0)
	{
		if (ex->infile && ex->infile[ex->i] > 0)
			dup2(ex->infile[ex->i], STDIN_FILENO);
		dup2(ex->pipex[1], STDOUT_FILENO);
	}
	else if (ex->idx == ex->nb_pipe)
	{
		if (ex->outfile && ex->outfile[ex->o] > 0)
			dup2(ex->outfile[ex->o], STDOUT_FILENO);
		dup2(ex->pipex[2 * ex->idx - 2], STDIN_FILENO);
	}
	else
	{
		dup2(ex->pipex[2 * ex->idx - 2], STDIN_FILENO);
		dup2(ex->pipex[2 * ex->idx + 1], STDOUT_FILENO);
	}
	close_pipes(ex);
}

void	set_fd(t_exec *ex, t_gc *garbage)
{
	if (ex->p)
	{
		set_fd_pipe(ex, garbage);
		return ;
	}
	if (ex->infile && ex->infile[ex->i] > 0)
	{
		dup2(ex->infile[ex->i], STDIN_FILENO);
	}
	if (ex->outfile && ex->outfile[ex->o] > 0)
	{
		dup2(ex->outfile[ex->o], STDOUT_FILENO);
	}
}
