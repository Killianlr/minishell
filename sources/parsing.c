/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:22:04 by flavian           #+#    #+#             */
/*   Updated: 2023/11/24 14:51:55 by flavian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_whitespace(char c)
{
	if ((c != '\n' && c > 9 && c < 14 )|| c == ' ')
		return (1);
	else
		return (0);
}

int	is_sep(char c)
{
	if (c == ';' || c == '<' || c == '>' || c == '|' || c == '\n')
		return (1);
	else
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
		if (is_sep(str[i]))
		{
			// printf("sep = %c\n", str[i]);
			count++;
		}
		i++;
	}
	count++;

	// printf("SEP COUNT = %d\n", count);
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
			// i++;
		}
		else if (set == 0)
		{
			count++;
			set = 1;
		}
		i++;
	}
	// printf("WORD COUNT = %d\n", count);
	return (count);
}

int	count_char(char *str, int i)
{
	int	count;

	count = 0;
	// printf("str in count char = %s ; i = %d\n", str, i);
	while (str[i] && (is_sep(str[i]) || is_whitespace(str[i])))
		i++;
	while (str[i] && !is_sep(str[i]) && !is_whitespace(str[i]))
	{
		if (ft_isprint(str[i])) 
		{
			count++;
			// i++;
		}
		i++;
	}
	// printf("CHAR COUNT = %d\n", count);
	return (count);
}

char	*copy_str(char *str, int i)
{
	int	y;
	char	*buf;

	buf = malloc(sizeof(char) * (count_char(str, i) + 1));
	if (!buf)
		return (NULL);
	y = 0;
	while (str[i] && (is_sep(str[i]) || is_whitespace(str[i])))
		i++;
	while (str[i] && !is_sep(str[i]) && !is_whitespace(str[i]))
	{
		// if (is_whitespace(str[i]))
		// 	i++;
		buf[y] = str[i];
		// printf("%c", buf[y]);
		y++;
		i++;
	}
	// printf("\nbuf in copy str = %s\n", buf);
	buf[y] = 0;
	return (buf);
}

char	get_sep(char *str, int i)
{
	char buf;

	buf = 0;
	while (str[i] && !is_sep(str[i]))
		i++;
	buf = str[i];
	return (buf);
}

char	**get_line(char *str, int i)
{
	char **buf;
	int	y;
	int	word_count;

	// printf("---------------------------------------------\n");
	word_count = count_word(str, i);
	buf = malloc(sizeof(char *) * (word_count + 1));
	if (!buf)
		return (NULL);
	y = 0;
	while (str[i] && !is_sep(str[i]) && word_count > 0)
	{
		// printf("I in get_line = %d\n", i);
		buf[y] = copy_str(str, i);
		word_count--;
		y++;
		i += count_char(str, i) + 1;
	}
	buf[y] = 0;
	// printf("---------------------------------------------\n");
	return (buf);
}

s_cmd	*parsing(char *str)
{
	int	sep_count;
	s_cmd	*cmd;
	s_cmd	*first;

	int	i;

	sep_count = count_sep(str);
	i = 0;
	while (sep_count > 0)
	{
		// printf("I in parsing = %d\n", i);
		cmd = malloc(sizeof(s_cmd));
		if (!cmd)
			return (NULL);
		cmd->line = get_line(str, i);
		cmd->sep = get_sep(str, i);
		printf("================================================\ncmd.line = %s\n%s\n%s\ncmd.sep = %c\n================================================\n", cmd->line[0], cmd->line[1], cmd->line[2], cmd->sep);
		if (sep_count == count_sep(str))
			first = cmd;
		cmd = cmd->next;
		while (str[i] && !is_sep(str[i]))
			i++;
		i++;
		sep_count--;
	}
	printf("ICI\n");
	cmd->next = NULL;
	return (first);
}