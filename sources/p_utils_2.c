/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:39:23 by fserpe            #+#    #+#             */
/*   Updated: 2024/01/09 15:29:54 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_arg	*post_parsing(t_arg *arg)
{
	t_arg	*first;
	t_arg	*tmp;

	if (!arg)
		return (NULL);
	first = arg;
	tmp = arg->next;
	while (tmp)
	{
		if (arg && arg->sep && !arg->next)
		{
			printf("minishell: syntax error near unexpected token `newline'\n");
			free_parsing(first);
			return (NULL);
		}
		arg = arg->next;
		tmp = arg;
	}
	if (arg && arg->sep && !arg->next)
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		free_parsing(first);
		return (NULL);
	}
	return (first);
}

int	env_strncmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	if (n <= 0)
		return (-1);
	if (!s1 || !s2)
		return (1);
	while (s1[i] == s2[i] && i < n - 1 && s1[i] && s2[i])
		++i;
	if (s1[i + 1] && s1[i + 1] != '=')
		return (1);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ms_strcmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (-1);
	if (n != (int)ft_strlen(s2) - 1)
		return (1);
	if (!s1 || !s2)
		return (1);
	while (s1[i] == s2[i] && i < n - 1 && s1[i] && s2[i])
		++i;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_strncmp_ms(char *s1, char *s2, int size, int l)
{
	int	i;

	i = 0;
	if (size == 0)
		return (0);
	if (!s1 || !s2)
		return (1);
	while (s1[l + i] == s2[i] && i < size - 1 && s1[l + i] && s2[i])
	{
		++i;
	}
	return (s1[l + i] - s2[i]);
}

int	get_var_env_2(t_pars *pars, int i)
{
	int	y;

	y = 0;
	while (pars->av[i] && !is_whitespace(pars->av[i])
		&& !is_sep(pars->av[i]) && !is_quote(pars->av[i]))
	{
		y++;
		i++;
	}
	return (y);
}
