/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:22:04 by flavian           #+#    #+#             */
/*   Updated: 2023/12/19 14:15:19 by flavian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_arg	*create_arg(t_pars *pars)
{
	t_arg	*arg;
	char	*del;

	printf("in create_arg\n");
	del = NULL;
	arg = malloc(sizeof(t_arg));
	arg->line = get_line(pars);
	if (!arg->line)
		return (NULL);
	arg->sep = get_sep(pars);
	if (!ft_strncmp(arg->sep, "<<", ft_strlen(arg->sep)))
	{
		del = get_del_hdoc(pars);
		printf("del = %s\n", del);
		if (del || !ft_strncmp(del, "", 1))
			arg->h_doc = get_here_doc(del);
		else
			arg->h_doc = NULL;
	}
	if (ft_strncmp(arg->sep, "<<", 2) || !arg->sep)
		arg->h_doc = NULL;
	return (arg);
}

t_arg	*parsing(t_pars *pars)
{
	int		sep_count;
	t_arg	*arg;
	t_arg	*first;

	sep_count = count_sep(pars);
	arg = create_arg(pars);
	if (!arg)
		return (NULL);
	first = arg;
	while (sep_count && pars->av[pars->i])
	{
		arg->next = create_arg(pars);
		arg = arg->next;
		sep_count--;
	}
	arg->next = NULL;
	return (first);
}

t_arg	*main_pars(char *str, t_bui *blts)
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
		ft_printf("Error, quote unclosed\n");
		free(pars);
		return (NULL);
	}
	arg = parsing(pars);
	if (!arg)
		printf("Error in parsing\n");
	free(pars);
	print_cmd(arg);
	return (arg);
}
