//poly.c

#include "headers/base.h"
#include "headers/bitsBase.h"
#include "headers/poly.h"

//unsigned long SEED;
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
UINT codeWORDDivPoly(UINT gd, // coefficientes de g(x) en utilisant (n-k) +1 bits de droite de gd
  UINT md0, //coefficientes de m(x) en utilisant k bits de droite de md0
  int n, //no total de bits de codeWord
  int k, //no total de bits de message
  UINT * qd) //sortie de quotient avec bits de droite de *qd
{
  UINT gg = 0, mg = 0;
  * qd = 0;
  gg = gd << (32 - (n - k)); // met gd a gauche de UINT. derniere 1 dehors

  UINT md = md0 << (n - k); //multiplie par x^(n-k); cooresponde à m[x]x^(n-k) = mxn_k

  UINT mg0 = md << (32 - n); // sauve  mxn_k a gauche de UINT 

  mg = md << ((32 - n) - (n - k)); //met md a gauche de UINT mais (n-k] positions a droite.

  int i = 0;
  UINT UNg = 1 << 31; // 1 en position 31
  int corri = 0;
  UINT res;
  do {
    res = UNg & mg;

    if (res == 0) //vérifie si bit 31 de mg est 0 ou 1
    { // est 0       
      * qd = * qd << 1; //deplacer q a gauche,set 0 a droite de q
      mg = mg << 1; //deplacer mxnk a gauche : 

    } else { // est 1	
      * qd = * qd << 1; //deplacer q a gauche
      * qd = * qd + 1; //set 1 a droite de q
      mg = mg << 1; //deplacer mxnk a gauche :
      mg = mg ^ gg; //xor g avec mxn_k
    }
    i = i + 1;
    corri = n - i;
  } while (corri > 0);

  UINT reste = mg >> (n - k); //déplace reste  pour le additionner à m(x)x^{n-k} et former codeWORD
  UINT codeWORDg = mg0 ^ reste; //positionné à gauche de UINT
  UINT codeWORDd = codeWORDg >> (32 - n); //positionné à droite de UINT
  return codeWORDd; // les n bits de droite de UINT
}

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
UINT resteDivPoly(UINT gd, // coefficientes de g(x) en utilisant (n-k) +1 bits de droite de gd
  UINT cd, //coefficientes de c(x) en utilisant n bits de droite de cd
  int n, //no total de bits de codeWord
  int k, //no total de bits de message
  UINT * qd) //sortie de quotient avec bits de droite de *qd
{
  UINT gg = 0, cg = 0;
  * qd = 0;
  gg = gd << (32 - (n - k)); // met gd a gauche de UINT. derniere 1 dehors
  cg = cd << ((32 - n) - (n - k)); //met md a gauche de UINT mais (n-k] positions a droite.
  int i = 0;
  UINT UNg = 1 << 31; // 1 en position 31
  int corri = 0;
  UINT res;

  do {
    res = UNg & cg;
    if (res == 0) //vérifie si bit 31 de mg est 0 ou 1
    { // est 0       
      * qd = * qd << 1; //deplacer q a gauche,set 0 a droite de q
      cg = cg << 1; //deplacer cg a gauche : 
    } else { // est 1	
      * qd = * qd << 1; //deplacer q a gauche
      * qd = * qd + 1; //set 1 a droite de q
      cg = cg << 1; //deplacer cg a gauche :
      cg = cg ^ gg; //xor g avec mxn_k
    }
    i = i + 1;
    corri = n - i;
  } while (corri > 0);

  UINT reste = cg >> (n - k); //déplace reste  a position apres de zone de message
  reste = reste >> (32 - n); //positionné à droite de UINT

  return reste; // les n bits de droite de UINT
}

/**                BITS EN CODE A GAUCHE de UINT!!!
Génére un reste de r corfficients pour un code de n coefficients
utilisant les polynômes generateurs cycliques de puissance: r
Cas général: 
	Sur les  bits de droite de un UINT viennent insèrées les coefficients
	du polynôme générateur. Le coefficient de la puissance (r) est
	en bit; r , en position (r+1) (de droite à gauche de UINT)
	Le UINT R=1<<r; R contient un 1 en position r+1: (00000 1 000000)
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
UINT resteDivPolyGEN(UINT gd, // coefficientes de g(x) en utilisant (r+1) bits de droite de gd
  int r, //puissance de g(x)
  UINT cg, //coefficientes de c(x) en utilisant n bits de gauche de UINT
  int n, //no total de bits de code
  UINT * qd) //sortie de quotient avec bits de droite de *qd
{

  UINT reste = 0;
  int i = 0;
  UINT UNR = 1 << r; // 1 en  bit r (pos r+1)
  UINT UNM = 1 << 31; // 1 en bit 31
  UINT res;

  do {
    res = UNM & cg; //vérifie si bit à gauche en cg est 1 ou 0
    cg = cg << 1; //move bits a gauche en cg
    if (res != 0) //si oui; bit est 1 ;non :bit est 0 °
    { //oui 
      reste = reste << 1; //deplace reste a gauche et 
      reste = reste + 1; //insère 1 en la droite de UINT
    } else { //non
      reste = reste << 1; //déplace reste a gauche et 
      //insère 0 en la droite de UINT
    }
    /*  FIN traspase de bit de c à bits de reste   */

    /*  vérification de bit de reste en position r+1    
        et calcule du quotient et le  reste             */

    res = UNR & reste; //vérifie si bit de reste en position de puissance de g est 1 ou 0

    if (res == 0) //vérifie si bit en puissanve de reste est 0 ou 1
    { // est 0       
      * qd = * qd << 1; //deplacer q a gauche,
      //set 0 a droite de q	
    } else { // est 1	
      * qd = * qd << 1; //deplacer q a gauche	
      * qd = * qd + 1; //set 1 a droite de q				
      reste = reste ^ gd; //xor g avec reste
    }
    /* FIN vérification de bit de reste en position r+1    
        et calcule de quotient et reste             */
    i = i + 1;

  } while (i < n);

  return reste; // les r bits de droite de UINT
}

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
UINT mgTDEmd(UINT md, int n, int k) {
  return md << ((n - k) + (32 - n));
}

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
UINT cgDEcd(UINT cd, int n) {
  return cd << (32 - n);
}

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

UINT creerCodeWordDuReste(UINT md, UINT rd, int n, int k) {
  return (rd ^ (md << (n - k)));
}

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
UINT creerCodeWord(UINT gd, UINT md, int nx, int rx, UINT * qd) {
  return creerCodeWordDuReste(md, resteDivPolyGEN(gd, rx, mgTDEmd(md, nx, rx), nx, qd), nx, rx);
}

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

UINT resteDeCoded(UINT gd, UINT cd, int nx, int rx, UINT * qd) {

  return resteDivPolyGEN(gd, rx, cgDEcd(cd, nx), nx, qd);

}

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
int genereCodeWordsUINTdePoly(UINT gd, int rx, int nx, UINT codeWords[]) {

  int k, i = 0;
  UINT base;
  UINT qd;
  UINT md = 0;
  UINT message; // espace pour message
  UINT cv8 = 1 << (nx - 1); //(100000000 ....00) 1 en bit nx-1
  int ncw = 1 << (nx - rx); //2^(kk), 16 si nx=8,rx=4 , kk=nx-rx;

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

    md = message >> (nx - rx); //positionne message a droite de UINT

    codeWords[i] = creerCodeWord(gd, md, nx, rx, & qd);

    i++;
  } while (i < ncw);

  return 0;
}

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
int identiteDeCodeWordUINTPoly(UINT reste, // reste de cw  avec posible (!=0 )erreur
  int nx, //taille de codeword
  UINT restes1e[]) //liste de restes pour chaque position de bit en erreur HT)
{
  UINT r;
  int i;

  for (i = 0; i < nx; i++) {
    r = reste ^ restes1e[i]; //XOR parcours liste  de restes de 1 erreur et vérifique égalité avec reste
    if (r == 0) return i; //si existe égalité sorte avec la identité de codeWord
  }

  return -1;
}
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
UINT codeCorrige1e(UINT code, UINT gd, int nx, int rx, UINT restes1e[]) {
  UINT qd;
  UINT error;
  UINT restex = resteDeCoded(gd, code, nx, rx, & qd);
  if (restex == 0) { // pas de erreur

    return code;
  }
  //montreFRASEUINT("restex :",rx,restex);
  int id = identiteDeCodeWordUINTPoly(restex,
    nx,
    restes1e);
  //printf("id de bit avec erreur:%d\n",id);
  if (id != -1) error = flipBitDeUINT(code, id); //si xiste identification corrige
  else
    error = code; // sinon rétourne le même code
  //montreFRASEUINT("correction :",nx,error);
  return error;

}

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
UINT codeCorrige1eS(UINT code, UINT gd, int nx, int rx, UINT restes1e[], int * EX) {
  UINT qd;
  UINT error;
  UINT restex = resteDeCoded(gd, code, nx, rx, & qd);
  if (restex == 0) { // pas de erreur
    * EX = 0;
    return code;
  }
  int id = identiteDeCodeWordUINTPoly(restex,
    nx,
    restes1e);
  if (id != -1) {
    error = flipBitDeUINT(code, id); //si xiste identification corrige
    * EX = 1;
  } else {
    error = code; // sinon rétourne le même code
    * EX = 4;
  }
  return error;

}

/**


*/

void initializeSEED(void) {
  srand(time(NULL));
  return;
}

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
UINT generaPerreursSurCode(UINT code, int nx, int prob) {
  long int val;
  //srand(SEED);   // Initialization, should only be called once.
  int bid;
  val = random() % 100;
  if (val < prob) {
    bid = random() % nx;
    code = flipBitDeUINT(code, bid);
  }
  return code;
}
/**
génére erreur sur une code(char) de 8 bits avec probabilité prob
générere multile intents d'erreur, mais quelcuns peuvent se canceler entre eux.
Entrées:
	code: code de 8 bits (char)
	prob:  entier (0>100)   (p= prob/100)

Sortie:
	code avec erreur en bits avec probabilite prob/100
*/
char generaPerreursSurCodeCHAR(char code, int prob) {
  long int val;
  //srand(time(NULL));   // Initialization, should only be called once.
  int bid;
  UINT codx;
  BYTE codeb = (BYTE) code; //évite problemes avec bit de signe
  codx = (UINT) codeb; //traspase a UINT
  val = random() % 100;
  if (val < prob) {
    bid = random() % 8;
    codx = flipBitDeUINT(codx, bid);
  }
  char ret = (char) codx; //met codex en char

  return ret;
}
/**
génére 1 erreur sur une code(char) de 8 bits avec probabilité 1
Le bit avec l'erreur est aleatoire
Entrées:
	code: code de 8 bits (char)


Sortie:
	code avec 1 erreur en bits
*/
char genera1erreursSurCodeCHAR(char code) {
  //srand(time(NULL));   // Initialization, should only be called once.
  int bid;
  UINT codx;
  BYTE codeb = (BYTE) code; //évite problemes avec bit de signe
  codx = (UINT) codeb; //traspase a UINT

  bid = random() % 8;
  codx = flipBitDeUINT(codx, bid);

  char ret = (char) codx; //met codex en char

  return ret;
}
/**
génére nf erreurs sur une code(char) de 8 bits avec probabilité 1
Les bits avec l'erreur est aleatoire
Entrées:
	code: code de 8 bits (char)


Sortie:
	code avec nf erreur en bits
*/
char generaNFerreursSurCodeCHAR(char code, int nf) {
  //long int val;
  //srand(time(NULL));   // Initialization, should only be called once.
  int bid, i;
  UINT codx;
  BYTE codeb = (BYTE) code; //évite problemes avec bit de signe
  codx = (UINT) codeb; //traspase a UINT

  for (i = 0; i < nf; i++) {
    bid = random() % 8;
    codx = flipBitDeUINT(codx, bid);
  }
  char ret = (char) codx; //met codex en char

  return ret;
}

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
char genereNFErreursSurCodeCharSUR(int nf, char code, int ntbits) {
  int fin = 0;
  int id[8];
  int i;
  char t;
  if (ntbits > 8) ntbits = 8; //seule sirve pour chars
  for (i = 0; i < ntbits; i++) id[i] = 0;
  //srandom(time(0));
  int nx = 0;
  if (nf > 8) nf = 8; //seule sirve pour chars

  while (!fin) {
    i = random() % ntbits;
    if (nx < nf) {
      fin = 0;
      if (id[i] == 0) {
        id[i] = 1;
        nx++;
        t = 1 << i;
        code = code ^ t;
      }
    } else {
      fin = 1;
    }

  }

  return code;
}

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
char genereNFErreursSurCodeCharSURrange(int nf, char code, int ntbits, int ini) {
  int fin = 0;
  int id[8];
  int i;
  char t;
  if (ntbits > 8) ntbits = 8; //seule sirve pour chars
  if (ntbits + ini > 8) ini = 8 - ntbits;
  for (i = 0; i < ntbits; i++) id[i + ini] = 0;
  //srandom(time(0));
  int nx = 0;
  if (nf > 8) nf = 8; //seule sirve pour chars

  while (!fin) {

    i = random() % ntbits + ini;

    if (nx < nf) {
      fin = 0;
      if (id[i] == 0) {
        id[i] = 1;
        nx++;
        t = 1 << i;
        code = code ^ t;
      }
    } else {
      fin = 1;
    }

  }

  return code;
}

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

char codeM4UINTaCHAR_H(UINT code, int nx, int mx) {
  char nh;
  if (nx != 8 || mx != 4) {
    fprintf(stderr, "Erreur codeM4UINTaCHAR_1: NO APPLICABLE A CODE\n");
    exit(1);
  }
  code = code >> 4; // transfère message à  4 bits bas
  nh = (char) code; // transfère message a char
  nh = nh << 4; //transfère message à  4 bits hautà
  return nh;
}
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

char codeM4UINTaCHAR_B(UINT code, int nx, int mx) {
  char nb;
  if (nx != 8 || mx != 4) {
    fprintf(stderr, "Erreur codeM4UINTaCHAR_1: NO APPLICABLE A CODE\n");
    exit(1);
  }
  code = code >> 4; // transfère message à  4 bits bas
  nb = (char) code; // transfère message a char
  return nb;
}

/**
retourne 1 char a partir de nibbles haut et bas
Entrées:
	nh: char contenant le nibble haut
	nb: char contenant le nibble bas
Sortie:
	char complète

*/
char nh_nbaCHAR(char nh, char nb) {
  return nh ^ nb;
}
/**
retourne 1 char a partir de UINT avec code en 8 bits bas
Entrées:
	code: UINT contenant 8 bits a droite
	nx: taille de code =8
Sortie:
	char contenant code

*/
char code_A_CHAR(UINT code, int nx) {
  if (nx != 8) {
    fprintf(stderr, "Erreur code_A_CHAR: NO APPLICABLE A CODE\n");
    exit(1);
  }

  return (char) code;
}
/**
retourne 1 UINT (en 8 bits bas) a partir de char
Entrées:
	code: 8 bits (char)
	nx: taille de code =8
Sortie:
	UINT contenant code

*/
UINT CHAR_A_UINT(char code, int nx) {
  if (nx != 8) {
    fprintf(stderr, "Erreur CHAR_A_UINT: NO APPLICABLE A CODE\n");
    exit(1);
  }
  BYTE a = (BYTE) code;
  return (UINT) a;
}
/**
retourne 1 UINT a partir de nibble haut de char 
Entrées:
	m: char contenant 4 bits en nibble haut (mmmmxxxxx)
	nx: taille de code =8
Sortie:
	code en UINT  contenant 4 bits en bas de UINT (0000000 00000000 0000000 0000mmmm)

*/
UINT charNH_A_MUINT(char m, int nx) {
  if (nx != 8) {
    fprintf(stderr, "Erreur charNH_A_MUINT: NO APPLICABLE A CODE\n");
    exit(1);
  }
  BYTE mx = (BYTE) m;
  UINT code = (UINT)(mx >> 4);
  return code;
}
/**
retourne 1 UINT a partir de nibble bas de char 
Entrées:
	m: char contenant 4 bits en nibble haut (xxxxmmmm)
	nx: taille de code =8
Sortie:
	code en UINT  contenant 4 bits en bas de UINT (0000000 00000000 0000000 0000mmmm)

*/
UINT charNB_A_MUINT(char m, int nx) {
  if (nx != 8) {
    fprintf(stderr, "Erreur charNB_A_MUINT: NO APPLICABLE A CODE\n");
    exit(1);
  }
  BYTE filtre = 15;
  BYTE a = ((BYTE) m) & filtre;
  UINT code = (UINT) a;
  return code;
}