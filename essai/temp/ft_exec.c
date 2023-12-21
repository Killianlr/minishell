
#include "essai.h"

int	ft_lstsize_targ(t_arg *lst)
{
	int	size;

	size = 0;
	while (lst)
	{
		lst = lst->next;
		size++;
	}
	return (size);
}

void    ft_cmd_not_find(char **paths, char *cmd)
{
    write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found\n", 21);
    free(paths);
    // mettre a jours ret a 127;
    exit(1);
}

int check_sep(t_arg *s_cmd)
{
    if (!s_cmd->sep)
        return (0);
    if (!ft_strncmp(s_cmd->sep, "<", 2))
        return (1);
    if (!ft_strncmp(s_cmd->sep, ">", 2))
        return (2);
    if (!ft_strncmp(s_cmd->sep, "<<", 3))
        return (3);
    if (!ft_strncmp(s_cmd->sep, ">>", 3))
        return (4);
    return (5);
}

int count_sep(t_arg *s_cmd, char *sep1, char *sep2)
{
    int i;

    i = 0;
    while (s_cmd->next)
    {
        if (!ft_strncmp(s_cmd->sep, sep1, 3) || !ft_strncmp(s_cmd->sep, sep2, 3))
            i++;
        s_cmd = s_cmd->next;
    }
    return (i);
}

int ft_open(char *file, int typeofsep)
{
	printf("file = %s\n", file);
    if (typeofsep == 1)
    {
        if (access(file, F_OK) == -1)
            return (-1);
        if (access(file, R_OK) == -1)
            return (-1);
        return (open(file, O_RDONLY));
    }
    else if (typeofsep == 2)
    {
        if (access(file, F_OK) == -1)
            return (open(file, O_CREAT | O_RDWR, 0000644));
        else if (access(file, R_OK) == -1)
            return (-1);
        else if (access(file, W_OK) == -1)
            return (-1);
        return (open(file, O_TRUNC | O_RDWR, 0000644));
    }
    else if (typeofsep == 3)
    {
        printf("is heredoc\n");
        return (10);
    }
    else if (typeofsep == 4)
    {
        if (access(file, F_OK) == -1)
            return (open(file, O_APPEND | O_CREAT | O_RDWR, 0000644));
        else if (access(file, R_OK) == -1)
            return (-1);
        else if (access(file, W_OK) == -1)
            return (-1);
        return (open(file, O_APPEND | O_RDWR, 0000644));
    }
	return (-1);
}

void    ft_exec(t_arg *s_cmd, char **paths, char **env, t_exec *ex)
{
	int 	pid;
	char	*cmd_path;
	char	buf[2];

	pid = fork();
	if (pid == -1)
		return ;
	if (!pid)
	{
		if (ex->r && ft_lstsize_targ(s_cmd) == 1)
		{
			read(ex->res_pipex, buf, 2);
			write(STDOUT_FILENO, buf, ft_strlen(buf));
			write(STDOUT_FILENO, "\n", 1);
		}
		if (ex->infile[ex->i] > 0)
		{
			if (ex->r)
			{
				dup2(ex->infile[ex->i], ex->res_pipex);
				ex->r = 0;
			}
			else
				dup2(ex->infile[ex->i], STDIN_FILENO);
		}
		if (ex->outfile[ex->o] > 0)
		{
			if (ex->r)
			{
				dup2(ex->outfile[ex->o], ex->res_pipex);
				ex->r = 0;
			}
			else
				dup2(ex->outfile[ex->o], STDOUT_FILENO);
		}
		cmd_path = get_cmd(paths, s_cmd->line, env);
		if (!cmd_path)
			ft_cmd_not_find(paths, s_cmd->line[0]);
		execve(cmd_path, s_cmd->line, env);
	}
}

int init_t_exec(t_exec *ex, t_arg *s_cmd, char **env)
{
    ex->i = -1;
    ex->o = -1;
    ex->paths = ft_split(find_path(env), ':');
    ex->res_pipex = open(".res_pipex", O_CREAT | O_TRUNC | O_RDWR, 0000644);
    if (!ex->res_pipex)
        return (1);
		printf("laaaaa\n");
	if (count_sep(s_cmd, "<", "<<"))
	{
    	ex->infile = malloc(sizeof(int) * count_sep(s_cmd, "<", "<<"));
    		if (!ex->infile)
        		return (1);
		printf("looooo\n");
		ex->infile[0] = -1;
	}
	if (count_sep(s_cmd, ">", ">>"))
	{
    	ex->outfile = malloc(sizeof(int) * count_sep(s_cmd, ">", ">>"));
    		if (!ex->outfile)
			{
				return (1);
			}
		ex->outfile[0] = -1;
	}
    return (0);
}

int init_open(t_exec *ex, t_arg *s_cmd, int typeofsep)
{
    if (typeofsep && typeofsep % 2 == 0)
    {
        ex->o++;
        ex->outfile[ex->o] = ft_open(s_cmd->next->line[0], typeofsep);
        if (ex->outfile[ex->o] == -1)
        {
            printf("error access file or open %s ", s_cmd->next->line[0]);
            return (1);
        }
		s_cmd->next->line++;
    }
    else if (typeofsep && typeofsep % 2 == 1 && typeofsep != 5)
    {
        ex->i++;
        ex->infile[ex->i] = ft_open(s_cmd->next->line[0], typeofsep);
        if (ex->infile[ex->i] == -1)
        {
            printf("error access file or open %s\n", s_cmd->next->line[0]);
            return (1);
        }
		s_cmd->next->line++;
    }
    return (0);
}

char    *convert_tab_2_str(char **tabl)
{
    int i;
    char    *res;

    i = 1;
    if (!tabl[0])
        return (NULL);
    res = ft_strdup(tabl[0]);
    if (!res)
        return (NULL);
    while (tabl[i])
    {
		res = ft_strjoin_fs1(res, " ");
        res = ft_strjoin_fs1(res, tabl[i]);
        if (!res)
            return (NULL);
        i++;
    }
    return (res);
}

int count_pipex_cmds(t_arg *s_cmd)
{
    t_arg	*tmp;
    int		nb_cmd;

    tmp = s_cmd;
    nb_cmd = 1;
	while (tmp && !ft_strncmp(tmp->sep, "|", 2))
    {
        nb_cmd++;
        tmp = tmp->next;
    }
	return (nb_cmd);
}

int	init_pipex(t_exec *ex, t_arg *s_cmd, char **env)
{
    int     nb_cmd;
    char    **cmds_pipex;
    char    *str_cmd;
    int     i;

    i = 0;
	nb_cmd = count_pipex_cmds(s_cmd);
    cmds_pipex = malloc(sizeof(char *) * (nb_cmd + 1));
    if (!cmds_pipex)
        return (1);
    while (i < nb_cmd)
    {
        str_cmd = convert_tab_2_str(s_cmd->line);
        if (!str_cmd)
            return (1);
        cmds_pipex[i] = str_cmd;
        i++;
		if (s_cmd->next)
    		s_cmd = s_cmd->next;
    }
    cmds_pipex[i] = NULL;
	pipex(nb_cmd, cmds_pipex, ex, env);
	return (0);
}

void    ft_init_exec(t_arg *s_cmd, char **env, int lstsize)
{
    t_exec  ex;
    int j;
    int typeofsep;

    j = 0;
    typeofsep = 0;
	printf("A\n");
    if (init_t_exec(&ex, s_cmd, env))
        return ;
		printf("B\n");
    while (j < lstsize)
    {
        typeofsep = check_sep(s_cmd);
        if (init_open(&ex, s_cmd, typeofsep))
            return ;
        if (typeofsep == 5)
		{
            if (init_pipex(&ex, s_cmd, env))
				return ;
			ex.r = 1;
		}
		printf("C\n");
		if (s_cmd->line[0])
        	ft_exec(s_cmd, ex.paths, env, &ex);
        j++;
        s_cmd = s_cmd->next;
		printf("D\n");
    }

}

void    print_line_cmd(t_arg *arg)
{
    int i;
    t_arg *s_cmd;

    s_cmd = arg;
    while (s_cmd->next)
    {
        i = 0;
        printf("(");
        while (s_cmd->line[i])
        {
            printf("%s", s_cmd->line[i]);
            i++;
        }
        if (s_cmd->sep)
            printf("%s", s_cmd->sep);
        s_cmd = s_cmd->next;
        printf(")");
    }
    i = 0;
    printf("(");
    while (s_cmd->line[i])
    {
        printf("%s", s_cmd->line[i]);
        i++;
    }
    if (s_cmd->sep)
        printf("%s", s_cmd->sep);
    s_cmd = s_cmd->next;
    printf(")\n");

}

int main(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;
    t_arg *s1;
    t_arg *s2;
    // t_arg *s3;
    int lstsize;

    s1 = malloc(sizeof(t_arg));
    s2 = malloc(sizeof(t_arg));
    // s3 = malloc(sizeof(t_arg));

    s1->line = malloc(sizeof(char *) * 3);
    s1->line[0] = ft_strdup("ls");
    s1->line[1] = ft_strdup("-l");
    s1->line[2] = NULL;
    s1->sep = ft_strdup("|");
    
    s2->line = malloc(sizeof(char *) * 3);
    s2->line[0] = ft_strdup("wc");
    s2->line[1] = ft_strdup("-l");
    s2->line[2] = NULL;
    s2->sep = NULL; //ft_strdup(">");

    // s3->line = malloc(sizeof(char *) * 2);
    // s3->line[0] = ft_strdup("temp2");
    // // s3->line[1] = ft_strdup("-c");
    // s3->line[1] = NULL;
    // s3->sep = NULL;

    s1->next = s2;
	s2->next = NULL;
    // s3->next = NULL;

    print_line_cmd(s1);
    lstsize = ft_lstsize_targ(s1);
    ft_init_exec(s1, env, lstsize);
    waitpid(-1, NULL, 0);
	printf("debut du free\n");
	free(s1->sep);
	free(s1);
	free(s2);
    printf("sorti exec\n");
}