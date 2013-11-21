#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include "incl.h"




void rotate(double angle,long int height,long int width,HIPL_IMAGE *it,HIPL_IMAGE *ot,char *argv)
{
int max,i=0,j=0;
long int hwidth = width / 2;
long int hheight = height / 2;
do {
max = HIPL_Getpart(it);
printf("returned row %d \n",max);
if (max < 0) {
fprintf(stderr, "Error in reading image\n");
exit(1);
}
 for (i=0; i<max; i++){
 for (j=0; j<it->img.COLS; j++){
long int xt = i - hwidth;
long int yt = j - hheight;
double sinma = sin(-angle);
double cosma = cos(-angle);

long int xs = (int)round((cosma * xt - sinma * yt) + hwidth);
long int ys = (int)round((sinma * xt + cosma * yt) + hheight);
		
if(xs >= 0 && xs < width && ys >= 0 && ys < height)
{
 ot->iarr[i][j] = it->iarr[xs][ys];
}
else
{
ot->iarr[i][j] = 0;
}
}
}

 if ((i = HIPL_Putpart(ot)) < 0) {
 fprintf(stderr, "Error in writing image\n");
 exit(1);
 }
 } while (ot->P.nleft > 0);
HIPL_StoreResult(argv,ot);

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
HIPL_Refresh(it,0);

long int nrow=it->img.ROWS;
long int ncol=it->img.COLS;
double angle;
printf("please enter the rotation amount in degrees");
scanf("%lf",&angle);
angle=angle*(3.1419265/180);
rotate(angle,nrow,ncol,it,ot,argv[2]);

printf("total row %ld \n",nrow);


HIPL_Refresh(ot, 0);
HIPL_Closeall(it);
HIPL_Closeall(ot);
exit(0);

}

