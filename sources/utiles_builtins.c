
#include "../includes/minishell.h"

char    *get_pwd(void)
{
    return (getcwd(NULL, 4096));
}

int	ft_strlen_tab(char **env)
{
	int		i;

	i = 0;
	if (!env[i])
		return (0);
	while (env && *env)
	{
		i++;
		env++;
	}
	return (i);
}

int	ft_size_var_env(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

int	update_var(t_bui *blts, char *arg, int j)
{
	int	i;
	int	e;

	i = 0;
	e = 0;
	while (arg[i])
	{
		if (arg[i] == '=')
			e = 1;
		i++;
	}
	if (!e)
		return (0);
	else if ((int)ft_strlen(arg) > ft_size_var_env(blts->exp[j]) + 1
		|| (int)ft_strlen(blts->exp[j]) == ft_size_var_env(blts->exp[j]))
	{
		printf("update var\n");
		free(blts->exp[j]);
		blts->exp[j] = add_db_quote(arg);
		if (!blts->exp[j])
			return (1);
		return (1);
	}
	return (0);
}

int	check_var_exist(t_gc *garbage, char *arg)
{
	int	i;
	int	len1;
	int	len2;

	i = 0;
	while (garbage->blts->exp[i])
	{
		len1 = ft_size_var_env(arg);
		len2 = ft_size_var_env(garbage->blts->exp[i]);
		if ((len1 - len2) == 0)
		{
			if (!ft_strncmp(arg, garbage->blts->exp[i], len1))
			{
				if (update_var(garbage->blts, arg, i))
					return (0);
				return (1);
			}
		}
		i++;
	}
	return (0);
}
