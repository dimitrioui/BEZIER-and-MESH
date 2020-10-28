#define  begin {
#define  end ;  }
#define PI 3.14159


	       /* INCLUDE LIBRARIES */

#include <dir.h>
#include <dos.h>
#include <stdlib.h>
#include <graphics.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <process.h>

		/* VOID ROUTINE(S) DEFINITION */

void give_names(),
     mult(),
     load_patches(),
     anagogh(),
     graph_com(),
     rot_surf();


	       /* GLOBAL VARIABLES */

FILE *mem ;
float bx[4][4],by[4][4],bz[4][4] ;
float r_vector[21][21][3] ;    /* The vectors of Bezier surfaces */
float w1[4][4],w2[4][4],w3[4][4],w4[4][4],w5[4][4],w6[4][4];
float max_x,min_x,max_y,min_y;
float cona1,cona2,conb1,conb2 ;   /* Variables used in maping a drawing */
int NOP1,NOP2;  /* Number Of Points  (from Bezier interpolation)  */
int gdriver=DETECT,gmode=0 ;
int patches;
char nams[26][26];
int num_of_files;
int i,j ;
float ax,ay,az ;        /* Angles in degrees */
float rax,ray,raz ;     /* Angles in radians */



main()
begin

char com_nam[26];
max_x=min_x=max_y=min_y=0;
clrscr();
give_names();
gotoxy(1,5);
printf("Give ax,ay,az:\n");
printf("ax=");  scanf("%f",&ax);  rax=(ax*PI)/180 ;
printf("ay=");  scanf("%f",&ay);  ray=(ay*PI)/180 ;
printf("az=");  scanf("%f",&az);  raz=(az*PI)/180 ;

for(patches=1;patches<=num_of_files;patches++)
begin
strcpy(com_nam,nams[patches]);
load_patches(com_nam);
rot_surf();
anagogh(&max_x,&min_x,&max_y,&min_y);
end ;

/*initgraph(&gdriver,&gmode,"c:\\turboc3\\BGI") ;*/
for(patches=1;patches<=num_of_files;patches++)
begin

strcpy(com_nam,nams[patches]);
load_patches(com_nam);
rot_surf();
graph_com();
end ;
 getch() ;
 closegraph () ;

end ;



void give_names()
begin
char name[16] ;
clrscr();

num_of_files=1;
do
begin
clrscr();
printf("   Give the name of the %d file:\n",num_of_files) ;
scanf("%s",&name) ;
strcpy(nams[num_of_files],name);
num_of_files+=1;
end
while(strcmp(name,"n")!=0);
num_of_files+=-2;
gotoxy(1,3);
printf("You gave (%d) files",num_of_files);
getch();
end ;



void load_patches (com_nam)
char com_nam[26];
begin
int counter1,counter2;
char name[16],rx[10],ry[10],rz[10] ;
char NOPA1[4],NOPA2[4];
gotoxy(1,4);
printf("%s",com_nam);
mem=fopen(com_nam,"r");

fscanf(mem,"%4s",NOPA1); NOP1=atoi(NOPA1);
fscanf(mem,"%4s",NOPA2); NOP2=atoi(NOPA2);

for(counter1=0;counter1<= NOP1;counter1++)
 begin
for(counter2=0;counter2<= NOP2;counter2++)
  begin

 fscanf(mem,"%10s",rx); r_vector[counter1][counter2][0]=atof(rx);
 fscanf(mem,"%10s",ry); r_vector[counter1][counter2][1]=atof(ry);
 fscanf(mem,"%10s",rz); r_vector[counter1][counter2][2]=atof(rz);
 fscanf(mem,"\n","");
  end ;
    end ;

fclose(mem);

end ;



void anagogh(max_x,min_x,max_y,min_y)
float *max_x,*min_x,*max_y,*min_y ;

begin
int counter1,counter2 ;


for(counter1=0;counter1<=NOP1;counter1++)
  begin
for(counter2=0;counter2<=NOP2;counter2++)
   begin
     if(*max_x<r_vector[counter1][counter2][0])
     begin
     *max_x=r_vector[counter1][counter2][0];
     end ;

     if(*min_x>r_vector[counter1][counter2][0])
     begin
     *min_x=r_vector[counter1][counter2][0];
     end ;

     if(*max_y<r_vector[counter1][counter2][1])
     begin
     *max_y=r_vector[counter1][counter2][1];
     end ;

     if(*min_y>r_vector[counter1][counter2][1])
     begin
     *min_y=r_vector[counter1][counter2][1];
     end ;

   end ;
  end ;

end ;



void graph_com ()

begin
int x1,y1,z1,x2,y2,z2,x3,y3,z3;
int counter1,counter2 ;
cona1=(600-30)/(max_x-min_x);
cona2=(300-30)/(max_y-min_y);
conb1=(600*min_x-30*max_x)/(min_x-max_x);
conb2=(300*min_y-30*max_y)/(min_y-max_y);


initgraph(&gdriver,&gmode,"c:\\turboc3\\BGI") ;
for(counter1=1;counter1< NOP1+1;counter1++)
for(counter2=0;counter2< NOP2+1;counter2++)
  begin
x1=floor(cona1*r_vector[counter1][counter2][0]+conb1);
y1=floor(cona2*r_vector[counter1][counter2][1]+conb2);
z1=floor(r_vector[counter1][counter2][2]);
x2=floor(cona1*r_vector[counter1-1][counter2][0]+conb1);
y2=floor(cona2*r_vector[counter1-1][counter2][1]+conb2);
z2=floor(r_vector[counter1-1][counter2][2]);

line(x1,y1,x2,y2);
  end ;

for(counter1=0;counter1<NOP1+1;counter1++)
for(counter2=1;counter2<NOP2+1;counter2++)
  begin
x1=floor(cona1*r_vector[counter1][counter2][0]+conb1);
y1=floor(cona2*r_vector[counter1][counter2][1]+conb2);
z1=floor(r_vector[counter1][counter2][2]);
x3=floor(cona1*r_vector[counter1][counter2-1][0]+conb1);
y3=floor(cona2*r_vector[counter1][counter2-1][1]+conb2);
z3=floor(r_vector[counter1][counter2-1][2]);

line(x1,y1,x3,y3);
  end ;


end ;




 void mult(a,b,c)
float a[4][4],b[4][4],c[4][4];
begin
int i,j,k ;
for (i=0;i<=3;i++)
 begin
for (j=0;j<=3;j++)
  begin
c[j][i]=0;
for (k=0;k<=3;k++)
   begin
c[j][i]+=a[j][k]*b[k][i];

   end ;
  end ;
 end ;

end ;


	   /*-------------------------------*/
	   /* ROUTINE ROTATES THE SURFACES  */
	   /*-------------------------------*/
void rot_surf()
begin
float RX[4][4],RY[4][4],RZ[4][4],ARX[4][4],ARY[4][4],ARZ[4][4] ;

float re[4][4],are[4][4];
int counter1,counter2 ;
int i,j ;

  if(ax==0)ax=ax+360;
  if(ay==0)ay=ay+360;
  if(az==0)az=az+360;
for(counter1=0;counter1<=3;counter1++)
for(counter2=0;counter2<=3;counter2++)
    begin
RX[counter1][counter2]=0; ARX[counter1][counter2]=0;
RY[counter1][counter2]=0; ARY[counter1][counter2]=0;
RZ[counter1][counter2]=0; ARZ[counter1][counter2]=0;
    end ;
RX[0][0]=1;RX[1][1]=cos(rax);RX[1][2]=sin(rax);RX[2][1]=-sin(rax);
RX[2][2]=cos(rax);RX[3][3]=1;
ARX[0][0]=1;ARX[1][1]=cos(rax);ARX[1][2]=-sin(rax);ARX[2][1]=sin(rax);
ARX[2][2]=cos(rax);ARX[3][3]=1;
RY[0][0]=cos(ray);RY[0][2]=sin(ray);RY[1][1]=1;RY[2][0]=-sin(ray);
RY[2][2]=cos(ray);RY[3][3]=1;
ARY[0][0]=cos(ray);ARY[0][2]=-sin(ray);ARY[1][1]=1;ARY[2][0]=sin(ray);
ARY[2][2]=cos(ray);ARY[3][3]=1;
RZ[0][0]=cos(raz);RZ[0][1]=sin(raz);RZ[1][0]=-sin(raz);RZ[1][1]=cos(raz);
RZ[2][2]=1;RZ[3][3]=1;

for(i=0;i<=3;i++)
for(j=0;j<=3;j++)
   begin
re[i][j]=0;
are[i][j]=0 ;
   end ;

for(counter1=0;counter1<NOP1+1;counter1++)
    begin
for(counter2=0;counter2<NOP2+1;counter2++)
      begin

re[0][0]=1;re[1][1]=1;re[2][2]=1;re[3][3]=1;
re[3][0]=-r_vector[counter1][counter2][0];
re[3][1]=-r_vector[counter1][counter2][1];
re[3][2]=-r_vector[counter1][counter2][2];

are[0][0]=1;are[1][1]=1;are[2][2]=1;are[3][3]=1;
are[3][0]=r_vector[counter1][counter2][0];
are[3][1]=r_vector[counter1][counter2][1];
are[3][2]=r_vector[counter1][counter2][2];

mult(re,RX,w1);
mult(w1,RY,w2);
mult(w2,RZ,w3);
mult(w3,ARY,w4);
mult(w4,ARX,w5);
mult(w5,are,w6);


  r_vector[counter1][counter2][0]=w6[3][0];
  r_vector[counter1][counter2][1]=w6[3][1];
  r_vector[counter1][counter2][2]=w6[3][2];

 end ;

end ;

end ;
