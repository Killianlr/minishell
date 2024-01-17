slt kyan

les quotes ainsi que les var_en ($) ne sont pas implémenter
sinon je skip bien les redirections dans la line
et les fichiers sont créer, open et close (sauf les derniers)

utilise la fonction free_cmd pour free s_cmd

niveau leak j'ai régler ce que j'ai vu mais si tu en vois d'autres dis moi


POUR IMPLEMENTER DANS MINISHELL :

tu ajoutes tous les fichier .c si présent (sauf main.c) dans /sources puis tu ajoutes tout ce qui est dans parsing.h dans minishell.h (oublie pas de modif le Makefile)
la fonction principale c'est "parsing(garbage->line)" elle return le first de s_cmd

hf

--------------------------------------------------------------------------------------------------------------------

Yoo flav

ducouuuuuuup j'ai reussi a implémenter ton parsing avec l'exec et ca marche plutot bien gg
pipex est en cours encore, quoi qu'il marche en vrai plutot bien, juste le test du "cat | cat | ls"
ls s'affiche bien, puis cat me demande d'ecrire... sauf que j'ecris une fois et ca se termine contre 2 avec bash (je pense
que le print d'ls s'affiche en stdin pour le premier cat, donc il me reste qu'une ecriture) apres ya pas de crash ni de leak donc a voir

reste donc les heredocs a gerer (pas compliquer je pense vu que tu as deja des fonctions pour);
ainsi que les quotes et les variables d'environ je crois.

aussi petit leak quand on veux redir dans un outfile rien de bien mechant, je te laisse check ca.

je continue a faire des tests pour pipe, c'est peux etre un jeu de waitpid au bon momment.. a voir
demain j'irai a l'ekole pour tester la varibale global et faire un coup de norm et aussi choper des points de correction,

d'ailleurs j'ai vu tu as des big fonctions, essaie de les ecrires a la norme des 25lignes pour eviter de tout casser par la suite en normant

j'ai push sur ma branche

pense a mettre en commentaire dans le main (minishell.c) la fonction signal et mettre en commentaire la variable g_signal 
dans tout les fichier.c et .h pour que tu puisse compiler

gl hf

-----------------------------------------------------------------------------------------------------------------------