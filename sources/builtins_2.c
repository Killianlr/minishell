
#include "../includes/minishell.h"

int	ft_echo_2(t_gc *garbage, char **args)
{
	if (!garbage->line)
		return (0);
	if (!ft_strncmp(args[0], "echo", ft_strlen(args[0])))
	{
		garbage->ret = 0;
		return (2);
	}
	return (0);
}

int	ft_echo(t_gc *garbage, char **args)
{
	int	e;
	int	i;

	e = 0;
	i = 1;
	if (!garbage->line)
		return (0);
	if (!ft_strncmp(args[0], "echo", ft_strlen(args[0])))
	{
		if (!ft_strncmp(args[1], "-n", ft_strlen(args[0])))
			e = 1;
		if (e)
		{
			while (args[i] && !ft_strncmp(args[i], "-n", ft_strlen(args[i])))
				i++;
		}
		while (args[i] && args[i + 1])
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
		if (!ft_strncmp(args[i], "$?", 4))
			ft_putnbr_fd(garbage->ret, STDOUT_FILENO);
		else
			write(STDOUT_FILENO, args[i], ft_strlen(args[i]));
		if (!e)
			write(STDOUT_FILENO, "\n", 1);
		garbage->ret = 0;
		return (2);
	}
	return (0);
}

int	ft_cd_2(t_gc *garbage, char **args)
{
	if (!garbage->line)
		return (0);
	if (!ft_strncmp(args[0], "cd", 3))
	{
		garbage->ret = 0;
		if (!args[1])
			return (2);
		if (chdir(args[1]))
		{
			garbage->ret = 1;
			garbage->go = 0;
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

int	ft_cd(t_gc *garbage, char **args)
{
	if (!garbage->line)
		return (0);
	if (!ft_strncmp(args[0], "cd", 3))
	{
		garbage->ret = 0;
		if (!args[1])
			return (2);
		if (chdir(args[1]))
		{
			printf("minishell: cd: %s: No such file or directory\n", args[1]);
			garbage->ret = 1;
			garbage->go = 0;
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

int	ft_pwd(t_gc *garbage, char **args)
{
	char	*pwd;

	if (!garbage->line)
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
