#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include "incl.h"


//function for rotating an image
void rotate(double angle,long int height,long int width,HIPL_IMAGE *it,HIPL_IMAGE *ot,char *argv){
long int x;
long int y;
printf("total rows %ld \n",height);
printf("total columns %ld \n",width);
int tr;
scanf("%d",&tr);
for(x = 0; x < height; x++) {
for(y = 0; y < width; y++) {
long int hwidth = width / 2;
long int hheight = height / 2;
		
long int xt = x - hwidth;
long int yt = y - hheight;
		

printf("currnent row %ld \n",x);
printf("currnent column %ld \n",y);
double sinma = sin(-angle);
double cosma = cos(-angle);
		
long int xs = (int)round((cosma * xt - sinma * yt) + hwidth);
long int ys = (int)round((sinma * xt + cosma * yt) + hheight);
//ot->iarr[x][y] = 100;
if(xs >= 0 && xs < width && ys >= 0 && ys < height) {
ot->iarr[x][y] = it->iarr[x][y];
} else {
ot->iarr[x][y] = 100;

}
HIPL_StoreResult(argv,ot);
}
}
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


long int nrow=it->img.ROWS;
long int ncol=it->img.COLS;
double angle=45*(3.147/180);
rotate(angle,nrow,ncol,it,ot,argv[2]);

printf("total row %ld \n",nrow);


HIPL_Refresh(ot, 0);
HIPL_Closeall(it);
HIPL_Closeall(ot);
exit(0);

}

