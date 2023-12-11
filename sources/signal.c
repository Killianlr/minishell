
#include "../includes/minishell.h"

void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
   		rl_on_new_line();
    	rl_replace_line("", 0);
    	rl_redisplay();
	}
	else if (signum == SIGQUIT)
	{
		write(1, "\b\b  \b\b", 7);
	}
}

int	signal_init(void)
{
	if (signal(SIGINT, signal_handler))
		return (1);
	if (signal(SIGQUIT, signal_handler))
		return (1);
	return (0);
}