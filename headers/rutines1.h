//rutines1.h
#ifndef RUTINES1H
#define RUTINES1H

#include "base.h"

/**
	addition en F(2) de deux bits
	<=> XOR
*/
int sommeB(int a, //bit 0,1
int b)//bit 0,1
;

/**
	multiplication en F(2)
	0*O=0;O*1=1*0=0;1*1=1
*/
int prodB(int a, //bit 0,1
  int b) //bit 0,1

;

/**
	Évalue la multiplication scalaire de deux vecteurs binaires v1 et v2 de taille: n
*/
int prodScaB(int n, // taille de vecteurs
  int * v1, //vecteur de entiers binaires
  int * v2) //vecteur de entiers binaires
;

/**
	Évalue la distance de Hamming du vecteur binaire : v de taille: n
*/
int distHamming(int n, int * v);

/**
	Génére 1 codeword a partir de la matrice generatrice Gx et un message.

	Entrées: Avec la matrice generatrice Gx et un message m[] de taille:KK
	Sorties: génère un  codeWord[] de taille NN
	L' espace pour les codeWords doit être crée en dehors la rutine.
	Renvoie toujours 0 .
*/
int genere1CodeWord(int message[], //message (KK,NN en base.h)
  int Gx[KK][NN], //matrice generatrice, Vient de dehors
  int * codeWord) //espace pour les codeword. Généré dehors
;

/**
	Avec la matrice generatrice Gx, génère le nombre maximale de
	codewords de blocs: KK et taille de code: NN
	L' espace pour les codeWords doit être crée en dehors la rutine.
	La nombre maximale de codeWords est calculé dehors
	Renvoie toujours 0 .
*/
int genereCodeWords(int LLx, // nombre maximal de codeWords= 2^KK (KK et NN sont en base.h; LLx=2^KK)
  int Gx[KK][NN], //matrice generatrice
  int ** codeWords) //espace pour les codewords
;

/**
	Avec la matrice génératrice Gx, génère le nombre maximale de
	codeWords de blocs :KK et taille de code:NN
	L' espace pour les codeWords doit être créé dehors la rutine.
	La nombre maximale de codeWords est calculé dehors
	Renvoie toujours 0 .
	(Version de genereCodeWords qui utilise la routine: genere1CodeWord)
*/
int genereCodeWords1(int LLx, // nombre maximal de codeWords= 2^KK (KK et NN sont en base.h; LLx=2^KK)
  int Gx[KK][NN], //matrice génératrice
  int ** codeWords) //espace pour les codewords
;

#endif