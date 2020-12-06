#define begin {
#define end; }
#define pi 3.1415926536
#define MAX_SHAPES 200
#define MAX_NODES 300

#include "graphics.h"
#include "conio.h"
#include "stdio.h"
#include "ctype.h"
#include "process.h"
#include "string.h"
#include "math.h"
#include "dir.h"



void
      open_message_window(),
      close_message_window(),
      load_shapes(),
      load_nest_shapes(),
      save_igs_file(),
      transform(),
      compute_real_coordinates(),
      chdirr(),
      read_parametric_file();

void *buf;
int   kind[MAX_SHAPES],tot_shapes=0,dif_shapes,totnodes;
float cx[MAX_NODES],cy[MAX_NODES],f_sign[MAX_NODES],
      xk[MAX_NODES],yk[MAX_NODES],matrix[MAX_SHAPES][3];
int numext[MAX_SHAPES],ext[MAX_SHAPES][7],no[MAX_SHAPES][20];
char filename[20];
char prg_dir[79],file_dir[79],drive1,drive2,directory[79];
char drive;int intargc;
FILE *memco;
float mem[800][6];
int mer,num_of_lines,g_lines=0,p_lines=0,d_lines=0;
/*--------------------------------------------------------------------------*/


main(argc,argv)
int argc;
char *argv[];
{
open_message_window(20,20,60,24,5);gotoxy(2,2);cprintf("Please wait...");
if (argc<=1) {clrscr();printf(" USAGE : %s filename \n",argv[0]);exit(1);}
strcpy(filename,argv[1]);
read_parametric_file();
chdirr(drive2,file_dir);
load_shapes();
load_nest_shapes();
compute_real_coordinates();
save_igs_file();
chdirr(drive1,prg_dir);
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

void close_message_window(left,top,right,botom,bcolor)
int left,top,right,botom,bcolor;
{
puttext(left,top,right,botom,buf);
free(buf);
}


void load_shapes()
begin
int k,i,j,jr,tot,t,times;
char proname[5],name1[20],p[30];
strcpy(proname,".db");
strnset(name1,' ',20);
strcpy(name1,filename);
strncat(name1,proname,3);
strupr(name1);
if (!(memco=fopen(name1,"r+")))
{clrscr();printf(" File %s does not exist \n",name1);chdirr(drive1,prg_dir);exit(1);}
/*---------------------------------------------------------------------------*/
/*---------------------  INITIALIZE   FIRST  VALUES -------------------------*/
ext[0][0]=numext[0]=tot=dif_shapes=0;
/*---------------------------------------------------------------------------*/
 fscanf(memco,"%5s",p);/* NUMBER OF RECORDS IN DB */
 dif_shapes=atoi(p);
 if (dif_shapes>=MAX_SHAPES) {clrscr();printf(" MEMORY OVERFLOW ");chdirr(drive1,prg_dir);exit(1);}
/*---------------------------------------------------------------------------*/
for(k=1;k<=dif_shapes;k++)
{
   fscanf(memco,"%8s",p); /* INSTEAD OF ** */
   fscanf(memco,"%5s",p); /* READ INDEX (NOT USED) */
   fscanf(memco,"%5s",p);numext[k]=atoi(p);
   /*--------------------------------------------------------*/
   ext[k][0]=0;
    for(i=0;i<=numext[k];i++)
   {
    fscanf(memco,"%5s",p);
    if (i==0) continue;
    ext[k][i]=ext[k-1][numext[k-1]]+atoi(p)-1;
    }
  /*--------------------------------------------------------------------*/
   j=0;
   for(i=ext[k-1][numext[k-1]]+1;i<=ext[k][numext[k]]+1;i++)
     begin
      tot++;
      fscanf(memco,"%8s",p);cx[tot]=atof(p);
      fscanf(memco,"%8s",p);cy[tot]=atof(p);
      fscanf(memco,"%8s",p);f_sign[tot]=atof(p);
      fscanf(memco,"%8s",p);xk[tot]=atof(p);
      fscanf(memco,"%8s",p);yk[tot]=atof(p);
/*---------------------------------------------------------------------------*/
      j++;no[k][j]=tot;
      end;
      /*------ THE LAST COORD OF EVERY SHAPES IS THE SAME WITH THE FIRST ---*/
      tot--;
      no[k][0]=j-1;
   /*--------------------------------------------------------------*/
}
fclose(memco);
/*-------------------------------------------------------------------------*/
end;

void load_nest_shapes()
{
int l,j,i;char p1[30];
char proname[5],name1[20];
 strcpy(proname,".dbr");
 strnset(name1,' ',20);
 strcpy(name1,filename);
 strncat(name1,proname,4);
 strupr(name1);
if (!(memco=fopen(name1,"r+")))
{clrscr();printf(" File %s does not exist \n",name1);chdirr(drive1,prg_dir);exit(1);}
while(!feof(memco))
{
 fscanf(memco,"%8s",p1);/* instaed of **  */
 tot_shapes++;
 fscanf(memco,"%5s",p1);kind[tot_shapes]=atoi(p1);
 fscanf(memco,"%8s",p1);matrix[tot_shapes][0]=atof(p1);
 fscanf(memco,"%8s",p1);matrix[tot_shapes][1]=atof(p1);
 fscanf(memco,"%8s",p1);matrix[tot_shapes][2]=atof(p1);
  if (kind[tot_shapes]>dif_shapes)
   {window(1,1,80,25);
    clrscr();printf("\n\nSolution file does not correspond with the database file\n");
    printf("You have probably erase a shape from the database.\n");
    printf("\nPress any key to continue");getch();
    chdirr(drive1,prg_dir);exit(1);}
 if (tot_shapes>=MAX_SHAPES) {clrscr();printf(" MEMORY OVERFLOW ");chdirr(drive1,prg_dir);exit(1);}
}
fclose(memco);
}

void transform(k,x,y)
int k;float *x,*y;
{
float f,fy,fx;
 fx=*x;
 fy=*y;
 f=matrix[k][0];
 *x=(cos(f)*fx+sin(f)*fy)+matrix[k][1];
 *y=(-sin(f)*fx+cos(f)*fy)+matrix[k][2];
}


t(i,j)
int i,j;
{
if (i<=j) return(i);
	  return(i-j);
}



check_file(name1)
char name1[20];
begin
  while(!(memco=fopen(name1,"r+")))
  {
   open_message_window(20,20,60,24,5);
   gotoxy(2,2);
   cprintf("File  %s does not exist",name1);
   gotoxy(2,4);
   cprintf("     Press any key ");
   getch();
   close_message_window(20,20,60,24,5);
   return(0);
   }
return(1);
end;

void read_parametric_file()
{
  while (!(memco=fopen("parametr.c","r+b")))
  {
   gotoxy(2,2);
   printf("File  parametric does not exist");
   gotoxy(2,4);
   printf("     Press any key ");getch();
   exit(1);
  }
  fscanf(memco,"%s",prg_dir);
  fscanf(memco,"%s",file_dir);
  fclose(memco);

  drive1=prg_dir[0];
  drive2=file_dir[0];
}

void chdirr(l_drive,direct)
char l_drive,direct[79];
{
char m[79],dir[79],ch;int i,deep;
switch(l_drive)
{
case 'a': i=0;break;
case 'b': i=1;break;
case 'c': i=2;break;
case 'd': i=3;break;
case 'e': i=4;break;
default : i=2;
}
setdisk(i);
getcurdir(i+1,dir);
deep=1;
if (strlen(dir)>2)
{
for(i=2;i<=strlen(dir)-1;i++)
{ch=dir[i];if (!(isalnum(ch))) deep+=1;}
for(i=1;i<=deep;i++)
system("cd ..");
}
strnset(m,' ',79);
strcpy(m,"cd ");
strcat(m,direct);
system(m);
}

void compute_real_coordinates()
{
int i,j,zz;
float x,y;
mer=0;
for(i=1;i<=tot_shapes;i++)
 {
  zz=kind[i];
  for(j=1;j<=no[zz][0];j++)
  {
    x=cx[no[zz][j]];
    y=cy[no[zz][j]];
    transform(i,&x,&y);
    mer++;
    mem[mer][1]=x;
    mem[mer][2]=y;
    mem[mer][3]=f_sign[no[zz][t(j+1,no[zz][0])]];
    x=xk[no[zz][t(j+1,no[zz][0])]];
    y=yk[no[zz][t(j+1,no[zz][0])]];
    transform(i,&x,&y);
    mem[mer][4]=x;
    mem[mer][5]=y;
   }
   x=cx[no[zz][1]];
   y=cy[no[zz][1]];
   transform(i,&x,&y);
   mer++;
   mem[mer][1]=x;
   mem[mer][2]=y;
   mem[mer][3]=f_sign[no[zz][2]];
   x=xk[no[zz][2]];
   y=yk[no[zz][2]];
   transform(i,&x,&y);
   mem[mer][4]=x;
   mem[mer][5]=y;
  }
  /*
for(i=1;i<=mer;i++)
{
printf("  %8.4f %8.4f %8.4f %8.4f %8.4f \n",mem[i][1],mem[i][2],mem[i][3],mem[i][4],mem[i][5]);
getch();
}
*/
}


void save_igs_file()
{
float x,first_cx,first_cy;
char name[20];
int i,j,r,first_pos,counter;
chdirr(drive2,file_dir);
if (intargc<=1) strcpy(name,"noname.igs");
else {strcpy(name,filename);strcat(name,".igs");}
if (!(memco=fopen(name,"w+")))
{
gotoxy(1,1);printf(" Could not open file ");
gotoxy(1,2);printf(" Press any ket to return");
getch();
clrscr();
chdirr(drive1,prg_dir);
exit(1);
}
/*---------------------------------------------------------------------------*/
fprintf(memco,"IGES file generated from a JOHN DIMITRIOU   by the IGES                 S0000001\n","");
fprintf(memco,"translator                    , translator version IGESOUT-2.0.         S0000002\n","");
fprintf(memco,",,1HY,5HY.IGS,10HAutoCAD-10,11HIGESOUT-2.0,16,38,6,99,15,1HY,1.0,1,4HINCG0000001\n","");
fprintf(memco,"H,32767,3.2767D1,13H910319.190735,1.0D-8,7.0,6HThroop,14HAutodesk, Inc.,G0000002\n","");
g_lines=2;
/*---------------------------------------------------------------------------*/
first_cx=mem[1][1];first_cy=mem[1][2];first_pos=1;counter=0;
for(i=1;i<=mer;i++)
{
if ( (fabs(first_cx-mem[i][1])<=0.001) &&
     (fabs(first_cy-mem[i][2])<=0.001) &&
     (first_pos!=i) )
 {first_cx=mem[i+1][1];first_cy=mem[i+1][2];first_pos=i+1;counter++;continue;}
  if (mem[i][3]==0)       {print_line_d_section(i-counter);continue;}
  if (fabs(mem[i][3])==1) {print_arc_d_section(i-counter);continue;}
}
first_cx=mem[1][1];first_cy=mem[1][2];first_pos=1;counter=0;
for(i=1;i<=mer;i++)
{
if ( (fabs(first_cx-mem[i][1])<=0.001) &&
     (fabs(first_cy-mem[i][2])<=0.001) &&
     (first_pos!=i) )
 {first_cx=mem[i+1][1];first_cy=mem[i+1][2];first_pos=i+1;counter++;continue;}
if (mem[i][3]==0)       {print_line_p_section(i-counter,i);continue;}
if (fabs(mem[i][3])==1) {print_arc_p_section(i-counter,i,mem[i][3]);continue;}
}
/*---------------------------------------------------------------------------*/
print_end();

fclose(memco);
chdirr(drive1,prg_dir);
}


print_line_d_section(k)
int k;
{
char temp[30],temp1[30];
temp[0]=temp1[0]=0;
if (2*k-1<10)        sprintf(temp,"000000%d",2*k-1);
else if (2*k-1<100) sprintf(temp,"00000%d",2*k-1);
else                sprintf(temp,"0000%d",2*k-1);
if (2*k<10)         sprintf(temp1,"000000%d",2*k);
else if (2*k<100)   sprintf(temp1,"00000%d",2*k);
else                sprintf(temp1,"0000%d",2*k);
if (k<10)        {fprintf(memco,"     110       ","");fprintf(memco,"%d",k);}
else if (k<100)  {fprintf(memco,"     110      ","");fprintf(memco,"%d",k);}
else             {fprintf(memco,"     110     ","");fprintf(memco,"%d",k);}
fprintf(memco,"       1       1                                00000000D","");
fprintf(memco,"%s\n",temp);
fprintf(memco,"     110                       1                                        D","");
fprintf(memco,"%s\n",temp1);
d_lines+=2;
}

print_arc_d_section(k)
int k;
{
char temp[30],temp1[30];
temp[0]=temp1[0]=0;
if (2*k-1<10)        sprintf(temp,"000000%d",2*k-1);
else if (2*k-1<100) sprintf(temp,"00000%d",2*k-1);
else                sprintf(temp,"0000%d",2*k-1);
if (2*k<10)         sprintf(temp1,"000000%d",2*k);
else if (2*k<100)   sprintf(temp1,"00000%d",2*k);
else                sprintf(temp1,"0000%d",2*k);
if (k<10)        {fprintf(memco,"     100       ","");fprintf(memco,"%d",k);}
else if (k<100)  {fprintf(memco,"     100      ","");fprintf(memco,"%d",k);}
else             {fprintf(memco,"     100     ","");fprintf(memco,"%d",k);}
fprintf(memco,"       1       1                       0        00000000D","");
fprintf(memco,"%s\n",temp);
fprintf(memco,"     100                       1                                        D","");
fprintf(memco,"%s\n",temp1);
d_lines+=2;
}

print_line_p_section(k,l)
int k,l;
{
char temp[90],temp1[30];
int len,i;
temp[0]=0;
fprintf(memco,"110,","");
sprintf(temp,"%f,%f,0.0,%f,%f,0.0;",mem[l][1],mem[l][2],mem[t(l+1,mer)][1],mem[t(l+1,mer)][2]);
len=strlen(temp);
if (2*k-1<10)       for(i=1;i<=67-len;i++) strcat(temp," ");
else if (2*k-1<100) for(i=1;i<=66-len;i++) strcat(temp," ");
else                for(i=1;i<=65-len;i++) strcat(temp," ");
sprintf(temp1,"%dP",2*k-1);
strcat(temp,temp1);
if (k<10)       sprintf(temp1,"000000%d",k);
else if (k<100) sprintf(temp1,"00000%d",k);
else            sprintf(temp1,"0000%d",k);
strcat(temp,temp1);
fprintf(memco,"%s\n",temp);
p_lines++;
}

print_arc_p_section(k,l,arc_direction)
int k,l,arc_direction;
{
char temp[90],temp1[30];
int len,i;
temp[0]=0;
fprintf(memco,"100,0.0,","");
if (arc_direction==1)
sprintf(temp,"%f,%f,%f,%f,%f,%f;",mem[l][4],mem[l][5],mem[l][1],mem[l][2],mem[t(l+1,mer)][1],mem[t(l+1,mer)][2]);
else
sprintf(temp,"%f,%f,%f,%f,%f,%f;",mem[l][4],mem[l][5],mem[t(l+1,mer)][1],mem[t(l+1,mer)][2],mem[l][1],mem[l][2]);
len=strlen(temp);
if (2*k-1<10)       for(i=1;i<=63-len;i++) strcat(temp," ");
else if (2*k-1<100) for(i=1;i<=62-len;i++) strcat(temp," ");
else                for(i=1;i<=61-len;i++) strcat(temp," ");
sprintf(temp1,"%dP",2*k-1);
strcat(temp,temp1);
if (k<10)       sprintf(temp1,"000000%d",k);
else if (k<100) sprintf(temp1,"00000%d",k);
else            sprintf(temp1,"0000%d",k);
strcat(temp,temp1);
fprintf(memco,"%s\n",temp);
p_lines++;
}


print_end()
{
char temp[90];
temp[0]=0;
fprintf(memco,"S0000002G","");
if (g_lines<10)       sprintf(temp,"000000%dD",g_lines);
else if (g_lines<100) sprintf(temp,"00000%dD",g_lines);
else                  sprintf(temp,"0000%dD",g_lines);
fprintf(memco,"%s",temp);
if (d_lines<10)       sprintf(temp,"000000%dP",d_lines);
else if (d_lines<100) sprintf(temp,"00000%dP",d_lines);
else                  sprintf(temp,"0000%dP",d_lines);
fprintf(memco,"%s",temp);
if (p_lines<10)       sprintf(temp,"000000%d",p_lines);
else if (p_lines<100) sprintf(temp,"00000%d",p_lines);
else                  sprintf(temp,"0000%d",p_lines);
fprintf(memco,"%s",temp);
fprintf(memco,"                                        T0000001\n");
}


