//fichier codeWordsP2.c
//se obtendran tous les codeWords pour P2=(x+1)(x^4+x+1)
//se obtendra la distance Hamming du code comme le minimum de distance de
//Hamming de chaque codeWord.
//La distance de Hamming de chaque codeword est la  addition des componentes 1
// du codeWord.
// gcc -o codeWordsP2 codeWordsP2.c

#include "headers/codification.h"

#include "headers/decodification.h"

int main() {
  //x^5+x^4+x^2+1
  UINT gd = 1 + 2 + 16 + 32;
  int nx = 8;
  int rx = 5;
  int k = (nx - rx);
  int ncw = 1 << k;
  UINT codeWords[1 << 8];
  genereCodeWordsUINTdePoly(gd, rx, nx, codeWords);
  int i;
  for (i = 0; i < ncw; i++) {
    printf("%d ", i);
    printf(" & ");
    montreUINTSNL(nx, codeWords[i]);
    printf(" & ");
    printf("%d \\\\ \n", distHammingUINT_nvar(codeWords[i], nx));
  }
  int min = distandeHammingCode(nx, ncw, codeWords);
  printf("Distance de Hamming de code:%d\n", min);
  return 0;
}
