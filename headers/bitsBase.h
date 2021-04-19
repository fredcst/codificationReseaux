#ifndef BITSBASEH
#define BITSBASEH
//fichier bitsBase.h
#include "base.h"

/**
Montre UINT en écran et termine avec: \n
Entrée:UINT a montrer (UINT)
	n : taille a montrer
Sortie:none
*/
void montreUINT(int n,UINT b);





/**
Montre UINT en écran et termine sans: \n
Entrée:UINT a montrer (UINT)
	n : taille a montrer
Sortie:none
*/
void montreUINTSNL(int n,UINT b);






/**
Montre byte en écran et termine avec: \n
Entrée:byte a montrer (BYTE)
Sortie:none
*/
void montreBYTE(BYTE b);






/**
Montre byte en écran et termine avec: \n
Entrée:byte a montrer (BYTE)
Sortie:none
*/
void montreFILEBYTE(FILE *fp,BYTE b);








/**
Montre byte en écran et termine sans: \n
Entrée:byte a montrer (BYTE)
Sortie:none
*/
void montreBYTESansNL(BYTE b);








/**
Montre byte en écran et termine sans: \n
Entrée:byte a montrer (BYTE)
	!:FILE fp ou écrire
Sortie:none
*/
void montreFILEBYTESansNL(FILE *fp,BYTE b);








/**
Montre les k bits de gauche de Byte et termine avec: \n
Entrée:UINT a montrer ses bits a gauche
	n: taille de codeword
Sortie:None
*/
void montreHNibleUINT(int n,int k,UINT b);








/**
Montre les k bits de gauche de Byte et termine sans: \n
Entrée:UINT a montrer ses bits a gauche
	n: taille de codeword
Sortie:None
*/
void montreHNibleUINTSNL(int n,int k,UINT b);









/**
Montre les 4 bits de gauche de Byte et termine avec: \n
Entrée:Byte a montrer ses bits a gauche
Sortie:None
*/
void montreHNible(BYTE b);








/**
Montre les 4 bits de gauche de Byte et termine avec: \n
Entrée:Byte a montrer ses bits a gauche
	FILE fp ou écrire
Sortie:None
*/
void montreFILEHNible(FILE *fp,BYTE b);










/**
Montre les 4 bits de gauche de Byte et termine sans: \n
Entrée:Byte a montrer ses bits a gauche
Sortie:None
*/
void montreHNibleSansNL(BYTE b);










/**
Montre les 4 bits de gauche de Byte et termine sans: \n
Entrée:Byte a montrer ses bits a gauche
       FILE ou montrer les data	
Sortie:None
*/
void montreFILEHNibleSansNL(FILE *fp,BYTE b);









/**
Rutine que inserte bits en byte à partir de un codeWord 
écrite comme une liste de entiers.(0,1)
Entrées:
	codewx[],: liste de bits comme entiers(0,1): 8 entiers 
	BYTE *b, espace pour le byte retouné
Sortie: 0 on succes , -1 on echec
*/
int genereByteDeCodeWord(int codeWx[],//codeWord comme liste de entiers
				BYTE *b);//b: byte rétourné








/**
Rutine que inserte bits en byte à partir de un codeWord 
écrite comme un entiere entre 0 et 255
Entrées:
	codewx,: 1 entier entre 0 et 255 
	BYTE *b, espace pour le byte retouné
Sortie: 0 on succes , -1 on echec
*/
int genereByteDeCW1Entiere(int codeWx,//codeWord comme 1 entiere
				BYTE *b);//b: byte rétourné










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
UINT genereUINTDeCW1Entiere(int n,//taille de codeword v< taille de entiere
			int codeWx//codeWord comme 1 entiere entre 0 
		);








/**
Rutine que inserte bits en byte à partir de un codeWord 
écrite comme un entiere entre 0 et 255
Entrées:
	codewx,: 1 entier entre 0 et 255 
Sortie: BYTE con codeword  
1--->(00000001)
2--->(00000010)
*/
BYTE genereBYTEDeCW1Entiere(int codeWx//codeWord comme 1 entiere entre 0 et 255
		);






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
UINT  insereUINTenAutreUINT_N_Positions(UINT a,int n);










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
int trouveCommenceDadaUINT(int sizeTot,UINT a );







/**
Calcule un produit scalaire de deux bytes en F(2)
Le resultat est dans le bit 0 du BYTE de return
Entrées: b1,b2 sont les UINTS.
	n: no de bits de codeword.
Sortie: le produit scalaire de b1 et b2 en la position 0 du UINT de return.
*/
UINT prodEscaUINT(int n,
		  UINT b1,// UINT
		  UINT b2) ;// UINT






/**
Calcule un produit scalaire de deux partial UINT en F(2)
calcule seule avec les kk bits de plus haut signification
Le resultat est dans le bit 0 du UINT de return
Entrées: b1,b2 sont les UINT.
	nn: taille de codewords
	kk: taille de messages    (       |mmmmmmbbbbbbbb)
					 nn< kk> |	0		
Sortie: le produit scalaire de b1 et b2 (KK positions m)sur la position 0 du UINT de return.
*/
UINT prodEscaBytesKKUINT(
			int nn, //taille de CW
			int kk, //taille de message
			UINT b1,// UINT  seule les positions NN-1 NN-KK sont valides
		        UINT b2); // UINT   seule les positions NN-1 NN-KK sont valides











/**
Calcule un produit scalaire de deux bytes en F(2)
Le resultat est dans le bit 0 du BYTE de return
Entrées: b1,b2 sont les BYTES.
Sortie: le produit scalaire de b1 et b2 en la position 0 du BYTE de return.
*/
BYTE prodEscaBytes8(BYTE b1,// byte  
		  BYTE b2); // byte







/**
Calcule un produit scalaire de deux medio bytes en F(2)
Le resultat est dans le bit 0 du BYTE de return
Entrées: b1,b2 sont les BYTES.
Sortie: le produit scalaire de b1 et b2 en la position 0 du BYTE de return.
*/
BYTE prodEscaBytes4(BYTE b1,// byte  seule les positions 4->7 sont valides
		  BYTE b2); // byte   seule les positions 4->7 sont valides







/**
change la position: p du BYTE b
Entrée: b:byte à changer son bits (BYTE)
        p:position de bit à changer (entier)
Sortie;
      le même BYTE b avec la position p changé
*/
BYTE flipBitDeByte(BYTE b,// byte à changer
		int p);  // position à xhanger (0-->7)






/**
change la position: p du UINT b
Entrée: b:UINT à changer son bits (UINT)
        p:position de bit à changer (entier)
Sortie;
      le même UINT b avec la position p changé
*/
UINT flipBitDeUINT(UINT b,// UINT à changer
		int p) ; // position à xhanger (0-->31)









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
		UINT b,// UINT à changer
		int nch,// nombre de changes	
		int pos[]);  // liste de position à changer (0-->31)











/**
Montre les len bits plus bas de un UINT
et les precede d'une frase.
Entrées:
frase: frase qui précédera UINT (char *)
len: no. de bits bas à montrer (int)
ux: UINT à montrer
*/
void montreFRASEUINT(char * frase,int len,UINT ux);





#endif

