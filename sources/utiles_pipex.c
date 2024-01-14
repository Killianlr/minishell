/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles_pipex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 15:01:29 by kle-rest          #+#    #+#             */
/*   Updated: 2024/01/14 11:12:26 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/pipex.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int	init_open_2(t_exec *ex, t_arg *s_cmd, int typeofsep, t_gc *garbage)
{
	if (typeofsep && typeofsep % 2 == 0)
	{
		ex->o++;
		ex->outfile[ex->o] = ft_open(s_cmd->line[0], typeofsep);
		if (ex->outfile[ex->o] == -1)
		{
			printf("error access file or open %s ", s_cmd->next->line[0]);
			return (1);
		}
		if (s_cmd->line[1])
			reset_line(s_cmd->next->line, garbage);
	}
	if (typeofsep && typeofsep % 2 == 1 && typeofsep != 5)
	{
		ex->i++;
		ex->infile[ex->i] = ft_open(s_cmd->line[0], typeofsep);
		if (ex->infile[ex->i] == -1)
		{
			printf("error access file or open %s\n", s_cmd->next->line[0]);
			return (1);
		}
		if (s_cmd->line[1])
			reset_line(s_cmd->next->line, garbage);
	}
	return (0);
}

void	end_of_pipex(t_arg *s_cmd, t_gc *garbage, t_exec *ex)
{
	int	typeofsep;
	int	pid;

	pid = fork();
	if (!pid)
	{
		typeofsep = check_sep_exec(s_cmd->prev_sep, ex);
		if (ft_strncmp(s_cmd->prev_sep, "|", 2))
		{
			if (init_open_2(ex, s_cmd, typeofsep, garbage))
			{
				garbage->go = 0;
				return ;
			}
			set_fd(ex);
			put_respipex(ex);
		}
		else
			put_respipex(ex);
		close_standard_fd();
		exit(0);
	}
	else
		waitpid(pid, NULL, 0);
}

void	set_pipex(t_arg *s_cmd, t_gc *garbage, t_exec *ex)
{
	int	i;

	i = 0;
	ex->r = 0;
	printf("SET_PIPEX\n");
	i = init_pipex(ex, s_cmd, garbage);
	if (i < 0)
		return ;
	while (i-- && s_cmd->next)
	{
		s_cmd = s_cmd->next;
		garbage->nb_exec--;
	}
	ex->r = 1;
	end_of_pipex(s_cmd, garbage, ex);
	return ;
}
