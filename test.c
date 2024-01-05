#include "includes/minishell.h"

void	girl_hanlder(int sig)
{
	printf("in girl handler\n");
	if (sig == SIGCHLD)
	{
		printf("GIRL got bullied\n");
		exit(0);
	}
}

void	boy_hanlder(int sig)
{
	printf("in boy handler\n");
	if (sig == SIGCHLD)
	{
		printf("BOY got bullied\n");
		exit(0);
	}
}

void	mom_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\nMOMY got a call\n");
		kill(0, SIGCHLD);
	}
	else if (sig == SIGQUIT)
	{
		printf("QUIT\n");
		exit(0);
	}
}

void	dad_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\nDADY got a call\n");
		kill(0, SIGCHLD);
	}
	else if (sig == SIGQUIT)
	{
		printf("QUIT\n");
		exit(0);
	}
}

int	main(void)
{
	int	pid;
	int	id;
	// int	pid2;

	id = getpid();
	printf("MY ID = %d\n", id);
	pid = fork();
	// pid2 = fork();
	if (pid < 0)
		return (printf("error fork\n"));
	if (pid == 0)
	{
		signal(SIGCHLD, boy_hanlder);
		while(1)
		{
			printf("BOY is at school\n");
			sleep(1);
		}
	}
	else if (pid > 0)
	{
		printf("DAD pid is = %d\n", pid);
		if (signal(SIGINT, dad_handler))
			printf("got SIGINT\n");
		signal(SIGQUIT, dad_handler);
		while (1)
		{
			printf("DAD is at work\n");
			sleep(2);
		}
	}
	// if (pid2 == 0)
	// {
	// 	signal(SIGCHLD, girl_hanlder);
	// 	while (1)
	// 	{
	// 		printf("GIRL is at school\n");
	// 		sleep(1);
	// 	}
	// }
	// else if (pid2 > 0)
	// {
	// 	printf("MOM pid is = %d\n", pid2);
	// 	signal(SIGINT, mom_handler);
	// 	signal(SIGQUIT, mom_handler);
	// 	while (1)
	// 	{
	// 		printf("MOM is in the kitchen\n");
	// 		sleep(2);
	// 	}
	// 	// return (2);
	// }
	waitpid(pid, NULL, 0);
	// waitpid(pid2, NULL, 0);
	printf("END OF PROGRAME\n");
}