//restesDe2erreurs.c
#include "headers/base.h"
#include "headers/poly.h"
//gcc --o restesDe2erreurs restesDe2erreurs.c
/**
Présente en écran les restes por codeword avec 2 erreurs
en deux bits pour tous les positions. 
Polynôme:
p(x)=x^4+x+1
*/


int main()
{
	int nx=8;
	int rx=4;
	UINT gd=16+2+1;
	UINT cw0=0;
	UINT cd;
	UINT e1=1;
	UINT e2=1;
	UINT qd;
	int i;
	int j;
	UINT reste;
	printf("-----   & $b_0$  &  $b_1$  & $b_2$ &  $b_3$ & $b_4$  & $b_5$  & $b_6$  & $b_7$\\\\\n");
	for(i=0;i<nx;i++)
	{	printf("$ b_%d ",i);
		for(j=0;j<nx;j++)
		{
		cd=cw0|(e1<<i)|(e2<<j);
		reste=resteDivPoly(gd,cd, nx,(nx-rx),&qd);
		printf("$ & $");montreUINTSNL(4,reste);
		}
		printf("$\\\\\n");
	}

return 0;
}
