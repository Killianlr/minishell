
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
		{
			printf("------------------ici-------------------\n");
            return (open(file, O_CREAT | O_RDWR, 0000644));
		}
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

void    ft_exec(t_arg *s_cmd, char **paths, char **env, int infile, int outfile)
{
	int 	pid;
	char	*cmd_path;

	pid = fork();
	if (pid == -1)
		return ;
	if (!pid)
	{
		if (infile > 0)
			dup2(infile, STDIN_FILENO);
		if (outfile > 0)
		{
			printf("===========LA==========\n");
			dup2(outfile, STDOUT_FILENO);
		}
		cmd_path = get_cmd(paths, s_cmd->line, env);
		if (!cmd_path)
			ft_cmd_not_find(paths, s_cmd->line[0]);
		execve(cmd_path, s_cmd->line, env);
	}
}

void    ft_init_exec(t_arg *s_cmd, char **env, int lstsize)
{
    int i;
    int o;
    int j;
    char **paths;
    char *cmd_path;
    int typeofsep;
    int res_pipex;
    int *infile;
    int *outfile;

    i = -1;
    o = -1;
    j = 0;
    typeofsep = 0;
    paths = ft_split(find_path(env), ':');
    cmd_path = NULL;
    res_pipex = open(".res_pipex", O_CREAT, O_RDWR);
    if (!res_pipex)
        return ;
    infile = malloc(sizeof(int) * count_sep(s_cmd, "<", "<<"));
    outfile = malloc(sizeof(int) * count_sep(s_cmd, ">", ">>"));
    while (j < lstsize)
    {
        typeofsep = check_sep(s_cmd);
        if (typeofsep && typeofsep % 2 == 0)
        {
            o++;
            outfile[o] = ft_open(s_cmd->next->line[0], typeofsep);
            if (outfile[o] == -1)
			{
                printf("error access file or open %s ", s_cmd->next->line[0]);
				printf("%d\n", o);
			}
			s_cmd->next->line++;
        }
        else if (typeofsep && typeofsep % 2 == 1 && typeofsep != 5)
        {
            i++;
            infile[i] = ft_open(s_cmd->next->line[0], typeofsep);
            if (infile[i] == -1)
                printf("error access file or open %s\n", s_cmd->next->line[0]);
			s_cmd->next->line++;
        }
		if (s_cmd->line[0])
        	ft_exec(s_cmd, paths, env, infile[i], outfile[o]);
        j++;
        s_cmd = s_cmd->next;
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
    t_arg *s3;
    int lstsize;

    s1 = malloc(sizeof(t_arg));
    s2 = malloc(sizeof(t_arg));
    s3 = malloc(sizeof(t_arg));

    s1->line = malloc(sizeof(char *) * 3);
    // s1->line[0] = ft_strdup("wc");
    // s1->line[1] = ft_strdup("temporaire");
    s1->line[0] = NULL;
    s1->sep = ft_strdup("<");
    
    s2->line = malloc(sizeof(char *) * 3);
    s2->line[0] = ft_strdup("temporaire");
    s2->line[1] = ft_strdup("wc");
    s2->line[2] = NULL;
    s2->sep = ft_strdup(">");

    s3->line = malloc(sizeof(char *) * 2);
    s3->line[0] = ft_strdup("temp2");
    // s3->line[1] = ft_strdup("-c");
    s3->line[1] = NULL;
    s3->sep = NULL;

    s1->next = s2;
	s2->next = s3;
    s3->next = NULL;

    print_line_cmd(s1);
    lstsize = ft_lstsize_targ(s1);
    ft_init_exec(s1, env, lstsize);
    waitpid(-1, NULL, 0);
    printf("sorti exec\n");
}