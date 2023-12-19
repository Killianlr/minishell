
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

void    ft_exec(t_arg *s_cmd, char **env)
{
    int i;
    int nb_cmd;
    char *path;
    int pid;
    int pip[2];

    i = 0;
    nb_cmd = ft_lstsize_targ(s_cmd);
    printf("nb_cmd = %d\n", nb_cmd);
    pipe(pip);
    while (i < nb_cmd)
    {
        path = ft_strjoin("/usr/bin/", s_cmd->line[0]);
        pid = fork();
        if (!pid)
        {
            if (i == 0)
            {
                close(pip[0]);
                dup2(pip[1], STDOUT_FILENO);
            }
            else if (i == nb_cmd - 1)
            {
                close(pip[1]);
                dup2(STDOUT_FILENO, pip[0]);
            }
            else
            {
                dup2(pip[0], STDIN_FILENO);
                close(pip[0]);
                dup2(pip[1], STDOUT_FILENO);
            }
            execve(path, s_cmd->line, env);
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
    ft_exec(s1, env);
    printf("sorti exec\n");
    waitpid(-1, NULL, 0);
}