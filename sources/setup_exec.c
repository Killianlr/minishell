/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:53:41 by kle-rest          #+#    #+#             */
/*   Updated: 2024/01/15 14:42:36 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_sep_exec(char *sep, t_exec *ex)
{
	(void)ex;
	if (!sep)
		return (0);
	if (!ft_strncmp(sep, "<", 2))
		return (1);
	if (!ft_strncmp(sep, ">", 2))
		return (2);
	if (!ft_strncmp(sep, "<<", 3))
		return (3);
	if (!ft_strncmp(sep, ">>", 3))
		return (4);
	return (5);
}

int	init_open(t_exec *ex, t_arg *s_cmd, int typeofsep, t_gc *garbage)
{
	if (typeofsep && typeofsep % 2 == 0)
	{
		ex->o++;
		ex->outfile[ex->o] = ft_open(s_cmd->next->line[0], typeofsep);
		if (ex->outfile[ex->o] == -1)
		{
			printf("error access file or open %s ", s_cmd->next->line[0]);
			return (1);
		}
		reset_line(s_cmd->next->line, garbage);
	}
	if (typeofsep && typeofsep % 2 == 1 && typeofsep != 5)
	{
		ex->i++;
		ex->infile[ex->i] = ft_open(s_cmd->next->line[0], typeofsep);
		if (ex->infile[ex->i] == -1)
		{
			printf("error access file or open %s\n", s_cmd->next->line[0]);
			return (1);
		}
		reset_line(s_cmd->next->line, garbage);
	}
	return (0);
}

void	check_for_pipex(int typeofsep, t_exec *ex, t_arg *s_cmd)
{
	(void)s_cmd;
	if (typeofsep == 5)
	{
		ex->p = 1;
		ex->idx++;
	}
	else if (check_sep_exec(s_cmd->prev_sep, ex) == 5)
	{
		ex->p = 1;
		ex->idx++;
	}
	else
		ex->idx = -1;
}

void	ft_init_exec(t_arg *s_cmd, t_gc *garbage, t_exec *ex)
{
	int	typeofsep;
	int	check;

	typeofsep = 0;
	check = garbage->go;
	ex->p = 0;
	if (!s_cmd)
		return ;
	typeofsep = check_sep_exec(s_cmd->sep, ex);
	if (init_open(ex, s_cmd, typeofsep, garbage))
	{
		garbage->go = 0;
		return ;
	}
	check_for_pipex(typeofsep, ex, s_cmd);
	if (s_cmd->line[0] && check)
		ft_exec(s_cmd, ex->paths, garbage, ex);
	else
		close_files(ex);
}
