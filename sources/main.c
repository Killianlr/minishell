
#include "../includes/minishell.h"

void	ft_free(t_gc *garbage)
{
	if (!garbage)
		return ;
	free(garbage->line);
	printf("FIN DU PROGRAMME\n");
}

int		clear_or_exit(char *str)
{
	if (!str)
		return (0);
	if (!ft_strncmp("clear history", str, 14))
		rl_clear_history();
    if (!ft_strncmp("exit", str, 4) && ft_strlen(str) == 4)
        return (1);
	else
		return (0);
}

int	is_builtins(t_gc *garbage)
{
	char **args;

	if (!garbage->line)
		return (0);
	args = ft_split(garbage->line, ' ');
	if (!ft_strncmp(args[0], "env", 4))
		print_env(garbage);
	if (!ft_strncmp(args[0], "pwd", 4))
		printf("%s\n", garbage->blts->pwd);
	return (0);
}

t_gc	*in_minishell()
{
	t_gc	*garbage;

	garbage = malloc(sizeof(t_gc));
	if (!garbage)
		return (NULL);
	ctrl_c();
	garbage->blts = set_builtins();
	if (!garbage->blts)
	{
		free(garbage);
		return (NULL);
	}
	while (1)
	{
		garbage->line = ft_prompt();
		if (clear_or_exit(garbage->line))
			break ;
		is_builtins(garbage);
		//printf("%s\n", garbage->line); // check prompt (A RETIRER)
		free(garbage->line);
	}
	return (garbage);
}

int main(void)
{
	t_gc	*garbage;

	if (clear_terminal())
		return (1);
	garbage = in_minishell();
	ft_free(garbage);
	return (0);
}
