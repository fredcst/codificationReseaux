//rutinesBits.c

#include "headers/base.h"
#include "headers/bitsBase.h"
#include "headers/rutinesBits.h"

/**
Génére GB , matrice génératrice comme 4 BYTES, a partir de
G ecrite en entiers(en base.h)
Entrées:
G qui est en base.h
Sortie:
GB= 4 BYTE , chacune est une ligne de G
return toujours 0;
*/
int creeGB(int Gx[4][8], BYTE GB[4]) {
  BYTE r = 128;
  int i, j;
  for (j = 0; j < 4; j++) {
    GB[j] = 0;
    for (i = 0; i < 8; i++) {
      if (Gx[j][i] == 1) GB[j] = GB[j] | (r >> i); //additionne le bit en position (7-i) au BYTE	
    }
  }

  return 0;
}

/**
Génére GB , matrice génératrice comme KK UINT, a partir de
G ecrite en entiers(en base.h)
Entrées:
G qui est en base.h
Sortie:
GB= KK UINT , chacune est une ligne de G
return toujours 0;
*/
int creeGBUINT(int Gx[KK][NN], UINT GB[KK]) {
  UINT r = 1 << (NN - 1); //se positione à la fin de codeWord
  int i, j;
  for (j = 0; j < KK; j++) {
    GB[j] = 0;
    for (i = 0; i < NN; i++) {
      if (Gx[j][i] == 1) GB[j] = GB[j] | (r >> i); //additionne le bit en position (NN-1-i) au UINT	
    }
  }

  return 0;
}

/**
Génére matrice trasposée de G avec 8 BYTES
Les 4 premiers bits de chaque BYTE sont valides et
representent les colonnes de G (4x8) 
Entrée:
Matrix G originale de 4 BYTES réprésentant chaque ligne de G
Sortie:
Matrix GT de 8 BYTES réprésentant les colonnes de G;espace généré dehors
*/
BYTE generaTrasposeDeMatriceG(BYTE Gx[4], BYTE GTx[8]) {
  int j, t;
  BYTE cv8, r = 0, b = 0;
  cv8 = 128; // (1000000)
  for (t = 0; t < 8; t++) GTx[7 - t] = 0;

  for (t = 0; t < 8; t++) { //parcours Gx de la gauche à la droite
    r = cv8 >> t;
    for (j = 0; j < 4; j++) {
      b = Gx[j] & r; //génére byte b de test: 
      GTx[7 - t] = (((b == 0) ? 0 : 1) * (cv8 >> j)) | GTx[7 - t]; // a7,a6...
      //Inserte 0 ou 1 en GTx[7-t] en position 7-j, selon valeur de b
    }
  }

  return 0;
}

/**
Génére matrice trasposée de G avec n UINT
Les k premiers bits de chaque UINT sont valides et
representent les colonnes de G (kxn) 
Entrée:
Matrix G originale de k UINT réprésentant chaque ligne de G
Sortie:
Matrix GT de n UINT réprésentant les colonnes de G;espace généré dehors
*/
UINT generaTrasposeDeMatriceGUINT(UINT Gx[KK], UINT GTx[NN]) {

  int j, t;
  UINT cv8, r = 0, b = 0;
  cv8 = 1 << (NN - 1); // (10000000)//se positione à  la fin de codeword

  for (t = 0; t < NN; t++) GTx[NN - 1 - t] = 0;

  for (t = 0; t < NN; t++) { //parcours Gx de la gauche à la droite
    r = cv8 >> t;
    for (j = 0; j < KK; j++) {
      b = Gx[j] & r; //génére byte b de test: 
      GTx[NN - 1 - t] = (((b == 0) ? 0 : 1) * (cv8 >> j)) | GTx[NN - 1 - t]; // 
      //Inserte 0 ou 1 en GTx[NN-t] en position NN-1-j, selon valeur de b
    }
  }

  return 0;
}

/**
Génére 1 codeword à partir de la Traspose de la matrice generatrice  (8 BYTES)
(chaque ligne est un BYTE, 4 bits à la  gauche sont significatives) 
Entrées:
	message (BYTE): les 4 bits de haut ordre du BYTE est message
	Traspose de matrice generatrice G comme BYTE[8] . Chaque BYTE est une colonne de la matrice
	Espace pour sauver le codeword: address de codeWord
Sortie:
	codeWord(BYTE): les 8 bits sont la codification du message en espace fournié
return: 0 toujours
*/
int genere1CodeWordBits(BYTE message, //message (4 bits de gauche important)
  BYTE GTx[8], //chaque BYTE est ligne de Traspose de matrice generatrice==colonne
  BYTE * codeWord) //espace pour les codeword. Généré dehors
{
  BYTE s = 0;
  * codeWord = 0;
  int t;
  for (t = 0; t < 8; t++) {
    s = prodEscaBytes4(message, GTx[t]); // producte escalaire de message avec colonne
    // de matrice generatrice ( s avec 1 ou 0 en bit 0)

    ( * codeWord) = ( * codeWord) | (s << t); //additione les bits à r  depuis la droite
  }

  return 0;
}

/**
Génére 1 codeword à partir de la Traspose de la matrice generatrice  (NN UINT)
(chaque ligne est un UINT, KK bits à la  gauche de bit NN sont significatives) 
Entrées:
	message (UINT): les KK bits a gauche de bit NN du UINT est message
	Traspose de matrice generatrice G comme UINT[NN] . Chaque UINT est une colonne de la matrice
	Espace pour sauver le codeword: address de codeWord
Sortie:
	codeWord(UINT): les NN bits mois significatives sont la codification du message en espace fournié
return: 0 toujours
*/
int genere1CodeWordBitsUINT(UINT message, //message (kk bits de gauche important)
  UINT GTx[NN], //chaque UINT est ligne de Traspose de matrice generatrice==colonne
  UINT * codeWord) //espace pour les codeword. Généré dehors
{
  UINT s = 0;
  * codeWord = 0;
  int t;
  for (t = 0; t < NN; t++) {
    //s= prodEscaBytes4(message, GTx[t]);// producte escalaire de message avec colonne
    // de matrice generatrice ( s avec 1 ou 0 en bit 0)

    s = prodEscaBytesKKUINT(
      NN, //taille de CW
      KK, //taille de message
      message, // UINT  seule les positions NN-1 NN-KK sont valides
      GTx[t]);

    ( * codeWord) = ( * codeWord) | (s << t); //additione les bits à r  depuis la droite
  }

  return 0;
}

/**
Génére 1 codeword a partir de la Traspose de la matrice generatrice de 8 BYTES
(chaque ligne est un BYTE, 4 bits à la  gauche sont significatives) 
Entrées:
	message (BYTE): les 4 bits de haut ordre de BYTE est message
	Traspose de matrice generatrice G comme BYTE[8] . Chaque BYTE est une colonne de la matrice
Sortie:
	codeWord(BYTE): les 8 bits sont la codification du message
return: codeWord(BYTE)
*/
BYTE genere1CodeWordBitsX(BYTE message, //message (4 bits de gauche important)
  BYTE GTx[8] //chaque BYTE est ligne de Traspose de matrice generatrice==colon
) //espace pour les codeword. Généré dehors
{
  BYTE s = 0;
  BYTE codeWord = 0;
  int t;
  for (t = 0; t < 8; t++) {
    s = prodEscaBytes4(message, GTx[t]); // producte escalaire de message avec colonne
    // de matrice generatrice ( s avec 1 ou 0 en bit 0)

    (codeWord) = (codeWord) | (s << t); //additione les bits à r  depuis la droite
  }

  return codeWord;
}

/**
Génére 1 codeword a partir de la Traspose de la matrice generatrice de NN UINTS
(chaque ligne est un UINT, KK bits à la  gauche sont significatives) 
Entrées:	
	message (UINT): les KK bits de haut ordre de  est message
	Traspose de matrice generatrice G comme UINT[NN] . Chaque UINT est une colonne de la matrice
Sortie:
	codeWord(UINT): les NN bits sont la codification du message
return: codeWord(UINT)
*/
UINT genere1CodeWordBitsXUINT(
  UINT message, //message (KK bits de gauche important depuis position NN-1 en UINT)
  UINT GTx[NN] //chaque UINT est ligne de Traspose de matrice generatrice==colon
) //espace pour les codeword. Généré dehors
{
  UINT s = 0;
  UINT codeWord = 0;
  int t;
  for (t = 0; t < NN; t++) {
    s = prodEscaBytesKKUINT(
      NN, //taille de CW
      KK, //taille de message
      message, // UINT  seule les positions NN-1 NN-KK sont valides
      GTx[t]);
    //s= prodEscaBytes4(message, GTx[t]);// producte escalaire de message avec colonne
    // de matrice generatrice ( s avec 1 ou 0 en bit 0)

    (codeWord) = (codeWord) | (s << t); //additione les bits à r  depuis la droite
  }

  return codeWord;
}

/**
Génére 1 syndrome à partir de la matrice H de 4 BYTES
(chaque ligne est un BYTE, 8 bits significatives) 
Entrées:
	message (BYTE): les 8 bits de code 
	matrice H comme BYTE[4] . Chaque BYTE est une colonne de la matrice HT
Sortie:
	syndrome(BYTE): les 4 bits de gauche sont significatives
*/

BYTE genereSYNDROMEBitsNew(BYTE code, //code (8 bits)
  BYTE Hx[4] //chaque BYTE est ligne  matrice H<==colonne de HT
) //espace pour les codeword. Généré dehors
{
  BYTE s = 0;
  BYTE syn = 0;
  int t;
  for (t = 0; t < 4; t++) {
    s = prodEscaBytes8(code, Hx[t]); // producte escalaire de message avec colonne
    // de matrice HT ( s avec 1 ou 0 en bit 0)

    syn = (syn) | (s << (7 - t)); //additione les bits à syn  depuis la position 7 gauche
  }

  return syn;

}

/**
Génére 1 syndrome à partir de la matrice H de KK UINT
(chaque ligne est un UINT, NN bits significatives) 
Entrées:
	message (UINT): les NN bits de code 
	matrice H comme UINT[KK] . Chaque UINT est une colonne de la matrice HT
Sortie:
	syndrome(UINT): les KK bits de gauche apres bit NN sont significatives
*/

UINT genereSYNDROMEBitsNewUINT(UINT code, //code (NN bits)
  UINT Hx[KK] //chaque UINT est ligne  matrice H<==colonne de HT
) //espace pour les codeword. Généré dehors
{
  UINT s = 0;
  UINT syn = 0;
  int t;
  for (t = 0; t < KK; t++) {
    s = prodEscaUINT(NN,
      code, // UINT
      Hx[t]); // UINT
    //s= prodEscaBytes8(code, Hx[t]);// producte escalaire de message avec colonne
    // de matrice HT ( s avec 1 ou 0 en bit 0)

    syn = (syn) | (s << (NN - 1 - t)); //additione les bits à syn  depuis la position NN-1 gauche vers la droite
  }
  return syn;

}

/**
évalue la distance de Hamming du vecteur binaire : b de taille: NN 
Entrée:
	octete b comme UINT
Sortie:
	distance de Hamming (no. de bits qui sont 1)
return:
	distance de Hamming
*/
int distHammingUINT(UINT b) {
  // calcule de la distance de Hamming
  //parcours le vecteur b et additionne les bits =1
  int i = 0, s = 0;
  UINT t = 1;
  for (i = 0; i < NN; i++) s = s + ((((t << i) & b) == 0) ? 0 : 1);
  return s; // distance de Hamming
}

/**
évalue la distance de Hamming du vecteur binaire : b de taille: nx
Entrée:
	octete b comme UINT
	nx: taille de code
Sortie:
	distance de Hamming (no. de bits qui sont 1)
return:
	distance de Hamming
*/
int distHammingUINT_nvar(UINT b, int nx) {
  // calcule de la distance de Hamming
  //parcours le vecteur b et additionne les bits =1
  int i = 0, s = 0;
  UINT t = 1;
  for (i = 0; i < nx; i++) s = s + ((((t << i) & b) == 0) ? 0 : 1);
  return s; // distance de Hamming
}

/**
Retourne la distance de Hamming du code à partir
du ensemble de codewords comme le minimum de la
distance de Hamming de chaque codeWord.
Entrées:
	nx: taille de codewords(int)
	ncw:nombre de codeWords(int)
	codeWords[]: liste de ncw codewords (UINT[])
Sortie:
	distance de Hamming de code(int)

*/
int distandeHammingCode(int nx, int ncw, UINT codeWords[]) {

  int i, min = nx, d;
  for (i = 0; i < ncw; i++) {
    d = distHammingUINT_nvar(codeWords[i], nx);
    if (d != 0 && d < min) min = d;
  }
  return min;
}

/**
évalue la distance de Hamming du vecteur binaire : b de taille: 8 BYTE
Entrée:
	octete b comme BYTE
Sortie:
	distance de Hamming (no. de bits qui sont 1)
return:
	distance de Hamming
*/
int distHammingBYTE(BYTE b) {
  // calcule de la distance de Hamming
  //parcours le vecteur b et additionne les bits =1
  int i = 0, s = 0;
  BYTE t = 1;
  for (i = 0; i < 8; i++) s = s + ((((t << i) & b) == 0) ? 0 : 1);
  return s; // distance de Hamming
}

/**
Calcule la distance de Hamming entre BYTES
Entrées:
	b1,b2 sont les BYTES
Sortie:
	distance de Hamming: Nombre de positions différents en b1 et b2
*/

int calculeDistHammingEntreBytesN(BYTE b1, BYTE b2) {
  return distHammingBYTE((BYTE) b1 ^ b2);
  return 0;
}
/**
Identité de codeWord avec 1 erreur
Entrée:
	syndrome ----- BYTE
	matrice HT ----BYTE[8] (traspose de H)
Sortié:
	identite de codeWord avec 1 erreur(0---7)
Return:
	identité ou
	-1 no identifiqué
*/
int identiteDeCodeWord(BYTE syndrome, // syndrome avec posible (!=0 )erreur
  BYTE HTx[8]) //matrice HT (chaque BYTE est ligne de Matrice HT=colonne de H)
{
  BYTE r;
  int i;

  for (i = 0; i < 8; i++) {
    r = syndrome ^ HTx[i]; //XOR parcours colonnes de H et vérifique égalité avec syndrome
    if (distHammingBYTE(r) == 0) return i; //si existe égalité sorte avec la identité de codeWord
  }

  return -1;
}
/**
Identité de codeWord avec 1 erreur
Entrée:
	syndrome ----- UINT
	matrice HT ----UINT[NN] (traspose de H)
Sortié:
	identite de codeWord avec 1 erreur(0,---,NN-1)
Return:
	identité ou
	-1 no identifiqué
*/
int identiteDeCodeWordUINT(UINT syndrome, // syndrome avec posible (!=0 )erreur
  UINT HTx[NN]) //matrice HT (chaque UINT est ligne de Matrice HT=colonne de H)
{
  UINT r;
  int i;

  for (i = 0; i < NN; i++) {
    r = syndrome ^ HTx[i]; //XOR parcours colonnes de H et vérifique égalité avec syndrome
    if (distHammingUINT(r) == 0) return i; //si existe égalité sorte avec la identité de codeWord
  }

  return -1;
}

/**
Génére le group cpmplète de 16 codewords pour la matrix G
4x8 k=4,n=8
Entres: BYTES de matrice génératrice trasposée GTx
Sortie: BYTES de chaque du 16 possible codewords (Espace génére dehors)
return: toujours 0
*/

int genereCodeWordsBYTE(BYTE GTx[8], //matrice génératrice Traspose
  BYTE codeWords[16]) //espace pour les codewords(2^4)
{

  int k, i = 0, base;
  BYTE message; // espace pour message
  BYTE cv8 = 128; //(10000000)
  do {
    message = 0;
    base = 1;
    for (k = 0; k < 16; k++) {
      base = 2 * base;
      if (i % base < base / 2) {
        message = message | (cv8 >> k);
      }

    }
    genere1CodeWordBits(message, //message (BYTE, 4 bits de gauche important)
      GTx, //chaque BYTE est ligne de Traspose de matrice generatrice==colonne
      &
      codeWords[i]); //espace pour les codeword. Généré dehors

    i++;
  } while (i < 16);

  return 0;
}
/**
Génére le group cpmplète de 2^KK codewords pour la matrix G
KKxNN 
Entres: UINT de matrice génératrice trasposée GTx
Sortie: UINT de chaque du 2^KK possible codewords (Espace génére dehors)

return: toujours 0
*/
int genereCodeWordsUINT(UINT GTx[NN], //matrice génératrice Traspose
  UINT codeWords[]) //espace pour les codewords(2^KK)
{

  int k, i = 0;
  UINT base;
  UINT message; // espace pour message
  UINT cv8 = 1 << (NN - 1); //(100000000 ....00) 1 en bit NN-1
  int ncw = 1 << KK; //2^KK, 16 si KK=4
  do {
    message = 0;
    base = 1;
    for (k = 0; k < ncw; k++) {
      base = (base << 1); //base =2*base;
      if (i % base < (base >> 1)) //  base>>1=   base =base/2;
      {
        message = message | (cv8 >> k);
      }

    }

    genere1CodeWordBitsUINT(message, //message (kk bits de gauche important)
      GTx, //chaque BYTE est ligne de Traspose de matrice generatrice==colonne
      &
      codeWords[i]); //espace pour les codeword. Généré dehors

    i++;
  } while (i < ncw);

  return 0;
}

/**
Génére un code avec t erreures en positionnes aleatories
Entrée:
	codeWord: BYTE contient le codeWord sans errurs
	t: nombre de erreurs  (0<-=t<8) (entier)
Sortie:
	code avec t erreures en codeWord, en postionnes  aleatoires.
return: code

*/
BYTE genereCodeMultipleErreurs(BYTE codeWord,
  int t
) {
  BYTE r = codeWord;
  BYTE posN, posU = 0;
  BYTE uno = 1;
  int pos, i = 0;
  do {
    do {
      pos = (int)(random() % 8); // nombre entre 0 et 7 inclus
      posN = posU | (uno << pos); // sauve position à changer en posN
      if (posN != posU) { // si la position est nouvelle se accepte
        r = flipBitDeByte(r, // byte à changer
          pos);
        posU = posN; // actualise posU         	
        i++; //augmente le nombre de changes effectues	
      }
    } while (posN == posU); //continue jusque trouve position différente aux antérieurs
  } while (i < t); // continue jusque le nombre de changes effectues soit t

  return r;
}