/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 19:58:02 by flavian           #+#    #+#             */
/*   Updated: 2024/01/14 09:51:55 by flavian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	init_open_new_arg(t_exec *ex, t_arg *s_cmd, int typeofsep)
{
	if (typeofsep && typeofsep % 2 == 0)
	{
		ex->o++;
		ex->outfile[ex->o] = ft_open(s_cmd->next->line[0], typeofsep);
		if (ex->outfile[ex->o] == -1)
		{
			printf("error access file or open %s ", s_cmd->next->line[0]);
			return (0);
		}
	}
	else if (typeofsep && typeofsep % 2 == 1 && typeofsep != 5)
	{
		ex->i++;
		ex->infile[ex->i] = ft_open(s_cmd->next->line[0], typeofsep);
		if (ex->infile[ex->i] == -1)
		{
			printf("error access file or open %s\n", s_cmd->next->line[0]);
			return (0);
		}
	}
	return (1);
}

t_arg	*loop_new_arg(t_exec *ex, t_arg *arg, t_na *n_a, t_arg *ret)
{
	int	len_to_skip;

	len_to_skip = 0;
	while (n_a->tmp)
	{
		printf("3\n");
		n_a->sep_val = check_sep_exec(arg->sep, ex);
		if (!n_a->sep_val)
			return (ret);
		if (!init_open_new_arg(ex, arg, n_a->sep_val))
			return (NULL);
		n_a->prev_sep_val = check_sep_exec(n_a->tmp->sep, ex);
		printf("val of sep = %d & val of prev_sep = %d\n", n_a->sep_val, n_a->prev_sep_val);
		if (n_a->sep_val == n_a->prev_sep_val && !arg->next->line[1])
		{
			printf("4\n");
			if (!n_a->first_to_free)
			{
				printf("4.1\n");

				n_a->first_to_free = arg;
				n_a->first_to_free->next = n_a->rest_to_free;
			}
			else
			{
				printf("4.2\n");

				if (!n_a->rest_to_free)
					n_a->rest_to_free = arg;
				else
				{
					n_a->rest_to_free->next = arg;
					n_a->rest_to_free = n_a->rest_to_free->next;
				}
			}
			len_to_skip++;
		}
		printf("len_to_skip = %d\n", len_to_skip);
		arg = arg->next;
		n_a->tmp = arg;
		if (len_to_skip > 0)
		{
			printf("5\n");
			ret->next = arg;
			len_to_skip--;
		}
		printf("6\n");
	}
	printf("OUT OF LOOP\n");
	if (len_to_skip > 0)
	{
		printf("7\n");
		ret->next = arg;
		len_to_skip--;
	}
	n_a->rest_to_free->next = NULL;
	printf("TO_FREE --->");
	print_arg(n_a->first_to_free);
	printf("========================\n");
	free_parsing(n_a->first_to_free);
	printf("RET --->");
	print_arg(ret);
	printf("-------------------------\n");
	printf("8\n");
	return (ret);
}

t_arg	*new_arg(t_exec *ex, t_arg *arg)
{
	t_na	*n_a;
	t_arg	*ret;

	printf("1\n");
	if (!ex || !arg)
		return (NULL);
	if (!arg->next)
		return (arg);
	n_a = malloc(sizeof(t_na));
	if (!n_a)
		return (NULL);
	ret = arg;
	n_a->tmp = arg->next;
	n_a->first_to_free = NULL;
	n_a->rest_to_free = NULL;
	n_a->sep_val = 0;
	n_a->prev_sep_val = 0;
	printf("2\n");
	ret = loop_new_arg(ex, arg, n_a, ret);
	free(n_a);
	return (ret);
}

// t_arg	*new_arg(t_exec *ex, t_arg *s_cmd, t_gc *garbage)
// {
// 	t_arg *tmp;
// 	t_arg *victime;
// 	t_arg *first_victime;

// 	int		typeofsep;
// 	int		typeofsep_next;

// 	tmp = s_cmd;
// 	typeofsep = check_sep_exec(s_cmd->sep, ex);
// 	if (!typeofsep)
// 		return (tmp);
// 	victime = NULL;
// 	(void)victime;
// 	first_victime = NULL;
// 	typeofsep_next = check_sep_exec(s_cmd->next->sep, ex);
// 	if (typeofsep != typeofsep_next)
// 		return (s_cmd);
// 	while (typeofsep == typeofsep_next && !s_cmd->next->line[1])
// 	{
// 		if (init_open_new_arg(ex, s_cmd, typeofsep, garbage))
// 			return (NULL);
// 		s_cmd = s_cmd->next;
// 		first_victime = s_cmd;
// 		typeofsep = check_sep_exec(s_cmd->sep, ex);
// 		if (!typeofsep)
// 			break ;
// 		typeofsep_next = check_sep_exec(s_cmd->next->sep, ex);		
// 	}
// 	s_cmd = s_cmd->next;
// 	free_victime(first_victime);
// 	tmp->next = s_cmd;
// 	printf("tmp.line = %s & tmp.NEXT.line = %s\n", tmp->line[0], tmp->next->line[0]);
// 	return (tmp);
// }