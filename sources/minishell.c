/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 11:18:43 by kle-rest          #+#    #+#             */
/*   Updated: 2024/01/04 11:27:23 by flavian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	clear_or_exit(char **str)
{
	
	if (!str || !str[0])
		return (0);
	if (!ft_strncmp("clear", str[0], ft_strlen(str[0])))
	{
		if (str[1])
		{
			if (!ft_strncmp("history", str[1], ft_strlen(str[1])))
				rl_clear_history();
		}
	}
	if (!ft_strncmp("exit", str[0], 4) && ft_strlen(str[0]) == 4)
		return (1);
	else
		return (0);
}

int	is_builtins(t_gc *garbage, char **args)
{
	int	i;

	i = 0;
	if (!args)
		return (0);
	i = ft_env(garbage, args);
	if (i == 1)
		exit_error(garbage);
	else if (i == 2)
		return (2);
	i = ft_pwd(garbage, args);
	if (i == 1)
		exit_error(garbage);
	else if (i == 2)
		return (2);
	i = ft_export(garbage, args, 0);
	if (i == 1)
		exit_error(garbage);
	else if (i == 2)
		return (2);
	i = ft_unset(garbage, args);
	if (i == 1)
		exit_error(garbage);
	else if (i == 2)
		return (2);
	i = ft_cd(garbage, args);
	if (i == 1)
		exit_error(garbage);
	else if (i == 2)
		return (2);
	i = ft_echo(garbage, args);
	if (i == 1)
		exit_error(garbage);
	else if (i == 2)
		return (2);
	i = ft_define_var(garbage, args);
	if (i == 1)
		exit_error(garbage);
	else if (i == 2)
		return (2);
	i = ft_put_ret_value(garbage, args);
	if (i == 1)
		exit_error(garbage);
	else if (i == 2)
		return (2);
	return (0);
}

int	loop_lst(char *str, t_arg *s_cm, t_gc *garbage)
{
	t_exec	ex;
	t_arg	*s_cmd;

	s_cmd = s_cm;
	if (!str || !s_cm)
		return (0);
	garbage->nb_exec = ft_lstsize_targ(s_cmd);
	if (init_t_exec(&ex, s_cmd, garbage))
        return (1);
	while (garbage->nb_exec)
	{
		if (clear_or_exit(s_cmd->line))
		{
			free_tab(ex.paths);
			return (1);
		}
		if (!garbage->go)
			break ;
		ft_init_exec(s_cmd, garbage, &ex);
		waitpid(-1, NULL, 0);
		if (s_cmd->next)
			s_cmd = s_cmd->next;
		garbage->nb_exec--;
	}
	free_tab(ex.paths);
	garbage->arg = s_cm;
	free_parsing(garbage->arg);
	return (0);
}

t_gc	*in_minishell(void)
{
	t_gc	*garbage;

	garbage = malloc(sizeof(t_gc));
	if (!garbage)
		return (NULL);
	garbage->blts = set_builtins();
	if (!garbage->blts)
	{
		free(garbage);
		return (NULL);
	}
	garbage->nb_exec = 0;
	garbage->ret = 0;
	garbage->go = 1;
	garbage->fd_hdoc = 0;
	while (1)
	{
		garbage->arg = NULL;
		garbage->line = ft_prompt();
		if ((int)ft_strlen(garbage->line))
			garbage->arg = main_pars(garbage->line, garbage->blts, garbage);
		free(garbage->line);
		if (loop_lst(garbage->line, garbage->arg, garbage))
			break ;
	}
	return (garbage);
}

int	main(void)
{
	t_gc	*garbage;

	if (clear_terminal())
		return (1);
	if (signal_init())
		return (1);
	garbage = in_minishell();
	free_all(garbage);
	return (0);
}
