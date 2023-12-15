/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_get.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fserpe <fserpe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:05:15 by flavian           #+#    #+#             */
/*   Updated: 2023/12/15 16:41:13 by fserpe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_in_env(char **env, char *str)
{
	char	*buf;
	int		i;
	int		y;
	int		j;

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
				break ;
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
	return (ms_strjoin("var_env", str, 2));
}

char	*get_var_env(t_pars *pars)
{
	char	*buf;
	int		y;
	int		j;
	int		i;

	i = pars->i;
	if (!is_var_env(pars->av[i]))
		return (NULL);
	if (is_quote(pars->av[i]) == 2)
	{
		if (pars->av[i + 1])
			i++;
	}
	if (pars->av[i + 1])
		i++;
	y = 0;
	j = i;
	while (pars->av[i] && !is_whitespace(pars->av[i])
		&& !is_sep(pars->av[i]) && !is_quote(pars->av[i]))
	{
		y++;
		i++;
	}
	buf = malloc(sizeof(char) * y + 1);
	if (!buf)
		return (NULL);
	buf[0] = 0;
	y = 0;
	while (pars->av[j] && !is_whitespace(pars->av[j])
		&& !is_sep(pars->av[j]) && !is_quote(pars->av[j]))
		buf[y++] = pars->av[j++];
	buf[y] = 0;
	buf = get_in_env(pars->env, buf);
	return (buf);
}

char	*get_sep(t_pars *pars)
{
	char	*buf;
	int		status;
	int		i;

	buf = NULL;
	buf = malloc(sizeof(char) * 3);
	status = 0;
	i = pars->i;
	if (!buf)
		return (NULL);
	while (pars->av[i])
	{
		if (is_quote(pars->av[i]) && quote_is_closed(pars) && status == 0)
			status = is_quote(pars->av[i]);
		else if (status > 0 && is_quote(pars->av[i]) == status)
			status = 0;
		if (is_sep(pars->av[i]) && status == 0)
			break ;
		i++;
	}
	if (!pars->av[i])
	{
		free(buf);
		return (NULL);
	}
	if (is_sep(pars->av[i]))
	{
		buf[0] = pars->av[i];
		buf[1] = 0;
	}
	if ((pars->av[i] == '<' || pars->av[i] == '>')
		&& (pars->av[i] == pars->av[i + 1]))
	{
		buf[1] = pars->av[i];
		buf[2] = 0;
	}
	if (pars->av[i] && (is_sep(pars->av[i]) || is_whitespace(pars->av[i])))
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
		else if (status == 0 && (is_whitespace(pars->av[pars->i])
				|| is_sep(pars->av[pars->i])))
			return (pars->i);
		pars->i++;
	}
	return (pars->i);
}

char	**get_line(t_pars *pars)
{
	char	**buf;
	int		y;
	int		word_count;
	int		status;
	int		i;

	word_count = count_word(pars);
	if (!word_count)
		return (strduptab(pars));
	buf = malloc(sizeof(char *) * (word_count + 1));
	if (!buf)
		return (NULL);
	y = 0;
	i = pars->i;
	status = is_quote(pars->av[i]);
	while (pars->av[i] && word_count > 0)
	{
		while (pars->av[i] && is_whitespace(pars->av[i]))
			i++;
		buf[y] = copy_str(pars);
		if (!buf[y])
			return (NULL);
		y++;
		i = get_next_word(pars);
		while (pars->av[i] && (is_whitespace(pars->av[i])
				|| is_sep(pars->av[i])))
		{
			if (is_quote(pars->av[i]))
			{
				status = is_quote(pars->av[i]);
				break ;
			}
			i++;
		}
		while (pars->av[i] && status > 0)
		{
			if (is_quote(pars->av[i]) == status)
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

char	*get_here_doc(char *av)
{
	int		doc;
	int		set;
	char	*buf;
	char	*ret;

	buf = NULL;
	ret = NULL;
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
