/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_pt0.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:22:04 by flavian           #+#    #+#             */
/*   Updated: 2023/12/07 23:32:38 by flavian          ###   ########.fr       */
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

int	count_sep(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (is_sep(str[i]) && !is_sep(str[i + 1]))
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

	count = 0;
	set = 0;
	while (str[i] && !is_sep(str[i]))
	{
		if (is_whitespace(str[i]))
		{
			set = 0;
		}
		else if (set == 0)
		{
			count++;
			set = 1;
		}
		i++;
	}
	return (count);
}

int	count_char(char *str, int i)
{
	int	count;

	count = 0;
	while (str[i] && (is_sep(str[i]) || is_whitespace(str[i])))
		i++;
	while (str[i] && ft_isprint(str[i]) && !is_whitespace(str[i]))
	{
		count++;
		i++;
	}
	return (count);
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


	buf = NULL;
	buf = malloc(sizeof(char) * 3);
	if (!buf)
		return (NULL);
	while (str[i] && !is_sep(str[i]))
		i++;
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
	if(str[i + 1])
		i++;
	if (str[i] && (is_sep(str[i]) || is_whitespace(str[i])))
		too_many_sep(str, i);
	return (buf);
}

char	*copy_str(char *str, int i)
{
	int	y;
	char	*buf;

	buf = malloc(sizeof(char) * (count_char(str, i) + 1));
	if (!buf)
		return (NULL);
	y = 0;
	while (str[i] && !is_sep(str[i]) && !is_whitespace(str[i]))
	{
		buf[y] = str[i];
		y++;
		i++;
	}
	buf[y] = 0;
	return (buf);
}

char	**get_line(char *str, int i)
{
	char **buf;
	int	y;
	int	word_count;

	word_count = count_word(str, i);
	if (!word_count)
		return (strduptab(str, i));
	buf = malloc(sizeof(char *) * (word_count + 1));
	if (!buf)
		return (NULL);
	y = 0;

	while (str[i] && word_count > 0)
	{
		while (str[i] && is_whitespace(str[i]))
			i++;
		buf[y] = copy_str(str, i);
		if (!buf[y])
			return (NULL);
		y++;
		i += count_char(str, i);
		while (str[i] && (is_whitespace(str[i]) || is_sep(str[i])))
			i++;
		word_count--;
	}
	buf[y] = NULL;
	return (buf);
}

t_cmd	*create_cmd(char *str, int *i)
{
    t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
    // if (!cmd)
    // 	return NULL;

	cmd->line = get_line(str, *i);
	if (!cmd->line)
		return (NULL);
	
    cmd->sep = get_sep(str, *i);

	while (str[*i] && !is_sep(str[*i]))
    	i[0]++;
	while (is_sep(str[*i]))
		i[0]++;

	return (cmd);
}

t_cmd *parsing(char *str)
{
    int		sep_count;
    t_cmd	*cmd;
	t_cmd	*first;
    int *i;

	i = malloc(sizeof(int) * 1);
	if (!i)
		return (NULL);
	*i = 0;
    sep_count = count_sep(str);
	cmd = create_cmd(str, i);
	first = cmd;
    while (sep_count && str[*i] && cmd->sep)
	{
		cmd->next = create_cmd(str, i);
		cmd = cmd->next;
		sep_count--;
    }
    cmd->next = NULL;
	free(i);
    return (first);
}
