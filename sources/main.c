
#include "../includes/minishell.h"

int	ft_builting(char *str)
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

void	ft_free(t_gc *garbage)
{
	free(garbage->line);
	printf("FIN DU PROGRAMME\n");
}

void	in_minishell()
{
	t_gc	garbage;

	ctrl_c();
	while (1)
	{
		garbage.line = ft_prompt();
		printf("%s\n", garbage.line);
		if (ft_builting(garbage.line))
			break ;
		if (signal_ctrl_c == 1)
			free(garbage.line);
		signal_ctrl_c = 0;
		free(garbage.line);
	}
	ft_free(&garbage);
}

int main(void)
{
	if (clear_terminal())
		return (0);
	in_minishell();
	return (0);
}
