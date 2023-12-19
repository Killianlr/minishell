
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
    write(2, cmd[0], ft_strlen(cmd[0]));
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
    return (0);
}

int count_sep(t_arg *s_cmd)
{
    int i;

    i = 0;
    while (s_cmd->next)
    {
        if (s_cmd->sep)
            i++;
        s_cmd = s_cmd->next;
    }
    if (s_cmd->sep)
            i++;
    return (i);
}

void    ft_exec(t_arg *s_cmd, char **env, int lstsize)
{
    int i;
    char **paths;
    char *cmd_path;
    int pid;
    int input;
    int output;
    int typeofsep;
    int *pip;

    i = 0;
    input = 0;
    output = 0;
    typeofsep = 0;
    paths = ft_split(find_path(env), ":");
    cmd_path = NULL;
    pip = malloc(sizeof(int) * (2 * count_sep(s_cmd)));
    if (!pip)
        return ;
    get_pipes()
    while (i < lstsize)
    {
        pid = fork();
        if (pid == -1)
            return ;
        if (!pid)
        {
            typeofsep = check_sep(s_cmd);
            if (typeofsep)
                lafonctionchiantedup2(typeofsep, pip);
            cmd_path = get_cmd(paths, s_cmd->line, env);
            if (!cmd_path)
                ft_cmd_not_find(paths, s_cmd->line[0]);
            execve(cmd_path, s_cmd->line, env);
        }
        i++;
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
            printf("%s ", s_cmd->line[i]);
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
        printf("%s ", s_cmd->line[i]);
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
    s1->line[0] = ft_strdup("ls");
    s1->line[1] = ft_strdup("-l");
    s1->line[2] = NULL;
    s1->sep = ft_strdup("|");
    
    s2->line = malloc(sizeof(char *) * 3);
    s2->line[0] = ft_strdup("wc");
    s2->line[1] = ft_strdup("-l");
    s2->line[2] = NULL;
    s2->sep = ft_strdup("|");

    s3->line = malloc(sizeof(char *) * 2);
    s3->line[0] = ft_strdup("wc");
    s3->line[1] = ft_strdup("-c");
    s3->line[2] = NULL;
    s3->sep = NULL;

    s1->next = s2;
    s2->next = s3;
    s3->next = NULL;

    print_line_cmd(s1);
    lstsize = ft_lstsize_targ(s1);
    ft_exec(s1, env, lstsize);
    printf("sorti exec\n");
    waitpid(-1, NULL, 0);
}