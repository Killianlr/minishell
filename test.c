#include "includes/minishell.h"

int	i = 0;

void	dad_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("signal recu\n");
		i = 1;
	}
	else if (sig == SIGQUIT)
	{
		printf("QUIT\n");
		exit(0);
	}
}

int	main(void)
{
	int	pid_main;
	int	pid_minishell;

	pid_main = fork();
	if (pid_main < 0)
		return (printf("error fork\n"));
	if (pid_main == 0)
		exit(0);
	if (pid_main > 0)
	{
		printf("main processus = %d\n", pid_main);
		while (1)
		{
			printf("creation de fork\n");
			pid_minishell = fork();
			if (pid_minishell == 0)
			{
				printf("child\n");
				while(1)
				{
					printf("in minishell\n\n");
					sleep(1);
				}
			}
			printf("parent\n");
			while (!i)
				signal(SIGINT, dad_handler);
			if (i == 1)
			{
				i = 0;
				printf("minishell is killed\n");
				kill(pid_minishell, SIGTERM);
			}
			waitpid(pid_minishell, NULL, 0);
			sleep(2);
		}
	}
	printf("END OF PROGRAME\n");
}