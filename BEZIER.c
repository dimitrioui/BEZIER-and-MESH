#define PI 3.14159
#define begin  {
#define end;   }


	     /* LIBRARIES INCLUDED */
#include <dos.h>
#include <stdlib.h>
#include <graphics.h>
#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <dir.h>
#include <process.h>
#include <ctype.h>



	     /* VOID ROUTINE(S) DEFINITION */

void mult() ,
     main_menu(),
     menu2(),
     menu3(),
     give_data(),
     plain_points(),
     symetry_x(),
     symetry_y(),
     symetry_z(),
     rot_curve(),
     curve_toz(),
     curve_toy(),
     curve_tox(),
     save_data(),
     bezier(),
     save_bezier(),
     graph () ,
     anagogh(),
     rot_zoom(),
     rot_zoom_menu(),
     rot_surf(),
     read_parametric_file(),
     open_message_window(),
     close_message_window(),
     make_window(),
     total_bezier(),
     give_names(),
     menu1();


		  /* INT ROUTINE(S) DEFINITION */

int load_bezier(),
    load_graph();

	/*-----------------------*/
	/*   GLOBAL VARIABLES    */
	/*-----------------------*/

FILE *mem ;
const float  m[4][4]={{1,0,0,0},{-3,3,0,0},{3,-6,3,0},{-1,3,-3,1}};
const float mt[4][4]={{1,-3,3,-1},{0,3,-6,3},{0,0,3,-3},{0,0,0,1}};
float a[4][4],c[4][4];
float q1[4][4],q2[4][4],q3[4][4],q4[4][4];
float bezier_x[4][4] ;       /* defining the 16 points needed */
float bezier_y[4][4] ;             /* to describe */
float bezier_z[4][4] ;          /* a Bezier surface */
float r_vector[21][21][3] ;  /* The vectors of Bezier surface */
float w1[4][4],w2[4][4],w3[4][4],w4[4][4],w5[4][4],w6[4][4];
int i,j ;
float u,v;   /* u,v are generalized x,y used in Bezier interpolation */
	     /* taking values in [0,1] with STEP */
float STEP ;   /* The step of u,v min(STEP)=0.05 and max(STEP)=0.33 */
int NOP1,NOP2;  /* Number Of Points (from the Bezier interpolation */
int gdriver=DETECT,gmode ;
void *buf;
char filename[16],prg_dir[79],file_dir[79];
int num_of_files,patches;
char nams[26][26];


main()
begin
loopmenu1:
menu1();
open_message_window(20,20,60,24,5);
close_message_window(20,20,60,24,5);
goto loopmenu1;

end ;



void give_data()
begin
menu2();
open_message_window(20,20,60,24,5);
close_message_window(20,20,60,24,5);
end ;





	     /*-------------------*/
	     /* MULT MATRICES 4*4 */
	     /*-------------------*/
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


	      /* insert all of the 16 points describe a Bezier surface */

void plain_points()
begin
float pointx,pointy,pointz ;
int i,j ;

for (i=0;i<=3;i++)
   begin
for (j=0;j<=3;j++)
      begin
clrscr();
gotoxy(1,20);
printf(" Give %d,%d: ",i,j);
scanf(" %f,%f,%f",&pointx,&pointy,&pointz);
bezier_x[i][j]=pointx;
bezier_y[i][j]=pointy;
bezier_z[i][j]=pointz;
      end ;
   end ;

end ;


	      /* Insert two points for an axis */
	       /* the angle of rotation */
	      /* and the points of side 2 */
void rot_curve()
begin
float x0,y0,z0,x1,y1,z1 ;
float d1,d2,d3,dsum ;
float u1,u2,u3 ;
int i,j,k,l ;
float a,ara ;
float A[4][4],re[4][4];
clrscr() ;
printf(" Insert the points of the axis :") ;
getch();
clrscr();
printf(" Give x0,y0,z0 :") ;
scanf("%f,%f,%f",&x0,&y0,&z0) ;
clrscr();
printf(" Give x1,y1,z1 :") ;
scanf("%f,%f,%f",&x1,&y1,&z1) ;
d1=x1-x0; d2=y1-y0; d3=z1-z0;
dsum=sqrt(d1*d1+d2*d2+d3*d3);
u1=d1/dsum; u2=d2/dsum; u3=d3/dsum;
clrscr() ;
gotoxy(5,10);
printf(" Give the angle of rotation:");
scanf("%f",&a);

  for(i=0;i<=3;i++)
  begin
clrscr();
printf(" Give x[%d][0],y[%d][0],z[%d][0] :",i,i,i);
scanf(" %f,%f,%f",&bezier_x[i][0],&bezier_y[i][0],&bezier_z[i][0]);
re[0][0]=bezier_x[i][0];re[0][1]=0;re[0][2]=0;re[0][3]=0;
re[1][0]=bezier_y[i][0];re[1][1]=0;re[2][1]=0;re[1][3]=0;
re[2][0]=bezier_z[i][0];re[2][1]=0;re[2][2]=0;re[2][3]=0;
re[3][0]=0;re[3][1]=0;re[3][2]=0;re[3][3]=0;

  begin
 for(j=0;j<=3;j++)
   begin

ara=(j*a*PI)/540;
A[0][0]=u1*u1+cos(ara)*(1-u1*u1);
A[1][0]=u1*u2*(1-cos(ara))+u3*sin(ara);
A[2][0]=u3*u1*(1-cos(ara))-u2*sin(ara);
A[0][1]=u1*u2*(1-cos(ara))-u3*sin(ara);
A[1][1]=u2*u2+cos(ara)*(1-u2*u2);
A[2][1]=u2*u3*(1-cos(ara))+u1*sin(ara);
A[0][2]=u3*u1*(1-cos(ara))+u2*sin(ara);
A[1][2]=u3*u2*(1-cos(ara))-u1*sin(ara);
A[2][2]=u3*u3+cos(ara)*(1-u3*u3);
A[0][3]=0;A[3][1]=0;A[3][2]=0;A[3][0]=0;A[1][3]=0;A[2][3]=0;A[3][3]=0;
mult(A,re,w1);
  bezier_x[i][j]=w1[0][0];
  bezier_y[i][j]=w1[1][0];
  bezier_z[i][j]=w1[2][0];

end ;
end ;
end ;

end ;

	       /* Takes  an exist file and regenerate the symetry */
			   /*  in axis X */
void symetry_x()
begin
char name[16],px[10],py[10],pz[10] ;
clrscr();
gotoxy(5,10);
printf("   Give the name of the file:") ;
scanf("%s",&name) ;
if((mem=fopen(name,"r"))==0)
begin
printf("  Error on opening file!\n");
printf("  This file not exist!\n");
getch();
end ;

for(i=0;i<=3;i++)
 begin
for(j=0;j<=3;j++)
  begin
 fscanf(mem,"%10s",px); bezier_x[i][j]=atof(px);
 fscanf(mem,"%10s",py); bezier_y[i][j]=atof(py);
 fscanf(mem,"%10s",pz); bezier_z[i][j]=atof(pz);
  end ;
 end ;
fclose(mem);

for(i=0;i<=3;i++)
for(j=0;j<=3;j++)
bezier_x[i][j]=-bezier_x[i][j];


end ;


		   /* Takes  an exist file and regenerate the symetry */
			   /*  in axis Y */
void symetry_y()
begin
char name[16],px[10],py[10],pz[10] ;
clrscr();
gotoxy(5,10);
printf("   Give the name of the file:") ;
scanf("%s",&name) ;
if((mem=fopen(name,"r"))==0)
begin
printf("  Error on opening file!\n");
printf("  This file not exist!\n");
getch();
end ;

for(i=0;i<=3;i++)
 begin
for(j=0;j<=3;j++)
  begin
 fscanf(mem,"%10s",px); bezier_x[i][j]=atof(px);
 fscanf(mem,"%10s",py); bezier_y[i][j]=atof(py);
 fscanf(mem,"%10s",pz); bezier_z[i][j]=atof(pz);
  end ;
 end ;
fclose(mem);

for(i=0;i<=3;i++)
for(j=0;j<=3;j++)
bezier_y[i][j]=-bezier_y[i][j];


end ;


	      /* Takes  an exist file and regenerate the symetry */
			   /*  in axis Z */

void symetry_z()
begin
char name[16],px[10],py[10],pz[10] ;
clrscr();
gotoxy(5,10);
printf("   Give the name of the file:") ;
scanf("%s",&name) ;
if((mem=fopen(name,"r"))==0)
begin
printf("  Error on opening file!\n");
printf("  This file not exist!\n");
getch();
end ;

for(i=0;i<=3;i++)
 begin
for(j=0;j<=3;j++)
  begin
 fscanf(mem,"%10s",px); bezier_x[i][j]=atof(px);
 fscanf(mem,"%10s",py); bezier_y[i][j]=atof(py);
 fscanf(mem,"%10s",pz); bezier_z[i][j]=atof(pz);
  end ;
 end ;
fclose(mem);

for(i=0;i<=3;i++)
for(j=0;j<=3;j++)
bezier_z[i][j]=-bezier_z[i][j];


end ;


/*--------------------Makes an elevation of a curve--------------------------*/
/*--------------------------to axis Z----------------------------------------*/
/*------------------Uses 4 points on xy-plane(side 2) and -------------------*/
/*-----------------the value of elevation on axis Z--------------------------*/
void curve_toz()
begin

float pointz1,pointx,pointy,pointz2,dz ;
int i,j ;
clrscr();
printf("     Give points in z_axis");getch();
clrscr();
printf("  Start,End :") ;
scanf("%f,%f",&pointz1,&pointz2);
dz=pointz2-pointz1;

for (i=0;i<=3;i++)
   begin
clrscr();
printf(" x(%d)(0),y(%d)(0):",i,i) ;
scanf("%f,%f",&pointx,&pointy);
bezier_x[i][0]=pointx;bezier_y[i][0]=pointy;

for (j=0;j<=3;j++)
      begin
bezier_x[i][j]=bezier_x[i][0];
bezier_y[i][j]=bezier_y[i][0];

      end ;
   end ;
   for (i=0;i<=3;i++)
   for (j=0;j<=3;j++)
   begin
bezier_z[i][j]=pointz1+(j*dz)/3;
   end ;
end ;


/*--------------------Makes an elevation of a curve--------------------------*/
/*--------------------------to axis X----------------------------------------*/
/*------------------Uses 4 points on zy-plane and----------------------------*/
/*-----------------the value of elevation on axis X--------------------------*/

void curve_tox()
begin

float pointx1,pointz,pointy,pointx2,dx ;
int i,j ;
clrscr();
printf("    Give points in x_axis");getch();
clrscr();
printf("  Start,End :") ;
scanf("%f,%f",&pointx1,&pointx2);
dx=pointx2-pointx1;

for (i=0;i<=3;i++)
   begin
   clrscr();
printf("  y(%d)(0),z(%d)(0):",i,i) ;
scanf("%f,%f",&pointy,&pointz);
bezier_y[i][0]=pointy;bezier_z[i][0]=pointz;

for (j=0;j<=3;j++)
      begin
bezier_z[i][j]=bezier_z[i][0];
bezier_y[i][j]=bezier_y[i][0];

      end ;
   end ;
   for (i=0;i<=3;i++)
   for (j=0;j<=3;j++)
   begin
bezier_x[i][j]=pointx1+(j*dx)/3;
   end ;
end ;



/*--------------------Makes an elevation of a curve--------------------------*/
/*--------------------------to axis Y----------------------------------------*/
/*------------------Uses 4 points on zx-plane and----------------------------*/
/*-----------------the value of elevation on axis Y--------------------------*/

void curve_toy()
begin

float pointy1,pointz,pointx,pointy2,dy ;
int i,j ;
clrscr();
printf("     Give points in y_axis"); getch();
clrscr();
printf("  Start,End :") ;
scanf("%f,%f",&pointy1,&pointy2);
dy=pointy2-pointy1;

for (i=0;i<=3;i++)
   begin
   clrscr();
printf(" x(%d)(0),z(%d)(0):",i,i) ;
scanf("%f,%f",&pointx,&pointz);
bezier_x[i][0]=pointx;bezier_z[i][0]=pointz;

for (j=0;j<=3;j++)
      begin
bezier_z[i][j]=bezier_z[i][0];
bezier_x[i][j]=bezier_x[i][0];

      end ;
   end ;
   for (i=0;i<=3;i++)
   for (j=0;j<=3;j++)
   begin
bezier_y[i][j]=pointy1+(j*dy)/3;
   end ;
end ;



void save_data()
begin
char name[16],px[10],py[10],pz[10] ;
int i,j ;
clrscr();
gotoxy(5,10);
printf("   Give the name of the file:") ;
scanf("%s",&name) ;
mem=fopen(name,"w+");

for(i=0;i<=3;i++)
  begin
for(j=0;j<=3;j++)
   begin
 sprintf(px,"%10.5f",bezier_x[i][j]);
 fprintf(mem,"%10s",px);
 sprintf(py,"%10.5f",bezier_y[i][j]);
 fprintf(mem,"%10s",py);
 sprintf(pz,"%10.5f",bezier_z[i][j]);
 fprintf(mem,"%10s",pz);
 fprintf(mem,"\n","");
  end ;
   end ;
fclose(mem);

end ;
	   /*--------------------------------*/
	   /*--------------------------------*/
	   /*      BEZIER'S ROUTINES         */
	   /*--------------------------------*/
	   /*--------------------------------*/

int load_bezier(com_nam)
char com_nam[26];
begin
char name[16],px[10],py[10],pz[10] ;
if((mem=fopen(com_nam,"r"))==0)
begin
printf("  Error on opening file!\n");
printf("  This file not exist!\n");
getch();
return(0);
end ;

for(i=0;i<=3;i++)
 begin
for(j=0;j<=3;j++)
  begin
 fscanf(mem,"%10s",px); bezier_x[i][j]=atof(px);
 fscanf(mem,"%10s",py); bezier_y[i][j]=atof(py);
 fscanf(mem,"%10s",pz); bezier_z[i][j]=atof(pz);
  end ;
 end ;
fclose(mem);
return(1);
end ;

	/*--------------------------------------------------*/
	/* CALCULATES WITH BEZIER THE POINTS OF THE SURFACE */
	/*--------------------------------------------------*/
void bezier()
begin
int  s1=0,s2;

for (u=0;u<=1.01;u+=STEP)
  begin
s2=0;
for (v=0;v<=1.01;v+=STEP)
   begin
for (i=0;i<=3;i++)
for (j=0;j<=3;j++)
    begin

a[j][i]=0;
c[i][j]=0;
    end ;
a[0][0]=1;a[0][1]=u;a[0][2]=u*u;a[0][3]=u*u*u ;
c[0][0]=1; c[1][0]=v;c[2][0]=v*v;c[3][0]=v*v*v ;



mult(a,m,q1);
mult(q1,bezier_x,q2);
mult(q2,mt,q3);
mult(q3,c,q4);
 r_vector[s1][s2][0]=q4[0][0];

mult(a,m,q1);
mult(q1,bezier_y,q2);
mult(q2,mt,q3);
mult(q3,c,q4);
 r_vector[s1][s2][1]=q4[0][0];

mult(a,m,q1);
mult(q1,bezier_z,q2);
mult(q2,mt,q3);
mult(q3,c,q4);
  r_vector[s1][s2][2]=q4[0][0] ;

  s2++;

   end ;
  s1++;

  end ;

NOP1=s1-1;NOP2=s2-1;

end ;

	  /*----------------------------------*/
	  /*   SAVES THE CALCULATED SURFACE   */
	  /*----------------------------------*/
void save_bezier()
begin

int counter1,counter2;
char name[16],bname[16],rx[10],ry[10],rz[10] ;
char NOPA1[4],NOPA2[4];
clrscr();
gotoxy(5,10);
printf("   Give the name of the file:") ;
scanf("%s",&bname) ;
strcpy(name,"b");
strcat(name,bname);gotoxy(5,11); printf("%s",name);
mem=fopen(name,"w+");

sprintf(NOPA1,"%4d",NOP1);
fprintf(mem,"%4s",NOPA1);
sprintf(NOPA2,"%4d",NOP2);
fprintf(mem,"%4s",NOPA2);

for(counter1=0;counter1<= NOP1;counter1++)

   begin
  for(counter2=0;counter2<= NOP2;counter2++)
    begin

 sprintf(rx,"%10.5f",r_vector[counter1][counter2][0]);
 fprintf(mem,"%10s",rx);
 sprintf(ry,"%10.5f",r_vector[counter1][counter2][1]);
 fprintf(mem,"%10s",ry);
 sprintf(rz,"%10.5f",r_vector[counter1][counter2][2]);
 fprintf(mem,"%10s",rz);


 fprintf(mem,"\n","");
    end ;
   end ;
fclose(mem);

end ;
		/*------------------------*/
		/*------------------------*/
		/*   GRAPH'S ROUTINES     */
		/*------------------------*/
		/*------------------------*/
int load_graph ()
begin
int counter1,counter2;
char name[16],rx[10],ry[10],rz[10] ;
char NOPA1[4],NOPA2[4];
clrscr();
gotoxy(5,10);
printf("   Give the name of the file:") ;
scanf("%s",&name) ;
if((mem=fopen(name,"r"))==0)
begin
printf("  Error on opening file!\n");
printf("  This file not exist!\n");
getch();
return(0);
end ;

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
return(1);
end ;
		 /*--------------------*/
		 /*     GRAPHICS       */
		 /*--------------------*/

void graph ()

begin
int x1,y1,z1,x2,y2,z2,x3,y3,z3,x4,y4,z4;
int counter1,counter2 ;
float max_x,min_x,max_y,min_y;
float cona1,cona2,conb1,conb2 ;

 max_x=r_vector[0][0][0];
 min_x=r_vector[0][0][0];
 max_y=r_vector[0][0][1];
 min_y=r_vector[0][0][1];

anagogh(&max_x,&min_x,&max_y,&min_y);
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
 getch() ;
 closegraph () ;
 rot_zoom();
end ;
	    /*-------------------------------------*/
	    /* REDUCTION OF COORDINATES ON SCREEN  */
	    /*-------------------------------------*/
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



void rot_zoom()
begin
loopmenu3:
menu3();
open_message_window(20,20,60,24,5);
close_message_window(20,20,60,24,5);
goto loopmenu3;

end ;


	   /*-------------------------------*/
	   /* ROUTINE ROTATES THE SURFACES  */
	   /*-------------------------------*/
void rot_surf()
begin
float RX[4][4],RY[4][4],RZ[4][4],ARX[4][4],ARY[4][4],ARZ[4][4] ;
float ax,ay,az ;
float rax,ray,raz ;
char fax[4],fay[4],faz[4];
float re[4][4],are[4][4];
int counter1,counter2 ;
int i,j ;

clrscr();
gotoxy(1,20);
printf("    Give ax,ay,az"); getch();
clrscr();gotoxy(1,20);
  printf(" ax=");
scanf("%s",&fax); ax=atof(fax); rax=(ax*PI)/180;
clrscr();gotoxy(1,20);
  printf(" ay=");
scanf("%s",&fay); ay=atof(fay); ray=(ay*PI)/180;
clrscr();gotoxy(1,20);
  printf(" az=");
scanf("%s",&faz); az=atof(faz); raz=(az*PI)/180;
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
graph();

end ;



void menu1()
{
char ch;int i,j,epilogh;char name[20],menu[8][40];
/*-------------------------- ORISMOS  EPILOGWN --------------------------*/
loop1:
window(1,1,80,25);
textbackground(4);
clrscr();
textcolor(0);
window(1,1,80,25);
textbackground(3);
gotoxy(1,2);
cprintf("                            BEZIER THREE DIMENSIONAL CAD                        ");
textbackground(0);
strcpy(menu[1]," Insert data ");
strcpy(menu[2]," Bezier      ");
strcpy(menu[3]," Graph       ");
strcpy(menu[4]," Quit        ");
/*------------------------------------------------------------------------*/
textcolor(15);
make_window(20,5,60,18,3);
/*------------------------------------------------------------------------*/
for(i=4;i>=1;i--)
 {
   if (i==1) textbackground(1);
   else      textbackground(3);
   gotoxy(10,2*i);
   cprintf("%s",menu[i]);
 }

epilogh=1;
do
{
ch=getch();
if ( (iscntrl(ch)) && (toascii(ch)!=13) )
{
ch=getch();
switch(toascii(ch))
{
case 72 : if (epilogh>1)
		 {
		    textbackground(3);
		    gotoxy(10,epilogh*2);
		    cprintf("%s",menu[epilogh]);
		    epilogh+=-1;
		    textbackground(1);
		    gotoxy(10,epilogh*2);
		    cprintf("%s",menu[epilogh]);
		  }
	   break;
case 80 : if (epilogh<4)
		 {
		    textbackground(3);
		    gotoxy(10,epilogh*2);
		    cprintf("%s",menu[epilogh]);
		    epilogh+=1;
		    textbackground(1);
		    gotoxy(10,epilogh*2);
		    cprintf("%s",menu[epilogh]);
		  }
	   break;
case 71 : if (epilogh!=1)
		 {
		    textbackground(3);
		    gotoxy(10,epilogh*2);
		    cprintf("%s",menu[epilogh]);
		    epilogh=1;
		    textbackground(1);
		    gotoxy(10,epilogh*2);
		    cprintf("%s",menu[epilogh]);
		  }
	   break;
case 79 : if (epilogh!=4)
		 {
		    textbackground(3);
		    gotoxy(10,epilogh*2);
		    cprintf("%s",menu[epilogh]);
		    epilogh=4;
		    textbackground(1);
		    gotoxy(10,epilogh*2);
		    cprintf("%s",menu[epilogh]);
		  }
	   break;
default :  break;
}
}
}
while(toascii(ch)!=13);

switch(epilogh)
{
case 1:give_data(); save_data(); main();
case 2:total_bezier(); main();
case 3:if (load_graph()!=0) graph(); main();
case 4:exit(0);
}

}



void menu2()
{
char ch;int i,j,epilogh;char name[20],menu[11][40];
/*-------------------------- ORISMOS  EPILOGWN --------------------------*/
loop1:
window(1,1,80,25);
textbackground(4);
clrscr();
textcolor(0);
window(1,1,80,25);
textbackground(3);
gotoxy(1,2);
cprintf("                            BEZIER THREE DIMENSIONAL CAD                        ");
textbackground(0);
strcpy(menu[1]," Plain_points");
strcpy(menu[2]," Rev_surf    ");
strcpy(menu[3]," Symetry_x   ");
strcpy(menu[4]," Symetry_y   ");
strcpy(menu[5]," Symetry_z   ");
strcpy(menu[6]," Curve_to_z  ");
strcpy(menu[7]," Curve_to_y  ");
strcpy(menu[8]," Curve_to_x  ");
strcpy(menu[9]," Quit        ");
/*------------------------------------------------------------------------*/
textcolor(15);
make_window(20,5,60,23,3);
/*------------------------------------------------------------------------*/
for(i=9;i>=1;i--)
 {
   if (i==1) textbackground(1);
   else      textbackground(3);
   gotoxy(10,2*i);
   cprintf("%s",menu[i]);
 }

epilogh=1;
do
{
ch=getch();
if ( (iscntrl(ch)) && (toascii(ch)!=13) )
{
ch=getch();
switch(toascii(ch))
{
case 72 : if (epilogh>1)
		 {
		    textbackground(3);
		    gotoxy(10,epilogh*2);
		    cprintf("%s",menu[epilogh]);
		    epilogh+=-1;
		    textbackground(1);
		    gotoxy(10,epilogh*2);
		    cprintf("%s",menu[epilogh]);
		  }
	   break;
case 80 : if (epilogh<9)
		 {
		    textbackground(3);
		    gotoxy(10,epilogh*2);
		    cprintf("%s",menu[epilogh]);
		    epilogh+=1;
		    textbackground(1);
		    gotoxy(10,epilogh*2);
		    cprintf("%s",menu[epilogh]);
		  }
	   break;
case 71 : if (epilogh!=1)
		 {
		    textbackground(3);
		    gotoxy(10,epilogh*2);
		    cprintf("%s",menu[epilogh]);
		    epilogh=1;
		    textbackground(1);
		    gotoxy(10,epilogh*2);
		    cprintf("%s",menu[epilogh]);
		  }
	   break;
case 79 : if (epilogh!=9)
		 {
		    textbackground(3);
		    gotoxy(10,epilogh*2);
		    cprintf("%s",menu[epilogh]);
		    epilogh=9;
		    textbackground(1);
		    gotoxy(10,epilogh*2);
		    cprintf("%s",menu[epilogh]);
		  }
	   break;
default :  break;
}
}
}
while(toascii(ch)!=13);

switch(epilogh)
{
case 1:plain_points();break ;
case 2:rot_curve(); break ;
case 3:symetry_x(); break ;
case 4:symetry_y(); break ;
case 5:symetry_z(); break ;
case 6:curve_toz (); break ;
case 7:curve_toy (); break ;
case 8:curve_tox (); break ;
case 9:main();
}

}


void menu3()
{
char ch;int i,j,epilogh;char name[20],menu[8][40];
/*-------------------------- ORISMOS  EPILOGWN --------------------------*/
loop1:
window(1,1,80,25);
textbackground(4);
clrscr();
textcolor(0);
window(1,1,80,25);
textbackground(3);
gotoxy(1,2);
cprintf("                            BEZIER THREE DIMENSIONAL CAD                        ");
textbackground(0);
strcpy(menu[1]," Rotation     ");
strcpy(menu[2]," Menu     ");
/*------------------------------------------------------------------------*/
textcolor(15);
make_window(20,5,60,18,3);
/*------------------------------------------------------------------------*/
for(i=2;i>=1;i--)
 {
   if (i==1) textbackground(1);
   else      textbackground(3);
   gotoxy(10,2*i);
   cprintf("%s",menu[i]);
 }

epilogh=1;
do
{
ch=getch();
if ( (iscntrl(ch)) && (toascii(ch)!=13) )
{
ch=getch();
switch(toascii(ch))
{
case 72 : if (epilogh>1)
		 {
		    textbackground(3);
		    gotoxy(10,epilogh*2);
		    cprintf("%s",menu[epilogh]);
		    epilogh+=-1;
		    textbackground(1);
		    gotoxy(10,epilogh*2);
		    cprintf("%s",menu[epilogh]);
		  }
	   break;
case 80 : if (epilogh<2)
		 {
		    textbackground(3);
		    gotoxy(10,epilogh*2);
		    cprintf("%s",menu[epilogh]);
		    epilogh+=1;
		    textbackground(1);
		    gotoxy(10,epilogh*2);
		    cprintf("%s",menu[epilogh]);
		  }
	   break;
case 71 : if (epilogh!=1)
		 {
		    textbackground(3);
		    gotoxy(10,epilogh*2);
		    cprintf("%s",menu[epilogh]);
		    epilogh=1;
		    textbackground(1);
		    gotoxy(10,epilogh*2);
		    cprintf("%s",menu[epilogh]);
		  }
	   break;
case 79 : if (epilogh!=2)
		 {
		    textbackground(3);
		    gotoxy(10,epilogh*2);
		    cprintf("%s",menu[epilogh]);
		    epilogh=2;
		    textbackground(1);
		    gotoxy(10,epilogh*2);
		    cprintf("%s",menu[epilogh]);
		  }
	   break;
default :  break;
}
}
}
while(toascii(ch)!=13);

switch(epilogh)
{
case 1:rot_surf();break;
case 2:main();
}

}



void open_message_window(left,top,right,botom,bcolor)
int left,top,right,botom,bcolor;
{
buf=(char *) malloc((right-left+1)*(botom-top+1)*2);
gettext(left,top,right,botom,buf);
window(left,top,right,botom);
textbackground(bcolor);
clrscr();

}


void close_message_window(left,top,right,botom)
int left,top,right,botom;
{
puttext(left,top,right,botom,buf);
free(buf);

}


void make_window(left,top,right,botom,bcolor)
int left,top,right,botom,bcolor;
{
window(left,top,right,botom);
textbackground(bcolor);
clrscr();

}




void read_parametric_file()
{
  while (!(mem=fopen("parametr.c","r+")))
  {
   gotoxy(2,2);
   printf("File  parametric does not exist");
   gotoxy(2,4);
   printf("     Press any key ");
   getch();
   exit(1);
  }
  fscanf(mem,"%s",prg_dir);
  fscanf(mem,"%s",file_dir);
  fclose(mem);

}





void give_names()
begin
char name[16] ;
clrscr();
num_of_files=1;
do
begin
clrscr();
gotoxy(1,3);
printf("   Give the name of the %d file:",num_of_files) ;
scanf("%s",&name) ;
strcpy(nams[num_of_files],name);
num_of_files+=1;
end
while(strcmp(name,"n")!=0);
num_of_files+=-2;
gotoxy(5,10);
printf("You gave (%d) files",num_of_files);
getch();
end ;


void total_bezier()
begin
char com_nam[26];
give_names();
clrscr(); gotoxy(5,10);
printf("   Give the STEP:") ;
scanf("%f",&STEP) ;
for(patches=1;patches<=num_of_files;patches++)
begin
strcpy(com_nam,nams[patches]);
load_bezier(com_nam); bezier(); save_bezier();
end;

exit(1);
end;




