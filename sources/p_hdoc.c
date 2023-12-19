/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_hdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 11:47:42 by flavian           #+#    #+#             */
/*   Updated: 2023/12/19 14:22:28 by flavian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	size_for_malloc_del(t_pars *pars)
{
	char	*tmp;
	int		set;
	int		size;
	int		i;

	size = 0;
	set = 0;
	tmp = NULL;
	i = pars->i;
	while (pars->av[i] && is_whitespace(pars->av[i]))
		i++;
	if (pars->av[i] == '<' && pars->av[i + 1] == '<')
		i += 2;
	else
		return (0);
	while (pars->av[i])
	{
		if (set == is_quote(pars->av[i]) && set > 0)
		{
			set = 0;
			i++;
		}
		if (is_quote(pars->av[i]) && set == 0)
		{
			set = is_quote(pars->av[i]);
			tmp = handle_quotes(pars, i);
			size += (int) ft_strlen(tmp);
			i++;
			while (is_quote(pars->av[i]) && set > 0)
				i++;
		}
		if (is_whitespace(pars->av[i]))
			i++;
		if (is_printable(pars->av[i]) && !is_sep(pars->av[i])
			&& !is_quote(pars->av[i]))
		{
			size++;
			i++;
		}
		if (is_sep(pars->av[i]))
		{
			free(tmp);
			return (size);
		}
	}
	if (tmp)
		free(tmp);
	return (size);
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


int	size_for_del(t_pars *pars, int l)
{
	int	i;
	int	count;
	int	status;

	i = l;
	count = 0;
	status = 0;
	while (pars->av[i])
	{
		if ((is_whitespace(pars->av[i]) || is_sep(pars->av[i])) && status == 0)
			break ;
		else if (is_quote(pars->av[i]) > 0
			&& is_quote(pars->av[i]) == is_quote(pars->av[i + 1])
				&& status == 0) 
			count++;
		else if (is_quote(pars->av[i]) > 0 && status == 0)
			status = is_quote(pars->av[i]);
		else
		{
			while (status > 0)
			{
				if (status == is_quote(pars->av[i]))
					status = 0;
				count++;
				i++;
			}
		}
		if (is_printable(pars->av[i]) && !is_quote(pars->av[i])
			&& !is_sep(pars->av[i]))
			count++;
		i++;
	}
	return (count);
}

char	*get_del_hdoc(t_pars *pars)
{
	int		i;
	int		y;
	int		size;
	char	*ret;

	i = pars->i;
	while (pars->av[i] && is_whitespace(pars->av[i]))
		i++;
	if (!pars->av[i])
		return (NULL);
	while (is_sep(pars->av[i]) || is_whitespace(pars->av[i]))
		i++;
	size = size_for_del(pars, i);
	printf("size = %d\n", size);
	ret = malloc(sizeof(char) * (size + 1));
	if (!ret)
		return (NULL);
	y = 0;
	while (pars->av[i] && y < size)
	{
		if (is_sep(pars->av[i]) || is_whitespace(pars->av[i]))
			break ;
		if (is_quote(pars->av[i]) > 0 
			&& is_quote(pars->av[i]) == is_quote(pars->av[i + 1]) && size == 1)
		{
			printf("in\n");
			free(ret);
			return (ft_strdup(""));
		}
		if (is_quote(pars->av[i]))
			i++;
		ret[y++] = pars->av[i++];
	}
	ret[y] = 0;
	return (ret);
}
