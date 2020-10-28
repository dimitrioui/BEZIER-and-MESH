#define begin {
#define end }


	      /*LIBRARIES INCLUDED */
#include <stdlib.h>
#include <math.h>
#include <dir.h>
#include <dos.h>
#include "graphics.h"
#include "conio.h"
#include "stdio.h"
#include "ctype.h"
#include "process.h"
#include "string.h"
#include "math.h"
#include "dir.h"
#include "stdlib.h"

	      /* VOID ROUTINE(S) DEFINITION */

void

      read_parametric_file(),
      graph(),
      tri_to_tetr(),
      clear_graph_window(),
      open_message_window(),
      close_message_window(),
      find_u1_u2(),
      anagwgh(float *xo,float *yo,float *nu),
      xyz_XY(float x,float y,float z,float *X,float *Y),
      read_data(),
      symetry_xy(char c),
      mesh_improve(),
      meshimprove(),
      typwnw(int x,int y,char c),
      printnum(int xo,int yo,int k),
      velos(int x1,int y1),
      zoom_myga(float *xo,float *yo,float *nu),
      zoom();

	       /* INT ROUTINE(S) DEFINITION */

int   mapx(float x,float y,float z),
      mapy(float x,float y,float z),
      belong_out(int k),t(int i,int j),isthesame(int i1,int j1),
      readstring(char name[20],int theshx,int theshy),
      readfloatnum(float *k,int theshx,int theshy),
      e(int i1,int i2);

		/* GLOBAL VARIABLES */

int no[4][1500],outnod[800];
float *cx,*cy,*cz;
float resolutiony,resolutionx;    /* The rsolution of the screen */
float dist,rox,roy,roz,u1x,u1y,u1z,u2x,u2y,u2z,ux,uy,uz,xo,yo,nu;
int totnod,kk,exnod,numfreed;
void *buf;
char filename[20];
char prg_dir[79],file_dir[79];
char typ,drive;int intargc;
FILE *memco;
FILE *memno;



main(argc,argv)
int argc;
char *argv[];
begin
int gdriver,gmode;
read_parametric_file();
strcpy(filename,argv[1]);
intargc=argc;
open_message_window(20,20,60,24,5);
gotoxy(2,2);cprintf("Please wait...");
read_data(argc,filename);
gdriver=DETECT;gmode=0;initgraph(&gdriver,&gmode,"c:\\turboc3\\BGI");
switch(gdriver)
{
case 1 :resolutiony=resolutionx=1.0;break;
case 2 :resolutiony=(480.0/200.0);resolutionx=1.0;break;
case 3 :resolutiony=(350.0/200.0);resolutionx=1.0;break;
case 4 :resolutiony=(350.0/200.0);resolutionx=1.0;break;
case 5 :resolutiony=(350.0/200.0);resolutionx=1.0;break;
case 7 :resolutionx=(720.0/640.0);resolutiony=(348.0/200.0);break;
case 8 :resolutiony=(400.0/200.0);resolutionx=1;break;
case 9 :resolutiony=(480.0/200.0);resolutionx=1;break;
case 10 :resolutiony=(350.0/200.0);resolutionx=(720.0/640.0);break;
default :resolutiony=resolutionx=1.0;break;
setcolor(WHITE);
}
graph(argc,filename);
free(cz);
free(cy);
free(cx);

end



void read_data(intargc,charargv)
int intargc;
char charargv[20];
begin
int i,j,jr,sum;float x,y,z;
char prothema[5],let,name[20],name1[20],p[10],p1[10],p2[10];
if (intargc<=1) strcpy(name1,"noname.num");
else
         begin
         strcpy(prothema,".num");
	 strnset(name1,' ',20);
         strcpy(name1,charargv);
         strncat(name1,prothema,4);
	 strupr(name1);
	 end
  while (!(memno=fopen(name1,"r+")))
  {
   gotoxy(30,22);
   printf("file  %s does not exist",name1);
   getch();
   exit(1);
  }
fscanf(memno,"%5s",p);totnod=atoi(p);
fscanf(memno,"%5s",p);kk=atoi(p);
fscanf(memno,"%5s",p);exnod=atoi(p);
fclose(memno);
/*-----------------   M E M O R Y   O V E R F L O W  ------------------------*/
if ( (!(cx=(float *)calloc((totnod+1),sizeof(float)))) ||
     (kk>=1805) ||
     (!(cy=(float *)calloc((totnod+1),sizeof(float)))) ||
     (!(cz=(float *)calloc((totnod+1),sizeof(float)))))
{
 		 open_message_window(15,20,65,24,5);
		 gotoxy(2,2);
		 cprintf("Not Enough  Memory   Press  any key");
		 gotoxy(2,4);
		 cprintf("TOTNOD=%d   ELEM=%d    EX.NOD=%d ",totnod,kk,exnod);
		 getch();
		 close_message_window(15,20,65,24,5);
		 exit(1);
}
/*---------------------------------------------------------------------------*/
if (intargc<=1) strcpy(name1,"noname.co");
else
         begin
         strcpy(prothema,".co");
         strnset(name1,' ',20);
         strcpy(name1,charargv);
         strncat(name1,prothema,3);
	 strupr(name1);
	 end
while (!(memco=fopen(name1,"r+")))
{
   gotoxy(30,22);
   printf("file  %s does not exist",name1);
   getch();
   exit(1);
  }
for(i=1;i<=totnod;i++)
begin
fscanf(memco,"%10s",p);
fscanf(memco,"%10s",p1);
fscanf(memco,"%10s",p2);
cx[i]=atof(p);cy[i]=atof(p1);cz[i]=atof(p2);

end
fclose(memco);
if (intargc<=1) strcpy(name1,"noname.no");
else
         begin
         strcpy(prothema,".no");
         strnset(name1,' ',20);
         strcpy(name1,charargv);
         strncat(name1,prothema,3);
	 strupr(name1);
	 end
  while (!(memno=fopen(name1,"r+")))
  {
   gotoxy(30,22);
   printf("file  %s does not exist",name1);
   getch();
   exit(1);
  }
for(i=1;i<=kk;i++)
begin
fscanf(memno,"%5s",p);
no[0][i]=atoi(p);
for(j=1;j<=no[0][i];j++)
begin
fscanf(memno,"%5s",p);
no[j][i]=atoi(p);
end
end
fclose(memno);
if (intargc<=1) strcpy(name1,"noname.out");
else
         begin
         strcpy(prothema,".out");
         strnset(name1,' ',20);
         strcpy(name1,charargv);
         strncat(name1,prothema,4);
	 strupr(name1);
	 end
  while (!(memno=fopen(name1,"r+")))
  {
   gotoxy(30,22);
   printf("file  %s does not exist",name1);
   getch();
   exit(1);
  }
for(i=1;i<=exnod;i++)
begin
fscanf(memno,"%5s",p);
outnod[i]=atoi(p);
end
fclose(memno);

end





void open_message_window(int left,int top,int right,int botom,int bcolor)
{
buf=(char *) malloc((right-left+1)*(botom-top+1)*2);
gettext(left,top,right,botom,buf);
window(left,top,right,botom);
textbackground(bcolor);
clrscr();

}



void close_message_window(int left,int top,int right,int botom,int bcolor)
{
puttext(left,top,right,botom,buf);
free(buf);

}



void read_parametric_file()
{
  while (!(memco=fopen("parametr.c","r+b")))
  {
   gotoxy(2,2);
   printf("File  parametric does not exist");
   gotoxy(2,4);
   printf("     Press any key ");
   getch();
   exit(1);
  }
  fscanf(memco,"%s",prg_dir);
  fscanf(memco,"%s",file_dir);
  fclose(memco);

}



void typwnw(int x,int y,char c)
begin
setcolor(RED);
switch(c)
{
case '1': line(x+2,y,x+2,y+4);
	  line(x+2,y,x,y+1);break;
case '3': line(x+4,y+4,x+4,y);
	  line(x+4,y+4,x,y+4);
	  line(x+4,y+2,x,y+2);
	  line(x+4,y,x,y);break;
case '4': line(x,y,x,y+2);
	  line(x,y+2,x+4,y+2);
	  line(x+4,y,x+4,y+4);break;
case '2': line(x+4,y+4,x,y+4);
	  line(x,y+4,x,y+2);
	  line(x,y+2,x+4,y+2);
	  line(x+4,y+2,x+4,y);
	  line(x+4,y,x,y);break;
case '5': line(x,y,x+4,y);
	  line(x,y,x,y+2);
	  line(x,y+2,x+4,y+2);
	  line(x+4,y+2,x+4,y+4);
	  line(x+4,y+4,x,y+4);break;
case '6': line(x,y,x,y+4);
	  line(x,y+4,x+4,y+4);
	  line(x+4,y+4,x+4,y+2);
          line(x+4,y+2,x,y+2);break;
case '7': line(x,y,x+4,y);
	  line(x+4,y,x,y+4);break;
case '0': line(x,y,x+4,y);
	  line(x+4,y,x+4,y+4);
	  line(x+4,y+4,x,y+4);
	  line(x,y+4,x,y);break;
case '8': line(x,y,x+4,y);
	  line(x+4,y,x+4,y+4);
	  line(x+4,y+4,x,y+4);
	  line(x,y+4,x,y);
	  line(x,y+2,x+4,y+2);break;
case '9': line(x,y,x+4,y);
	  line(x+4,y,x+4,y+2);
	  line(x+4,y+2,x+2,y+4);
	  line(x,y,x,y+2);
	  line(x,y+2,x+4,y+2);break;
}

end



void printnum(int xo,int yo,int k)
begin
char num[10];
int i;
char ch;
itoa(k,num,10);
for(i=0;i<=strlen(num);i++)
begin
ch=num[i];
typwnw(xo+6*(i-1),yo,ch);
end

end



void zoom_myga(float *xo,float *yo,float *nu)
begin
int x1,y1,taxythta,number,sizex,sizey;
float maxx,minx,maxy,miny;
void *buf;
char ch;
unsigned size;
taxythta=1;sizex=10;sizey=10;
setcolor(GREEN);
x1=floor(resolutionx*320);
y1=floor(resolutiony*100);
size=imagesize(x1,y1,x1+sizex,y1+sizey);
buf=malloc(size);
do
{
size=imagesize(x1,y1,x1+sizex,y1+sizey);
if (size!=-1)
begin
 free(buf);
 buf=malloc(size);
 if (buf)
 begin
  getimage(x1,y1,x1+sizex,y1+sizey,buf);
  rectangle(x1,y1,x1+sizex,y1+sizey);
loopch:ch=getch();
  if ( (iscntrl(ch)) || (ch=='+') || (ch=='-') )
  begin
  putimage(x1,y1,buf,COPY_PUT);
  if (iscntrl(ch)) ch=getch();
 switch(ch)
{
case 'G':  return;
case 'H':  if (y1-taxythta>2)    y1+=-taxythta;break;
case 'P':  if (y1+taxythta+sizey<=resolutiony*170)  y1+=taxythta;break;
case 'M':  if (x1+2*taxythta+sizex<=resolutionx*600)  x1+=2*taxythta;break;
case 'K':  if (x1-2*taxythta>1)    x1+=-2*taxythta;break;
case '+':  if (taxythta<15)        taxythta+=1;goto loop0;
case '-':  if (taxythta>2)         taxythta+=-1;goto loop0;
case 't':  if (x1+sizex+2<resolutionx*600) sizex+=2;break;
case 's':  if (sizex>10)   sizex+=-2;break;
case 'Q':  if (y1+sizey+2<resolutiony*170)  sizey+=+2;break;
case 'I':  if (sizey>10)   sizey+=-2;break;
}
end
else goto loopch;
end
else {
      clear_graph_window();
      outtextxy(1,1,"MEMORY FULL");
      outtextxy(1,12,"Press 'C'");
      do
      {ch=getch();}
      while((ch!='C'));
      clear_graph_window();
      free(buf);
      return;
      }
end
else return;
loop0:;}
while((ch!='O'));
maxx=(((x1+sizex)/resolutionx)-300)/(2.7*(*nu))+(*xo);
minx=((x1/resolutionx)-300)/(2.7*(*nu))+(*xo);
miny=((((y1+sizey)/resolutiony)-85)/(-(*nu)))+(*yo);
maxy=(((y1/resolutiony)-85)/(-(*nu)))+(*yo);
*xo=(maxx+minx)/2;*yo=(maxy+miny)/2;
*nu=160/(maxx-minx);
if (160/(maxy-miny)<*nu)  *nu=160/(maxy-miny);
setcolor(WHITE);

end



int t(int i,int j)
begin
if (i<=j) return(i);
return(i-j);

end



int mapx(float x,float y,float z)
  begin
  float x1,aa,bb;
  aa=-dist*((x-rox)*u1x+(y-roy)*u1y+(z-roz)*u1z);
  bb=(x-rox)*ux+(y-roy)*uy+(z-roz)*uz-dist;
  x1=aa/bb;
  return(floor(resolutionx*(2.7*(x1-xo)*nu+300)));

end



int mapy(float x,float y,float z)
begin
  float y1,aa,bb;
  aa=-dist*((x-rox)*u2x+(y-roy)*u2y+(z-roz)*u2z);
  bb=(x-rox)*ux+(y-roy)*uy+(z-roz)*uz-dist;
  y1=aa/bb;
  return(floor(resolutiony*(-(y1-yo)*nu+85)));

end



void xyz_XY(float x,float y,float z,float *X,float *Y)
begin
float aa,bb;
  aa=-dist*((x-rox)*u1x+(y-roy)*u1y+(z-roz)*u1z);
  bb=(x-rox)*ux+(y-roy)*uy+(z-roz)*uz-dist;
*X=aa/bb;
  aa=-dist*((x-rox)*u2x+(y-roy)*u2y+(z-roz)*u2z);
*Y=aa/bb;

end



void find_u1_u2()
begin
float mro,mu1;
   rox=100*rox;
   roy=100*roy;
   roz=100*roz;
   mro=sqrt(rox*rox+roy*roy+roz*roz);
   if (roz==0)
     begin
      u1x=0;
      u1y=0;
      u1z=1;
      goto label_2;
     end
   if ((rox==0)&&(roy==0)&&(roz==1))
     begin
      u1x=1;
      u1y=0;
      u1z=0;
      goto label_2;
      end

   u1x=-rox;
   u1y=-roy;
   u1z=mro*mro/roz-roz;
   mu1=sqrt(u1x*u1x+u1y*u1y+u1z*u1z);
   u1x=u1x/mu1;
   u1y=u1y/mu1;
   u1z=u1z/mu1;
label_2:u2x=(u1y*roz-u1z*roy)/mro;
   u2y=(u1z*rox-u1x*roz)/mro;
   u2z=(u1x*roy-u1y*rox)/mro;
   ux=rox/mro;
   uy=roy/mro;
   uz=roz/mro;

end




void anagwgh(float *xo,float *yo,float *nu)
begin
int i;
float x1,y1,xmax,xmin,ymax,ymin,XMAX,YMAX,ZMAX,ZMIN,YMIN,XMIN,max[9][4];
find_u1_u2();
XMIN=XMAX=cx[1];YMIN=YMAX=cy[1];ZMIN=ZMAX=cz[1];
for(i=1;i<=totnod;i++)
 begin
 if (cx[i]>=XMAX) XMAX=cx[i];
 if (cy[i]>=YMAX) YMAX=cy[i];
 if (cz[i]>=ZMAX) ZMAX=cz[i];
 if (cx[i]<=XMIN) XMIN=cx[i];
 if (cy[i]<=YMIN) YMIN=cy[i];
 if (cz[i]<=ZMIN) ZMIN=cz[i];
 end
max[1][1]=XMIN;max[1][2]=YMIN;max[1][3]=ZMIN;
max[2][1]=XMIN;max[2][2]=YMAX;max[2][3]=ZMIN;
max[3][1]=XMAX;max[3][2]=YMAX;max[3][3]=ZMIN;
max[4][1]=XMAX;max[4][2]=YMIN;max[4][3]=ZMIN;
max[5][1]=XMIN;max[5][2]=YMIN;max[5][3]=ZMAX;
max[6][1]=XMIN;max[6][2]=YMAX;max[6][3]=ZMAX;
max[7][1]=XMAX;max[7][2]=YMAX;max[7][3]=ZMAX;
max[8][1]=XMAX;max[8][2]=YMIN;max[8][3]=ZMAX;
dist=0.1*ZMAX;
if (fabs(ZMAX)<=0.0001) dist=0.1;
xyz_XY(max[1][1],max[1][2],max[1][3],&x1,&y1);
xmax=xmin=x1;
ymax=ymin=y1;
for(i=2;i<=8;i++)
 begin
  xyz_XY(max[i][1],max[i][2],max[i][3],&x1,&y1);
  if (xmax<x1) xmax=x1;
  if (ymax<y1) ymax=y1;
  if (xmin>x1) xmin=x1;
  if (ymin>y1) ymin=y1;
 end
*xo=(xmax+xmin)/2;
*yo=(ymax+ymin)/2;
*nu=160/(xmax-xmin);
if (160/(ymax-ymin)<*nu)  *nu=160/(ymax-ymin);

end



void zoom()
begin
int i,j,x1,y1,x2,y2;
setviewport(1,1,floor(resolutionx*639),floor(resolutiony*198),1);
setbkcolor(BLUE);setcolor(WHITE);
clearviewport();
clear_graph_window();
outtextxy(1,1,"         Please  wait .... ");
setviewport(floor(resolutionx*20),floor(resolutiony*20),floor(resolutionx*630),floor(resolutiony*190),1);
line(floor(resolutionx*1),floor(resolutiony*1),floor(resolutionx*610),floor(resolutiony*1));
line(floor(resolutionx*610),floor(resolutiony*1),floor(resolutionx*610),floor(resolutiony*170));
line(floor(resolutionx*610),floor(resolutiony*170),floor(resolutionx*1),floor(resolutiony*170));
line(floor(resolutionx*1),floor(resolutiony*170),floor(resolutionx*1),floor(resolutiony*1));
   for(j=1;j<=kk;j++)
     for(i=1;i<=3;i++)
     begin
     x1=mapx(cx[no[i][j]],cy[no[i][j]],cz[no[i][j]]);
     y1=mapy(cx[no[i][j]],cy[no[i][j]],cz[no[i][j]]);
     x2=mapx(cx[no[t(i+1,3)][j]],cy[no[t(i+1,3)][j]],cz[no[t(i+1,3)][j]]);
     y2=mapy(cx[no[t(i+1,3)][j]],cy[no[t(i+1,3)][j]],cz[no[t(i+1,3)][j]]);
     if ((x1>10) && (x1<720) &&  (y1>1) && (y2<400))
     {line(x1,y1,x2,y2);}
     end /* of j */

end



void graph(intargc,charargv)
int intargc;
char charargv[20];
begin

void *buf;
unsigned size;
int tot,i,j;
char ans1,ok;

rox=roy=roz=1.0;
loopthf:
anagwgh(&xo,&yo,&nu);
zoom();
loop1:
clear_graph_window();
outtextxy(1,1,"   Rotate-ZOOM-NZOOM-rESIZE-MOVE>-<MOVE-UP-DOWN-EXIT-nUM- ");
setviewport(floor(resolutionx*20),floor(resolutiony*20),floor(resolutionx*630),floor(resolutiony*190),1);
ans1=getch();
if (ans1=='R')
begin
clear_graph_window();
outtextxy(1,1,"Give ");
scanf("%f%f%f",&rox,&roy,&roz);
goto loopthf;

end
if (ans1=='E') goto loop2;
if (ans1=='Z' )  begin
   zoom_myga(&xo,&yo,&nu);
   zoom();
end

if (ans1=='n')
begin
window(1,1,80,20);
for(i=1;i<=totnod;i++)
printnum(mapx(cx[i],cy[i],cz[i]),mapy(cx[i],cy[i],cz[i]),i);
end
if (ans1=='r') goto loopthf;
goto loop1 ;
loop2:
clearviewport();
closegraph();

end






int belong_out(int k)
begin
int i;
for(i=1;i<=exnod;i++)
if (k==outnod[i]) return(1);
return(0);

end




void clear_graph_window()
begin
setviewport(1,1,floor(resolutionx*639),floor(resolutiony*10),1);
clearviewport();
setviewport(1,1,floor(resolutionx*639),floor(resolutiony*10),1);

end




int  readstring(char name[20],int theshx,int theshy)
begin
int namekk;
char ch,num1[1],name2[20];
namekk=0;
strset(name,' ');
do
{
ch=getch();
if (!iscntrl(ch))
begin
  name[namekk]=ch;
  namekk+=1;
  num1[0]=ch;
  setviewport(floor(resolutionx*(theshx+9*(namekk-1))),floor(resolutiony*theshy),floor(resolutionx*(theshx+9+9*(namekk-1))),floor(resolutiony*theshy+10),1);
  outtextxy(1,1,num1);
end
}
while(!iscntrl(ch));
name[namekk]='\0';

end



int readfloatnum(float *k,int theshx,int theshy)
begin
int numkk,kk,i,true_false;
char ch,num[20],num1[1];
strnset(num,' ',20);
numkk=0;
true_false=1;
do
{
ch=getch();
if ( ( (isdigit(ch)) || (ch=='.') || (ch=='-') ) && (numkk<=4) )
begin
 num[numkk]=ch;numkk+=1;
 num1[0]=ch;
 setviewport(floor(resolutionx*(theshx+9*(numkk-1))),floor(resolutiony*theshy),floor(resolutionx*(theshx+9+9*(numkk-1))),floor(resolutiony*theshy+10),1);
 outtextxy(1,1,num1);
 continue;
end
if ( (toascii(ch)==8) && (numkk>=1) )
    begin
    setviewport(floor(resolutionx*(theshx+9*(numkk-1))),floor(resolutiony*theshy),floor(resolutionx*(theshx+9+9*(numkk-1))),floor(resolutiony*theshy+10),1);
    numkk+=-1;
    num1[0]=num[numkk];
    num[numkk]=' ';
    setcolor(0);
    outtextxy(1,1,num1);
    setcolor(1);
    end
}
while(toascii(ch)!=13);
kk=0;
for(i=0;i<=numkk-1;i++)
begin
ch=num[i];
if ( (isdigit(ch)) || (ch=='.') || (ch=='-') )  begin num[kk]=ch;kk=kk+1;end
else true_false=0;
end
*k=atof(num);
return(true_false);

end

