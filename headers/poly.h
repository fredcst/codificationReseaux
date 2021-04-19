//poly.h
#ifndef POLYH
#define POLYH
#include "base.h"
#include "bitsBase.h"

/**
Génére un codeword de n corfficients pour un message de k coefficients
utilisant les polynômes generateurs cycliques.
Entrées:
	1-
	gd:coefficients du polynôme generateur g(x) comme UINT, met à droite de UINT.
	//Exemple:n=8,k=4,(degre de g=n-4):  g(x)=x^4+x+1 ==>gd=00000000 00000000 00000000 00010011	
	md0: coefficientes de message: m(x) comme UINT en utilisant k bits de droite de md0
	//Exemple:n=8,k=4,  m(x)=x^3     ==>md0=00000000 00000000 00000000 00001000
	2-
	n:taille de codeword comme int
	3-
	k:taille de message comme int
	4-
	*qd: addresse des coefficients dy polynôme quotient, comme UINT*. 
	 Les coefficients du polynôme quotient sortent à la droite de qd.

return:
	1-
	codeWORD de coefficients du polynôme : m(x)x^{n-k}+ m(x)x^{n-k}/g(x); comme UINT
	à la droite du UINT.
	Exemple: 00000000 00000000 00000000 00010011
	2-
	coefficients dy polynôme quotient,  en droite de :qd.
	Exemple: 00000000 00000000 00000000 00000001
	
*/
UINT codeWORDDivPoly(	UINT gd,// coefficientes de g(x) en utilisant (n-k) +1 bits de droite de gd
			UINT md0,//coefficientes de m(x) en utilisant k bits de droite de md0
			int n,//no total de bits de codeWord
			int k,//no total de bits de message
			UINT *qd);//sortie de quotient avec bits de droite de *qd


/**     Exemples detaillé de fonctionnement

	exemple:
	g(x)=g_{n-k}x^(n-k)+.....+g_{0}1
	g(x)=x^4+x+1
	n=8
	k=4
	n-k=4

	gd=		00000000 00000000 00000000 00010011
	                            		      ^
	                            		ibitd=4               (31,00000,0)    

	gg=gd<<32-(n-k)=gd <<32-4=gd <<28                                  
	gg=		00110000 00000000 00000000 00000000    


	___________________________________________________
	____________________________________________________
	A)
	m(x)=m_{k-1}x^(k-1)+.....+m_{0}1
	m(x)=1
	m(x)x^(n-k)=x^(n-k)=x^4
	m(x)x^(n-k)=m_{0}x^4
	md0=		00000000 00000000 00000000 00000001
	***************************************************
	md=md0<<(n-k)=md0<<(4)=
			00000000 00000000 00000000 00010000
	***************************************************                                  


	Pour réponse:!!
	mg0=md<<32-n=md<<32-8=md<<24
	mg0=		00010000 00000000 00000000 00000000
	***************************************************  


	mg=md<<((32-n)-(n-k));
	mg=md<<((32-n)-(n-k))=md<<(24)-(4)=md<<(20);
	mg=		00000001 00000000 00000000 00000000                     

	*qd=		00000000 00000000 00000000 00000000
	i=0
	UNg=		10000000 00000000 00000000 00000000

	---------------------------------------------------
	UNg & mg=0
	*qd=*qd<<1=	00000000 00000000 00000000 00000000
	mg=mg<<1=	00000010 00000000 00000000 00000000   

	i=i+1=1;
	corri=8-i=8-1=7
	---------------------------------------------------
	UNg & mg=0
	*qd=*qd<<1=	00000000 00000000 00000000 00000000
	mg=mg<<1=	00000100 00000000 00000000 00000000   

	i=i+1=2;
	corri=n-i=8-2=6
	---------------------------------------------------
	UNg & mg=0
	*qd=*qd<<1=	00000000 00000000 00000000 00000000
	mg=mg<<1=	00001000 00000000 00000000 00000000   

	i=i+1=3;
	corri=n-i=8-3=5
	---------------------------------------------------
	UNg & mg=0
	*qd=*qd<<1=	00000000 00000000 00000000 00000000
	mg=mg<<1=	00010000 00000000 00000000 00000000  

	i=i+1=4;
	corri=n-i=8-4=4
	---------------------------------------------------
	UNg & mg=0
	*qd=*qd<<1=	00000000 00000000 00000000 00000000
	mg=mg<<1=	00100000 00000000 00000000 00000000  

	i=i+1=5;
	corri=n-i=8-5=3

	---------------------------------------------------
	UNg & mg=0
	*qd=*qd<<1=	00000000 00000000 00000000 00000000
	mg=mg<<1=	01000000 00000000 00000000 00000000  

	i=i+1=6;
	corri=n-i=8-6=2

	---------------------------------------------------
	UNg & mg=0
	*qd=*qd<<1=	00000000 00000000 00000000 00000000
	mg=mg<<1=	10000000 00000000 00000000 00000000  

	i=i+1=7;
	corri=n-i=8-7=1


	---------------------------------------------------

	UNg & mg!=0
	*qd=*qd<<1=	00000000 00000000 00000000 00000000
	*qd=*qd+1= 	00000000 00000000 00000000 00000001
	mg=mg<<1=  	00000000 00000000 00000000 00000000  
	mg=mg^gg= 	00110000 00000000 00000000 00000000 
				^
 		  	00000000 00000000 00000000 00000000
        	= 	00110000 00000000 00000000 00000000 

	i=i+1=8;
	corri=n-i=8-8=0
	---------------------------------------------------

	SORTE

	mg=		00110000 00000000 00000000 00000000 
	*qd=		00000000 00000000 00000000 00000001

	x^4= (x^4+x+1)(1)+(x+1) OK!!

	reste=		mg>>(n-k)  
			00000011 00000000 00000000 00000000

    
 	c(x)=m(x)x^{n-k}+reste;
	codeWORDg= mg0 ^ reste
			00010000 00000000 00000000  00000000
				^
			00000011 00000000 00000000  00000000
	codeWORDg= 	00010011 00000000 00000000  00000000

	codeWORDd=codeWORDg>>(32-n)=codeWORDg>>(24)

	codeWORDd=	00000000 00000000 00000000  00010011

	____________________________________________________
	____________________________________________________
	B)
	m(x)=_{k-1}x^(k-1)+.....+m_{3}x^3
	m(x)=x^3
	m(x)x^(n-k)=x^(n-k)=x^7
	m(x)x^(n-k)=m_{3}x^7
	md0=		00000000 00000000 00000000 00001000
	***************************************************
	md=md0<<(n-k)=md0<<(4)=
			00000000 00000000 00000000 10000000
	***************************************************                                  

	pour réponse:!!
	mg0=md<<32-n=md<<32-8=md<<24
	mg0=		10000000 00000000 00000000 00000000
	***************************************************  




	gg=gd<<32-(n-k)=gd <<32-4=gd <<28                                  
	gg=		00110000 00000000 00000000 00000000    

	mg=md<<((32-n)-(n-k));
	mg=md<<((32-n)-(n-k))=md<<(24)-(4)=md<<(20);
	mg=		00001000 00000000 00000000 00000000                     

	*qd=		00000000 00000000 00000000 00000000
	i=0
	UNg=		10000000 00000000 00000000 00000000

	---------------------------------------------------
	UNg & mg=0
	*qd=*qd<<1=	00000000 00000000 00000000 00000000
	mg=mg<<1=	00010000 00000000 00000000 00000000   

	i=i+1=1;
	corri=8-i=8-1=7
	---------------------------------------------------
	UNg & mg=0
	*qd=*qd<<1=	00000000 00000000 00000000 00000000
	mg=mg<<1=	00100000 00000000 00000000 00000000   
	
	i=i+1=2;
	corri=n-i=8-2=6
	---------------------------------------------------
	UNg & mg=0
	*qd=*qd<<1=	00000000 00000000 00000000 00000000
	mg=mg<<1=	01000000 00000000 00000000 00000000   
	
	i=i+1=3;
	corri=n-i=8-3=5
	---------------------------------------------------
	UNg & mg=0
	*qd=*qd<<1=	00000000 00000000 00000000 00000000
	mg=mg<<1=	10000000 00000000 00000000 00000000  
	
	i=i+1=4;
	corri=n-i=8-4=4
	---------------------------------------------------
	UNg & mg!=0
	*qd=*qd<<1=	00000000 00000000 00000000 00000000
	*qd=*qd+1= 	00000000 00000000 00000000 00000001
	mg=mg<<1=  	00000000 00000000 00000000 00000000  
	mg=mg^gg= 	00110000 00000000 00000000 00000000 
				^
 		  	00000000 00000000 00000000 00000000
	mg=mg^gg=	00110000 00000000 00000000 00000000 


	i=i+1=5;
	corri=n-i=8-5=3

	---------------------------------------------------
	UNg & mg=0
	*qd=*qd<<1	00000000 00000000 00000000 00000010
	mg=mg<<1=	01100000 00000000 00000000 00000000  

	i=i+1=6;
	corri=n-i=8-6=2

	---------------------------------------------------
	UNg & mg=0
	*qd=*qd<<1=	00000000 00000000 00000000 00000100
	mg=mg<<1=	11000000 00000000 00000000 00000000  

	i=i+1=7;
	corri=n-i=8-7=1


	---------------------------------------------------
	UNg & mg!=0
	*qd=*qd<<1=	00000000 00000000 00000000 00001000
	*qd=*qd+1= 	00000000 00000000 00000000 00001001
	mg=mg<<1=  	10000000 00000000 00000000 00000000  
	mg=mg^gg= 	00110000 00000000 00000000 00000000 
				^
 		  	10000000 00000000 00000000 00000000
	mg=mg^gg=	10110000 00000000 00000000 00000000 


	i=i+1=8;
	corri=n-i=8-8=0
	---------------------------------------------------

	SORTE

	mg=		10110000 00000000 00000000 00000000 
	*qd=		00000000 00000000 00000000 00001001

	x^7= (x^4+x+1)x^3+(x^4++x+1+x+1 x^3)=(x^4+x+1)(x^3+1)+x^3+x+1 OK!!

	reste=		mg>>(n-k)  =mg>>4  
			00001011 00000000 00000000 00000000

    

	codeWORDg= mg0 ^ reste
			10000000 00000000 00000000 00000000
				^
			00001011 00000000 00000000 00000000
	codeWORDg= 	10001011 00000000 00000000 00000000

	codeWORDd=codeWORDg>>(32-n)=codeWORDg>>(24)

	codeWORDd=00000000 00000000 00000000  10001011
	___________________________________________________
	____________________________________________________

*/

















/**            BITS EN CODE A DROITE de UINT!!!
Génére un reste de n-k corfficients pour un code de n coefficients
utilisant les polynômes generateurs cycliques de puissance: n-k
Entrées:
	gd:coefficients du polynôme generateur g(x) comme UINT, positionné à droite de UINT.
	//Exemple:n=8,k=4,(degre de g=8-4=4):  g(x)=x^4+x+1 ==>gd=00000000 00000000 00000000 00010011	
	
	cd: coefficientes de code: c(x) comme UINT en utilisant n bits de droite de cd
	//Exemple:n=8,k=4,                     ==>cd=00000000 00000000 00000000 00010011

	n:taille de codeword comme int

	k:taille de message comme int

	*qd: addresse des coefficients du polynôme quotient, comme UINT*. 
	 Les coefficients du polynôme quotient sortent à la droite de qd.
return:

	coefficients du polynôme reste : c(x)/g(x); comme UINT
                         (n-k) bits depuis la droite du UINT.
	
	coefficients du polynôme quiotient de c(x)/g(x); comme UINT a droite 
*/
UINT resteDivPoly(	UINT gd,// coefficientes de g(x) en utilisant (n-k) +1 bits de droite de gd
			UINT cd,//coefficientes de c(x) en utilisant n bits de droite de cd
			int n,//no total de bits de codeWord
			int k,//no total de bits de message
			UINT *qd);//sortie de quotient avec bits de droite de *qd

















/**                BITS EN CODE A GAUCHE de UINT!!!
		   bits de code sont  transférés au UINT de reste.
		  [  g   ]
	             xor
                  [reste ] <- [ code ]
		    | 
	 [q]<-------+	
Génére un reste de r corfficients pour un code de n coefficients
utilisant les polynômes generateurs cycliques de puissance: r
Cas général: 
	Sur les  bits de droite de un UINT viennent insèrées les coefficients
	du polynôme générateur. Le coefficient de la puissance (r) est
	en bit; r , en position (r+1) (de droite à gauche de UINT)
	Le UINT R=1<<r; R contient un 1 en position r+1: (00000 1 000000)
						                ^
						            bit r    
Entrées:
	1-
	gd:coefficients du polynôme generateur g(x) comme UINT, positionné à droite de UINT.
	//Exemple:n=8,k=4,(degre de g=8-4=4):  g(x)=x^4+x+1 ==>gd=00000000 00000000 00000000 00010011	
	Ici, le bit de haut poid de g est r=4 en position; 5
	2-
	r: puissance de g(x) , comme int 
	Pour le exemple, r=4
	3-
	cg: coefficientes de code: c(x) comme UINT en utilisant n bits de gauche de cg
	Les coefficients de c(x) sont dans un UINT placés au coté gauche  remplissant n places du
	UINT;
	Exemple: c(x)=1 , n=8
	0000 0001 00000000 00000000 00000000
      	4-
	n:taille de codeword comme int
	Exemple: n=8
	5-
	*qd: addresse des coefficients du polynôme quotient, comme UINT*.
	Les coefficients du polynôme quotient sortent à la droite de qd.

Sortie:
return:
	1-
	coefficients  du polynôme  reste : c(x)/g(x); comme UINT
                         (r) bits à la droite du UINT.
	Exemple: 000000 000000 000000 00000011
	2-
	en addresse *q se sauvent les coefficients du quotient
	du division:c(x)/g(x) à la droite de UINT
	Exemple: 000000 000000 000000 00000001
	qui corresponde à q(x)=1

*/
UINT resteDivPolyGEN(	UINT gd,// coefficientes de g(x) en utilisant (r+1) bits de droite de gd
			int r,//puissance de g(x)
			UINT cg,//coefficientes de c(x) en utilisant n bits de gauche de UINT
			int n,//no total de bits de code
			UINT *qd);//sortie de quotient avec bits de droite de *qd












/**
Avec les coefficients du  message en positions plus bas du UINT et
le ordre de polynôme générateur produire les coefficients du
polynome: m(x)x^{n-k}
ou: n est la taille de codewords
    k est la puissance de polynôme générteur
Entrées:
	md: coefficients de message , a droite de UINT
	Exemple:
	m(x)= x
	md=00000000 00000000 00000000 00000010

	n: taille de codeword, comme int

	k: ordre de polynôme gérénateur, comme int
	Exemple:
	g(x)=x^4+x+1
	k=4

Sortie:
	cg: coefficients de m(x)x^{n-k} , positionnés
    	a gauche de UINT, dans les derniers n positiones  
	Exemple:
	n=8,k=4
	md=00000000 00000000 00000000 00000010
	cg=00100000 00000000 00000000 00000000
	cg=md<<(32-n)+(n-k);
*/
UINT mgTDEmd(UINT md,int n,int k);








/**
Avec les coefficients du code en positions plus bas du UINT(à droite) et
la taille de codeword transférer les bits a gauche de UINT
ou: n est la taille de codewords
Entrées:
	md: coefficients de message , a droite de UINT
	Exemple:
	m(x)= x
	md=00000000 00000000 00000000 00000010

	n: taille de codeword, comme int

Sortie:
	cg:  a gauche de UINT, dans les derniers n positiones  
	Exemple:
	n=8
	cd=00000000 00000000 00000000 00000010
	cg=00000010 00000000 00000000 00000000
	cg=cd<<(32-n);
*/
UINT cgDEcd(UINT cd,int n);








/**
sorte le codeword à partir de reste et m(x)x^(n-k)
cwd=(rested ^ (md<<(n-k)))
Entrées:

	md: coefficients de message en droite de UINT
	Exemple: m(x): 1
	md=00000000 00000000 00000000 00000001

	rd: coefficients de reste en droite de UINT
	Exemple: r(x): x+1
	rd=00000000 00000000 00000000 00000011

	n: taille de codeword
	Exemple n=8

	k: puissance de polynôme générateur
	Exemple k=4 pour g(x)=x^4+x+1

	Sortie:
	(rd ^ (md<<(n-k)))
	Exemple:
	00000000 00000000 00000000 00010011

*/

UINT creerCodeWordDuReste(UINT md,UINT rd, int n, int k);










/**
Sorte les coefficients du codeWord associé à un message m
et un polynôme générateur g(x) comme les n bits de droite
du UINT
Entrées:

	gd:coefficients du polynôme generateur g(x) comme UINT, positionné à droite de UINT.
	//Exemple:n=8,k=4,(degre de g=8-4=4):  g(x)=x^4+x+1 ==>gd=00000000 00000000 00000000 00010011	
	Ici, le bit de haut poid de g est r=4 en position: 5

	md: coefficients de message à la droite de UINT
	Exemple: m(x): 1
	md=00000000 00000000 00000000 00000001

	nx: taille de codeword
	Exemple nx=8

	rx: puissance de polynôme générateur
	Exemple rx=4 pour g(x)=x^4+x+1

Sorties:
	cwd : codeword associé a : m(x)x^{n-rx}+ m(x)x^{n-rx}/g(x) mod {g(x)}
	Exemple: 
	cwd:00000000 00000000 00000000 00010011
	associé à: m(x)=1  et g(x)=x^4+x+1
*/
UINT creerCodeWord(UINT gd,UINT md,int nx,int rx,UINT *qd);





/**             CODE est a droite de UINT 
Sorte reste de code de n bits possicionné a droite de UINT

Entrées:
	1-
	gd:coefficients du polynôme generateur g(x) comme UINT, positionné à droite de UINT.
	//Exemple:n=8,k=4,(degre de g=8-4=4):  g(x)=x^4+x+1 ==>gd=00000000 00000000 00000000 00010011	
	Ici, le bit de haut poid de g est r=4 en position; 5
	2-
	r: puissance de g(x) , comme int 
	Pour le exemple, r=4
	3-
	cd: coefficientes de code: c(x) comme UINT en utilisant n bits de droite de cg
	Les coefficients de c(x) sont dans un UINT placés au coté droite  remplissant n places du
	UINT;
	Exemple: c(x)=1 , n=8
	00000000 00000000 00000000 00000001
      	4-
	n:taille de codeword comme int
	Exemple: n=8
	5-
	*qd: addresse des coefficients du polynôme quotient, comme UINT*.
	Les coefficients du polynôme quotient sortent à la droite de qd.

Sortie:
return:
	1-
	coefficients  du polynôme  reste : c(x)/g(x); comme UINT
                         (r) bits à la droite du UINT.
	Exemple: 000000 000000 000000 00000011
	2-
	en addresse *q se sauvent les coefficients du quotient
	du division:c(x)/g(x) à la droite de UINT
	Exemple: 000000 000000 000000 00000001
	qui corresponde à q(x)=1
*/
UINT resteDeCoded(UINT gd,UINT cd,int nx,int rx,UINT *qd);












/**
Génére le group complète de 2^(nx-rx) codewords pour le polynome g de degre rx:

Entres: g
        1-
	gd:coefficients du polynôme generateur g(x) comme UINT, positionné à droite de UINT.
	//Exemple:nx=8,rx=4,(degre de g=4):  g(x)=x^4+x+1 ==>gd=00000000 00000000 00000000 00010011	
	Ici, le bit de haut poid de g est r=4 en position; 5
	2-
	rx: puissance de g(x) , comme int 
	Pour le exemple, rx=4
	3-
	n:taille de codeword comme int
	Exemple: n=8
	4-
	Espace pour codewords.codeWords[2^k], avec:  k=(nx-rx)
	chaque codeword est dans  les n positionnes de coté droite de UINT
       
Sortie: UINT de chaque du 2^k possible codewords (Espace génére dehors)

return: toujours 0
*/
int genereCodeWordsUINTdePoly(UINT gd,int rx,int nx,UINT codeWords[]);








/**
Identité de codeWord avec 1 erreur
Entrée:
	reste: reste à investiquer UINT. Au coté droit de UINT (000000000000 | n positions)
	n: taille de codeword
	restes1e :liste de n restes de 1 error en codeWord (tous au coté droit de UINT)
Sortié:
	identite de codeWord avec 1 erreur(0,---,n-1)
Return:
	identité ou
	-1 no identifiqué
*/
int identiteDeCodeWordUINTPoly(	UINT reste,// reste de cw  avec posible (!=0 )erreur
				int nx, //taille de codeword
		     		UINT restes1e[]);//liste de restes pour chaque position de bit en erreur HT)













/**
Identifique si existe erreur et corrige erreur de 1 bit en code
Entrées:
	code: code à détecter erreurs UINT (coté droite)
	gd:coefficients de polynôme générateur g(x) comme UINT, positionné à droite de UINT.
	//Exemple:nx=8,rx=4,(degre de g=4):  g(x)=x^4+x+1 ==>gd=00000000 00000000 00000000 00010011	
	Ici, le bit de haut poid de g est r=4 en position; 5
	
	nx:   taille de code (int). Example nx=8

	rx: puissance de g(x) , comme int 
	Pour le exemple, rx=4
	
	restes1e[nx]: Liste de restes pour 1 seule erreur en codewords.

Sortie;
	si existe identification de erreur se corrige et
	sorte le code corrigé comme n positions à droite de UINT.
	si non, se retourne le même code.


*/
UINT codeCorrige1e(UINT code,UINT gd,int nx,int rx,UINT restes1e[]);
















/**
Identifique si existe erreur et corrige erreur de 1 bit en code
Entrées:
	code: code à détecter erreurs UINT (coté droite)
	gd:coefficients de polynôme générateur g(x) comme UINT, positionné à droite de UINT.
	//Exemple:nx=8,rx=4,(degre de g=4):  g(x)=x^4+x+1 ==>gd=00000000 00000000 00000000 00010011	
	Ici, le bit de haut poid de g est r=4 en position; 5
	
	nx:   taille de code (int). Example nx=8

	rx: puissance de g(x) , comme int 
	Pour le exemple, rx=4
	
	restes1e[nx]: Liste de restes pour 1 seule erreur en codewords.
        *EX : addresse de indicateur de type de erreur
Sortie;
	si existe identification de erreur se corrige et
	sorte le code corrigé comme n positions à droite de UINT.
	si non, se retourne le même code.
	En EX sorte: 0 si n'existe pas erreur 
		     1 si existe erreur mais corrige
	             4 si existe erreur mais pas corrige		

*/
UINT codeCorrige1eS(UINT code,UINT gd,int nx,int rx,UINT restes1e[],int *EX);









/**
Inicialise le seed pour le générateur random

*/
void initializeSEED(void);










/**
génére erreur sur une code de nx bits avec probabilité prob
générere multile intents d'erreur, mais quelcuns peuvent se canceler entre eux.
Entrées:
	code: code de nx bits (droite de UINT)
	nx: taille de code
	prob:  entier (0->100)   (p= prob/100)

Sortie:
	code avec erreur en bits avec probabilite prob/100
*/
UINT generaPerreursSurCode(UINT code,int nx,int prob);








/**
génére erreur sur une code(char) de 8 bits avec probabilité prob
générere multile intents d'erreur, mais quelcuns peuvent se canceler entre eux.
Entrées:
	code: code de 8 bits (char)
	prob:  entier (0>100)   (p= prob/100)

Sortie:
	code avec erreur en bits avec probabilite prob/100
*/
char generaPerreursSurCodeCHAR(char code,int prob);







/**
génére 1 erreur sur une code(char) de 8 bits avec probabilité 1
Le bit avec l'erreur est aleatoire
Entrées:
	code: code de 8 bits (char)


Sortie:
	code avec 1 erreur en bits
*/
char genera1erreursSurCodeCHAR(char code);














/**
génére nf erreurs sur une code(char) de 8 bits avec probabilité 1
Les bits avec l'erreur est aleatoire
Entrées:
	code: code de 8 bits (char)


Sortie:
	code avec nf erreur en bits
*/
char generaNFerreursSurCodeCHAR(char code,int nf);










/**
Génére bruit en char avec nf changes en positions
aleatoires du char, sur ntbits de droite a gauche.
Ex.
pour un char met ntbits=8 si toute le char veut être changé
pour un char met ntbits=4 si seulement le nibble inferieur veut être changé
Le nombre de changes faites est ce qui a été démandé!!
Les positions des changes sont aleatoires.
Entrées:
	nf: no total de bits à changer(int)
	code:  char=8 bits 
	nbits: nombre de bits à changer, de droite a gauche de char
Sortie:
	le code changé

*/
char  genereNFErreursSurCodeCharSUR(int nf,char code,int ntbits);










/**
Génére bruit en char avec nf changes en positions
aleatoires du char, sur ntbits de droite a gauche depuis position ini.
Ex.
pour un char met ntbits=8 si toute le char veut être changé
pour un char met ntbits=4 ,ini=0 si seulement le nibble inferieur veut être changé
pour un char met ntbits=4 ,ini=4 si seulement le nibble superieur veut être changé
Le nombre de changes faites est ce qui a été démandé!!
Les positions des changes sont aleatoires.
Entrées:
	nf: no total de bits à changer(int)
	code:  char=8 bits 
	nbits: nombre de bits à changer, de droite a gauche de char
	ini: position de comencement de changes de droite a gauche de char
	                xxxxxxxx
			     ^
			     ini
Sortie:
	le code changé

*/
char  genereNFErreursSurCodeCharSURrange(int nf,char code,int ntbits,int ini);











/**
Transfère le message de 4bits de 1 code a le nibble haut
d'un char.
Entrées;
	code; le code come UINT  (00000000 00000000 00000000 mmmm pppp) . 
	nx: taille de code  =8
	mx: taille de message)4

Sorte:
	nh: nibble superieur de char (mmmm0000)
		avec part de message de code
*/


char codeM4UINTaCHAR_H(UINT code,int nx,int mx);









/**
Transfère le message de 4bits de 1 code a le nibble bas
d'un char.
Entrées;
	code; le code come UINT  (00000000 00000000 00000000 mmmm pppp) . 
	nx: taille de code  =8
	mx: taille de message)4

Sorte:
	nb: nibble superieur de char (0000mmmm)
		avec part de message de code
*/
char codeM4UINTaCHAR_B(UINT code,int nx,int mx);










/**
retourne 1 char a partir de nibbles haut et bas
Entrées:
	nh: char contenant le nibble haut
	nb: char contenant le nibble bas
Sortie:
	char complète

*/
char nh_nbaCHAR(char nh,char nb);








/**
retourne 1 char a partir de UINT avec code en 8 bits bas
Entrées:
	code: UINT contenant 8 bits a droite
	nx: taille de code =8
Sortie:
	char contenant code

*/
char code_A_CHAR(UINT code,int nx);










/**
retourne 1 UINT (en 8 bits bas) a partir de char
Entrées:
	code: 8 bits (char)
	nx: taille de code =8
Sortie:
	UINT contenant code

*/
UINT CHAR_A_UINT(char code,int nx);









/**
retourne 1 UINT a partir de nibble haut de char 
Entrées:
	m: char contenant 4 bits en nibble haut (mmmmxxxxx)
	nx: taille de code =8
Sortie:
	code en UINT  contenant 4 bits en bas de UINT (0000000 00000000 0000000 0000mmmm)

*/
UINT charNH_A_MUINT(char m,int nx);












/**
retourne 1 UINT a partir de nibble bas de char 
Entrées:
	m: char contenant 4 bits en nibble haut (xxxxmmmm)
	nx: taille de code =8
Sortie:
	code en UINT  contenant 4 bits en bas de UINT (0000000 00000000 0000000 0000mmmm)

*/
UINT charNB_A_MUINT(char m,int nx);














/**

char ---> nh nb  ----> UINT mh UINT mb ---> UINT ch UINT cb -----> charh charb   
8          4  4             4        4           8        8          8     8
					|
					medium
				        |
                                        v

charh charb ---> UINT chr UINT cbr ---> correction ---->  UINT mhc UINT mbc ---> nhc nbc ---> charc
8       8              8        8                               4        4        4   4        8

char m;// char à envoier

UINT mh= charNH_A_MUINT(m,8);//obtient  nibble haut en UINT
UINT mb= charNB_A_MUINT(m,8);//obtient  nibble bas  en UINT
UINT ch= creerCodeWord(gd,mh,8,4,&qd);//crée code words
UINT cb= creerCodeWord(gd,mb,8,4,&qd);//crée code words
char charh=code_A_CHAR(ch,8);//met code en chars
char charb=code_A_CHAR(cb,8);//met code en chars

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

















#endif


