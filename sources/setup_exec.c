
#include "../includes/minishell.h"
#include "../includes/pipex.h"

int check_sep_exec(char *sep, t_exec *ex)
{
    if (!sep)
        return (0);
    if (!ft_strncmp(sep, "<", 2))
        return (1);
    if (!ft_strncmp(sep, ">", 2))
        return (2);
    if (!ft_strncmp(sep, "<<", 3))
        return (3);
    if (!ft_strncmp(sep, ">>", 3))
	{
		return (4);
	}
	printf("ex->r = %d\n", ex->r);
	if (ex->r)
		printf("il faut prendre en compte prev_sep\n");
    return (5);
}

int init_t_exec(t_exec *ex, t_arg *s_cmd, t_gc *garbage)
{
    ex->i = -1;
    ex->o = -1;
    ex->r = 0;
    ex->infile = NULL;
    ex->outfile = NULL;
    ex->paths = ft_split(find_path(garbage->blts->env), ':');
    ex->res_pipex = -1;
	if (count_sep_exec(s_cmd, "<", "<<"))
	{
    	ex->infile = malloc(sizeof(int) * count_sep_exec(s_cmd, "<", "<<"));
    		if (!ex->infile)
        		return (1);
		ex->infile[0] = -1;
	}
	if (count_sep_exec(s_cmd, ">", ">>"))
	{
    	ex->outfile = malloc(sizeof(int) * count_sep_exec(s_cmd, ">", ">>"));
    		if (!ex->outfile)
			{
				return (1);
			}
		ex->outfile[0] = -1;
	}
    return (0);
}

int init_open(t_exec *ex, t_arg *s_cmd, int typeofsep, int fd_hdoc)
{
    if (typeofsep && typeofsep % 2 == 0)
    {
        printf("outfile open\n");
        ex->o++;
        ex->outfile[ex->o] = ft_open(s_cmd->next->line[0], typeofsep, fd_hdoc);
		printf("ok\n");
        if (ex->outfile[ex->o] == -1)
        {
            printf("error access file or open %s ", s_cmd->next->line[0]);
            return (1);
        }
		if (s_cmd->line[1])
        	reset_line(s_cmd->next->line);
    }
    if (typeofsep && typeofsep % 2 == 1 && typeofsep != 5)
    {
        ex->i++;
        ex->infile[ex->i] = ft_open(s_cmd->next->line[0], typeofsep, fd_hdoc);
        if (ex->infile[ex->i] == -1)
        {
            printf("error access file or open %s\n", s_cmd->next->line[0]);
            return (1);
        }
        if (s_cmd->line[1])
        	reset_line(s_cmd->next->line);
    }
    return (0);
}

void	end_of_pipex(t_arg *s_cmd, t_gc *garbage, t_exec *ex)
{
	int	typeofsep;

    typeofsep = check_sep_exec(s_cmd->prev_sep, ex);
	printf("s_cmd->line[0], = %s\n", s_cmd->line[0]);
	printf("s_cmd->prev_sep %s\n", s_cmd->prev_sep);
	if (ft_strncmp(s_cmd->prev_sep, "|", 2))
	{
		printf("ici1\n");
		if (init_open(ex, s_cmd, typeofsep, garbage->fd_hdoc))
    	{
        	garbage->go = 0;
        	return ;
    	}
		printf("ici2\n");
		set_fd(ex);
		put_respipex();
	}
}

void    ft_init_exec(t_arg *s_cmd, t_gc *garbage, t_exec *ex)
{
    int typeofsep;
    int i;


	probleme de ft_open;


    typeofsep = 0;
    if (!s_cmd)
        return ;
    typeofsep = check_sep_exec(s_cmd->sep, ex);
    if (init_open(ex, s_cmd, typeofsep, garbage->fd_hdoc))
    {
        garbage->go = 0;
        return ;
    }
    if (typeofsep == 5)
	{
		ex->r = 0;
        i = init_pipex(ex, s_cmd, garbage->blts->env);
        if (i < 0)
            return ;
        while (i-- && s_cmd->next)
        {
            s_cmd = s_cmd->next;
            garbage->nb_exec--;
        }
		ex->r = 1;
		end_of_pipex(s_cmd, garbage, ex);
        return ;
	}
	if (s_cmd->line[0])
        ft_exec(s_cmd, ex->paths, garbage, ex);
}