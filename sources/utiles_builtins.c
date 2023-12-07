
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
