
#include "../includes/minishell.h"

int	replace_old_exp(t_bui *blts, char *arg_w_db_q)
{
	int		i;
	char	**new_export;
	int		size_tab;

	i = 0;
	if (!arg_w_db_q)
		return (1);
	size_tab = ft_strlen_tab(blts->exp);
	new_export = malloc(sizeof(char *) * (size_tab + 2));
	if (!new_export)
		return (1);
	while (blts->exp[i])
	{
		new_export[i] = blts->exp[i];
		i++;
	}
	new_export[i] = arg_w_db_q;
	new_export[i + 1] = NULL;
	free(blts->exp);
	blts->exp = new_export;
	return (0);
}

int	add_var_export(t_gc *garbage, char *arg)
{
	int		i;
	char	*arg_w_db_q;

	i = 0;
	if (check_var_exist(garbage, arg))
		return (0);
	arg_w_db_q = ft_strdup(arg);
	while (arg[i])
	{
		if (arg[i] == '=')
		{
			printf("add var to env\n");
			if (add_var_env(garbage->blts, arg))
				return (1);
			free(arg_w_db_q);
			arg_w_db_q = add_db_quote(arg);
		}
		i++;
	}
	if (replace_old_exp(garbage->blts, arg_w_db_q))
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
			if ((!ft_isalpha(args[i][j]) && args[i][j] != '=')
				|| (!j && args[i][j] == '='))
			{
				printf("minishell: export: `%c': not a valid identifier\n", args[i][j]);
				break ;
			}
			if (args[i][j] == '=')
				break ;
			j++;
		}
		if (j == (int)ft_strlen(args[i]) || args[i][j] == '=')
		{
			if (add_var_export(garbage, args[i]))
				return (1);
		}
		i++;
	}
	return (0);
}

int	set_export(t_bui *blts)
{
	blts->exp = ft_sort_tab(blts->env);
	if (!blts->exp)
	{
		free_blts(blts);
		return (1);
	}
	return (0);
}