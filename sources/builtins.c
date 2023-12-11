
#include "../includes/minishell.h"

int	ft_export(t_gc *garbage)
{
	char **args;
	int		i;

	if (!garbage->line)
		return (0);
	args = ft_split(garbage->line, ' ');
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
		}
		else
			update_export(garbage, args);
	}
	// A RETIRER //
	free(args[0]);
	free(args);
	return (0);
}

int	ft_env(t_gc *garbage)
{
	char **args;

	if (!garbage->line)
		return (0);
	args = ft_split(garbage->line, ' ');
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
	// A RETIRER //
	free_tab(args);
	free(args);
	return (0);
}

int	ft_pwd(t_gc *garbage)
{
	char **args;

	if (!garbage->line)
		return (0);
	args = ft_split(garbage->line, ' ');
	if (!ft_strncmp(args[0], "pwd", 4))
	{
		free(garbage->blts->pwd);
		garbage->blts->pwd = get_pwd();
		printf("%s\n", garbage->blts->pwd);
	}
	// A RETIRER //
	free_tab(args);
	free(args);
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