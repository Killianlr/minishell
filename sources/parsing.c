/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 16:19:50 by fserpe            #+#    #+#             */
/*   Updated: 2024/01/19 20:30:22 by flavian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*check_sep_count_2(char *str, int i, int sep_val, int set)
{
	while (str[i])
	{
		if (ft_find_sep_val(str[i]) > 0)
		{
			if (sep_val && ft_find_sep_val(str[i]) != 1
				&& sep_val != ft_find_sep_val(str[i]))
				return (NULL);
			if (ft_find_sep_val(str[i]) == 1 && sep_val == 1)
				return (NULL);
			set++;
			if (set > 2)
				return (NULL);
			sep_val = ft_find_sep_val(str[i]);
		}
		else if (!ft_find_sep_val(str[i]))
		{
			set = 0;
			sep_val = 0;
		}
		i++;
	}
	return (str);
}

char	*check_sep_count(char *str)
{
	int	i;
	int	sep_val;
	int	set;

	i = 0;
	sep_val = 0;
	set = 0;
	return (check_sep_count_2(str, i, sep_val, set));
}

t_cmd	*define_cmd(t_pars	*pars)
{
	t_cmd	*cmd;

	printf("  IN DEFINE CMD\n");
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->fd_in = 0;
	cmd->fd_out = 0;
	cmd->hdoc = 0;
	cmd->next = NULL;
	if (!set_cmd_fd(pars, cmd) || !check_fd(cmd))
	{
		printf("  OUT DEFINE CMD ERROR\n");
		free(cmd);
		return (NULL);
	}
	cmd->line = get_cmd_line(pars);
	printf("  OUT DEFINE CMD\n");
	return (cmd);
}

t_cmd	*create_cmd(t_pars	*pars)
{
	t_cmd	*cmd;
	t_cmd	*first;
	int		pipe_count;

	printf(" IN CREATE CMD\n");
	pipe_count = ft_count_pipe(pars->av);
	cmd = define_cmd(pars);
	if (!cmd)
	{
		printf(" OUT CREATE CMD ERROR\n");
		return (NULL);
	}
	first = cmd;
	while (pipe_count)
	{
		cmd->next = define_cmd(pars);
		if (!cmd->next)
			break ;
		cmd = cmd->next;
		pipe_count--;
	}
	cmd->next = NULL;
	printf(" OUT CREATE CMD\n");
	return (first);
}

t_cmd	*parsing(t_gc *garbage)
{
	t_pars	*pars;
	t_cmd	*cmd;

	cmd = NULL;
	printf("IN PARSING\n");
	pars = malloc(sizeof(t_pars));
	if (!pars)
		return (NULL);
	pars->av = garbage->line;
	pars->env = garbage->blts->env;
	pars->i = 0;
	pars->av = new_str(pars, garbage->ret);
	if (!pars->av)
	{
		printf("PARSING ERROR\n");
		return (NULL);
	}
	cmd = create_cmd(pars);
	if (!cmd)
	{
		printf("OUT PARSING ERROR\n");
		free(pars);
		return (NULL);
	}
	cmd = end_of_pars(pars, cmd);
	print_cmd(cmd);
	printf("OUT PARSING\n");
	return (cmd);
}
