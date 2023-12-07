
#include "../includes/minishell.h"

int	replace_old_exp(t_bui *blts, char *arg)
{
	int		i;
	char	**new_export;
	int		size_tab;

	i = 0;
	size_tab = ft_strlen_tab(blts->exp);
	new_export = malloc(sizeof(char *) * (size_tab + 2));
	if (!new_export)
		return (1);
	while (blts->exp[i])
	{
		new_export[i] = blts->exp[i];
		i++;
	}
	new_export[i] = arg;
	new_export[i + 1] = NULL;
	free(blts->exp);
	blts->exp = new_export;
	i = 0;
	while (blts->exp[i])
	{
		printf("exp[%d] = %s\n", i, blts->exp[i]);
		i++;
	}
	return (0);
}

int	add_var_export(t_gc *garbage, char *arg)
{
	int		i;
	char	*tmp;

	i = 0;
	while (arg[i])
	{
		tmp = arg;
		if (arg[i] == '=')
		{
			arg = add_db_quote(arg);
			if (!arg)
				return (1);
			free(tmp);
		}
		i++;
	}
	if (replace_old_exp(garbage->blts, arg))
		return (1);
	return (0);
}

int	update_export(t_gc *garbage, char **args)
{
	int	i;
	int	j;

	i = 1;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if (!ft_isalpha(args[i][j]))
			{
				printf("minishell: export: `%c': not a valid identifier", args[i][j]);
				break ;
			}
			j++;
		}
		if (j == (int)ft_strlen(args[i]))
		{
			if (add_var_export(garbage, args[i]))
				return (1);
		}
		i++;
	}
	return (0);
}

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