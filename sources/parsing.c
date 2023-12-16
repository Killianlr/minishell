/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:22:04 by flavian           #+#    #+#             */
/*   Updated: 2023/12/16 10:11:31 by flavian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	after_var_env(t_pars *pars)
{
	int	i;

	i = pars->i;
	if (!pars->av || i < 0)
		return (0);
	while (pars->av[i] && !is_whitespace(pars->av[i])
		&& !is_sep(pars->av[i]) && !is_quote(pars->av[i]))
		i++;
	return (i);
}

void	too_many_sep(t_pars *pars)
{
	char	*buf;
	int		is_print;
	int		y;
	int		i;

	i = pars->i;
	y = pars->i;
	is_print = 0;
	while (pars->av[y] && is_whitespace(pars->av[y]) && !is_sep(pars->av[y]))
	{
		if (is_printable(pars->av[y]))
		{
			is_print = 1;
			break ;
		}
		y++;
	}
	if (pars->av[y] && y > i && is_print == 1 && !is_sep(pars->av[y]))
		return ;
	buf = malloc(sizeof(char) * 3);
	if (!buf)
		return ;
	y = 0;
	while (pars->av[i] && is_whitespace(pars->av[i]))
		i++;
	if (pars->av[i] && is_sep(pars->av[i]))
		buf[y++] = pars->av[i];
	if ((pars->av[i] == '<' || pars->av[i] == '>')
		&& (pars->av[i] == pars->av[i + 1]))
		buf[y++] = pars->av[++i];
	buf[y] = 0;
	if (!buf[0])
		printf("Minishell: syntax error near unexpected token `%s'\n", buf);
	free(buf);
	return ;
}

char	*copy_str(t_pars *pars)
{
	int		y;
	int		i;
	char	*buf;
	char	*quote;

	buf = NULL;
	buf = malloc(sizeof(char) * (count_char(pars) + 1));
	if (!buf)
		return (NULL);
	y = 0;
	i = pars->i;
	quote = NULL;
	while (pars->av[i] && is_whitespace(pars->av[i]))
		i++;
	while (pars->av[i] && !is_sep(pars->av[i]) && !is_whitespace(pars->av[i]))
	{
		if (is_quote(pars->av[i]) && quote_is_closed(pars))
		{
			quote = handle_quotes(pars);
			if (!quote)
				return (NULL);
			buf = ms_strjoin(buf, quote, 3);
			y = ft_strlen(buf);
			i = quote_is_closed(pars);
		}
		else if (is_var_env(pars->av[i]) && !is_quote(pars->av[i]))
		{
			buf = ms_strjoin(buf, get_var_env(pars), 3);
			if (!buf)
				return (NULL);
			y = ft_strlen(buf);
			i = after_var_env(pars);
			break ;
		}
		else if (!is_quote(pars->av[i]) && !is_var_env(pars->av[i])
			&& !is_sep(pars->av[i]) && !is_whitespace(pars->av[i]))
		{
			buf[y] = pars->av[i];
			y++;
		}
		i++;
	}
	buf[y] = 0;
	return (buf);
}

t_arg	*create_arg(t_pars *pars)
{
	t_arg	*arg;
	char	*tmp;
	int		set;

	tmp = NULL;
	arg = malloc(sizeof(t_arg));
	arg->line = get_line(pars);
	if (!arg->line)
		return (NULL);
	arg->sep = get_sep(pars);
	if (!ft_strncmp(arg->sep, "<<", 2))
	{
		tmp = is_here_doc(pars);
		if (tmp)
			arg->h_doc = get_here_doc(tmp);
		// free(tmp);
	}
	else
		arg->h_doc = NULL;
	set = 0;
	while (pars->av[pars->i])
	{
		if (is_sep(pars->av[pars->i]) && set == 0)
			break ;
		else if (is_quote(pars->av[pars->i])
			&& quote_is_closed(pars) && set == 0)
			set = is_quote(pars->av[pars->i]);
		else if (is_quote(pars->av[pars->i]) == set && set > 0)
			set = 0;
		pars->i++;
	}
	while (is_sep(pars->av[pars->i]))
		pars->i++;
	return (arg);
}

t_arg	*parsing(t_pars *pars)
{
	int		sep_count;
	t_arg	*arg;
	t_arg	*first;

	sep_count = count_sep(pars);
	arg = create_arg(pars);
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
	arg = parsing(pars);
	if (!arg)
		printf("Error in parsing\n");
	free(pars);
	print_cmd(arg);
	return (arg);
}
