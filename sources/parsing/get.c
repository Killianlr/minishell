/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:05:15 by flavian           #+#    #+#             */
/*   Updated: 2023/12/11 18:06:28 by flavian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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