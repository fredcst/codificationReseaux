//lector.c
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <fcntl.h>
#include "headers/codification.h"
#include "headers/decodification.h"
#include "headers/rutinesBits.h"
//gcc -o lector lector.c 

#define MAX_MESSAGE 50
#define MAX_MSG_CODE 100

// lis de fichier et codifique , met bruit, decodifique et sauve en autre fichier
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
	char nombreIn[40];
	char nombreOut[40];
	
	char message[MAX_MESSAGE];
 	 memset(message, '\0', MAX_MESSAGE*sizeof(char));
	char messageR[MAX_MESSAGE];
 	 memset(messageR, '\0', MAX_MESSAGE*sizeof(char));

        if(argc!=4){
		printf("usage: %s fichierIN fichierOUT typeRuid\n",argv[0]);
		printf("%s\n",messageA);
			printf("Ex: %s in.dat out.dat 1\n",argv[0]);		
		exit(1);
	}
	if(argc==4 && !((argv[3][0]>='0')&&(argv[3][0]<='8')))
	// if(argc==2 && !((argv[1][0]=='1')||(argv[1][0]=='2')))
	{
		printf("usage: %s  fichierIN fichierOUT type\n",argv[0]);
		printf("%s\n",messageA);
			printf("Ex: %s in.dat out.dat 1\n",argv[0]);			
		exit(1);	
	}
	strcpy(nombreIn,argv[1]);
	strcpy(nombreOut,argv[2]);
	typoRuid=argv[3][0]-'0';

	
  //-- open the file in read mode
  	mode_t mode = S_IRUSR|S_IWUSR;
	int readFile,saveFile;
  
	if((readFile = open(argv[1], O_RDONLY, mode)) == -1)
    	{
      	perror(argv[1]);
      	exit(1);
    	}
	int size;
	while((size = read(readFile, message, MAX_MESSAGE)) > 0)
   	 {
    	  printf("%s %d\n",message, size); 
   	 }
	close(readFile);
      

	
	
	initializeSEED();// pour generateurs random();

	int cont=0;
	size=strlen(message);
	printf("size:%d\n",size);
        while(cont<size){
	printf("%d\n",cont);
			
		m=(char)message[cont];
		genere2charsAvecCode(m,nx,rx,gd,codes);


		//zone de medium
		codes[0]=genereNFErreursSurCodeCharSURrange(typoRuid,codes[0],8,0);
		codes[1]=genereNFErreursSurCodeCharSURrange(typoRuid,codes[1],8,0);
		//fin zone de medium
		
		typeE=genere1charDe2codes(codes,8,4,gd,restes8_1e,&mc);
		messageR[cont]=mc;
	
		cont++;
	}
	printf("%s\n",messageR); 


	if((saveFile = open(argv[2],O_WRONLY|O_CREAT|O_TRUNC, mode)) == -1)
    	{
      		perror(argv[2]);
      		exit(1);
    	}
	
	size_t res;
	if((res = write(saveFile, message, size))!=size)
	{
		perror("write");
		exit(1);
	}
	printf("message sauvé en: %s\n",argv[2]);
	close(saveFile);
return 0;
}
