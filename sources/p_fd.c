#include "../includes/minishell.h"

int	check_fd(s_cmd *cmd)
{
	if (cmd->fd_in < 0 || cmd->fd_out < 0)
		return (0);
	return (1);
}

int	find_type_of_sep(s_pars *pars, int i)
{
	int	ret;
	int	set;
	
	ret = 0;
	set = 0;
	while (pars->av[i] && ft_find_sep_val(pars->av[i])
			&& !is_whitespace(pars->av[i]))
	{
		if (!set && ft_find_sep_val(pars->av[i]) == 2)
			ret = 1;
		else if (!set && ft_find_sep_val(pars->av[i]) == 3)
			ret = 2;
		else if (set && ft_find_sep_val(pars->av[i]) == 2)
			ret = 3;
		else if (set && ft_find_sep_val(pars->av[i]) == 3)
			ret = 4;
		i++;
		set = ft_find_sep_val(pars->av[i]);
	}
	return (ret);	
}

char	*find_file_name(s_pars *pars, int i)
{
	char	*ret;
	int		len;
	int		y;

	ret = NULL;
	while (pars->av[i] && (ft_find_sep_val(pars->av[i]) > 1
			|| is_whitespace(pars->av[i])))
		i++;
	if (!pars->av[i])
		return (0);
	len = 0;
	y = i;
	while (pars->av[y] && !is_whitespace(pars->av[y])
			&& !ft_find_sep_val(pars->av[y]))
	{
		len++;
		y++;
	}
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	y = 0;
	while (pars->av[i] && !is_whitespace(pars->av[i])
			&& !ft_find_sep_val(pars->av[i]))
		ret[y++] = pars->av[i++];
	ret[y] = 0;
	return (ret);	
}

int	set_cmd_fd(s_pars *pars, s_cmd *cmd)
{
	int	i;
	char	*file_name;
	int		type_of_sep;

	i = pars->i;
	if (ft_find_sep_val(pars->av[i]) == 1)
		i++;
	type_of_sep = 0;
	while (pars->av[i] && ft_find_sep_val(pars->av[i]) != 1)
	{
		if (ft_find_sep_val(pars->av[i]) > 1)
		{
			file_name = find_file_name(pars, i);
			if (!file_name)
				return (0);
			type_of_sep = find_type_of_sep(pars, i);
			if (type_of_sep == 1 || type_of_sep == 3)
			{
				if (cmd->fd_in)
				{
					close(cmd->fd_in);
					cmd->fd_in = parsing_open(file_name, type_of_sep, cmd);
				}
				else
					cmd->fd_in = parsing_open(file_name, type_of_sep, cmd);
			}
			if (type_of_sep == 2 || type_of_sep == 4)
			{
				if (cmd->fd_out)
				{
					close(cmd->fd_out);
					cmd->fd_out = parsing_open(file_name, type_of_sep, cmd);
				}
				else
					cmd->fd_out = parsing_open(file_name, type_of_sep, cmd);
			}
			free(file_name);
			i = new_val_i(pars, i);
			if (!pars->av[i])
				return (1);
		}
		i++;
	}
	return (1);
}