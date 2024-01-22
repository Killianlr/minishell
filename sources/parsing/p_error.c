/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_error.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fserpe <fserpe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:09:20 by fserpe            #+#    #+#             */
/*   Updated: 2024/01/22 19:17:20 by fserpe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		ret_error_file_sep(char *token)
{
	printf("minishell: syntax error near unexpected token `%s'\n", token);
	free(token);
	return (0);
}

int		error_file_sep(char *str, int i)
{
	char	*token;
	int		y;

	if (str[i + 1])
		i++;
	else
	{
		token = ft_strdup("newline");
		return (ret_error_file_sep(token));
	}
	token = ft_calloc(3 , 1);
	if (!token)
		return (1);
	while (str[i] && !ft_find_sep_val(str[i]))
		i++;
	y = 0;
	while (str[i] && ft_find_sep_val(str[i]))
	{
		token[y] = str[i];
		i++;
		y++;
	}
	return (ret_error_file_sep(token));
}

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
