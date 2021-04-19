#include "headers/codification.h"
#include "headers/decodification.h"
#include "headers/rutinesBits.h"
#include "headers/restes8_1e.h"


char *messageA="Entrez le type de bruit a appliquer:\n"
	      "\t0: cero bit changé sur les codewords\n"
	      "\t1: un bit changé aleatoirement sur les codewords\n"
	      "\t2: deux bit changés aleatoirement sur les codewords\n"
	      "\tnf: nf bit changées aleatoirement sur les codewords(0<=nf<=8)\n";
int main(int argc, char *argv[]){
	UINT gd; //(00000000 00000000 00000000 00010011); x^4+x+1
	gd=16+2+1;	
	char m;
	int nx=8;
	int rx=4;
	char codes[2];
	int sym=0;
	char mc;
	int typeE;
	int typoRuid=1;	
        if(argc!=2){
		printf("usage: %s type\n",argv[0]);
		printf("%s\n",messageA);
			printf("Ex: %s 1\n",argv[0]);		
		exit(1);
	}
	if(argc==2 && !((argv[1][0]>='0')&&(argv[1][0]<='8')))
	// if(argc==2 && !((argv[1][0]=='1')||(argv[1][0]=='2')))
	{
		printf("usage: %s type\n",argv[0]);
		printf("%s\n",messageA);
			printf("Ex: %s 1\n",argv[0]);			
		exit(1);	
	}
	typoRuid=argv[1][0]-'0';

	printf("Entrez symbole (1 char) s.v.p?. (terminer avec CONTROL D)\n");
	
	initializeSEED();// pour generateurs random();

	while((sym=getchar())!=EOF){
	
	
		if(sym!='\n')
		{
			//ZONA DE CODIFICATION
			m=(char)sym;
			genere2charsAvecCode(m,nx,rx,gd,codes);
			//FIN ZONA DE CODIFICATION
			



			//ZONA DE BRUIT
			printf("___________________________________________________________\n");	
			printf("___________________________________________________________\n");
			printf("\tavant medium code entrée nibble bas   ");montreBYTE((BYTE) codes[0]);
			codes[0]=genereNFErreursSurCodeCharSURrange(typoRuid,codes[0],8,0);
			printf("\taprès medium code entrée nibble bas   ");montreBYTE((BYTE) codes[0]);
			printf("\n\tavant medium code entrée nibble haut  ");montreBYTE((BYTE) codes[1]);	
			codes[1]=genereNFErreursSurCodeCharSURrange(typoRuid,codes[1],8,0);
			printf("\taprès medium code entrée nibble haut  ");montreBYTE((BYTE) codes[1]);	
			//FIN ZONA DE BRUIT
			


			//ZONA DE DECODIFICATION
			typeE=genere1charDe2codes(codes,8,4,gd,restes8_1e,&mc);
			//FIN ZONA DE DECODIFICATION




			//ZONA DE DIAGNOSTIQUE
			printf("\n\tchar entrée;   ");montreBYTE((BYTE) m);		        
			printf("\tchar recoperé; ");montreBYTE((BYTE) mc);
			printf("\n\tmessage originel:  %c\n",m);
			printf("\tmessage recouperé: %c\n",mc);
			int dh=calculeDistHammingEntreBytesN((BYTE)mc,(BYTE)m );
			printf("\tdistance de Hamming :%d\n",dh);
			printf("\ttype ruid:%d\t type de cor:%d\t distHamming:%d\n",typoRuid,typeE,dh);

			
		     	printf("___________________________________________________________\n");	
			switch (typeE)
			{
				case 0:
					printf("diagnostique:\n\tPas de erreurs\n");
					break;
				case 1:
					printf("diagnostique:\n\terreur en 1 bit dans un code et corrigé\n");
					break;
				case 2:
					printf("diagnostique:\n\terreur en 1 bit dans deux codes et corrigé\n");
					break;
				case 5:
					printf("diagnostique:\n\terreur en 1 bit dans un code et corrige,"
						"\n et l'autre pas corrigé\n");
				case 8:
					printf("diagnostique:\n\terreur de plus de 1 bit dans les deux "
						"codes et pas corrigé\n");			
				default:
					break;
					
			} 
			printf("___________________________________________________________\n");
			//FIN ZONA DE DIAGNOSTIQUE
			printf("Entrez symbole  (1 char) s.v.p?. (terminer avec CONTROL D)\n");	    
		}
		
	}
	

return 0;
}
