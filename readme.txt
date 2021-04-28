Ligne de commande pour la compilation :
gcc -Wall -Werror paint.c queue.c fill.c test_fill.c -o main.exe

Ligne de commande pour l'execution :
./main.exe nombre_ini

où nombre_ini est un entier positif représentant le nombre de points initiaux

Les dessins obtenus étant particulièrement esthétiques, je vous ai mis en exemple 
une fenêtre de 1900x1200 avec 100 points initiaux, converti en jpg, 
mais la valeur demandée de width et height dans le test_fill est la bonne.