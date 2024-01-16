#include "parsing.h"

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

void	free_tab(char **tabl)
{
	int	i;

	if (!tabl[0])
		return ;
	i = 0;
	while (tabl[i])
	{
		free(tabl[i]);
		i++;
	}
	free(tabl);
}

void	free_cmd(s_cmd *cmd)
{
	s_cmd *tmp;

	if (!cmd)
		return ;
	tmp = cmd->next;
	while (tmp)
	{
		free_tab(cmd->line);
		free(cmd);
		cmd = tmp;
		tmp = cmd->next;
	}
	free_tab(cmd->line);
	free(cmd);
}