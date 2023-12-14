/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_get.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:05:15 by flavian           #+#    #+#             */
/*   Updated: 2023/12/14 18:59:35 by flavian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
			if (env[i][y - 1] != '=')
				break;
			buf = malloc(sizeof(char) * (ft_strlen(env[i]) - y + 1));
			if (!buf)
				return (NULL);
			while (env[i][y])
				buf[j++] = env[i][y++];
			buf[j] = 0;
			free(str);
			return (buf);
		}
		i++;
	}
	return (ms_strjoin("$", str, 2));
}

char	*get_$(t_pars *pars)
{
	char	*buf;
	int		y;
	int		j;

	if (!is_$(pars->av[pars->i]))
		return (NULL);
	if (is_quote(pars->av[pars->i]) == 2)
	{
		if (pars->av[pars->i + 1])
			pars->i++;
	}
	if (pars->av[pars->i + 1])
		pars->i++;
	y = 0;
	j = pars->i;
	while (pars->av[pars->i] && !is_whitespace(pars->av[pars->i]) && !is_sep(pars->av[pars->i]) && !is_quote(pars->av[pars->i]))
	{
		y++;
		pars->i++;
	}
	buf = malloc(sizeof(char) * y + 1);
	if (!buf)
		return (NULL);
	buf[0] = 0;
	y = 0;
	while (pars->av[j] && !is_whitespace(pars->av[j]) && !is_sep(pars->av[j]) && !is_quote(pars->av[j]))
		buf[y++] = pars->av[j++];
	buf[y] = 0;
	buf = get_in_env(pars->env, buf);
	return (buf);
}
char	*get_sep(t_pars *pars)
{
	char *buf;
	int	status;


	buf = NULL;
	buf = malloc(sizeof(char) * 3);
	status = 0;
	if (!buf)
		return (NULL);
	while (pars->av[pars->i])
	{
		if (is_quote(pars->av[pars->i]) && quote_is_closed(pars) && status == 0)
			status = is_quote(pars->av[pars->i]);
		else if (status > 0 && is_quote(pars->av[pars->i]) == status)
			status = 0;
		if (is_sep(pars->av[pars->i]) && status == 0)
			break;
		pars->i++;
	}
	if (!pars->av[pars->i])
	{
		free(buf);
		return (NULL);
	}
	if (is_sep(pars->av[pars->i]))
	{
		buf[0] = pars->av[pars->i];
		buf[1] = 0;
	}
	if ((pars->av[pars->i] == '<' || pars->av[pars->i] == '>') && (pars->av[pars->i] == pars->av[pars->i + 1]))
	{
		buf[1] = pars->av[pars->i];
		buf[2] = 0;
	}
	if (pars->av[pars->i] && (is_sep(pars->av[pars->i]) || is_whitespace(pars->av[pars->i])))
		too_many_sep(pars);
	return (buf);
}

int	get_next_word(t_pars *pars)
{
	int	status;

	if (!pars->av[pars->i])
		return (0);
	status = is_quote(pars->av[pars->i]);
	pars->i++;
	while (pars->av[pars->i])
	{
		if (status > 0)
		{
			while (pars->av[pars->i] && is_quote(pars->av[pars->i]) != status)
				pars->i++;
			return (pars->i);
		}
		else if (status == 0 && (is_whitespace(pars->av[pars->i]) || is_sep(pars->av[pars->i])))
			return (pars->i);
		pars->i++;
	}
	return (pars->i);
}

char	**get_line(t_pars *pars)
{
	char **buf;
	int	y;
	int	word_count;
	int	status;

	word_count = count_word(pars);
	printf("A\ni in get_line = %d & av = %s\n", pars->i ,pars->av);
	if (!word_count)
		return (strduptab(pars));
	buf = malloc(sizeof(char *) * (word_count + 1));
	if (!buf)
		return (NULL);
	y = 0;
	status = is_quote(pars->av[pars->i]);
	while (pars->av[pars->i] && word_count > 0)
	{
		printf("B\n");

		while (pars->av[pars->i] && is_whitespace(pars->av[pars->i]))
			pars->i++;
		buf[y] = copy_str(pars);
		if (!buf[y])
			return (NULL);
		y++;
		pars->i = get_next_word(pars);
		while (pars->av[pars->i] && (is_whitespace(pars->av[pars->i]) || is_sep(pars->av[pars->i])))
		{
			printf("C\n");

			if (is_quote(pars->av[pars->i]))
			{
				status = is_quote(pars->av[pars->i]);
				break ;
			}
			pars->i++;
		}
		while (pars->av[pars->i] && status > 0)
		{
			printf("D\n");

			if (is_quote(pars->av[pars->i]) == status)
			{
				pars->i++;
				status = 0;
			}
			pars->i++;
		}
		word_count--;
	}
	buf[y] = NULL;
	printf("E\n");

	for (int l = 0; buf[l]; l++)
		printf("GET LINE buf = %s\n", buf[l]);
	// printf("GET LINE buf = %s\n", buf[l]);
	
	return (buf);
}

char	*get_here_doc(char *av)
{
	int		doc;
	int		set;
	char	*buf = NULL;
	char	*ret = NULL;

	doc = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (doc < 0)
		return (NULL);
	set = 0;
	while (1)
	{
		write(1, "> ", 3);
		buf = get_next_line(0, 0);
		if (!buf)
			return (NULL);
		if (!ms_strcmp(av, buf, ft_strlen(av)))
		{
			free(buf);
			break ;
		}
		write(doc, buf, ft_strlen(buf));
		write(doc, "\n", 1);
		if (set == 0)
		{
			ret = ms_strjoin(ret, buf, 2);
			set = 1;
		}
		else if (set > 0)
			ret = ms_strjoin(ret, buf, 3);
	}
	get_next_line(0, 1);
	close(doc);
	unlink(".heredoc_tmp");
	return (ret);
}