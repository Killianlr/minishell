/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fserpe <fserpe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:22:04 by flavian           #+#    #+#             */
/*   Updated: 2023/12/21 14:34:59 by fserpe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_arg	*create_arg(t_pars *pars)
{
	t_arg	*arg;

	arg = malloc(sizeof(t_arg));
	arg->line = get_line(pars);
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
	arg = create_arg(pars);
	if (!arg)
		return (NULL);
	first = arg;
	while (sep_count && pars->av[pars->i])
	{
		arg->next = create_arg(pars);
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
	if (!arg)
		ft_printf("Error in parsing\n");
	free(pars);
	print_cmd(arg);
	return (arg);
}
