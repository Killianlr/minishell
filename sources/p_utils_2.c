/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fserpe <fserpe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:39:23 by fserpe            #+#    #+#             */
/*   Updated: 2023/12/19 16:39:44 by fserpe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
