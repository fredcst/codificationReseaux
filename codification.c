//codification.c
#include "headers/base.h"
#include "headers/rutinesBits.h"
#include "headers/poly.h"
#include "headers/codification.h"

/**
Codifique 1 char comme 2 chars, chaqu'un avec un nibble de parite.
Génére 2 chars qui contient  les codewords pour chaque  nibble de un char.
Les chars sortent en un array de chars de taille 2.
La routine sert seulement pour codewords de 8 bits et section de message de 4 bits per codeword!!
Entrées:
	m: char à codifiquer (char)
	nx: no de bits de codeword pour chaque nibble de m=8
	rx: ordre de polynome générateur=4
	gd: coefficients de polynôme générateur comme UINT (0000000 0000000 0000000 0001 0011)(g(x)=x^4+x+1)
	*c: address de 2 chars pour sauver les codes des nibbles de m
Sortie:
	c[2}: array de deux chars avec les codes des nibbles superier et inderieur de m.
	en c[0] sorte code nibble inferieur;en c[1] sorte code nibble superieur;
         nibble superieur= zone de bits: s en: (ssss iiiii)  
	 nibble inferieur = zone de bits: i en: (ssss iiiii)  
return : toujours 0
*/

int genere2charsAvecCode(char m, int nx, int rx, UINT gd, char * c) {
  UINT qd;
  if (nx != 8 || rx != 4) {
    fprintf(stderr, "Erreur genere2charsAvecCode. nx!=8 ou rx!=4\n");
    exit(1);
  }
  UINT mh = charNH_A_MUINT(m, 8); //obtient  nibble haut en UINT
  UINT mb = charNB_A_MUINT(m, 8); //obtient  nibble bas  en UINT
  UINT ch = creerCodeWord(gd, mh, 8, 4, & qd); //crée code words                        
  UINT cb = creerCodeWord(gd, mb, 8, 4, & qd); //crée code words
  char charh = code_A_CHAR(ch, 8); //met code en chars
  char charb = code_A_CHAR(cb, 8); //met code en chars
  c[0] = charb;
  c[1] = charh;

  return 0;
}

/**
	Codifique 1 char comme deux chars ,un avec le char originel, et l'autre
	avec les bits de parite de chaque nibble du char originel. 
	Les chars sortent en un array de chars de taille 2.
	La routine sert seulement pour codewords de 8 bits et section de message de 4 bits per codeword!!
Entrées:
	m: char à codifiquer (char)
	nx: no de bits de codeword pour chaque nibble de m=8
	rx: ordre de polynome générateur=4
	gd: coefficients de polynôme générateur comme UINT (0000000 0000000 0000000 0001 0011)(g(x)=x^4+x+1)
	*c: address de 2 chars pour sauver les codes des nibbles de m
Sortie:
	c[2}: array de deux chars avec le char originel et un char de bits de control de deux nibbles.
	en c[0] sorte le char originel. En c[1] sortent les  bits de control de deux nibbles de char;
	m=(h,b) --->  c[0}=(h,b) c[1]=(hc, bc)
         nibble superieur= zone de bits: s en: (ssss iiiii)  
	 nibble inferieur = zone de bits: i en: (ssss iiiii)  
*/
int genere2charsAvecCodeBItsDeControlEn1Char(char m, int nx, int rx, UINT gd, char * c) {
  UINT qd;
  if (nx != 8 || rx != 4) {
    fprintf(stderr, "Erreur genere2charsAvecCode. nx!=8 ou rx!=4\n");
    exit(1);
  }
  UINT mh = charNH_A_MUINT(m, 8); //met  nibble haut en UINT
  UINT mb = charNB_A_MUINT(m, 8); //met  nibble bas  en UINT
  UINT ch = creerCodeWord(gd, mh, 8, 4, & qd); //crée code words de nibble haut                     
  UINT cb = creerCodeWord(gd, mb, 8, 4, & qd); //crée code words de nibble bas

  UINT filtroB = 15;
  UINT filtroH = filtroB << 4;

  UINT chb = ch & filtroB;
  UINT chh = ch & filtroH;
  UINT cbb = cb & filtroB;
  UINT cbh = cb & filtroH;

  UINT cm = (cbh >> 4) | chh; // contient message?
  UINT cc = cbb | (chb << 4); // contient bit de control?
  char charh = code_A_CHAR(cc, 8); //met code en chars
  char charb = code_A_CHAR(cm, 8); //met code en chars
  c[0] = charb;
  c[1] = charh;
  return 0;
}