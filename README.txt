slt kyan

les quotes ainsi que les var_en ($) et les here_doc ne sont pas implémenter
sinon je skip bien les redirections dans la line
et les fichiers sont créer, open et close (sauf les derniers)

utilise la fonction free_cmd pour free s_cmd

niveau leak j'ai régler ce que j'ai vu mais si tu en vois d'autres dis moi


POUR IMPLEMENTER DANS MINISHELL :

tu ajoutes tous les fichier .c si présent (sauf main.c) dans /sources puis tu ajoutes tout ce qui est dans parsing.h dans minishell.h (oublie pas de modif le Makefile)
la fonction principale c'est "parsing(garbage->line)" elle return le first de s_cmd

hf
