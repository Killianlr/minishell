#include "../includes/minishell.h"

t_cmd	*define_cmd(t_pars	*pars)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->fd_in = 0;
	cmd->fd_out = 0;
	cmd->hdoc = 0;
	cmd->next = NULL;
	if (!set_cmd_fd(pars, cmd) || !check_fd(cmd))
	{
		// printf("BAAD fd\n");
		free(cmd);
		return (NULL);
	}
	cmd->line = get_cmd_line(pars);
	return (cmd);
}

t_cmd	*create_cmd(t_pars	*pars)
{
	t_cmd	*cmd;
	t_cmd	*first;
	int		pipe_count;

	// cmd = NULL;
	// first = NULL;
	pipe_count = ft_count_pipe(pars->av);
	cmd = define_cmd(pars);
	if (!cmd)
		return (NULL);
	first = cmd;
	while (pipe_count)
	{
		// printf("IS PIPE\n");
		cmd->next = define_cmd(pars);
		if (!cmd->next)
			break ;
		cmd = cmd->next;
		pipe_count--;
	}
	cmd->next = NULL;
	return (first);
}

char	*check_sep_count(char *str)
{
	int	i;
	int	sep_val;
	int	set;

	i = 0;
	sep_val = 0;
	set = 0;
	while (str[i])
	{
		if (ft_find_sep_val(str[i]) > 0)
		{
			if (sep_val && ft_find_sep_val(str[i]) !=  1
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

t_cmd	*parsing(t_gc *garbage)
{
	t_pars	*pars;
	t_cmd	*cmd;

	cmd = NULL;
	pars = malloc(sizeof(t_pars));
	if (!pars)
		return (NULL);
	if (!check_sep_count(garbage->line))
		return (NULL);
	pars->av = garbage->line;
	if (!pars->av)
	{
		printf("PARSING ERROR\n");
		return (NULL);
	}
	pars->env = garbage->blts->env;
	pars->i = 0;
	pars->av = new_str(pars, garbage->ret);
	// printf("new_av = %s\n", pars->av);
	cmd = create_cmd(pars);
	if (!cmd)
	{
		free(pars);
		return (NULL);
	}
	free(pars->av);
	free(pars);
	// print_cmd(cmd);
	if (cmd->hdoc)
		open(".heredoc_tmp", O_RDONLY);
	return (cmd);
}