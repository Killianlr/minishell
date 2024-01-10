/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:22:04 by flavian           #+#    #+#             */
/*   Updated: 2024/01/10 11:28:03 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*copy_sep(char *src, int len)
{
	int		i;
	char	*ret;

	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	i = -1;
	while (src[++i])
		ret[i] = src[i];
	ret[i] = 0;
	return (ret);
}

void	create_prev_sep(t_arg *first)
{
	t_arg	*next;

	if (!first)
		return ;
	next = first->next;
	if (!next)
		return ;
	while (next)
	{
		if (first->sep)
			next->prev_sep = copy_sep(first->sep, ft_strlen(first->sep));
		first = next;
		next = first->next;
	}
	if (first->sep)
			next->prev_sep = copy_sep(first->sep, ft_strlen(first->sep));
}

t_arg	*create_arg(t_pars *pars, int ret_val)
{
	t_arg	*arg;

	arg = malloc(sizeof(t_arg));
	if (!arg)
		return (NULL);
	arg->line = get_line(pars, ret_val);
	if (!arg->line)
	{
		free(arg);
		return (NULL);
	}
	arg->sep = get_sep(pars);
	if (check_sep(arg->sep) < 0)
	{
		free_pars_tab(arg->line);
		free(arg->sep);
		free(arg);
		return (NULL);
	}
	arg->prev_sep = NULL;
	return (arg);
}

t_arg	*parsing(t_pars *pars, t_gc *garbage)
{
	int		sep_count;
	t_arg	*arg;
	t_arg	*first;

	sep_count = count_sep(pars);
	if (sep_count > 0)
		garbage->fd_hdoc = scan_av_for_hdoc(pars, garbage->fd_hdoc);
	arg = create_arg(pars, garbage->ret);
	if (!arg)
		return (NULL);
	first = arg;
	while (sep_count && pars->av[pars->i])
	{
		arg->next = create_arg(pars, garbage->ret);
		if (!arg->next)
			break ;
		arg = arg->next;
		sep_count--;
	}
	arg->next = NULL;
	return (first);
}

t_arg	*main_pars(char *str, t_bui *blts, t_gc *garbage)
{
	t_arg	*arg;
	t_pars	*pars;

	if (!str)
		return (NULL);
	arg = NULL;
	pars = NULL;
	pars = malloc(sizeof(t_pars));
	if (!pars)
		return (NULL);
	pars->av = str;
	pars->env = blts->env;
	pars->i = 0;
	if (count_quote(pars) % 2 != 0)
	{
		free(pars);
		ft_printf("Error, quote unclosed\n");
		return (NULL);
	}
	arg = parsing(pars, garbage);
	create_prev_sep(arg);
	arg = post_parsing(arg);
	free(pars);
	return (arg);
}
