//fichier bitsBase.h
#include "headers/base.h"

#include "headers/bitsBase.h"


/**
Montre UINT en écran et termine avec: \n
Entrée:UINT a montrer (UINT)
    n : taille a montrer
Sortie:none
*/
void montreUINT(int n, UINT b) {
  int i;
  UINT r, r0 = 1 << (n - 1), d;
  for (i = 0; i < n; i++) {
    r = r0 >> i; // positionne 1 en bit n-1-i;
    d = b & r; //sélectionne bit r de b pour tester si est null or non
    printf("%d", (d == 0) ? 0 : 1); //si est null écrit 0, sinon 1
  }
  printf("\n");
  return;
}
void montreUINTSNL(int n, UINT b) {
  int i;
  UINT r, r0 = 1 << (n - 1), d;
  for (i = 0; i < n; i++) {
    r = r0 >> i; // positionne 1 en bit n-1-i;
    d = b & r; //sélectionne bit r de b pour tester si est null or non
    printf("%d", (d == 0) ? 0 : 1); //si est null écrit 0, sinon 1
  }
  //printf("\n");
  return;
}


/**
Montre byte en écran et termine avec: \n
Entrée:byte a montrer (BYTE)
Sortie:none
*/
void montreBYTE(BYTE b) {
  int i;
  BYTE r, r0 = 128, d;
  for (i = 0; i < 8; i++) {
    r = r0 >> i; // positionne 1 en bit 7-i;
    d = b & r; //sélectionne bit r de b pour tester si est null or non
    printf("%d", (d == 0) ? 0 : 1); //si est null écrit 0, sinon 1
  }
  printf("\n");
  return;
}

/**
Montre byte en écran et termine avec: \n
Entrée:byte a montrer (BYTE)
Sortie:none
*/
void montreFILEBYTE(FILE * fp, BYTE b) {
  int i;
  BYTE r, r0 = 128, d;
  for (i = 0; i < 8; i++) {
    r = r0 >> i; // positionne 1 en bit 7-i;
    d = b & r; //sélectionne bit r de b pour tester si est null or non
    if (fprintf(fp, "%d", (d == 0) ? 0 : 1) < 0) {
      perror("montreFILEBYTE");
      exit(-1);
    }; //si est null écrit 0, sinon 1
  }

  if (fprintf(fp, "\n") < 0) {
    perror("montreFILEBYTE");
    exit(-1);
  };

  return;
}

/**
Montre byte en écran et termine sans: \n
Entrée:byte a montrer (BYTE)
Sortie:none
*/
void montreBYTESansNL(BYTE b) {
  int i;
  BYTE r, r0 = 128, d;
  for (i = 0; i < 8; i++) {
    r = r0 >> i; // positionne 1 en bit 7-i;
    d = b & r; //sélectionne bit r de b pour tester si est null or non
    printf("%d", (d == 0) ? 0 : 1); //si est null écrit 0, sinon 1
  }

  return;
}

/**
Montre byte en écran et termine sans: \n
Entrée:byte a montrer (BYTE)
    !:FILE fp ou écrire
Sortie:none
*/
void montreFILEBYTESansNL(FILE * fp, BYTE b) {
  int i;
  BYTE r, r0 = 128, d;
  for (i = 0; i < 8; i++) {
    r = r0 >> i; // positionne 1 en bit 7-i;
    d = b & r; //sélectionne bit r de b pour tester si est null or non
    if (fprintf(fp, "%d", (d == 0) ? 0 : 1) < 0) {
      perror("montreFILEBYTESansNL");
      exit(-1);
    }; //si est null écrit 0, sinon 1
  }

  return;
}


/**
Montre les k bits de gauche de Byte et termine avec: \n
Entrée:UINT a montrer ses bits a gauche
    n: taille de codeword
Sortie:None
*/
void montreHNibleUINT(int n, int k, UINT b) {
  int i;
  UINT r, r0 = 1 << (n - 1), d;
  for (i = 0; i < k; i++) {
    r = r0 >> i; // positionne 1 en bit n-1-i;
    d = b & r; //sélectionne bit r de b pour tester si est null or non
    printf("%d", (d == 0) ? 0 : 1); //si est null écrit 0, sinon 1
  }
  printf("\n");
  return;
}
void montreHNibleUINTSNL(int n, int k, UINT b) {
  int i;
  UINT r, r0 = 1 << (n - 1), d;
  for (i = 0; i < k; i++) {
    r = r0 >> i; // positionne 1 en bit n-1-i;
    d = b & r; //sélectionne bit r de b pour tester si est null or non
    printf("%d", (d == 0) ? 0 : 1); //si est null écrit 0, sinon 1
  }
  //printf("\n");
  return;
}


/**
Montre les 4 bits de gauche de Byte et termine avec: \n
Entrée:Byte a montrer ses bits a gauche
Sortie:None
*/
void montreHNible(BYTE b) {
  int i;
  BYTE r, r0 = 128, d;
  for (i = 0; i < 4; i++) {
    r = r0 >> i; // positionne 1 en bit 7-i;
    d = b & r; //sélectionne bit r de b pour tester si est null or non
    printf("%d", (d == 0) ? 0 : 1); //si est null écrit 0, sinon 1
  }
  printf("\n");
  return;
}

/**
Montre les 4 bits de gauche de Byte et termine avec: \n
Entrée:Byte a montrer ses bits a gauche
    FILE fp ou écrire
Sortie:None
*/
void montreFILEHNible(FILE * fp, BYTE b) {
  int i;
  BYTE r, r0 = 128, d;
  for (i = 0; i < 4; i++) {
    r = r0 >> i; // positionne 1 en bit 7-i;
    d = b & r; //sélectionne bit r de b pour tester si est null or non
    if (fprintf(fp, "%d", (d == 0) ? 0 : 1) < 0) {
      perror("montreFILEHNible");
      exit(-1);
    }; //si est null écrit 0, sinon 1
  }
  if (fprintf(fp, "\n") < 0) {
    perror("montreFILEHNible");
    exit(-1);
  };
  return;
}

/**
Montre les 4 bits de gauche de Byte et termine sans: \n
Entrée:Byte a montrer ses bits a gauche
Sortie:None
*/
void montreHNibleSansNL(BYTE b) {
  int i;
  BYTE r, r0 = 128, d;
  for (i = 0; i < 4; i++) {
    r = r0 >> i; // positionne 1 en bit 7-i;
    d = b & r; //sélectionne bit r de b pour tester si est null or non
    printf("%d", (d == 0) ? 0 : 1); //si est null écrit 0, sinon 1
  }

  return;
}

/**
Montre les 4 bits de gauche de Byte et termine sans: \n
Entrée:Byte a montrer ses bits a gauche
       FILE ou montrer les data
Sortie:None
*/
void montreFILEHNibleSansNL(FILE * fp, BYTE b) {
  int i;
  BYTE r, r0 = 128, d;
  for (i = 0; i < 4; i++) {
    r = r0 >> i; // positionne 1 en bit 7-i;
    d = b & r; //sélectionne bit r de b pour tester si est null or non
    if (fprintf(fp, "%d", (d == 0) ? 0 : 1) < 0) {
      perror("montreFILEHNibleSansNL"); //si est null écrit 0, sinon 1
      exit(-1);
    }
  }

  return;
}

/**
Rutine que inserte bits en byte à partir de un codeWord
écrite comme une liste de entiers.(0,1)
Entrées:
    codewx[],: liste de bits comme entiers(0,1): 8 entiers
    BYTE *b, espace pour le byte retouné
Sortie: 0 on succes , -1 on echec
*/
int genereByteDeCodeWord(int codeWx[], //codeWord comme liste de entiers
  BYTE * b) //b: byte rétourné
{

  * b = 0;
  unsigned char unox, cv8 = 128; //1000000
  int i;
  if (NN != 8) {
    perror("taille de codeword n'est pas 8\n");
    return (-1);
  }
  for (i = 0; i < 8; i++) {
    unox = cv8; //se positionne a gauche en pos 7

    if (codeWx[i] == 1) {
      unox = cv8 >> i; // positionne 1 en position i
      * b = * b | unox; // ajoute le bit au BYTE en position: i
    }
  }

  return 0; //avec succes
}

/**
Rutine que inserte bits en byte à partir de un codeWord
écrite comme un entiere entre 0 et 255
Entrées:
    codewx,: 1 entier entre 0 et 255
    BYTE *b, espace pour le byte retouné
Sortie: 0 on succes , -1 on echec
*/
int genereByteDeCW1Entiere(int codeWx, //codeWord comme 1 entiere
  BYTE * b) //b: byte rétourné
{
  /*
  0---->(00000000)
  1---->(00000001)
  ..
  255-->(11111111)
  */

  * b = 0;
  unsigned char unox, uno = 1; //0000001
  int i;
  if (NN != 8) {
    perror("taille de codeword n'est pas 8\n");
    return (-1);
  }
  unox = uno; //se positionne a droite en pos 0
  for (i = 0; i < 8; i++) {
    unox = uno << i; // positionne 1 en position i
    if ((codeWx & unox) != 0) * b = * b | unox; // ajoute le bit au BYTE en position: i si est 1 en codeWx

  }

  return 0; //avec succes
}


/**
Rutine que inserte bits en byte à partir de un codeWord
écrite comme un entiere entre 0
Entrées:
    codewx,: 1 entier
Sortie: UINT con codeword
1--->(000000....00000001)
2--->(000000....00000010)


N--->(000000111111111111)
                n bits

*/

UINT genereUINTDeCW1Entiere(int n, //taille de codeword v< taille de entiere
  int codeWx //codeWord comme 1 entiere entre 0
) {
  /*

  1--->(000000....00000001)
  2--->(000000....00000010)

  N--->(000000111111111111)
                  n bits
  */

  UINT b = 0;
  UINT unox, uno = 1; //0000000...00000001
  int i;
  unox = uno; //se positionne a droite en pos 0
  for (i = 0; i < n; i++) { //couvre tout le codeword de n bits
    unox = uno << i; // positionne 1 en position i
    if ((codeWx & unox) != 0) b = b | unox; // ajoute le bit au UINT en position: i si est 1 en codeWx

  }
  return b;
}

/**
Rutine que inserte bits en byte à partir de un codeWord
écrite comme un entiere entre 0 et 255
Entrées:
    codewx,: 1 entier entre 0 et 255
Sortie: BYTE con codeword
1--->(00000001)
2--->(00000010)
*/

BYTE genereBYTEDeCW1Entiere(int codeWx //codeWord comme 1 entiere entre 0 et 255
) {
  /*
  0---->(00000000)
  1---->(00000001)
  ..
  255-->(11111111)
  */

  BYTE b = 0;
  unsigned char unox, uno = 1; //1000000
  int i;
  unox = uno; //se positionne a droite en pos 0
  for (i = 0; i < 8; i++) {
    unox = uno << i; // positionne 1 en position i
    if ((codeWx & unox) != 0) b = b | unox; // ajoute le bit au BYTE en position: i si est 1 en codeWx

  }
  return b;
}

/**
Rutine que insere bits de un UINT dans un autre UINT n positions
depuis le droite
Entrées:
    a: UINT avec kes bist à inserer
        n: no. de postions à inserer
Sortie:
    b; UINT avec les bits de a inserés a droite
*/

//$m(x)x^{n-k}=m_{k-1}x^{n-1}+m_{k-2}x^{n-2}+...+m_{0}x^{n-k}$
//$g(x)=g_{n-k}x^{n-k}+g_{n-k-1}x^{n-k-1}+...+g_{0}x^0$

UINT insereUINTenAutreUINT_N_Positions(UINT a, int n) {
  UINT b = 0;
  b = a << n;

  return b;
}

/**
Trouve le bit de commencement de data dans un UINT
Entrée:
    sizeTot: tamano total de UINT (int)
    UINT où trouver première bit de gauche
    different de cerO
Soortie:
    Indice  de premièere bit de gauche qui est non cerp
    ou -1 si a==0
return : indice de bit ou -1 si UINT est cero
*/
int trouveCommenceDadaUINT(int sizeTot, UINT a) {
  UINT r, z = 1 << (sizeTot - 1); // se pose a la gauche
  int ib, i = 0;
  if (a == 0) return -1;
  do {
    i++;
    ib = sizeTot - i; //pos de bit à vérifier
    r = z & a; //and avec UINT en pos ib
    //printf("%d\n",r);
    z = z >> 1;
  } while (r == 0 && i <= sizeTot); //si r!=0 sorte

  return ib;
}

/**
Calcule un produit scalaire de deux bytes en F(2)
Le resultat est dans le bit 0 du BYTE de return
Entrées: b1,b2 sont les UINTS.
    n: no de bits de codeword.
Sortie: le produit scalaire de b1 et b2 en la position 0 du UINT de return.
*/
UINT prodEscaUINT(int n,
  UINT b1, // UINT
  UINT b2) // UINT
{
  UINT r = 0;
  int i, s = 0, s1 = 0, s2 = 0;
  r = b1 & b2; // calcule and
  s1 = r; // le inserte comme un entier

  for (i = 0; i < n; i++) {
    s2 = s1 << (i + 1); //desplace le bits à la position n+1 de  de s1
    s = s ^ s2; //accumule les resultats en s (seulement la position n+1 de s est importante)
  }
  UINT t = 1 << n; // créé 1 en position n+1  (bit n)
  s = s & t; //élimine tous le bits , conservant  le bit n, ou est le résultat.
  //entier et son ordre de bits:(31|..        |15| ....|9|8  |7|6|5|4|3|2|1|0)
  //                                               BYTE   ^      BYTE
  //                                                      +-- résultat en pos n+1 (bit n)

  s = s >> n; //positionne bit en position 0;
  //pos                        n                1
  //(31|..        |15| ....|9|8  |7|6|5|4|3|2|1|0)
  //bit                       n-1               0
  //                                            ^
  //                                            +--résultat qui sorte en bit 0 de BYTE
  //                   |  BYTE
  r = s; // rétourne 0, ou 1 en position 0 de UINT
  return r;
}


/**
Calcule un produit scalaire de deux partial UINT en F(2)
calcule seule avec les kk bits de plus haut signification
Le resultat est dans le bit 0 du UINT de return
Entrées: b1,b2 sont les UINT.
    nn: taille de codewords
    kk: taille de messages    (       |mmmmmmbbbbbbbb)
                     nn< kk> |    0
Sortie: le produit scalaire de b1 et b2 (KK positions m)sur la position 0 du UINT de return.
*/
UINT prodEscaBytesKKUINT(
  int nn, //taille de CW
  int kk, //taille de message
  UINT b1, // UINT  seule les positions NN-1 NN-KK sont valides
  UINT b2) // UINT   seule les positions NN-1 NN-KK sont valides
{
  UINT r = 0;
  int i;
  UINT s = 0, s1 = 0, s2 = 0;
  r = b1 & b2; // calcule and
  s1 = r; //le inserta dans un UINT
  //(00000000 00000000 00000rrrrrr0000)
  for (i = 0; i < kk; i++) {
    s2 = s1 << (i + 1); //desplace itérativamente le bits a position NN du UINT de s1
    s = s ^ s2; //accumule les resultats de XOR en s (seulement la position NN de
    // UINT de s est importante)
  }
  //s=(00000000 00000000 0000abcd 00000000)
  s = s & 1 << nn; //élimine tous le bits , conserve  le bit NN, ou est le résultat.
  //s=(00000000 00000000 0000000d 00000000)
  //entier et son ordre de bits:(31|..        |15| ....|9|8  |7|6|5|4|3|2|1|0)
  //                                               BYTE   ^  |    BYTE
  //                                                      |
  //                            NN

  s = s >> nn; //positionne bit en position 0;
  //(31|..        |15| ....|9|8  |7|6|5|4|3|2|1|0)
  //                             |              ^
  //                                            |
  r = s; // rétourne 0, ou 1 en position 0 de BYTE
  return r;
}


/**
Calcule un produit scalaire de deux bytes en F(2)
Le resultat est dans le bit 0 du BYTE de return
Entrées: b1,b2 sont les BYTES.
Sortie: le produit scalaire de b1 et b2 en la position 0 du BYTE de return.
*/
BYTE prodEscaBytes8(BYTE b1, // byte
  BYTE b2) // byte
{
  BYTE r = 0;
  int i, s = 0, s1 = 0, s2 = 0;
  r = b1 & b2; // calcule and
  s1 = r; // le inserte comme un entier

  for (i = 0; i < 8; i++) {
    s2 = s1 << (i + 1); //desplace le bits à la position 0 de prochain BYTE de S1
    s = s ^ s2; //accumule les resultats en s (seulement la position 0 de 2 byte de s est importante)
  }
  s = s & 256; //élimine tous le bits , conservant  le bit 8, ou est le résultat.
  //entier et son ordre de bits:(31|..        |15| ....|9|8  |7|6|5|4|3|2|1|0)
  //                                               BYTE   ^      BYTE
  //                                                      +-- résultat

  s = s >> 8; //positionne bit en position 0;
  //(31|..        |15| ....|9|8  |7|6|5|4|3|2|1|0)
  //                                            ^
  //                                            +--résultat qui sorte en bit 0 de BYTE
  r = (BYTE) s; // rétourne 0, ou 1 en position 0 de BYTE
  return r;
}

/**
Calcule un produit scalaire de deux medio bytes en F(2)
Le resultat est dans le bit 0 du BYTE de return
Entrées: b1,b2 sont les BYTES.
Sortie: le produit scalaire de b1 et b2 en la position 0 du BYTE de return.
*/
BYTE prodEscaBytes4(BYTE b1, // byte  seule les positions 4->7 sont valides
  BYTE b2) // byte   seule les positions 4->7 sont valides
{
  BYTE r = 0;
  int i, s = 0, s1 = 0, s2 = 0;
  r = b1 & b2; // calcule and
  s1 = r; //le inserta dans un entiere
  //(00000000 00000000 00000000 rrrr0000)
  for (i = 0; i < 4; i++) {
    s2 = s1 << (i + 1); //desplace itérativamente le bits a position 0 du deuxième BYTE de s1
    s = s ^ s2; //accumule les resultats de XOR en s (seulement la position 0 de
    //2ème byte de s est importante)
  }
  //s=(00000000 00000000 0000abcd 00000000)
  s = s & 256; //élimine tous le bits , conserve  le bit 8, ou est le résultat.
  //s=(00000000 00000000 0000000d 00000000)
  //entier et son ordre de bits:(31|..        |15| ....|9|8  |7|6|5|4|3|2|1|0)
  //                                               BYTE   ^  |    BYTE
  //                                                      |

  s = s >> 8; //positionne bit en position 0;
  //(31|..        |15| ....|9|8  |7|6|5|4|3|2|1|0)
  //                             |              ^
  //                                            |
  r = (BYTE) s; // rétourne 0, ou 1 en position 0 de BYTE
  return r;
}

/**
change la position: p du BYTE b
Entrée: b:byte à changer son bits (BYTE)
        p:position de bit à changer (entier)
Sortie;
      le même BYTE b avec la position p changé
*/
BYTE flipBitDeByte(BYTE b, // byte à changer
  int p) // position à xhanger (0-->7)
{

  BYTE s = 1; //(00000001)
  s = s << p; //(00010000)
  //    p
  b = b ^ s; // flip bit: 1<->0

  return b;
}

/**
change la position: p du UINT b
Entrée: b:UINT à changer son bits (UINT)
        p:position de bit à changer (entier)
Sortie;
      le même UINT b avec la position p changé
*/
UINT flipBitDeUINT(UINT b, // UINT à changer
  int p) // position à xhanger (0-->31)
{

  UINT s = 1; //(00000001)
  s = s << p; //(00010000)
  //    p
  b = b ^ s; // flip bit: 1<->0

  return b;
}

/**
Flipp multiple positions en UINT
Entree:
    b: UINT à changer ses bits
    pos[]: liste de positiones entiers  des bits a changer (0-->31)
    nch: entière que est le nombre total de bits a changer
Sortie:
    b avec ses positiones changés
*/
UINT flipMBitDeUINT(
  UINT b, // UINT à changer
  int nch, // nombre de changes
  int pos[]) // liste de position à changer (0-->31)
{
  int i;
  for (i = 0; i < nch; i++) {
    b = flipBitDeUINT(b, pos[i]);

  }
  return b;
}


/**
Montre les len bits plus bas de un UINT
et les precede d'une frase.
Entrées:
frase: frase qui précédera UINT (char *)
len: no. de bits bas à montrer (int)
ux: UINT à montrer
*/
void montreFRASEUINT(char * frase, int len, UINT ux) {
  printf("%s\t", frase);
  montreUINT(len, ux);
  return;
}

//int calculeDistHammingEntreBytes(BYTE b1,BYTE b2)
//{
//return distHammingBYTE( b1^b2);
//}
