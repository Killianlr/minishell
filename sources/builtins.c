
#include "../includes/minishell.h"

int	ft_export(t_gc *garbage)
{
	int		i;

	if (!garbage->line)
		return (0);
	i = 0;
	if (!ft_strncmp(garbage->arg->line[0], "export", 7))
	{
		if (!garbage->arg->line[1])
		{
			while (garbage->blts->exp[i])
			{
				printf("declare -x %s\n", garbage->blts->exp[i]);
				i++;
			}
		}
		else
			update_export(garbage);
	}
	return (0);
}

int	ft_env(t_gc *garbage)
{
	if (!garbage->line)
		return (0);
	if (!ft_strncmp(garbage->arg->line[0], "env", 4))
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

int	ft_pwd(t_gc *garbage)
{
	if (!garbage->line)
		return (0);
	if (!ft_strncmp(garbage->arg->line[0], "pwd", 4))
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