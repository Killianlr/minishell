
#include "../includes/minishell.h"

char    *get_pwd(void)
{
    return (getcwd(NULL, 4096));
}

void	print_env(t_gc *garbage)
{
	int	i;

	i = 0;
	while (garbage->blts->env[i])
	{
		printf("%s\n", garbage->blts->env[i]);
		i++;
	}
}

void    set_env(t_bui *blts)
{
	extern char **environ;
	if (!*environ)
    {
		blts->env = malloc(sizeof(char *) * 2);
		blts->pwd = get_pwd();
        blts->env[0] = ft_strjoin("PWD=", blts->pwd);
        blts->env[1] = NULL;
    }
    else
    {
        blts->env = environ;
        blts->pwd = getenv("PWD");
        if (!blts->pwd)
            blts->pwd = get_pwd();
    }
}

t_bui   *set_builtins(void)
{
    t_bui       *blts;

	blts = malloc(sizeof(t_bui));
	if (!blts)
		return (NULL);
	set_env(blts);
	return (blts);
}