/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 11:18:43 by kle-rest          #+#    #+#             */
/*   Updated: 2023/12/21 18:44:25 by kle-rest         ###   ########.fr       */
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
	i = ft_export(garbage, args);
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

int	test(t_arg *s_cmd)
{
	t_arg	*tmp;
	int		i;

	if (!s_cmd->sep && !s_cmd->next)
		return (0);
	if (s_cmd->sep && !s_cmd->next)
	{
		printf("bash: syntax error near unexpected token `newline'\n");
		return (1);
	}
	tmp = s_cmd->next;
	while (tmp->next)
	{
		i = 0;
		if (tmp->sep && !tmp->next)
		{
			printf("bash: syntax error near unexpected token `newline'\n");
			return (1);
		}
		while (tmp->line[0] && tmp->line[0][i])
		{
			if (!ft_isalnum(tmp->line[0][i]))
			{
				printf("minishell: syntax error near unexpected token `%c'\n", tmp->line[0][i]);
				return (1);
			}
			i++;
		}
		tmp = tmp->next;
	}
	i = 0;
	if (tmp->sep && !tmp->next)
	{
		printf("bash: syntax error near unexpected token `newline'\n");
		return (1);
	}
	while (tmp->line[0] && tmp->line[0][i])
	{
		printf("tmp->line[0][%d] %c\n", i, tmp->line[0][i]);
		if (!ft_isalnum(tmp->line[0][i]))
		{
			printf("minishell: syntax error near unexpected token `%c'\n", tmp->line[0][i]);
			return (1);
		}
		i++;
	}
	return (0);
}

int	loop_lst(char *str, t_arg *s_cm, t_gc *garbage)
{
	t_exec	ex;
	t_arg	*s_cmd;

	s_cmd = s_cm;
	if (!str)
		return (0);
	garbage->nb_exec = ft_lstsize_targ(s_cmd);
	if (init_t_exec(&ex, s_cmd, garbage))
        return (1);
	while (garbage->nb_exec)
	{
		// printf("-----------loooooping--------\n");
		if (clear_or_exit(s_cmd->line))
			return (1);
		ft_init_exec(s_cmd, garbage, &ex);
		waitpid(-1, NULL, 0);
		s_cmd = s_cmd->next;
		garbage->nb_exec--;
		for (int b = 0; garbage->blts->env[b]; b++)
			printf("%s\n", garbage->blts->env[b]);	
	}
	free_tab(ex.paths);
	// printf("fin de looop\n");
	free_parsing(garbage->arg);
	// printf("apres free_parsing\n");
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
	while (1)
	{
		garbage->arg = NULL;
		garbage->line = ft_prompt();
		if ((int)ft_strlen(garbage->line))
			garbage->arg = main_pars(garbage->line, garbage->blts, garbage);
		free(garbage->line);
		// if (test(garbage->arg))
		// 	garbage->arg->line = NULL;
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
