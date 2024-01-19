NOTES DE TEST :

ctrl c pas egale a 130 pour new line;

ctrl \ pas bon apres une commande;

bash: a: Permission denied quand pas de droit > leak new_str
check permissions open / exec

ls > "fds qewr rtry" : ca essaye d'ouvrir fds et qewr et rtry
echo "q n c g g g e f " : essaye d'ouvrir un fichier ? et leak de handle_quote
quote unclosed == boucle infinie
echo "cat lol.c | cat>lol.c" : invalid read size 8 dans echo =>> erreur qd pipe dans quote
ls > 'a' : creer un fichier qui s'appelle "'a'"
'' ou "" crash

cd sources et ../minishell;
cp /bin/ls . puis unset PATH puis ls(command not found) mais ./ls fonctionne
nfs/homes/fserpe/gits/minishell/main_ms/ls : command not found

.hdoc pas close et leak (faire des test!!!!!)

builints > fichier == fichier tjs open