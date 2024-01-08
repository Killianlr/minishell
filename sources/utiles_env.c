
#include "../includes/minishell.h"

char	*remove_quote(char *str)
{
	int		i;
	int		q;
	char	*dest;

	i = 0;
	q = 0;
	while (str[i])
	{
		if (str[i] == '"')
			q++;
		i++;
	}
	dest = malloc(sizeof(char) * (ft_strlen(str) - q + 1));
	if (!dest)
		return (NULL);
	i = 0;
	q = 0;
	while (str[i + q])
	{
		while (str[i + q] == '"')
			q++;
		if (!str[i + q])
			break ;
		dest[i] = str[i + q];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

int	print_env(t_gc *garbage)
{
	int	i;

	i = 0;
	while (garbage->blts->env[i])
	{
		printf("%s\n", garbage->blts->env[i]);
		i++;
	}
	return (0);
}

int	update_env(t_bui *blts)
{
	int		i;
	int		e;
	char	*oldpwd;

	i = 0;
	e = 0;
	oldpwd = NULL;
	while (blts->env[i])
	{
		if (!ft_strncmp("PWD", blts->env[i], ft_size_var_env(blts->env[i])))
		{
			oldpwd = ft_strdup(blts->env[i] + 4);
			free(blts->env[i]);
			free(blts->pwd);
			blts->pwd = get_pwd();
			if (!blts->pwd)
				return (1);
			blts->env[i] = ft_strjoin("PWD=", blts->pwd);
			if (!blts->env[i])
				return (1);
		}
		i++;
	}
	if (!oldpwd)
	{
		go_to_find_var_and_del(blts, "OLDPWD");
		e = 1;
	}
	if (blts->uoldpwd)
		free(oldpwd);
	i = 0;
	while (blts->env[i] && !e)
	{
		if (!ft_strncmp("OLDPWD", blts->env[i], 6))
		{
			free(blts->env[i]);
			blts->env[i] = ft_strjoin_fs2("OLDPWD=", oldpwd);
			if (!blts->env[i])
				return (1);
		}
		i++;
	}
	return (0);
}

int	it_is_an_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}
