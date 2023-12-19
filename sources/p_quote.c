/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_quote.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:06:01 by flavian           #+#    #+#             */
/*   Updated: 2023/12/19 11:44:00 by flavian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_quote(t_pars *pars)
{
	int	i;
	int	s_count;
	int	d_count;


	i = 0;
	s_count = 0;
	d_count = 0;
	while (pars->av[i])
	{
		if (is_quote(pars->av[i]) == 1)
			s_count++;
		if (is_quote(pars->av[i]) == 2)
			d_count++;
		i++;
	}
	if (s_count % 2 != 0 || d_count % 2 != 0)
		return (1);
	return (s_count + d_count);
}

int	quote_is_closed(t_pars *pars, int l)
{
	int	target;
	int		i;

	target = 0;
	i = l;
	if (count_quote(pars) % 2 != 0)
	{
		ft_printf("Error 1, quote unclosed\n");
		return (0);
	}
	else
	{
		while (pars->av[i])
		{
			if (target == 0 && is_quote(pars->av[i]) > 0)
			{
				target = is_quote(pars->av[i]);
				i++;
			}
			if (target > 0 && target == is_quote(pars->av[i]))
				return (i);
			i++;
		}
	}
	// ft_printf("Error 2, quote unclosed\n");
	return (0);
}

char	*handle_quotes(t_pars *pars, int l)
{
	char	*buf;
	int		end;
	int		y;
	int		i;

	i = l;
	end = quote_is_closed(pars, i);
	if (end == 0)
		return (NULL);
	while (pars->av[i] && !is_quote(pars->av[i]))
		i++;
	buf = malloc(sizeof(char) * (end - i + 1));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	y = 0;
	if (is_quote(pars->av[i]) == 1)
	{
		i++;
		while (pars->av[i] && i < end)
			buf[y++] = pars->av[i++];
	}
	else if (is_quote(pars->av[i]) == 2)
	{
		i++;
		while (pars->av[i] && i < end && is_quote(pars->av[i]) != 2)
		{
			if (is_var_env(pars->av[i]))
			{
				buf = ms_strjoin(buf, get_var_env(pars, i), 3);
				if (!buf)
					return (NULL);
				y = ft_strlen(buf);
				i = after_var_env(pars, i);
				if (i < 0)
					break ;
			}
			if (is_quote(pars->av[i]) == 2)
			{
				buf[y] = 0;
				return (buf);
			}
			buf[y++] = pars->av[i++];
		}
	}
	buf[y] = 0;
	return (buf);
}
