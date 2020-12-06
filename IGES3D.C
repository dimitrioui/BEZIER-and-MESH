#define begin {
#define end; }

#include "conio.h"
#include "stdio.h"
#include "ctype.h"
#include "process.h"
#include "string.h"
#include "math.h"
#include "dir.h"

void
      chdirr(),
      read_parametric_file(),
      read_mesh(),
      save_igs_file(),
      syndesmoi(),
      select_node(),
      print_line_d_section(),
      print_line_p_section(),
      print_end(),
      open_message_window(),
      close_message_window();

  int t(),ok(),check_file();

int no[9][1805],conect[1000][9];
float *cx,*cy,*cz;
int totnod,kk,exnod,numfreed,g_lines,d_lines,p_lines;
void *buf;
char filename[20];
char prg_dir[79],file_dir[79],drive1,drive2,directory[79];
char typ,drive;int intargc;
FILE *memco;

main(argc,argv)
int argc;
char *argv[];
begin
read_parametric_file();
strcpy(filename,argv[1]);intargc=argc;
clrscr();
open_message_window(20,20,60,24,5);gotoxy(2,2);cprintf("Please wait...");
read_mesh();
syndesmoi();
save_igs_file();
close_message_window(20,20,60,24,5);
free(cz);
free(cy);
free(cx);
end;

int  t(i,j)
int i,j;
{
if (i<=j) return(i);
return(i-j);
}


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


int check_file(name1)
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
 /*  chdirr(drive1,prg_dir);*/
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

void read_mesh()
begin
int i,j,jr,sum;float x,y,z;
char proname[5],let,name[20],name1[20],p[10],p1[10],p2[10];
/*chdirr(drive2,file_dir);*/
if (intargc<=1) strcpy(name1,"noname.num");
else begin
         strcpy(proname,".num");
	 strnset(name1,' ',20);
         strcpy(name1,filename);
         strncat(name1,proname,4);
	 strupr(name1);
end;
   if(check_file(name1)==0) exit(1);
fscanf(memco,"%5s",p);totnod=atoi(p);
fscanf(memco,"%5s",p);kk=atoi(p);
fscanf(memco,"%5s",p);exnod=atoi(p);
fclose(memco);
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
	/*	 chdirr(drive1,prg_dir);    */
		 exit(1);
}
/*---------------------------------------------------------------------------*/
if (intargc<=1) strcpy(name1,"noname.co");
else begin
	 strcpy(proname,".co");
         strnset(name1,' ',20);
         strcpy(name1,filename);
         strncat(name1,proname,3);
	 strupr(name1);
end;
   if(check_file(name1)==0) exit(1);
for(i=1;i<=totnod;i++)
begin
fscanf(memco,"%10s",p);
fscanf(memco,"%10s",p1);
fscanf(memco,"%10s",p2);
cx[i]=atof(p);cy[i]=atof(p1);cz[i]=atof(p2);
end;
fclose(memco);
if (intargc<=1) strcpy(name1,"noname.no");
else begin
         strcpy(proname,".no");
         strnset(name1,' ',20);
         strcpy(name1,filename);
         strncat(name1,proname,3);
	 strupr(name1);
end;
   if(check_file(name1)==0) exit(1);
for(i=1;i<=kk;i++)
begin
 fscanf(memco,"%5s",p);
 no[0][i]=atoi(p);
 for(j=1;j<=no[0][i];j++)
  begin
  fscanf(memco,"%5s",p);
  no[j][i]=atoi(p);
  end;
end;
fclose(memco);
/*chdirr(drive1,prg_dir);*/
end;



void save_igs_file()
{
char name[20];
int i,zz,j,counter;
/*chdirr(drive2,file_dir);*/
if (intargc<=1) strcpy(name,"noname.igs");
else {strcpy(name,filename);strcat(name,".igs");}
if (!(memco=fopen(name,"w+")))
{
gotoxy(1,1);printf(" Could not open file ");
gotoxy(1,2);printf(" Press any ket to return");
getch();
clrscr();
/*chdirr(drive1,prg_dir);*/
exit(1);
}
/*---------------------------------------------------------------------------*/
fprintf(memco,"IGES file generated from a JDIMITRIOU MESH  by the IGES                 S0000001\n","");
fprintf(memco,"translator                    , translator version IGESOUT-2.0.         S0000002\n","");
fprintf(memco,",,1HY,5HY.IGS,10HAutoCAD-10,11HIGESOUT-2.0,16,38,6,99,15,1HY,1.0,1,4HINCG0000001\n","");
fprintf(memco,"H,32767,3.2767D1,13H910319.190735,1.0D-8,7.0,6HThroop,14HAutodesk, Inc.,G0000002\n","");
g_lines=2;
/*---------------------------------------------------------------------------*/
/*
counter=0;
for(zz=1;zz<=kk;zz++)
 for(j=1;j<=no[0][zz];j++)
 {
   if (no[j][zz]<no[t(j+1,no[0][zz])][zz])
       {counter++;print_line_d_section(counter);}
}
counter=0;
for(zz=1;zz<=kk;zz++)
 for(j=1;j<=no[0][zz];j++)
 {
   if (no[j][zz]<no[t(j+1,no[0][zz])][zz])
       {counter++;print_line_p_section(counter,j,zz);}
}
*/
counter=0;
for(i=1;i<=totnod;i++)
 for(j=1;j<=conect[i][0];j++)
   {
     if (i<conect[i][j])
	{counter++;print_line_d_section(counter);}
   }
counter=0;
for(i=1;i<=totnod;i++)
 for(j=1;j<=conect[i][0];j++)
   {
     if (i<conect[i][j])
	{counter++;print_line_p_section(counter,i,conect[i][j]);}
   }
/*---------------------------------------------------------------------------*/
print_end();

fclose(memco);
/*chdirr(drive1,prg_dir);*/
}


void print_line_d_section(k)
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

 void print_line_p_section(k,l1,l2)
int k,l1,l2;
{
char temp[90],temp1[30];
int len,i;
temp[0]=0;
fprintf(memco,"110,","");
sprintf(temp,"%f,%f,%f,%f,%f,%f;",cx[l1],cy[l1],cz[l1],cx[l2],cy[l2],cz[l2]);
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

void print_end()
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



/*---------------------------------------------------------------------------*/
/*   E Y R E S H   K O M B W N   S Y N D E D E M E N W N  M E   K O M B O    */
/*---------------------------------------------------------------------------*/
void syndesmoi()
begin
int i,i1,i2,zz,k,k1,k2,j;
for(i=1;i<=totnod;i++) conect[i][0]=0;
for(k=1;k<=totnod;k++)
for(zz=1;zz<=kk;zz++)
for(i=1;i<=no[0][zz];i++)
if (no[i][zz]==k)
  begin
  i1=t(i+1,no[0][zz]);k1=no[i1][zz];
  i2=t(i+no[0][zz]-1,no[0][zz]);k2=no[i2][zz];
  if( ok(k,k1)==1 )select_node(k,k1);
  if( ok(k,k2)==1 )select_node(k,k2);
  end;
end;
/*---------------------------------------------------------------------------*/
int  ok(io,i1)
int io,i1;
{
int i;
 if (conect[io][0]==0) return(1);
 for(i=1;i<=conect[io][0];i++)
 if (conect[io][i]==i1) return(0);
 return(1);
}

void select_node(k,k1)
int k,k1;
{
   conect[k][0]+=1;
   conect[k][conect[k][0]]=k1;
 }







