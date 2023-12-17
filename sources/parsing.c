/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:22:04 by flavian           #+#    #+#             */
/*   Updated: 2023/12/17 20:31:30 by flavian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	after_var_env(t_pars *pars, int i)
{
	int	y;

	y = i;
	if (!pars->av || y < 0)
		return (0);
	while (pars->av[y] && !is_whitespace(pars->av[y])
		&& !is_sep(pars->av[y]) && !is_quote(pars->av[y]))
		y++;
	if (!pars->av[y])
		return (-1);
	return (y);
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

char	size_for_line(t_pars *pars, char *buf, char *quote)
{
	int	i;
	int	count;

	i = pars->i;
	printf("BUF = %s\nQUOTE = %s\n", buf, quote);
	printf("av[i] = %c[%d]\n", pars->av[i], i);
	count = (int)ft_strlen(buf) + (int)ft_strlen(quote);
	printf("COUNT start = %d\n", count);

	if (is_quote(pars->av[i]))
		i++;
	while (pars->av[i])
	{
		if (is_quote(pars->av[i]))
		{
			count += (int)ft_strlen(handle_quotes(pars, i));
			printf("COUNT quote = %d\n", count);
			i = quote_is_closed(pars, i);
			if (i == 0)
				return (count);
			printf("i aftet quote_is_closed = %d\n", i);
		}
		else if (is_printable(pars->av[i]) && !is_sep(pars->av[i])
			&& !is_quote(pars->av[i]) && !is_var_env(pars->av[i]))
		{
			count++;
			printf("COUNT char = %d\n", count);
		}
		else if (is_var_env(pars->av[i]))
		{
			count += (int)ft_strlen(get_var_env(pars, i));
			printf("COUNT $= %d\n", count);
			while (pars->av[i + 1] && !is_whitespace(pars->av[i + 1])
				&& !is_sep(pars->av[i + 1]) && !is_quote(pars->av[i + 1]))
				i++;
		}
		else if (is_sep(pars->av[i]) || is_whitespace(pars->av[i]))
			break ;
		i++;
	}
	printf("COUNT end = %d\n", count);
	return (count);
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
	while (pars->av[pars->i] && is_whitespace(pars->av[pars->i]))
		pars->i++;
	while (pars->av[pars->i] && !is_sep(pars->av[pars->i]) && !is_whitespace(pars->av[pars->i]))
	{
		if (is_quote(pars->av[pars->i]) && quote_is_closed(pars, pars->i))
		{
			printf("in TARGET\n");
			quote = handle_quotes(pars, pars->i);
			if (!quote)
				return (NULL);
			buf = ms_strjoin_len(buf, quote, 3, size_for_line(pars, buf, quote));
			printf("buf after TARGET = %s\n", buf);
			y = ft_strlen(buf);
			if (quote_is_closed(pars, pars->i) > 0)
				pars->i = quote_is_closed(pars, pars->i);
			else
				return  (ft_strdup(""));
		}
		else if (is_var_env(pars->av[pars->i]) && !is_quote(pars->av[pars->i - 1]))
		{
			buf = ms_strjoin(buf, get_var_env(pars, pars->i), 3);
			if (!buf)
				return (NULL);
			y = ft_strlen(buf);
			break ;
		}
		else if (!is_quote(pars->av[pars->i]) && !is_var_env(pars->av[pars->i])
			&& !is_sep(pars->av[pars->i]) && !is_whitespace(pars->av[pars->i]))
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
	char	*tmp;
	int		set;

	tmp = NULL;
	arg = malloc(sizeof(t_arg));
	arg->line = get_line(pars);
	if (!arg->line)
		return (NULL);
	arg->sep = get_sep(pars);
	if (!ft_strncmp(arg->sep, "<<", ft_strlen(arg->sep)))
	{
		tmp = is_here_doc(pars);
		printf("del = %s\n", tmp);
		if (tmp)
			arg->h_doc = get_here_doc(tmp);
	}
	if (ft_strncmp(arg->sep, "<<", 2) || !arg->sep)
		arg->h_doc = NULL;
	set = 0;
	while (pars->av[pars->i])
	{
		if (is_sep(pars->av[pars->i]) && set == 0)
			break ;
		else if (is_quote(pars->av[pars->i])
			&& quote_is_closed(pars, pars->i) && set == 0)
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
	if (!arg)
		return (arg);
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
