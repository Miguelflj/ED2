#! /bin/bash




echo "Arvore Binária:" >> teste.txt
gcc -o exec ArvoreBin.c
./exec $1 >> teste.txt

echo "\nArvore AVL:" >> teste.txt
gcc -o exec ArvAvl.c
./exec $1 >> teste.txt
echo "\nArvore RN:" >> teste.txt
gcc -o exec ArvRN.c
./exec $1 >> teste.txt

echo "------------------------------------------------------------" >> teste.txt

