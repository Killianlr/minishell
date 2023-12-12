
#include "../includes/minishell.h"

int	ft_unset(t_gc *garbage, char **args)
{
	if (!garbage->line)
		return (0);
	if (!ft_strncmp(args[0], "unset", 6))
	{
		if (!args[1])
			return (0);
		if (del_var_unset(garbage, args))
			return (1);
	}
	return (0);
}

int	ft_export(t_gc *garbage, char **args)
{
	int		i;

	if (!garbage->line)
		return (0);
	i = 0;
	if (!ft_strncmp(args[0], "export", 7))
	{
		if (!args[1])
		{
			while (garbage->blts->exp[i])
			{
				printf("declare -x %s\n", garbage->blts->exp[i]);
				i++;
			}
			return (0);
		}
		if (update_export(garbage, args))
			return (1);
	}
	return (0);
}

int	ft_env(t_gc *garbage, char **args)
{
	if (!garbage->line)
		return (0);
	if (!ft_strncmp(args[0], "env", 4))
	{
		if (print_env(garbage))
		{
			free_tab(garbage->blts->env);
			free_blts(garbage->blts);
			free(garbage->blts);
			return (1);
		}
	}
	return (0);
}

int	ft_pwd(t_gc *garbage, char **args)
{
	if (!garbage->line)
		return (0);
	if (!ft_strncmp(args[0], "pwd", 4))
	{
		free(garbage->blts->pwd);
		garbage->blts->pwd = get_pwd();
		printf("%s\n", garbage->blts->pwd);
	}
	return (0);
}

t_bui   *set_builtins(void)
{
    t_bui       *blts;
	extern char **environ;

	blts = malloc(sizeof(t_bui));
	if (!blts)
		return (NULL);
	blts->exi_env = 1;
	if (!*environ)
		blts->exi_env = 0;
	if (set_env(blts))
	{
		free(blts);
		return (NULL);
	}
	if (set_export(blts))
	{
		free(blts);
		return (NULL);
	}
	return (blts);
}