#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include "incl.h"


//function for entropy calculation
double calcEntropy(long int *freq,double totalPix)
{  
int trk;
double Problity,E=0;  
for(trk=0;trk<256;trk++) 
{ 
Problity=(double) freq[trk]/totalPix;
if(Problity > 0.0)
{
E=E+ (Problity * log(1/Problity));
             }
}
return E;
}


//declaration of main function
int main(int argc, char *argv[]) {
//declaring images and initializing them
HIPL_IMAGE *it, *ot;
DATA *ID;
HIPL_Setmemory(500);
it=(THEADER *)malloc(sizeof(THEADER));
ot=(THEADER *)malloc(sizeof(THEADER));
ID=(DATA *)malloc(sizeof(DATA));
HIPL_Initialise(it,argv[1],0,0,ID);
HIPL_Initialise(ot,NULL,1,0,ID);
HIPL_AllocateMem(it);
HIPL_AllocateMem(ot);


long int histarr[256];//array to store frequency of pixels
int trk;


for(trk=0;trk<256;trk++)
histarr[trk]=0;
HIPL_FindHistogram(it,histarr);
HIPL_Refresh(it,0);
double totalpix=(it->img.ROWS)*(it->img.COLS);
double E1 = calcEntropy(histarr,totalpix);
HIPL_Refresh(it,0);
printf ("\nEntropy before equalisation: %lf", E1);

HIPL_Equalise(it,ot,histarr);
HIPL_Refresh(it,0);
HIPL_Refresh(ot,0);
for (trk=0;trk<=256;trk++)
histarr[trk]=0;
HIPL_FindHistogram(ot,histarr);
double E2 = calcEntropy(histarr, totalpix);
HIPL_Refresh(ot,0);  
HIPL_StoreResult(argv[2],ot);
printf ("\nEntropy after equalisation: %lf\n", E2 );


HIPL_Refresh(ot, 0);
HIPL_Closeall(it);
HIPL_Closeall(ot);
exit(0);

}

