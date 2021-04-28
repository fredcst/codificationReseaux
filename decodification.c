//decodification.c

#include "headers/base.h"
#include "headers/rutinesBits.h"
#include "headers/poly.h"
#include "headers/decodification.h"

/**
Génère 1 char decodifié à partir des codewords pour les nibbles haut et bas de un char.
Seulement sert pour codewords de 8 bits et message de 4 bits par codeword!
Entrées:
	codes: char|2] qui contient les codes de nibbles (codes[0] pour nibble inferieur,codes[1] pour nibble superieur)
	nx: no de bits de codeword=8
	rx: ordre de polynome générateur=4
	gd: coefficients de polynôme générateur comme UINT (0000000 0000000 0000000 0001 0011)
	restex1e: liste de 8 restes pour les flips dans un seule bit du codewords.
	*mc: addresse de 1 chars où sauver le message decodifié
Sortie:
	mc: char que contient decodification de deux nibble

Renvioe: 0 si il n'y a pas erreur de 1 bit detecté en les deux codes
         1 si existe possible erreur de 1 bit detecte et corrigé dans un code
	 2 si existe possible erreur de 1 bit dans 2 codes et corrigé.
	 4 si existe erreur de plus de 1 bit en 1 code et non corrigé
         5 un code avec possible erreur de 1 bit et corrige  et l'autre avec erreur et non corrigé
	 8 deux codes avec erreur et pas corrigés 
*/

int genere1charDe2codes(char codes[2], int nx, int rx, UINT gd, UINT restex1e[], char * mc) {
  //UINT qd;
  if (nx != 8 || rx != 4) {
    fprintf(stderr, "Erreur genere1charDe2codes. nx!=8 ou rx!=4\n");
    exit(1);
  }

  int EX1 = 0;
  int EX2 = 0;
  UINT cbr = CHAR_A_UINT(codes[0], 8); //met codes char en codes UINT                <----section a travailler
  UINT chr = CHAR_A_UINT(codes[1], 8); //met codes char en codes UINT
  UINT cbc = codeCorrige1eS(cbr, gd, 8, 4, restex1e, & EX1); // corrige ou non codes UINT
  UINT chc = codeCorrige1eS(chr, gd, 8, 4, restex1e, & EX2); // corrige ou non codes UINT

  char nbc = codeM4UINTaCHAR_B(cbc, 8, 4); //transfère de message de code a nibble bas de char
  char nhc = codeM4UINTaCHAR_H(chc, 8, 4); //transfère de message de code a nibble haut de char
  * mc = nh_nbaCHAR(nhc, nbc); //récuperation de char envoié avec possible corrections   

  return EX1 + EX2;
}

/**
Génére 1 char decodifiqué à partir des codewords pour les nibbles haut et bas de un char.
Seule sert pour codewords de 8 bits et message de 4 bits per codeword!!
Entrées:
	codes: char|2] qui contient les codes de nibbles (codes[0] pour message,codes[1] pour bits de control)
	nx: no de bits de codeword=8
	rx: ordre de polynome générateur=4
	gd: coefficients de polynôme générateur comme UINT (0000000 0000000 0000000 0001 0011)
	restex1e: liste de 8 restes pour les flips dans un seule bit du codewords.
	*mc: address de 1 chars où sauver le message decodifiqué
Sortie:
	mc: char que contient decodification de deux nibble

return : 0 si il n'y a pas erreur de 1 bit detecté en les deux codes
         1 si existe possible erreur de 1 bit detecte et corrigé dans un code
	 2 si existe possible erreur de 1 bit dans 2 codes et corrigé.
	 4 si existe erreur de plus de 1 bit en 1 code et non corrigé
         5 un code avec possible erreur de 1 bit et corrige  et l'autre avec erreur et non corrigé
	 8 deux codes avec erreur et pas corrigés 
*/

int genere1charDe2codesBItsDeControlEn1Char(char codes[2], int nx, int rx, UINT gd, UINT restex1e[], char * mc) {
  if (nx != 8 || rx != 4) {
    fprintf(stderr, "Erreur genere1charDe2codes. nx!=8 ou rx!=4\n");
    exit(1);
  }

  int EX1 = 0;
  int EX2 = 0;

  BYTE filtroB = 15; // sélecctione nibble bas     00001111 
  BYTE filtroH = 15 << 4; // sélectionne nibble haut  11110000

  BYTE mb = codes[0] & filtroB; //parte de nibble bas de deux chars
  BYTE cb = codes[1] & filtroB;

  BYTE mh = codes[0] & filtroH; //parte de nibble haut de deux chars
  BYTE ch = codes[1] & filtroH;

  BYTE codenb = (mb << 4) | cb; // recombine nibble inferieur de m avec son bits de control
  BYTE codenh = mh | (ch >> 4); // recombine nibble superieur de m avec son bits de control

  UINT cbr = CHAR_A_UINT((char) codenb, 8);
  UINT chr = CHAR_A_UINT((char) codenh, 8);

  UINT cbc = codeCorrige1eS(cbr, gd, 8, 4, restex1e, & EX1); // corrige ou non codes UINT

  UINT chc = codeCorrige1eS(chr, gd, 8, 4, restex1e, & EX2); // corrige ou non codes UINT

  char nbc = codeM4UINTaCHAR_B(cbc, 8, 4); //transfère de message de code a nibble bas de char
  char nhc = codeM4UINTaCHAR_H(chc, 8, 4); //transfère de message de code a nibble haut de char
  * mc = nh_nbaCHAR(nhc, nbc); //récuperation de char envoié avec possible corrections   

  return EX1 + EX2;
}