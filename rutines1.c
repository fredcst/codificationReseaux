//rutines1.h
#include "headers/rutines1.h"

/**
	addition en F(2) de deux bits
	<=> XOR
*/
int sommeB(int a, //bit 0,1
  int b) //bit 0,1
{
  int r = 0;
  if (a == b) r = 0;
  if (a != b) r = 1;
  return r; // a XOR b
}

/**
	multiplication en F(2)
	0*O=0;O*1=1*0=0;1*1=1
*/
int prodB(int a, //bit 0,1
  int b) //bit 0,1
{
  int r = 0;
  if (a == 1 && b == 1) r = 1;
  else
    r = 0;
  return r; // a * b
}

/**
	Évalue la multiplication scalaire de deux vecteurs binaires v1 et v2 de taille: n
*/
int prodScaB(int n, // taille de vecteurs
  int * v1, //vecteur de entiers binaires
  int * v2) //vecteur de entiers binaires
{
  int i, somme = 0;
  for (i = 0; i < n; i++) somme = sommeB(somme, prodB(v1[i], v2[i]));
  return somme; // v1.v2
}

/**
	Évalue la distance de Hamming du vecteur binaire : v de taille: n
*/
int distHamming(int n, int * v) {
  // calcule de la distance de Hamming
  //parcours le vecteur v et additionne les bits =1
  int i, r = 0;
  for (i = 0; i < n; i++) r = r + v[i];
  return r; // distance de Hamming
}
/**
	Génére 1 codeword a partir de la matrice generatrice Gx et un message.

	Entrées: Avec la matrice generatrice Gx et un message m[] de taille:KK
	Sorties: génère un  codeWord[] de taille NN
	L' espace pour les codeWords doit être crée dehors la rutine.
	Renvoie toujours 0;
*/
int genere1CodeWord(int message[KK], //message (KK,NN en base.h)
  int Gx[KK][NN], //matrice generatrice, Vient de dehors
  int * codeWord) //espace pour les codeword. Généré dehors
{
  int i1, i2, somme;

  for (i2 = 0; i2 < NN; i2++) {
    somme = 0;
    for (i1 = 0; i1 < KK; i1++) somme = sommeB(somme, prodB(message[i1], Gx[i1][i2]));
    codeWord[i2] = somme;
  }

  return 0;
}
/**
	Avec la matrice generatrice Gx,génère le nombre maximale de
	codewords de blocs :KK et taille de code:NN
	L' espace pour les codeWords doit être crée dehors la rutine.
	La nombre maximale de codeWords est calculé dehors
	Renvoie toujours 0 .
*/
int genereCodeWords(int LLx, // nombre maximal de codeWords= 2^KK (KK et NN sont en base.h; LLx=2^KK)
  int Gx[KK][NN], //matrice generatrice
  int ** codeWords) //espace pour les codewords
{
  int k, i = 0, i1, i2, base, somme;
  int message[KK]; // espace pour message
  do {
    base = 1;
    for (k = 0; k < KK; k++) {
      base = 2 * base;
      if (i % base < base / 2) {
        message[k] = 1;
      } else {
        message[k] = 0;
      }

    }
    for (i2 = 0; i2 < NN; i2++) {
      somme = 0;
      for (i1 = 0; i1 < KK; i1++) somme = sommeB(somme, prodB(message[i1], Gx[i1][i2]));
      codeWords[i][i2] = somme;
    }

    i++;

  } while (i < LLx);

  return 0;
}

/**
Avec la matrice génératrice Gx,génère le nombre maximale de
codewords de blocs :KK et taille de code:NN
L' espace pour les codeWords doit être créé dehors la rutine.
La nombre maximale de codeWords est calculé dehors
Sorte toujours 0 .
(Version de genereCodeWords qui utilise la routine: genere1CodeWord)
*/
int genereCodeWords1(int LLx, // nombre maximal de codeWords= 2^KK (KK et NN sont en base.h; LLx=2^KK)
  int Gx[KK][NN], //matrice génératrice
  int ** codeWords) //espace pour les codewords
{

  int k, i = 0, base;
  int message[KK]; // espace pour message
  do {
    base = 1;
    for (k = 0; k < KK; k++) {
      base = 2 * base;
      if (i % base < base / 2) {
        message[k] = 1;
      } else {
        message[k] = 0;
      }

    }
    genere1CodeWord(message, Gx, codeWords[i]); //message --> codeWords[i]=message.Gx
    i++;
  } while (i < LLx);

  return 0;
}