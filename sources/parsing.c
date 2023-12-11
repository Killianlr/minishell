/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fserpe <fserpe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:22:04 by flavian           #+#    #+#             */
/*   Updated: 2023/12/11 15:50:17 by fserpe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int	is_printable(char c)
{
	if (c > 32 && c < 127)
		return (1);
	else
		return (0);
}

int	is_whitespace(char c)
{

	if ((c != '\n' && c > 9 && c < 14 )|| c == ' ')
		return (1);
	else
		return (0);
}

int	is_sep(char c)
{
	if (!c)
		return (0);
	if (c == '<' || c == '>' || c == '|' || c == '\n') 
		return (1);
	return (0);
}

int	is_$(char c)
{
	if (!c)
		return (0);
	if (c == '$') 
		return (1);
	return (0);
}

int	is_quote(char c)
{
	if (!c)
		return (0);
	else if (c == 39)
		return (1);
	else if (c == 34)
		return (2);
	return (0);
}

char	**strduptab(char *src, int i)
{
	char **dup;
	int	y;

	if (!src || !src[i])
		return (NULL);
	dup = malloc(sizeof(char *) * 2);
	if (!dup)
		return (NULL);
	dup[0] = malloc(sizeof(char) * 2);
	y = 0;
	if (src[i] && !is_sep(src[i]))
		dup[0][y++] = src[i];
	dup[0][y] = 0;
	dup[1] = NULL;
	return (dup);
}

int	count_sep(char *str)
{
	int	i;
	int	count;
	int	status;

	i = 0;
	count = 0;
	status = is_quote(str[i]);
	while (str[i])
	{
		if (status > 0 && is_quote(str[i]) == status)
			status = 0;
		else if (is_quote(str[i]) > 0)
			status = is_quote(str[i]);
		if (is_sep(str[i]) && !is_sep(str[i + 1]) && status == 0)
			count++;
		i++;
	}
	count++;
	return (count);
}

int	count_word(char *str, int i)
{
	int	count;
	int	set;
	int	quote_s;

	count = 0;
	set = 0;
	quote_s = 0;
	while (str[i] )
	{
		if (is_sep(str[i]) && quote_s == 0)
			break;
		else if (is_quote(str[i]) && quote_s == 0)
			quote_s = is_quote(str[i]);
		else if (is_whitespace(str[i]) && quote_s == 0)
			set = 0;
		else if (set == 0 && quote_s == 0)
		{
			count++;
			set = 1;
		}
		else if (is_quote(str[i]) == quote_s)
		{
			set = 0;
			quote_s = 0;
		}
		else if (quote_s > 0 && set == 0)
		{
			count++;
			set = 1;
		}
		i++;
	}
	return (count);
}

char	*get_in_env(char **env, char *str)
{
	char *buf;
	int i;
	int y;
	int	j;

	if (!env[0] || !str)
		return (NULL);
	i = 0;
	buf = NULL;
	while (env[i])
	{
		y = 0;
		j = 0;
		if (!ft_strncmp(env[i], str, ft_strlen(str)))
		{
			y += ft_strlen(str) + 1;
			buf = malloc(sizeof(char) * (ft_strlen(env[i]) - y + 1));
			if (!buf)
				return (NULL);
			while (env[i][y])
				buf[j++] = env[i][y++];
			buf[j] = 0;
			printf("buf = %s\n", buf);
			free(str);
			return (buf);
		}
		i++;
	}

	return (NULL);
}

char	*get_$(char *str, int i, t_bui *blts)
{
	char	*buf;
	int		y;
	int		j;

	if (!is_$(str[i]))
		return (NULL);
	if (str[i + 1])
		i++;
	buf = NULL;
	y = 0;
	j = i;
	while (str[i] && !is_whitespace(str[i]) && !is_sep(str[i]))
	{
		y++;
		i++;
	}
	buf = malloc(sizeof(char) * y + 1);
	if (!buf)
		return (NULL);
	y = 0;
	while (str[j] && !is_whitespace(str[j]) && !is_sep(str[j]))
		buf[y++] = str[j++];
	buf[y] = 0;
	buf = get_in_env(blts->env, buf);
	return (buf);
}

int	after_$(char *str, int i)
{
	if (!str || i < 0)
		return (0);
	while (str[i] && !is_whitespace(str[i]) && !is_sep(str[i]))
		i++;
	return (i);
}

int	count_char(char *str, int i, t_bui *blts)
{
	int	count;
	char	*var_env;

	count = 0;
	var_env = NULL;
	while (str[i] && (is_sep(str[i]) || is_whitespace(str[i])))
		i++;
	while (str[i] && ft_isprint(str[i]) && !is_whitespace(str[i]))
	{
		if (is_$(str[i]))
		{
			var_env = get_$(str, i, blts);
			count += ft_strlen(var_env) - 1;
			i = after_$(str, i) - 1;
		}
		count++;
		i++;
	}
	return (count);
}

int	quote_is_closed(char *str, int i)
{
	char target;

	target = str[i];
	if (!str || i < 0 || !is_quote(target))
		return (0);
	if (str[i + 1])
		i++;
	else
	{
		// ft_printf("Error 1, quote unclosed\n");
		return (0);
	}
	while (str[i])
	{
		if (str[i] == target)
			return (i);
		i++;
	}
	// ft_printf("Error 2, quote unclosed\n");
	return (0);
}

char	*handle_quotes(char * str, int i)
{
	char	*buf;
	int		end;
	int		y;

	end = quote_is_closed(str, i);
	if (end == 0)
		return (NULL);
	buf = malloc(sizeof(char) * (end - i + 1));
	if (!buf)
		return (NULL);
	y = 0;
	i++;
	while (str[i] && i < end)
		buf[y++] = str[i++];
	buf[y] = 0;
	return (buf);
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

char	*get_sep(char *str, int i)
{
	char *buf;
	int	status;


	buf = NULL;
	buf = malloc(sizeof(char) * 3);
	status = 0;
	if (!buf)
		return (NULL);
	while (str[i])
	{
		if (is_quote(str[i]) && quote_is_closed(str, i) && status == 0)
			status = is_quote(str[i]);
		else if (status > 0 && is_quote(str[i]) == status)
			status = 0;
		if (is_sep(str[i]) && status == 0)
			break;
		i++;
	}
	if (!str[i])
	{
		free(buf);
		return (NULL);
	}
	if (is_sep(str[i]))
	{
		buf[0] = str[i];
		buf[1] = 0;
	}
	if ((str[i] == '<' || str[i] == '>') && (str[i] == str[i + 1]))
	{
		buf[1] = str[++i];
		buf[2] = 0;
	}
	if (str[i + 1])
		i++;
	if (str[i] && (is_sep(str[i]) || is_whitespace(str[i])))
		too_many_sep(str, i);
	return (buf);
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
			quote = handle_quotes(str, i);
			if (!quote)
				return (NULL);
			buf = ft_strjoin(buf, quote);
			y = ft_strlen(buf);
			i = quote_is_closed(str, i);
		}
		if (is_$(str[i]) && !is_quote(str[i]))
		{
			buf = ft_strjoin(buf, get_$(str, i, blts));
			if (!buf)
				return (NULL);
			y = ft_strlen(buf);
			i = after_$(str, i);
		}
		if (!is_quote(str[i]) && !is_$(str[i]))
		{
			buf[y] = str[i];
			y++;
		}
		i++;
	}
	buf[y] = 0;
	return (buf);
}

char	**get_line(char *str, int i, t_bui *blts)
{
	char **buf;
	int	y;
	int	word_count;
	int	status;

	word_count = count_word(str, i);
	if (!word_count)
		return (strduptab(str, i));
	buf = malloc(sizeof(char *) * (word_count + 1));
	if (!buf)
		return (NULL);
	y = 0;
	status = is_quote(str[i]);
	while (str[i] && word_count > 0)
	{
		while (str[i] && is_whitespace(str[i]))
			i++;
		buf[y] = copy_str(str, i, blts);
		if (!buf[y])
			return (NULL);
		y++;
		i += count_char(str, i, blts);
		while (str[i] && (is_whitespace(str[i]) || is_sep(str[i])))
		{
			if (is_quote(str[i]))
			{
				status = is_quote(str[i]);
				break ;
			}
			i++;
		}
		while (str[i] && status > 0)
		{
			if (is_quote(str[i]) == status)
			{
				i++;
				status = 0;
			}
			i++;
		}
		word_count--;
	}
	buf[y] = NULL;
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
		else if (is_quote(str[*i]) == set)
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