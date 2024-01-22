/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_error.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:09:20 by fserpe            #+#    #+#             */
/*   Updated: 2024/01/22 22:30:57 by flavian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*end_get_in_env(t_gie *data, char *ret, int set, char *str)
{
	if (!ret)
	{
		free(data);
		if (str[0])
		{
			free(str);
			return (NULL);
		}
		else
			return (ms_strjoin("$", str, 2));
	}
	else if (ret && set)
	{
		free(data);
		ret = strjoin_env(ret, str, (ft_strlen(ret) + ft_strlen(str)));
		return (ret);
	}
	return (ret);
}

int	ret_error_file_sep(char *token, t_gc *garbage)
{
	printf("minishell: syntax error near unexpected token `%s'\n", token);
	free(token);
	garbage->ret = 2;
	return (0);
}

int	error_file_sep(char *str, int i, t_gc *garbage)
{
	char	*token;
	int		y;

	if (str[i + 1])
		i++;
	else
	{
		token = ft_strdup("newline");
		return (ret_error_file_sep(token, garbage));
	}
	token = ft_calloc(3, 1);
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
	return (ret_error_file_sep(token, garbage));
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
