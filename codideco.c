#include "headers/codification.h"

#include "headers/decodification.h"

#include "headers/rutinesBits.h"

#include "headers/restes8_1e.h"


char * messageA = "Entrez le type de bruit à appliquer:\n"
"\t0: Zéro bit changé sur les codewords\n"
"\t1: Un bit changé aleatoirement sur les codewords\n"
"\t2: Deux bits changés aleatoirement sur les codewords\n"
"\tnf: nf bit changées aleatoirement sur les codewords(0<=nf<=8)\n";
int main(int argc, char * argv[]) {
  UINT gd; //(00000000 00000000 00000000 00010011); x^4+x+1
  gd = 16 + 2 + 1;
  char m;
  int nx = 8;
  int rx = 4;
  char codes[2];
  int sym = 0;
  char mc;
  int typeE;
  int typoRuid = 1;
  if (argc != 2) {
    printf("Usage: %s type\n", argv[0]);
    printf("%s\n", messageA);
    printf("Ex: %s 1\n", argv[0]);
    exit(1);
  }
  if (argc == 2 && !((argv[1][0] >= '0') && (argv[1][0] <= '8')))
  // if(argc==2 && !((argv[1][0]=='1')||(argv[1][0]=='2')))
  {
    printf("Usage: %s type\n", argv[0]);
    printf("%s\n", messageA);
    printf("Ex: %s 1\n", argv[0]);
    exit(1);
  }
  typoRuid = argv[1][0] - '0';

  printf("Entrez un symbole (1 char) SVP... (finir avec Ctrl+D)\n");

  initializeSEED(); // pour generateurs random();

  while ((sym = getchar()) != EOF) {

    if (sym != '\n') {
      //ZONE DE CODIFICATION
      m = (char) sym;
      genere2charsAvecCode(m, nx, rx, gd, codes);
      //FIN ZONE DE CODIFICATION

      //ZONE DE BRUIT
      printf("___________________________________________________________\n");
      printf("___________________________________________________________\n");
      printf("\tAvant medium code entrée nibble bas   ");
      montreBYTE((BYTE) codes[0]);
      codes[0] = genereNFErreursSurCodeCharSURrange(typoRuid, codes[0], 8, 0);
      printf("\tAprès medium code entrée nibble bas   ");
      montreBYTE((BYTE) codes[0]);
      printf("\n\tAvant medium code entrée nibble haut  ");
      montreBYTE((BYTE) codes[1]);
      codes[1] = genereNFErreursSurCodeCharSURrange(typoRuid, codes[1], 8, 0);
      printf("\tAprès medium code entrée nibble haut  ");
      montreBYTE((BYTE) codes[1]);
      //FIN ZONE DE BRUIT

      //ZONE DE DECODIFICATION
      typeE = genere1charDe2codes(codes, 8, 4, gd, restes8_1e, & mc);
      //FIN ZONE DE DECODIFICATION

      //ZONE DE DIAGNOSTIQUE
      printf("\n\tChar entré;   ");
      montreBYTE((BYTE) m);
      printf("\tChar recupéré; ");
      montreBYTE((BYTE) mc);
      printf("\n\tMessage originel:  %c\n", m);
      printf("\tMessage recuperé: %c\n", mc);
      int dh = calculeDistHammingEntreBytesN((BYTE) mc, (BYTE) m);
      printf("\tDistance de Hamming :%d\n", dh);
      printf("\tType ruID:%d\t Type de cor:%d\t distHamming:%d\n", typoRuid, typeE, dh);

      printf("___________________________________________________________\n");
      switch (typeE) {
      case 0:
        printf("Diagnostique:\n\tPas de erreurs\n");
        break;
      case 1:
        printf("Diagnostique:\n\tErreur en 1 bit dans un code et corrigé\n");
        break;
      case 2:
        printf("Diagnostique:\n\tErreur en 1 bit dans deux codes et corrigé\n");
        break;
      case 5:
        printf("Diagnostique:\n\tErreur en 1 bit dans un code et corrige,"
          "\n et l'autre pas corrigé\n");
      case 8:
        printf("Diagnostique:\n\tErreur de plus de 1 bit dans les deux "
          "codes et pas corrigé\n");
      default:
        break;

      }
      printf("___________________________________________________________\n");
      //FIN ZONE DE DIAGNOSTIQUE
      printf("Entrez un symbole (1 char) SVP... (finir avec Ctrl+D)\n");
    }

  }

  return 0;
}