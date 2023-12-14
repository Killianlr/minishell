/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:22:04 by flavian           #+#    #+#             */
/*   Updated: 2023/12/14 18:57:23 by flavian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int	after_$(t_pars *pars)
{
	if (!pars->av || pars->i < 0)
		return (0);
	while (pars->av[pars->i] && !is_whitespace(pars->av[pars->i]) && !is_sep(pars->av[pars->i]) && !is_quote(pars->av[pars->i]))
		pars->i++;
	return (pars->i);
}

void	too_many_sep(t_pars *pars)
{
	char	*buf;
	int		is_print;
	int		y;

	y = pars->i;
	is_print = 0;
	while (pars->av[y] && is_whitespace(pars->av[y]) && !is_sep(pars->av[y]))
	{
		if (is_printable(pars->av[y]))
		{
			is_print = 1;
			break;
		}
		y++;
	}
	if (pars->av[y] && y > pars->i && is_print == 1 && !is_sep(pars->av[y]))
		return ;
	buf = malloc(sizeof(char) * 3);
	if (!buf)
		return ;
	y = 0;
	
	if (pars->av[pars->i] && is_sep(pars->av[pars->i]))
		buf[y++] = pars->av[pars->i];
	if ((pars->av[pars->i] == '<' || pars->av[pars->i] == '>') && (pars->av[pars->i] == pars->av[pars->i + 1]))
		buf[y++] = pars->av[++pars->i];
	buf[y] = 0;
	if (!buf[0])
		printf("Minishell: syntax error near unexpected token `%s'\n", buf);
	free(buf);
	return ;
}

char	*copy_str(t_pars *pars)
{
	int		y;
	char	*buf;
	char	*quote;

	buf = malloc(sizeof(char) * (count_char(pars) + 1));
	if (!buf)
		return (NULL);
	buf[0] = 0; 
	y = 0;
	quote = NULL;
	while (pars->av[pars->i] && !is_sep(pars->av[pars->i]) && !is_whitespace(pars->av[pars->i]))
	{
		if (is_quote(pars->av[pars->i]) && quote_is_closed(pars))
		{
			quote = handle_quotes(pars);
			if (!quote)
				return (NULL);
			buf = ms_strjoin(buf, quote, 3);
			y = ft_strlen(buf);
			pars->i = quote_is_closed(pars);
		}
		else if (is_$(pars->av[pars->i]) && !is_quote(pars->av[pars->i]))
		{
			buf = ms_strjoin(buf, get_$(pars), 3);
			if (!buf)
				return (NULL);
			y = ft_strlen(buf);
			pars->i = after_$(pars);
			break ;
		}
		else if (!is_quote(pars->av[pars->i]) && !is_$(pars->av[pars->i]) && !is_sep(pars->av[pars->i]) && !is_whitespace(pars->av[pars->i]))
		{
			buf[y] = pars->av[pars->i];
			y++;
		}
		pars->i++;
	}
	buf[y] = 0;
	return (buf);
}

t_arg	*create_arg(t_pars *pars)
{
    t_arg	*arg;
	char	*tmp = NULL;
	int		set;

	arg = malloc(sizeof(t_arg));

	printf("1\ni in create_arg = %d\n", pars->i);
	arg->line = get_line(pars);
	if (!arg->line)
		return (NULL);
	printf("2\n");
	
    arg->sep = get_sep(pars);
	if (!ft_strncmp(arg->sep, "<<", 2))
	{
		tmp = is_here_doc(pars);
		if (tmp)
			arg->h_doc = get_here_doc(tmp);
		free(tmp);
	}
	else
		arg->h_doc = NULL;
	printf("3\n");
	
	set = 0;
	while (pars->av[pars->i])
	{
		if (is_sep(pars->av[pars->i]) && set == 0)
			break;
		else if (is_quote(pars->av[pars->i]) && quote_is_closed(pars) && set == 0)
			set = is_quote(pars->av[pars->i]);
		else if (is_quote(pars->av[pars->i]) == set && set > 0)
			set = 0;
    	pars->i++;
	}
	printf("4\n");

	while (is_sep(pars->av[pars->i]))
		pars->i++;

	return (arg);
}

t_arg *parsing(t_pars *pars)
{
    int		sep_count;
    t_arg	*arg;
	t_arg	*first;

    sep_count = count_sep(pars->av);
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