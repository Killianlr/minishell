/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fserpe <fserpe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 19:58:02 by flavian           #+#    #+#             */
/*   Updated: 2024/01/14 14:45:43 by fserpe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_arg	*end_of_new_arg(t_arg *ret, t_na *n_a, t_exec *ex, int len_to_skip)
{
	if (len_to_skip && n_a->rest_to_free)
		n_a->rest_to_free->next = NULL;
	else if (len_to_skip && !n_a->rest_to_free)
		n_a->first_to_free->next = NULL;
	n_a->first_to_free = open_to_free(n_a->first_to_free, ex);
	if (!n_a->first_to_free)
		return (NULL);
	free_parsing(n_a->first_to_free);
	return (ret);
}

t_arg	*fill_to_free(t_arg *arg, t_na *n_a)
{
	arg = arg->next;
	n_a->tmp = arg;
	if (!n_a->first_to_free)
		n_a->first_to_free = arg;
	else
	{
		if (!n_a->rest_to_free)
		{
			n_a->rest_to_free = arg;
			n_a->first_to_free->next = n_a->rest_to_free;
		}
		else
		{
			n_a->rest_to_free->next = arg;
			n_a->rest_to_free = n_a->rest_to_free->next;
		}
	}
	return (arg);
}

void	fill_ret(t_arg *arg, t_arg *ret, t_na *n_a)
{
	if (!n_a->ret_next)
	{
		n_a->ret_next = arg;
		ret->next = n_a->ret_next;
	}
	else
		n_a->ret_next->next = arg;
}

t_arg	*loop_new_arg(t_exec *ex, t_arg *arg, t_na *n_a, t_arg *ret)
{
	int	len_to_skip;

	len_to_skip = 0;
	while (n_a->tmp)
	{
		if (!set_sep_val(n_a, arg, ex))
			break ;
		while (n_a->sep_val == n_a->next_sep_val && !arg->next->line[1])
		{
			arg = fill_to_free(arg, n_a);
			len_to_skip++;
			if (!set_sep_val(n_a, arg, ex))
				break ;
		}
		arg = arg->next;
		n_a->tmp = arg;
		if (len_to_skip > 0)
			fill_ret(arg, ret, n_a);
	}
	return (end_of_new_arg(ret, n_a, ex, len_to_skip));
}

t_arg	*new_arg(t_exec *ex, t_arg *arg)
{
	t_na	*n_a;
	t_arg	*ret;

	if (!ex || !arg)
		return (NULL);
	if (!arg->next)
		return (arg);
	n_a = malloc(sizeof(t_na));
	if (!n_a)
		return (NULL);
	ret = arg;
	n_a->ret_next = NULL;
	n_a->tmp = arg->next;
	n_a->first_to_free = NULL;
	n_a->rest_to_free = NULL;
	n_a->sep_val = 0;
	n_a->next_sep_val = 0;
	ret = loop_new_arg(ex, arg, n_a, ret);
	free(n_a);
	return (ret);
}
