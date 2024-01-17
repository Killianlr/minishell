#include "../includes/minishell.h"

void	print_cmd(s_cmd *cmd)
{
	s_cmd	*tmp;

	if (!cmd)
		return ;
	tmp = cmd->next;
	while (tmp)
	{
		if (cmd->line)
		{
			for (int i = 0; cmd->line[i]; i++)
				printf("line[i] = %s[%i]\n", cmd->line[i], i);			
		}
		printf("fd_in = %d & fd_out = %d\n", cmd->fd_in, cmd->fd_out);
		cmd = cmd->next;
		tmp = cmd;
	}
	if (cmd)
	{
		if (cmd->line)
		{
			for (int i = 0; cmd->line[i]; i++)
				printf("line[i] = %s[%i]\n", cmd->line[i], i);			
		}
		printf("fd_in = %d & fd_out = %d\n", cmd->fd_in, cmd->fd_out);
	}

}
