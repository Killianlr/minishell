/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_to_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fserpe <fserpe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 13:54:57 by fserpe            #+#    #+#             */
/*   Updated: 2024/01/14 13:56:11 by fserpe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	set_sep_val(t_na *n_a, t_arg *arg, t_exec *ex)
{
	n_a->sep_val = check_sep_exec(arg->sep, ex);
	if (!n_a->sep_val)
		return (0);
	n_a->next_sep_val = check_sep_exec(arg->next->sep, ex);
	return (1);
}

int	init_open_to_free(t_exec *ex, t_arg *s_cmd, int typeofsep)
{
	if (typeofsep && typeofsep % 2 == 0)
	{
		ex->o++;
		ex->outfile[ex->o] = ft_open(s_cmd->line[0], typeofsep);
		if (ex->outfile[ex->o] == -1)
		{
			printf("error access file or open %s ", s_cmd->line[0]);
			return (0);
		}
	}
	else if (typeofsep && typeofsep % 2 == 1 && typeofsep != 5)
	{
		ex->i++;
		ex->infile[ex->i] = ft_open(s_cmd->line[0], typeofsep);
		if (ex->infile[ex->i] == -1)
		{
			printf("error access file or open %s\n", s_cmd->line[0]);
			return (0);
		}
	}
	return (1);
}

t_arg	*open_to_free(t_arg *to_free, t_exec *ex)
{
	t_arg	*tmp;
	t_arg	*first;
	int		type_of_sep;

	if (!to_free)
		return (NULL);
	first = to_free;
	tmp = to_free->next;
	type_of_sep = 0;
	while (tmp)
	{
		type_of_sep = check_sep_exec(to_free->sep, ex);
		if (!init_open_to_free(ex, to_free, type_of_sep))
			return (NULL);
		to_free = to_free->next;
		tmp = to_free;
	}
	return (first);
}
