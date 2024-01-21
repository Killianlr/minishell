/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_error.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:09:20 by fserpe            #+#    #+#             */
/*   Updated: 2024/01/21 13:52:00 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**get_cmd_line_error(char **ret)
{
	free(ret);
	return (NULL);
}

char	*handle_quotes_error(t_hq *data)
{
	free(data);
	return (NULL);
}
