
#include "../includes/minishell.h"

void gestionnaire_ctrl_c() 
{
    signal_ctrl_c = 1;
    printf("\n");
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

int ctrl_c() 
{
    struct sigaction sa_ctrl_c;

    sa_ctrl_c.sa_handler = gestionnaire_ctrl_c;
    sigemptyset(&sa_ctrl_c.sa_mask);
    sa_ctrl_c.sa_flags = 0;
    if (sigaction(SIGINT, &sa_ctrl_c, NULL) == -1) 
    {
        perror("Erreur lors de l'installation du gestionnaire de signal pour SIGINT");
        return 1;
    }
    return (1);
}