//genereBruit.h
#ifndef GENEREBRUIT_H
#define GENEREBRUIT_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/**
Génére bruit en char avec nchanges en positions
aleatoires du char, sur ntbits de droite a gauche.
Ex.
pour un char met ntbits=8 si toute le char veut être changé
pour un char met ntbits=4 si seulement le nibble inferieur veut être changé
Le nombre de changes faites est ce qui a été démandé!!
Les positions des changes sont aleatoires.
Entrées:
	nchanges: no total de bits à changer(int)
	sym:  char=8 bits 
	nbits: nombre de bits à changer, de droite a gauche de char
Sortie:
	le symbole changé

*/
char  genereBruit(int nchanges,char sym,int ntbits);










#endif
