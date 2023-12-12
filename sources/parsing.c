/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:22:04 by flavian           #+#    #+#             */
/*   Updated: 2023/12/12 11:14:43 by flavian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	after_$(char *str, int i)
{
	if (!str || i < 0)
		return (0);
	while (str[i] && !is_whitespace(str[i]) && !is_sep(str[i]))
		i++;
	return (i);
}

void	too_many_sep(char *str, int i)
{
	char	*buf;
	int		is_print;
	int		y;

	y = i;
	is_print = 0;
	while (str[y] && is_whitespace(str[y]) && !is_sep(str[y]))
	{
		if (is_printable(str[y]))
		{
			is_print = 1;
			break;
		}
		y++;
	}
	if (str[y] && y > i && is_print == 1 &&!is_sep(str[y]))
		return ;
	buf = malloc(sizeof(char) * 3);
	if (!buf)
		return ;
	y = 0;
	if (str[i] && is_sep(str[i]))
		buf[y++] = str[i];
	if ((str[i] == '<' || str[i] == '>') && (str[i] == str[i + 1]))
		buf[y++] = str[++i];
	buf[y] = 0;
	if (buf[0])
		printf("Minishell: syntax error near unexpected token `%s'\n", buf);
	free(buf);
	return ;
}

char	*copy_str(char *str, int i, t_bui *blts)
{
	int		y;
	char	*buf;
	char	*quote;

	(void) blts;
	buf = malloc(sizeof(char) * (count_char(str, i, blts) + 1));
	if (!buf)
		return (NULL);
	buf[0] = 0; 
	y = 0;
	quote = NULL;
	while (str[i] && !is_sep(str[i]) && !is_whitespace(str[i]))
	{
		if (is_quote(str[i]) && quote_is_closed(str, i))
		{
			quote = handle_quotes(str, i, blts);
			if (!quote)
				return (NULL);
			buf = ms_strjoin(buf, quote, 3);
			y = ft_strlen(buf);
			i = quote_is_closed(str, i);
		}
		else if (is_$(str[i]) && !is_quote(str[i]))
		{
			buf = ms_strjoin(buf, get_$(str, i, blts), 3);
			if (!buf)
				return (NULL);
			y = ft_strlen(buf);
			i = after_$(str, i);
			break ;
		}
		else if (!is_quote(str[i]) && !is_$(str[i]) && !is_sep(str[i]) && !is_whitespace(str[i]))
		{
			buf[y] = str[i];
			y++;
		}
		i++;
	}
	buf[y] = 0;
	return (buf);
}

t_arg	*create_arg(char *str, int *i, t_bui *blts)
{
    t_arg	*arg;
	int		set;

	arg = malloc(sizeof(t_arg));

	arg->line = get_line(str, *i, blts);
	if (!arg->line)
		return (NULL);
	
    arg->sep = get_sep(str, *i);

	set = 0;
	while (str[*i])
	{
		if (is_sep(str[*i]) && set == 0)
			break;
		else if (is_quote(str[*i]) && quote_is_closed(str, *i) && set == 0)
			set = is_quote(str[*i]);
		else if (is_quote(str[*i]) == set && set > 0)
			set = 0;
    	i[0]++;
	}
	while (is_sep(str[*i]))
		i[0]++;

	return (arg);
}

t_arg *parsing(char *str, t_bui *blts)
{
    int		sep_count;
    t_arg	*arg;
	t_arg	*first;
    int *i;

	i = malloc(sizeof(int) * 1);
	if (!i)
		return (NULL);
	*i = 0;
    sep_count = count_sep(str);
	arg = create_arg(str, i, blts);
	first = arg;
    while (sep_count && str[*i] && arg->sep)
	{
		arg->next = create_arg(str, i, blts);
		arg = arg->next;
		sep_count--;
    }
    arg->next = NULL;
	free(i);
    return (first);
}

t_arg	*main_pars(char *str, t_bui *blts)
{
	t_arg	*arg;
	
	if (!str)
		return (NULL);
	arg = NULL;
	arg = parsing(str, blts);
	if (!arg)
		printf("Error in parsing\n");
	print_cmd(arg);
	// free_parsing(arg);
	return (arg);
}