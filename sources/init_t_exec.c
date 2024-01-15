/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_t_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:07:33 by kle-rest          #+#    #+#             */
/*   Updated: 2024/01/15 14:08:03 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_pipe(t_arg *s_cmd, char *sep)
{
	int	i;

	i = 0;
	while (s_cmd->next)
	{
		if (!ft_strncmp(s_cmd->sep, sep, 2))
			i++;
		s_cmd = s_cmd->next;
	}
	return (i);
}

int	get_pipes(t_exec *ex)
{
	int	i;

	i = 0;
	if (!ex->nb_pipe)
		return (0);
	while (i < ex->nb_pipe)
	{
		if (pipe(ex->pipex + 2 * i) < 0)
			return (1);
		i++;
	}
	return (0);
}

int	init_t_exec_2(t_exec *ex, t_arg *s_cmd, t_gc *garbage)
{
	ex->i = -1;
	ex->o = -1;
	ex->r = 0;
	ex->p = 0;
	ex->idx = -1;
	ex->pipex = NULL;
	ex->nb_pipe = count_pipe(s_cmd, "|");
	ex->infile = NULL;
	ex->outfile = NULL;
	ex->paths = ft_split(find_path(garbage->blts->env), ':');
	if (!ex->paths)
		return (1);
	if (ex->nb_pipe)
	{
		ex->pipex = malloc(sizeof(int) * (2 * ex->nb_pipe));
		if (!ex->pipex)
			return (1);
		if (get_pipes(ex))
			return (1);
	}
	return (0);
}

int	init_t_exec(t_exec *ex, t_arg *s_cmd, t_gc *garbage)
{
	if (init_t_exec_2(ex, s_cmd, garbage))
		return (1);
	if (count_sep_exec(s_cmd, "<", "<<"))
	{
		ex->infile = malloc(sizeof(int) * count_sep_exec(s_cmd, "<", "<<"));
		if (!ex->infile)
			return (1);
		ex->infile[0] = -1;
	}
	if (count_sep_exec(s_cmd, ">", ">>"))
	{
		ex->outfile = malloc(sizeof(int) * count_sep_exec(s_cmd, ">", ">>"));
		if (!ex->outfile)
			return (1);
		ex->outfile[0] = -1;
	}
	s_cmd = new_arg(ex, s_cmd);
	return (0);
}
