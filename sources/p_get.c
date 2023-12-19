/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_get.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:05:15 by flavian           #+#    #+#             */
/*   Updated: 2023/12/19 11:51:37 by flavian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int	get_next_word(t_pars *pars)
// {
// 	if (!pars->av[pars->i])
// 		return (0);
// 	while (pars->av[pars->i] && !is_printable(pars->av[pars->i])
// 			&& !is_quote(pars->av[pars->i]))
// 		pars->i++;
// 	while (pars->av[pars->i])
// 	{
// 		if (is_quote(pars->av[pars->i]) > 0 && quote_is_closed(pars, pars->i) > 0)
// 			pars->i = quote_is_closed(pars, pars->i);
// 		else if ((is_whitespace(pars->av[pars->i]) || is_sep(pars->av[pars->i])))
// 			return (pars->i);
// 		pars->i++;
// 	}
// 	return (pars->i);
// }

