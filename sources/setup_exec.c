/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:53:41 by kle-rest          #+#    #+#             */
/*   Updated: 2024/01/14 18:44:11 by kle-rest         ###   ########.fr       */
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

int	init_t_exec(t_exec *ex, t_arg *s_cmd, t_gc *garbage)
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
	if (ex->nb_pipe)
	{
		ex->pipex = malloc(sizeof(int) * (2 * ex->nb_pipe));
		if (!ex->pipex)
			return (1);
		if (get_pipes(ex))
			return (1);
	}
	ex->paths = ft_split(find_path(garbage->blts->env), ':');
	ex->res_pipex = -1;
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
	if (typeofsep == 5)
	{
		ex->p = 1;
		ex->idx++;
		//set_pipex(s_cmd, garbage, ex);
	}
	else if (check_sep_exec(s_cmd->prev_sep, ex) == 5)
	{
		ex->p = 1;
		ex->idx++;
	}
	else
		ex->idx = -1;
	if (s_cmd->line[0] && check)
	{
		// printf("go for exec\n");
		ft_exec(s_cmd, ex->paths, garbage, ex);
	}
	else
		close_files(ex);
}

// void	ft_init_exec(t_arg *s_cmd, t_gc *garbage, t_exec *ex)
// {
// 	int	typeofsep;
// 	int	check;
// 	int	chiant;

// 	typeofsep = 0;
// 	check = garbage->go;
// 	printf("s_cmd->line[0] = %s\n", s_cmd->line[0]);
// 	if (!s_cmd)
// 		return ;
// 	typeofsep = check_sep_exec(s_cmd->sep, ex);
// 	chiant = check_redir_file(s_cmd, typeofsep, ex, garbage);
// 	while (chiant > 0)
// 	{
// 		if (chiant == 2)
// 			return ;
// 		s_cmd = s_cmd->next;
// 		garbage->nb_exec--;
// 		chiant = check_redir_file(s_cmd, typeofsep, ex, garbage);
// 	}
// 	if (init_open(ex, s_cmd, typeofsep, garbage))
// 	{
// 		garbage->go = 0;
// 		return ;
// 	}
// 	if (typeofsep == 5)
// 	{
// 		set_pipex(s_cmd, garbage, ex);
// 		return ;
// 	}
// 	if (s_cmd->line[0] && check)
// 		ft_exec(s_cmd, ex->paths, garbage, ex);
// 	else
// 		close_files(ex);
// }
