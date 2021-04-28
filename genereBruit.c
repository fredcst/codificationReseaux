//genereBruit.c

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "headers/genereBruit.h"

/**
Génére bruit en char avec nchanges en positions
aleatoires du char, sur ntbits de droite a gauche.
Ex.
pour un char met ntbits=8 si tout le char veut être changé
pour un char met ntbits=4 si seulement le nibble inferieur veut être changé
Le nombre de changes faites est ce qui a été démandé!!
Les positions des changes sont aleatoires.
Entrées:
	nchanges: nb total de bits à changer(int)
	sym:  char=8 bits 
	nbits: nombre de bits à changer, de droite a gauche de char
Sortie:
	Le symbole changé

*/
char genereBruit(int nchanges, char sym, int ntbits) {
  int fin = 0;
  int id[ntbits];
  int i;
  char t;
  if (ntbits > 8) ntbits = 8; //seulement sert pour chars
  for (i = 0; i < ntbits; i++) id[i] = 0;
  srandom(time(0));
  int nx = 0;
  if (nchanges > 8) nchanges = 8; //seulement sert pour chars

  while (!fin) {
    i = random() % ntbits;
    if (nx < nchanges) {
      fin = 0;
      if (id[i] == 0) {
        id[i] = 1;
        nx++;
        t = 1 << i;
        sym = sym ^ t;
      }
    } else {
      fin = 1;
    }

  }

  return sym;
}