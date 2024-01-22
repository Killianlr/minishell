/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_size_for_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 19:27:47 by flavian           #+#    #+#             */
/*   Updated: 2024/01/18 20:53:01 by flavian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void	size_for_quote_2(char *str, t_sfl *data)
// {
// 	while (str[data->i] && ft_find_sep_val(str[data->i]) != 1)
// 	{
// 		if (is_quote(str[data->i]))
// 		{
// 			data->quote = handle_quotes(str, data->i);
// 			data->count += (int)ft_strlen(data->quote);
// 			free(data->quote);
// 			data->i = quote_is_closed(str, data->i);
// 			if (data->i == 0)
// 				return ;
// 		}
// 		else
// 			data->count++;
// 		data->i++;
// 	}
// }

// int	size_for_quote(char *str)
// {
// 	t_sfl	*data;
// 	int		ret;

// 	data = malloc(sizeof(t_sfl));
// 	if (!data)
// 		return (-1);
// 	data->i = 0;
// 	data->count = 0;
// 	data->quote = NULL;
// 	data->tmp = NULL;
// 	size_for_quote_2(str, data);
// 	ret = data->count;
// 	free(data);
// 	return (ret);
// }