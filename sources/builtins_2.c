
#include "../includes/minishell.h"

int	loop_echo_write(char **args, int i, t_gc *garbage, int pid)
{
	while (args[i] && args[i + 1] && !pid)
	{
		if (!ft_strncmp(args[i], "$?", 4))
			ft_putnbr_fd(garbage->ret, STDOUT_FILENO);
		else
		{
			write(STDOUT_FILENO, args[i], ft_strlen(args[i]));
			write(STDOUT_FILENO, " ", 1);
			i++;
		}
	}
	return (i);
}

int	option_echo(char *tiret_n)
{
	int	i;

	i = 0;
	if (!tiret_n[i])
		return (1);
	if (tiret_n[i] != '-')
		return (1);
	i++;
	while (tiret_n[i] && tiret_n[i] == 'n')
		i++;
	if (i == (int)ft_strlen(tiret_n))
		return (0);
	else
		return (1);
}

int	ft_echo(t_gc *garbage, char **args, int pid)
{
	int	e;
	int	i;

	e = 0;
	i = 1;
	if (!garbage->line)
		return (0);
	if (!ft_strncmp(args[0], "echo", ft_strlen(args[0])))
	{
		while (args[i] && !option_echo(args[i]))
		{
			i++;
			e = 1;
		}
		i = loop_echo_write(args, i, garbage, pid);
		if (args[i] && !ft_strncmp(args[i], "$?", 4) && !pid)
			ft_putnbr_fd(garbage->ret, STDOUT_FILENO);
		else if (!pid)
			write(STDOUT_FILENO, args[i], ft_strlen(args[i]));
		if (!e && !pid)
			write(STDOUT_FILENO, "\n", 1);
		garbage->ret = 0;
		return (2);
	}
	return (0);
}

int	ft_cd(t_gc *garbage, char **args, int pid)
{
	// if (!garbage->line)
	// 	return (0);
	if (!ft_strncmp(args[0], "cd", 3))
	{
		garbage->ret = 0;
		if (!args[1])
			return (2);
		if (chdir(args[1]))
		{
			if (pid)
				printf("minishell: cd: %s: No such file or directory\n", args[1]);
			garbage->ret = 1;
			printf("ret = %d\n", garbage->ret);
			return (2);
		}
		else
		{
			if (cd_set_pwd(garbage->blts))
			{
				garbage->ret = 2;
				return (1);
			}
		}
		return (2);
	}
	return (0);
}

int	ft_pwd(t_gc *garbage, char **args, int pid)
{
	char	*pwd;

	if (!garbage->line || pid)
		return (0);
	if (!ft_strncmp(args[0], "pwd", 4))
	{
		garbage->ret = 0;
		pwd = get_pwd();
		if (!pwd)
		{
		garbage->ret = 1;
			return (1);
		}
		printf("%s\n", pwd);
		free(pwd);
		return (2);
	}
	return (0);
}
