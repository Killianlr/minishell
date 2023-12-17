/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_get.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:05:15 by flavian           #+#    #+#             */
/*   Updated: 2023/12/17 17:40:07 by flavian          ###   ########.fr       */
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
			buf[0] = 0;
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

char	*get_var_env(t_pars *pars, int i)
{
	char	*buf;
	int		y;
	int		j;

	while (pars->av[i] && !is_var_env(pars->av[i]))
		i++;
	if (!pars->av[i])
		return (NULL);
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

int	get_sep_size(t_pars *pars)
{
	int	i;
	int	count;

	i = pars->i;
	count = 0;
	while (pars->av[i] && !is_sep(pars->av[i]))
		i++;
	while (pars->av[i] && is_sep(pars->av[i]))
	{
		count++;
		i++;
	}
	return (count);
}

char	*get_sep(t_pars *pars)
{
	char	*buf;
	int		i;
	int		y;

	buf = malloc(sizeof(char) * (get_sep_size(pars) + 1));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	i = pars->i;
	y = 0;
	while (pars->av[i] && !is_sep(pars->av[i]))
		i++;
	if (!pars->av[i])
	{
		free(buf);
		return (NULL);
	}
	while (pars->av[i] && is_sep(pars->av[i]))
		buf[y++] = pars->av[i++];
	buf[y] = 0;
	return (buf);
}

int	get_next_word(t_pars *pars)
{
	if (!pars->av[pars->i])
		return (0);
	while (pars->av[pars->i] && !is_printable(pars->av[pars->i])
			&& !is_quote(pars->av[pars->i]))
		pars->i++;
	while (pars->av[pars->i])
	{
		if (is_quote(pars->av[pars->i]) > 0 && quote_is_closed(pars, pars->i) > 0)
			pars->i = quote_is_closed(pars, pars->i);
		else if ((is_whitespace(pars->av[pars->i]) || is_sep(pars->av[pars->i])))
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

	word_count = count_word(pars);
	if (!word_count)
		return (strduptab(pars));
	buf = malloc(sizeof(char *) * (word_count + 1));
	if (!buf)
		return (NULL);
	y = 0;
	while (pars->av[pars->i] && word_count > 0)
	{
		while (pars->av[pars->i] && is_whitespace(pars->av[pars->i]))
			pars->i++;
		buf[y] = copy_str(pars);
		if (!buf[y])
			return (NULL);
		y++;
		// if (get_next_word(pars) == 0)
		// 	break ;
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
	free(av);
	return (ret);
}
