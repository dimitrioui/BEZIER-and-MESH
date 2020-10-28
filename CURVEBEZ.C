#define  MAX_N 20
#define  TOTAL 1000

#include <dos.h>
#include "stdio.h"
#include "math.h"
#include "graphics.h"
#include "stdlib.h"
#include <conio.h>
#include <dir.h>
#include <process.h>
#include <ctype.h>


void dat_input(),
     mhtra_m(),
     mhtra_ta(),
     mult(),
     curve_int(),
     save_curve(),
     anagogh(),
     draw_curve();

long int factorial(long int n);

float bez_x[MAX_N][MAX_N],bez_y[MAX_N][MAX_N],bez_z[MAX_N][MAX_N];
float m[MAX_N][MAX_N];
float ta[MAX_N][MAX_N];
float q1[MAX_N][MAX_N],q2[MAX_N][MAX_N];
float r_vector[TOTAL][3];
long int NOP;
int NOP1;
int gdriver=DETECT,gmode ;
float t,STEP ;
FILE *mem ;

main()
{
clrscr();
gotoxy(1,5);
dat_input();
mhtra_m();
curve_int();
draw_curve();
save_curve();
}

void dat_input()
{
int nop,i,j;
float px,py,pz;

for(i=0;i<=MAX_N-1;i++)
for(j=0;j<=MAX_N-1;j++)
{
bez_x[i][j]=0;bez_y[i][j]=0;bez_z[i][j]=0;
m[i][j]=0;ta[i][j]=0;
}
nop=0;
do
{
printf("give the %d point:\n",nop);
scanf("%f,%f,%f",&px,&py,&pz);
bez_x[0][nop]=px;
bez_y[0][nop]=py;
bez_z[0][nop]=pz;
nop+=1;
}while(px!=-100);
bez_x[0][nop-1]=0;bez_y[0][nop-1]=0;bez_z[0][nop-1]=0;
nop-=2;
/*printf("nop1=%d\n",nop);getch();*/
/*for(i=0;i<=MAX_N-1;i++)
{
for(j=0;j<=MAX_N-1;j++)
 {
printf("%f,%f,%f\n",bez_x[i][j],bez_y[i][j],bez_z[i][j]);
 } getch();
}  */
NOP=nop;
}

void mhtra_m()
{
char das[10];
long int y,z,r,p,t,g,l,e;
long int i,j;
/*printf("NOP=%d\n",NOP);getch();*/
for(i=0;i<=NOP;i++)
for(j=0;j<=NOP;j++)
{
t=factorial(NOP);
l=factorial(NOP-j);
y=factorial(j);
z=factorial(i);
r=factorial(j-i);
p=y/(z*r);
e=t/(y*l);
if(i>j) g=0;
else
g=p*e;
if(fmod(i-j,2)!=0) g=-g;
itoa(g,das,10);
m[i][j]=atof(das);
/*printf("gino=%d,=%s,= %f",g,das,m[i][j]);getch();*/
}

}

void mhtra_ta()
{
long int i,j ;

ta[0][0]=1;
t+=STEP;
/*for (t=0;t<=1.01;t+=STEP)*/
for (i=0;i<=NOP;i++)
{
ta[i+1][0]=ta[i][0]*t ;
/*printf("ta[i][0]=%f\n",ta[i][0]);*/
}}

void curve_int()
{
int i,j;
int s1=0 ;

printf("   Give the STEP:") ;
scanf("%f",&STEP) ;
if((1/STEP)>TOTAL) STEP=1/TOTAL ;
/*if((NOP>=3) && (STEP>(1/NOP))) STEP=1/NOP ;*/
do
{
mhtra_ta();
/* printf("bez_x=%f,,m=%f\n",bez_x[i][j],m[i][j]);*/
mult(bez_x,m,q1);
/*printf("%f,,%f,,%f,,%f,,%f\n",q1[0][0],q1[0][1],q1[0][2],q1[0][3],a[1][0]);*/
mult(q1,ta,q2);
 r_vector[s1][0]=q2[0][0];
/* printf("q2=%f",q2[0][0]);getch();*/
mult(bez_y,m,q1);
mult(q1,ta,q2);
 r_vector[s1][1]=q2[0][0];

mult(bez_z,m,q1);
mult(q1,ta,q2);
  r_vector[s1][2]=q2[0][0] ;
 s1++;

}
while(ta[1][0]<=1.001);
NOP1=s1-1;  printf("NOP1=%d\n",NOP1);
getch();
}



void draw_curve()
{
int j ;
int x1,y1,z1,x2,y2,z2,x3,y3,z3,x4,y4,z4;
int counter1,counter2 ;
float max_x,min_x,max_y,min_y;
float cona1,cona2,conb1,conb2 ;

 max_x=r_vector[0][0];
 min_x=r_vector[0][0];
 max_y=r_vector[0][1];
 min_y=r_vector[0][1];

anagogh(&max_x,&min_x,&max_y,&min_y);
cona1=(600-30)/(max_x-min_x);
cona2=(300-30)/(max_y-min_y);
conb1=(600*min_x-30*max_x)/(min_x-max_x);
conb2=(300*min_y-30*max_y)/(min_y-max_y);


initgraph(&gdriver,&gmode,"c:\\turboc3\\BGI") ;

for(j=0;j<=NOP-1;j++)
{  setcolor(RED);
x1=floor(cona1*bez_x[0][j]+conb1);
y1=floor(cona2*bez_y[0][j]+conb2);
z1=floor(bez_z[0][j]);
x2=floor(cona1*bez_x[0][j+1]+conb1);
y2=floor(cona2*bez_y[0][j+1]+conb2);
z2=floor(bez_z[0][j+1]);

line(x1,y1,x2,y2);
}

for(counter1=0;counter1<NOP1-1;counter1++)
  {  setcolor(WHITE);
x1=floor(cona1*r_vector[counter1][0]+conb1);
y1=floor(cona2*r_vector[counter1][1]+conb2);
z1=floor(r_vector[counter1][2]);
x2=floor(cona1*r_vector[counter1+1][0]+conb1);
y2=floor(cona2*r_vector[counter1+1][1]+conb2);
z2=floor(r_vector[counter1+1][2]);

line(x1,y1,x2,y2);
}


 getch() ;
 closegraph () ;
}






long int factorial(n)
long int n;
{

if (n<=1)
return(1);
else
return(n*factorial(n-1));
}


	     /*-------------------*/
	     /* MULT MATRICES N*N */
	     /*-------------------*/
void mult(a,b,c)
float a[MAX_N][MAX_N],b[MAX_N][MAX_N],c[MAX_N][MAX_N];
{
int i,j,k ;
for (i=0;i<=NOP;i++)
 {
for (j=0;j<=NOP;j++)
  {
c[j][i]=0;
for (k=0;k<=NOP;k++)
   {
c[j][i]+=a[j][k]*b[k][i];

   }
  }
 }
}



	    /*-------------------------------------*/
	    /* REDUCTION OF COORDINATES ON SCREEN  */
	    /*-------------------------------------*/
void anagogh(max_x,min_x,max_y,min_y)
float *max_x,*min_x,*max_y,*min_y ;

{
int counter1,counter2 ;


for(counter1=0;counter1<=NOP1;counter1++)
  {
     if(*max_x<r_vector[counter1][0])
     {
     *max_x=r_vector[counter1][0];
     }

     if(*min_x>r_vector[counter1][0])
     {
     *min_x=r_vector[counter1][0];
     }

     if(*max_y<r_vector[counter1][1])
     {
     *max_y=r_vector[counter1][1];
     }

     if(*min_y>r_vector[counter1][1])
     {
     *min_y=r_vector[counter1][1];
     }

  }

  for(counter1=0;counter1<=NOP-1;counter1++)
  {
     if(*max_x<bez_x[0][counter1])
     {
     *max_x=bez_x[0][counter1];
     }

     if(*min_x>bez_x[0][counter1])
     {
     *min_x=bez_x[0][counter1];
     }

     if(*max_y<bez_y[0][counter1])
     {
     *max_y=bez_y[0][counter1];
     }

     if(*min_y>bez_y[0][counter1])
     {
     *min_y=bez_y[0][counter1];
     }

  }

}



void save_curve()
{
char name[16],px[10],py[10],pz[10] ;
int j ;
clrscr();
gotoxy(5,10);
printf("   Give the name of the file:") ;
scanf("%s",&name) ;
mem=fopen(name,"w+");


for(j=0;j<=NOP;j++)
 {
 sprintf(px,"%10.5f",bez_x[0][j]);
 fprintf(mem,"%10s",px);
 sprintf(py,"%10.5f",bez_y[0][j]);
 fprintf(mem,"%10s",py);
 sprintf(pz,"%10.5f",bez_z[0][j]);
 fprintf(mem,"%10s",pz);
 fprintf(mem,"\n","");
}


fclose(mem);
}



