#include "../includes/minishell.h"

s_cmd	*define_cmd(s_pars	*pars)
{
	s_cmd	*cmd;

	cmd = malloc(sizeof(s_cmd));
	if (!cmd)
		return (NULL);
	cmd->fd_in = 0;
	cmd->fd_out = 0;
	if (!set_cmd_fd(pars, cmd))
	{
		free(cmd);
		return (NULL);
	}
	cmd->line = get_cmd_line(pars);
	return (cmd);
}

s_cmd	*create_cmd(s_pars	*pars)
{
	s_cmd	*cmd;
	s_cmd	*first;
	int		pipe_count;

	cmd = NULL;
	first = NULL;
	pipe_count = ft_count_pipe(pars->av);
	//printf("pipe_count = %d\n", pipe_count);
	cmd = define_cmd(pars);
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

s_cmd	*parsing(char *str)
{
	s_pars	*pars;
	s_cmd	*cmd;

	cmd = NULL;
	pars = malloc(sizeof(s_pars));
	if (!pars)
		return (NULL);
	pars->av = check_sep_count(str);
	//printf("pars->av = %s\n", pars->av);
	if (!pars->av)
	{
		printf("PARSING ERROR\n");
		return (NULL);
	}
	pars->env = NULL;
	pars->i = 0;
	cmd = create_cmd(pars);
	if (!cmd)
	{
		free(pars);
		return (NULL);
	}
	free(pars);
	//print_cmd(cmd);
	return (cmd);
}