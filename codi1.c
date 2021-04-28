// fichier: codi1.c
/**
1-Demande l'entrée de un message arbitraire de KK bits, sans espaces avec (0,1)
	ex. 1111
 	Montre en écran le codeWord généré.
2-Demande l'entrée d'un code arbitraire de NN bits, sans espaces avec (0,1)
	ex. 0111000
	· Montre en écran si le code a d'errurs et son sindrome
	· Montre en écran s'il y a une colonne dans H égal au syndrome et identifie le bit en erreur 
	· (seule valide si on assume que 1 bit a change dans le codeword)
3-Montre en écran H
4-Montre en écran l'ensemble maximal de codeWords et leur distance de Hamming
5-Montre la distance de Hamming du code.

//gcc -o codi1 codi1.c
*/

#include "headers/rutines1.h"

#include "headers/codi.h"


int main() {
  int i, i0, i1, i2, k, LL, estado = SUCCES;
  int somme;
  char chifreM[80], * chifreS;
  chifreS = memset(chifreM, '\0', 80);
  int m[KK], res[NN - KK];
  int codeW[NN];
  LL = 1;
  for (k = 0; k < KK; k++) LL = LL * 2; // calcule LL=2^k;Nombre maximal de codewords

  int ** codeWords; //matrice de entiers

  //printf("chifra=%s\n",chifreS);

  for (i0 = 0; i0 < NN; i0++) {
    codeW[i0] = 0;
  }
  for (i0 = 0; i0 < NN - KK; i0++) {
    res[i0] = 0;
  }

  do {
    printf("\nEntrez une code binaire de %d chiffres (0,1)(sans espaces). Exemple: 0011, S'il-vous-plaît...\n"
      "Les chiffres excédentaires ne seront pas pris en compte\n", KK);
    if (fscanf(stdin, "%s", chifreS) != 1) {
      perror("Chiffre pas lu. Sorte\n");
      exit(1);
    }
    estado = SUCCES;
    i = 0;
    while (i < KK) { //vérification de chiffre

      if (isdigit(chifreS[i]) && (chifreS[i] == '0' || chifreS[i] == '1')) {
        //printf("%c",chifreS[i]);
        m[i] = chifreS[i] - '0';

      } else {
        printf("CHIFFRE avec erreurs\n");
        estado = ECHEC;
        break;
      }
      i++;
    }
  } while (estado == ECHEC);
  //printf("\n");
  if (estado == SUCCES) { //chiffre aceptée
    printf("\nChiffre: ");
    for (i = 0; i < KK; i++) printf("%d", m[i]);
    printf("\n");

    printf("\nMATRICE G:\n");
    for (i1 = 0; i1 < KK; i1++) {
      for (i2 = 0; i2 < NN; i2++) {
        printf("%d ", G[i1][i2]);
      }
      printf("\n");
    }

    for (i2 = 0; i2 < NN; i2++) {
      somme = 0;
      for (i1 = 0; i1 < KK; i1++) somme = sommeB(somme, prodB(m[i1], G[i1][i2]));
      codeW[i2] = somme;
    }
    printf("\nCodeW: ");
    for (i2 = 0; i2 < NN; i2++) printf("%d", codeW[i2]);
    printf("\n");

    for (i1 = 0; i1 < NN - KK; i1++) {
      somme = 0;
      for (i2 = 0; i2 < NN; i2++) somme = sommeB(somme, prodB(codeW[i2], H[i1][i2]));
      res[i1] = somme;
    }
    printf("Syndrome de codeW: (doit être null)");
    for (i1 = 0; i1 < NN - KK; i1++) printf("%d", res[i1]);
    printf("\n");

  }

  /**** Verification d'erreurs en codes arbitraries*****/

  do {
    printf("\n\nEntrez une code binaire de %d chiffres (0,1)(sans espaces). Exemple: 00110011, S'il-vous-plaît...\n"
      "Les chiffres excédentaires ne seront pas pris en compte\n", NN);
    if (fscanf(stdin, "%s", chifreS) != 1) {
      perror("Chiffre pas lu. Exit\n");
      exit(1);
    }
    i = 0;
    estado = SUCCES;
    while (i < NN) { //vérification de chiffre

      if (isdigit(chifreS[i]) && (chifreS[i] == '0' || chifreS[i] == '1')) {
        //printf("%c",chifreS[i]);
        codeW[i] = chifreS[i] - '0';

      } else {
        printf("CHIFFRE avec erreurs\n");
        estado = ECHEC;
        break;
      }
      i++;
    }

  } while (estado == ECHEC);
  if (estado == SUCCES) { //chiffre accepté
    printf("\nMATRICE H:\n");
    for (i1 = 0; i1 < NN - KK; i1++) {
      for (i2 = 0; i2 < NN; i2++) {
        printf("%d ", H[i1][i2]);
      }
      printf("\n");
    }

    printf("\ncode: ");
    for (i = 0; i < NN; i++) printf("%d", codeW[i]);
    printf("\n");
    for (i1 = 0; i1 < NN - KK; i1++) { //calcule de syndrome de code  = code.H^T
      somme = 0;
      for (i2 = 0; i2 < NN; i2++) somme = sommeB(somme, prodB(codeW[i2], H[i1][i2]));
      res[i1] = somme;
    }
    printf("\nSyndrome de code: ");
    for (i1 = 0; i1 < NN - KK; i1++) printf("%d", res[i1]); //montre en ecran syndrome de code
    printf("\n");
    somme = 0;
    for (i1 = 0; i1 < NN - KK; i1++) somme = somme + res[i1]; //somme le nombre de bits differentes a cero
    //dans le sindrome
    if (somme != 0) {
      printf("Code avec erreurs!\n");
      for (i1 = 0; i1 < NN; i1++) { //si il y a 1 bit avec erreur , le syndrome permit le identifier.
        somme = 0;
        for (i2 = 0; i2 < NN - KK; i2++) somme = somme + sommeB(res[i2], H[i2][i1]); //fait XOR entre bits de syndrome 
        //et bits de chaque colonne de H
        //Si pour chaque colonne
        //la addition de XOR est 0,la colonne
        //est identique au syndrome et alors
        //le indice de colonne de H est
        //le bit de code avec l'erreur!!
        //(seulement s'il y a 1 erreur)

        if (somme == 0) {
          printf("\nS'il y a 1 erreur, ceci est dans bit %d de codeWord. [0...%d]\n", i1, NN - 1);
          printf("CodeWord avec 1 erreur:\n");
          for (i2 = 0; i2 < NN; i2++) printf("%d", codeW[i2]); //montre en ecran codeW avec erreur 
          printf("\n");
          codeW[i1] = (codeW[i1] == 1) ? 0 : 1; //correction de codeW
          printf("CodeWord corrigé:\n");
          for (i2 = 0; i2 < NN; i2++) printf("%d", codeW[i2]); //montre en ecran codeW corrigé 
          printf("\n");
        }
      }
    }

  }

  codeWords = (int ** ) malloc(LL * sizeof(int * )); // se genere le matrice de adresses de lignes=codeWord
  if (codeWords != NULL) {
    for (k = 0; k < LL; k++) codeWords[k] = (int * ) malloc(NN * sizeof(int)); // chaque ligne a NN bits	
    genereCodeWords1(LL, G, codeWords);
    printf("\nEnsemble complet de codeWords et leurs distance de Hamming: \n");
    int dH, mindH = NN;
    for (i = 0; i < LL; i++) {
      dH = distHamming(NN, codeWords[i]);
      for (k = 0; k < NN; k++) printf("%d", codeWords[i][k]);
      printf("	d=%d \n", dH);
      if (dH != 0 && mindH > dH) mindH = dH;
    }
    printf("Distance de Hamming du code: %d\n", mindH);

  }

  /**********************************************************************************************
       On choisit le codeWord 0 et on change séquentielment ses bits
        On obtient le syndrome et le montre en éecran	   
  **********************************************************************************************/
  int codeErr[8]; // espace pour code vec erreur
  printf("\nEnsemble de syndromes pour 1 erreur dans codeWord 0\n");
  printf("---------------------------------------------------\n");
  printf("codeWord 0: ");
  for (i = 0; i < NN; i++) {
    codeErr[i] = codeWords[0][i];
    printf("%d", codeWords[0][i]);
  }
  printf("\n");
  int q;
  for (q = 0; q < NN; q++) {

    codeErr[q] = (codeWords[0][q] == 0) ? 1 : 0; //se changent les bits q de codeWord

    for (i1 = 0; i1 < NN - KK; i1++) { //calcule de syndrome de code  = code.H^T
      somme = 0;
      for (i2 = 0; i2 < NN; i2++) somme = sommeB(somme, prodB(codeErr[i2], H[i1][i2]));
      res[i1] = somme;
    }

    for (i = 0; i < NN; i++) {
      printf("%d", codeWords[0][i]);
    }

    printf(" ");

    for (i = 0; i < NN; i++) {
      printf("%d", codeErr[i]);
    }

    printf(" ");

    for (i1 = 0; i1 < NN - KK; i1++) printf("%d", res[i1]);
    printf("\n");

    codeErr[q] = codeWords[0][q]; //revient en arrière
  }

  if (codeWords != NULL) {
    for (k = 0; k < LL; k++)
      if (codeWords[k] != NULL) free(codeWords[k]);
    free(codeWords);
  }

  return 0;
}