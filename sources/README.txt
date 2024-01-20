NOTES DE TEST :

ctrl c pas egale a 130 pour new line; >> ok

ctrl \ pas bon apres une commande; >> ok

bash: a: Permission denied quand pas de droit > leak new_str >> OK 
check permissions open / exec

ls > "fds qewr rtry" : ca essaye d'ouvrir fds et qewr et rtry >> OK
echo "q n c g g g e f " : essaye d'ouvrir un fichier ? et leak de handle_quote >> OK
quote unclosed == boucle infinie >> OK
echo "cat lol.c | cat>lol.c" : invalid read size 8 dans echo =>> erreur qd pipe dans quote >> OK
ls > 'a' : creer un fichier qui s'appelle "'a'" >> OK
'' ou "" crash >> OK

cd sources et ../minishell;
cp /bin/ls . puis unset PATH puis ls(command not found) mais ./ls fonctionne
nfs/homes/fserpe/gits/minishell/main_ms/ls : command not found >> ok

.hdoc pas close et leak (faire des test!!!!!) (wc << del > a == hdoc et a open) >> OK 

builints > fichier == fichier tjs open >> OK


/mnt/nfs/homes/fserpe/gits/minishell/main_ms/minishell

../minishell