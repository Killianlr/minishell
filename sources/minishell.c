/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 11:18:43 by kle-rest          #+#    #+#             */
/*   Updated: 2024/01/18 23:17:38 by flavian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int g_signal = 0;

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
	s_cmd	*cmd;
	int		nb_cmd;

	while (1)
	{
		g_signal = 0;
		garbage->pipe = 0;
		garbage->s_cmd = NULL;
		garbage->line = ft_prompt(garbage);
		if ((int)ft_strlen(garbage->line))
			cmd = parsing(garbage);
		else
			cmd = NULL;
		free(garbage->line);
		nb_cmd = ft_lstsize_cmd(cmd);
		if (nb_cmd > 1)
			garbage->pipe = 1;
		garbage->s_cmd = cmd;
		setup_exec(garbage, cmd, nb_cmd);
		free_cmd(garbage->s_cmd);
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
	garbage->ret = 0;
	in_minishell(garbage);
	free_all(garbage);
	return (0);
}
