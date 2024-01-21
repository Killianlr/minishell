/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_is.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:01:34 by flavian           #+#    #+#             */
/*   Updated: 2024/01/21 13:52:32 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_printable(char c)
{
	if (c > 32 && c < 127)
		return (1);
	else
		return (0);
}

int	is_whitespace(char c)
{
	if ((c != '\n' && c > 9 && c < 14) || c == ' ')
		return (1);
	else
		return (0);
}

int	is_sep(char c)
{
	if (!c)
		return (0);
	if (c == '|')
		return (1);
	if (c == '<')
		return (2);
	if (c == '>')
		return (3);
	return (0);
}

int	is_var_env(char c)
{
	if (!c)
		return (0);
	if (c == '$')
		return (1);
	return (0);
}

int	is_quote(char c)
{
	if (!c)
		return (0);
	else if (c == 39)
		return (1);
	else if (c == 34)
		return (2);
	return (0);
}
