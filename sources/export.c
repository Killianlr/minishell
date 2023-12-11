
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
	new_export[i] = ft_strdup(arg);
	new_export[i + 1] = NULL;
	free(blts->exp);
	blts->exp = new_export;
	return (0);
}

int	add_var_export(t_gc *garbage)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	if (check_var_exist(garbage, garbage->arg->line[i]))
		return (0);
	printf("ici\n");
	while (garbage->arg->line[i])
	{
		j = 0;
		tmp = garbage->arg->line[i];
		if (garbage->arg->line[i][j] == '=')
		{
			if (add_var_env(garbage->blts, garbage->arg->line[i]))
				return (1);
			garbage->arg->line[i] = add_db_quote(garbage->arg->line[i]);
			if (!garbage->arg->line[i])
				return (1);
			free(tmp);
			j++;
		}
		i++;
	}
	if (replace_old_exp(garbage->blts, garbage->arg->line[i]))
		return (1);
	return (0);
}

int	update_export(t_gc *garbage)
{
	int	i;
	int	j;

	i = 1;
	while (garbage->arg->line[i])
	{
		j = 0;
		while (garbage->arg->line[i][j])
		{
			if ((!ft_isalpha(garbage->arg->line[i][j]) && garbage->arg->line[i][j] != '=')
				|| (!j && garbage->arg->line[i][j] == '='))
			{
				printf("minishell: export: `%c': not a valid identifier\n", garbage->arg->line[i][j]);
				break ;
			}
			if (garbage->arg->line[i][j] == '=')
				break ;
			j++;
		}
		if (j == (int)ft_strlen(garbage->arg->line[i]) || garbage->arg->line[i][j] == '=')
		{
			if (add_var_export(garbage))
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