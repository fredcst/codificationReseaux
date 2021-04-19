//codification.c

#include "headers/base.h"
#include "headers/rutinesBits.h"
#include "headers/poly.h"
//#include "restes8_1e.h"

#include "headers/codification.h"



/**


xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

char ---> nh nb  ----> UINT mh UINT mb ---> UINT ch UINT cb -----> charh charb   <---section a travailler
8          4  4             4        4           8        8          8     8
					
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
					|
					medium
				        |
                                        v

charh charb ---> UINT chr UINT cbr ---> correction ---->  UINT mhc UINT mbc ---> nhc nbc ---> charc
8       8              8        8                               4        4        4   4        8


xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
char m;// char à envoier

UINT mh= charNH_A_MUINT(m,8);//obtient  nibble haut en UINT
UINT mb= charNB_A_MUINT(m,8);//obtient  nibble bas  en UINT
UINT ch= creerCodeWord(gd,mh,8,4,&qd);//crée code words                        <----section a travailler
UINT cb= creerCodeWord(gd,mb,8,4,&qd);//crée code words
char charh=code_A_CHAR(ch,8);//met code en chars
char charb=code_A_CHAR(cb,8);//met code en chars
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx


put (charb);// se envoie message avec bits bas
put (charh);// se envoie message avec bits haut

SOCKETS

BRUIT



rec (charb);// se réceive message avec bits bas
rec (charh);// se réceive message avec bits haut

UINT cbr=CHAR_A_UINT(charb,8);//met codes char en codes UINT
UINT chr=CHAR_A_UINT(charh,8);//met codes char en codes UINT
UINT cbc=codeCorrige1eS(cbr,gd,8,4,restes1e,&EX);// corrige ou non codes UINT
if(EX==2 && FLAG_AVIS==1){printf("Erreur no identifié\n");}//avis si existe erreur avec no intention de corrige
UINT chc=codeCorrige1eS(chr,gd,8,4,restes1e,&EX);// corrige ou non codes UINT
if(EX==2 && FLAG_AVIS==1){printf("Erreur no identifié\n");}//avis si existe erreur avec no intention de corrige
char nbc=codeM4UINTaCHAR_B(cbc,8,4);//transfère de message de code a nibble bas de char
char nhc=codeM4UINTaCHAR_H(chc,8,4);//transfère de message de code a nibble haut de char
char mc=nh_nbaCHAR(nhc,nbc);//récuperation de char envoié avec possible corrections


**/

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


int genere2charsAvecCode(char m,int nx,int rx,UINT gd,char *c)
{
UINT qd;
if(nx!=8 || rx!=4 )
{
	fprintf(stderr,"Erreur genere2charsAvecCode. nx!=8 ou rx!=4\n");
	 exit(1);
}
UINT mh= charNH_A_MUINT(m,8);//obtient  nibble haut en UINT
UINT mb= charNB_A_MUINT(m,8);//obtient  nibble bas  en UINT
UINT ch= creerCodeWord(gd,mh,8,4,&qd);//crée code words                        
UINT cb= creerCodeWord(gd,mb,8,4,&qd);//crée code words
char charh=code_A_CHAR(ch,8);//met code en chars
char charb=code_A_CHAR(cb,8);//met code en chars
c[0]=charb;
c[1]=charh;

return 0;
}


/**
MOVAISE SOLUTION envoyer les bits de parite des deux nibbles en une seule byte, et les bits de
 message en autre!!,car il est possible que pour un niveau de bruit de 1 bit per BYTE de erreur, dans 
deux bytes consécutif les bits changés soient dans la meme region : sur le nibble haut ou sur 
le nibble bas des  deux bytes, ce que signifique  que le code reconstruit des deux nibbles hauts
 ou des deux nibbles bas montrerait deux errors!. Par exemple deux erreurs :un dans les premier
 4 bits de message et l'autre en les 4 bits qui servent de control de parite. Dans cet cas il n'est 
pas possible de corriger.



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
int genere2charsAvecCodeBItsDeControlEn1Char(char m,int nx,int rx,UINT gd,char *c)
{
UINT qd;
if(nx!=8 || rx!=4 )
{
	fprintf(stderr,"Erreur genere2charsAvecCode. nx!=8 ou rx!=4\n");
	 exit(1);
}
UINT mh= charNH_A_MUINT(m,8);//met  nibble haut en UINT
UINT mb= charNB_A_MUINT(m,8);//met  nibble bas  en UINT




UINT ch= creerCodeWord(gd,mh,8,4,&qd);//crée code words de nibble haut                     
UINT cb= creerCodeWord(gd,mb,8,4,&qd);//crée code words de nibble bas


//montreFRASEUINT("codenh:",32,ch);

//montreFRASEUINT("codenb:",32,cb);

UINT filtroB=15;
//montreFRASEUINT("filtroB:",32,filtroB);
UINT filtroH=filtroB<<4;
//montreFRASEUINT("filtroH:",32,filtroH);

UINT chb=ch&filtroB;
//montreFRASEUINT("chb:",8,chb);
UINT chh=ch&filtroH;
//montreFRASEUINT("chh:",8,chh);
UINT cbb=cb&filtroB;
//montreFRASEUINT("cbb:",8,cbb);
UINT cbh=cb&filtroH;
//montreFRASEUINT("cbh:",8,cbh);

UINT cm=(cbh>>4)|chh; // contient message?
UINT cc=cbb|(chb<<4); // contient bit de control?
//montreFRASEUINT("message:",8,cm);
//montreFRASEUINT("control:",8,cc);
char charh=code_A_CHAR(cc,8);//met code en chars
char charb=code_A_CHAR(cm,8);//met code en chars
c[0]=charb;
c[1]=charh;
return 0;
}










