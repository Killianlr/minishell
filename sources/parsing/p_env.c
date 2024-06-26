/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 11:49:41 by flavian           #+#    #+#             */
/*   Updated: 2024/01/22 22:24:37 by flavian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	after_var_env(t_pars *pars, int i)
{
	int	y;

	y = i;
	if (!pars->av || y < 0)
		return (0);
	while (pars->av[y] && !is_whitespace(pars->av[y])
		&& !is_sep(pars->av[y]) && !is_quote(pars->av[y]))
		y++;
	if (!pars->av[y])
		return (-1);
	return (y);
}

char	*is_ret_val(char *str, int ret_val)
{
	char	*ret;

	ret = NULL;
	if (str[0] == '?')
	{
		ret = ft_itoa(ret_val);
		return (ret);
	}
	else
		return (NULL);
}

char	*get_var_env_bis(t_pars *pars, int start_index, int length, int ret_val)
{
	char	*buf;
	int		j;
	int		y;

	buf = malloc(sizeof(char) * (length + 1));
	if (!buf)
		return (NULL);
	j = start_index;
	y = 0;
	while (pars->av[j] && !is_whitespace(pars->av[j])
		&& !is_sep(pars->av[j]) && !is_quote(pars->av[j]))
	{
		buf[y++] = pars->av[j++];
	}
	buf[y] = 0;
	if (!buf[0])
	{
		free(buf);
		return (NULL);
	}
	buf = get_in_env(pars->env, buf, ret_val);
	return (buf);
}

char	*get_var_env(t_pars *pars, int i, int ret_val)
{
	char	*buf;
	int		y;
	int		j;

	while (pars->av[i] && !is_var_env(pars->av[i]))
		i++;
	if (!pars->av[i])
		return (NULL);
	if (pars->av[i + 1] && !is_quote(pars->av[i + 1])
		&& !is_whitespace(pars->av[i + 1]))
		i++;
	else if (!pars->av[i + 1] || (is_whitespace(pars->av[i + 1]))
		|| is_quote(pars->av[i + 1]))
		return (ft_strdup("$"));
	y = 0;
	j = i;
	while (pars->av[j] && !is_whitespace(pars->av[j])
		&& !is_sep(pars->av[j]) && !is_quote(pars->av[j]))
	{
		j++;
		y++;
	}
	buf = get_var_env_bis(pars, i, y, ret_val);
	return (buf);
}
