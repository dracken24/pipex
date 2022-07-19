PIPEX:

Nom du programme:               pipex
Fichiers de rendu:              Makefile, *.h, *.c
Makefile:                       NAME, all, clean, fclean, re
Arguments:                      file1 cmd1 cmd2 file2

Fonctions externes autorisées:  • open, close, read, write,
								malloc, free, perror,
								strerror, access, dup, dup2,
								execve, exit, fork, pipe,
								unlink, wait, waitpid
								• ft_printf et tout équivalent
								que VOUS avez codé

Libft autorisée:				Non
Description:					Ce projet consiste à gérer des pipes.


Votre programme sera exécuté comme suit :	./pipex file1 cmd1 cmd2 file2

Il doit prendre 4 arguments :				• file1 et file2 sont des noms de fichier.

• cmd1 et cmd2 sont des commandes shell avec leurs paramètres.

Votre programme doit se comporter exactement comme la commande shell suivante :	< file1 cmd1 | cmd2 > file2


Exemples
$> ./pipex infile "ls -l" "wc -l" outfile
Devrait être identique à < infile ls -l | wc -l > outfile

$> ./pipex infile "grep a1" "wc -w" outfile
Devrait être identique à < infile grep a1 | wc -w > outfile

Prérequis
Votre projet doit respecter les règles suivantes :
• Vous devez rendre un Makefile qui compilera vos fichiers sources. Il ne doit pas
relink.
• Vous devez gérer les erreurs avec du bon sens. En aucun cas votre programme ne
doit quitter de manière inattendue (erreur de segmentation, erreur de bus, double
free, etc.).
• Votre programme ne doit pas avoir de fuites de mémoire.
• Si vous avez le moindre doute, référez-vous à la commande shell :	< file1 cmd1 | cmd2 > file2


Partie bonus
Vous aurez des points supplémentaires si vous :	• Gérez plusieurs pipes.

Ceci :	$> ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2
Devrait être identique à :	< file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2

• Gérez « et » quand le premier paramètre est "here_doc".
Ceci :
$> ./pipex here_doc LIMITER cmd cmd1 file
Devrait être identique à :
cmd << LIMITER | cmd1 >> file
