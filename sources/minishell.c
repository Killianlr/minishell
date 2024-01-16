/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 11:18:43 by kle-rest          #+#    #+#             */
/*   Updated: 2023/12/15 14:27:32 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	clear_history_rl(char **str)
{
	printf("clear or exit\n");
	if (!str)
		return (0);
	if (!ft_strncmp("clear", str[0], ft_strlen(str[0])))
	{
		if (str[1])
		{
			if (!ft_strncmp("history", str[1], ft_strlen(str[1])))
				rl_clear_history();
		}
	}
	return (0);
}

int	in_minishell(t_gc *garbage)
{
	while (1)
	{
		g_signal = 0;
		garbage->args = NULL;
		garbage->line = ft_prompt(garbage);
		if ((int)ft_strlen(garbage->line))
			garbage->args = ft_split(garbage->line, ' ');
		free(garbage->line);
		setup_exec(garbage, garbage->args);
		// if (clear_history_rl(garbage->args))
		// 	break ;
		free_tab(garbage->args);
	}
	return (0);
}

int	main(void)
{
	t_gc	*garbage;

	garbage = malloc(sizeof(t_gc));
	if (!garbage)
		return (1);
	garbage->blts = set_builtins();
	if (!garbage->blts)
	{
		free(garbage);
		return (1);
	}
	if (signal_init())
		return (1);
	in_minishell(garbage);
	free_all(garbage);
	return (0);
}
