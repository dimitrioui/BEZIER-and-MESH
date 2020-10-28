#include <stdlib.h>
#include <graphics.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <conio.h>
#include <process.h>
#include <ctype.h>
#define  begin {
#define  end;  }
#define PI 3.14159


void open_message_window(int left,int top,int right,int botom,int bcolor),
     close_message_window(int left,int top,int right,int botom,int bcolor),
     translate_to_ascii_files(),
     save_mesh_data(),
     make_no(),
     give_names(),
     load_patches();

FILE *memco ;
int outnod[400] ;
float r_vector[21][21][3],cx[500],cy[500],cz[500] ;
int NOP1,NOP2;  /* Number Of Points */
int patches;
char nams[26][26];
int num_of_files;
int kk,nv,nh,exnod,totnod ;
int no[4][400];
char filename[16];
void *buf;
main()

begin
char com_nam[26];
int counter1,counter2,i;
clrscr();
give_names();
gotoxy(15,15);
printf("give the final filename:");scanf("%s",filename);
for(patches=1;patches<=num_of_files;patches++)
begin
strcpy(com_nam,nams[patches]);
load_patches(com_nam);
i=1;
for(counter1=0;counter1<=NOP1;counter1++)
  begin
for(counter2=0;counter2<=NOP2;counter2++)
   begin
cx[i]=r_vector[counter1][counter2][0];
cy[i]=r_vector[counter1][counter2][1];
cz[i]=r_vector[counter1][counter2][2];
i=i+1;
   end;
  end;
nh=NOP1+1;nv=NOP2+1;
make_no();
save_mesh_data();
clrscr();
spawnl(P_WAIT,"unitsurf.exe","",filename,NULL);

end;  translate_to_ascii_files();
end;


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
printf("You gave (%d) file(s)",num_of_files);getch();

end;



void load_patches (com_nam)
char com_nam[26];
begin
int counter1,counter2;
char name[16],rx[10],ry[10],rz[10] ;
char NOPA1[4],NOPA2[4];
clrscr();
open_message_window(20,2,60,5,5);
gotoxy(2,2);
cprintf("the current file is:");
gotoxy(25,2);
cprintf("%s",com_nam);
memco=fopen(com_nam,"r");

fscanf(memco,"%4s",NOPA1); NOP1=atoi(NOPA1);
fscanf(memco,"%4s",NOPA2); NOP2=atoi(NOPA2);

for(counter1=0;counter1<= NOP1;counter1++)
 begin
for(counter2=0;counter2<= NOP2;counter2++)
  begin

 fscanf(memco,"%10s",rx); r_vector[counter1][counter2][0]=atof(rx);
 fscanf(memco,"%10s",ry); r_vector[counter1][counter2][1]=atof(ry);
 fscanf(memco,"%10s",rz); r_vector[counter1][counter2][2]=atof(rz);
 fscanf(memco,"\n","");
  end;
    end;
fclose(memco);
close_message_window(20,2,60,5,5);
end;


void save_mesh_data()
begin
int jr,i,j;
float x,y,z;
memco=fopen("meshco_areas","wb+");
for(i=1;i<=totnod;i++)
begin
x=cx[i];y=cy[i];z=cz[i];
fwrite(&x,sizeof(float),1,memco);
fwrite(&y,sizeof(float),1,memco);
fwrite(&z,sizeof(float),1,memco);
end;
fclose(memco);
memco=fopen("meshno_areas","wb+");
for(i=1;i<=kk;i++)
for(j=1;j<=3;j++)
begin
jr=no[j][i];
fwrite(&jr,sizeof(int),1,memco);
end;
fclose(memco);
memco=fopen("meshout_areas","wb+");
for(i=1;i<=exnod;i++)
begin
jr=outnod[i];
fwrite(&jr,sizeof(int),1,memco);
end;
fclose(memco);
memco=fopen("meshnum_areas","wb+");
jr=totnod;fwrite(&jr,sizeof(int),1,memco);
jr=kk;fwrite(&jr,sizeof(int),1,memco);
jr=exnod;fwrite(&jr,sizeof(int),1,memco);
fclose(memco);
end;


/*---------------------------C. A. D.---------------------------------------*/
void make_no()
begin
int jr,i,j,z,n,zz,xx,ll,a,sum;

kk=2*(nv-1)*(nh-1);
n=nh*nv;

for(j=1;j<=n;j++)
for(i=1;i<=3;i++) no[i][j]=0;
 no[1][1]=1;
 no[2][1]=2;
 no[3][1]=nv+1;
 no[1][2]=2;
 no[2][2]=nv+2;
 no[3][2]=nv+1;
 z=1;
for(j=3;j<=kk-1;j++)
begin
if (j > 3) j=j+1;
if (j>kk-1) goto loop1560;
z=z+1;
for(i=1;i<=3;i++)
begin
if (z==nv) begin
  no[i][j]=no[i][j-2]+2;
  no[i][j+1]=no[i][j-1]+2;
  goto loop1530;
  end;
no[i][j]=no[i][j-2]+1;
no[i][j+1]=no[i][j-1]+1;
loop1530:end;
no[3][1]=nv+2;no[1][2]=nv+2;no[2][2]=nv+1;no[3][2]=1;
no[3][kk-1]=no[3][kk-1]+1;no[1][kk]=no[2][kk];no[2][kk]=no[3][kk];no[3][kk]=no[1][kk-1];
if (z==nv) z=1;
loop1560:end;
outnod[1]=1;
ll=nh+nv-1;xx=(nv*nh)-(nv-1);
for(i=2;i<=ll;i++)
begin
if ( (outnod[i-1]+nv)>=1 && (outnod[i-1]+nv)<=xx )
begin
outnod[i]=outnod[i-1]+nv;goto loop3000;end;
if ( (outnod[i-1]+1)>xx &&  (outnod[i-1]+1)<=nh*nv )
begin
outnod[i]=outnod[i-1]+1;goto loop3000;end;
loop3000:end;
for(i=1;i<=nh-1;i++) outnod[ll+i]=outnod[ll+i-1]-nv;
for(i=1;i<=nv-2;i++) outnod[i+ll+nh-1]=outnod[i-1+ll+nh-1]-1;
ll=2*nh+2*nv-4;
exnod=2*(nv+nh)-4;
totnod=n;
end;



/*-------------------------------------------------------------------------*/
/*------------------   TRANSLATION   FROM   BIN  TO ASCII -----------------*/
/*-------------------------------------------------------------------------*/

void translate_to_ascii_files()
begin
int jr,*no,i,j;float xo,yo,zo,*x,*y,*z;
char name[20],name1[20],name2[20],name3[20],p[30];

strcpy(name,filename);strcat(name,".no");strcpy(name1,filename);strcat(name1,".co");
      strcpy(name2,filename);strcat(name2,".out");strcpy(name3,filename);strcat(name3,".num");
/*------------------- TRANSLATE  ' N '  FILE -----------------------------*/
if (!(memco=fopen(name3,"r+b")))
{
printf("file does not exist--3---");getch();
exit(1);
}
 fread(&totnod,sizeof(int),1,memco);
 fread(&kk,sizeof(int),1,memco);
 fread(&exnod,sizeof(int),1,memco);
fclose(memco);
memco=fopen(name3,"w+");
itoa(totnod,p,10);fprintf(memco,"%5s",p);
itoa(kk,p,10);fprintf(memco,"%5s",p);
itoa(exnod,p,10);fprintf(memco,"%5s",p);
fclose(memco);
/*-----------------   M E M O R Y   O V E R F L O W  ------------------------*/
if ( (!(x=(float *)calloc((totnod+1),sizeof(float)))) ||
     (!(y=(float *)calloc((totnod+1),sizeof(float)))) ||
     (!(z=(float *)calloc((totnod+1),sizeof(float))))
      )
{
		 gotoxy(2,4);
		 printf("TOTNOD=%d   ",totnod);
		 getch();
		 exit(1);
}
/*---------------------------------------------------------------------------*/
/*------------------- TRANSLATE  ' J '  FILE -----------------------------*/
if (!(memco=fopen(name1,"r+b")))
{
printf("file does not exist--4--");
getch();exit(1);
}
for(i=1;i<=totnod;i++)
begin
 fread(&xo,sizeof(float),1,memco);
 fread(&yo,sizeof(float),1,memco);
 fread(&zo,sizeof(float),1,memco);
 x[i]=xo;y[i]=yo;z[i]=zo;
end;
fclose(memco);
memco=fopen(name1,"w+");
for(i=1;i<=totnod;i++)
begin
sprintf(p,"%10.5f",x[i]);      /* length of float number */
fprintf(memco,"%10s",p);
sprintf(p,"%10.5f",y[i]);
fprintf(memco,"%10s",p);
sprintf(p,"%10.5f",z[i]);
fprintf(memco,"%10s",p);
fprintf(memco,"\n","");
end;
fclose(memco);
free(z);free(y);free(x);
/*-----------------   M E M O R Y   O V E R F L O W  ------------------------*/
if ( (!(no=(int *)calloc((4*kk+4),sizeof(int)))) )
{
		 gotoxy(2,4);
		 printf("   ELEM=%d  ",kk);
		 getch();
		 exit(1);
}
/*---------------------------------------------------------------------------*/
/*------------------- TRANSLATE  ' I '  FILE -----------------------------*/
if (!(memco=fopen(name,"r+b")))
{
printf("file does not exist--5--");
getch();exit(1);
}
for(i=1;i<=kk;i++)
 for(j=1;j<=4;j++)
begin
 fread(&jr,sizeof(int),1,memco);
 no[j+4*(i-1)]=jr;
end;
fclose(memco);
memco=fopen(name,"w+");
for(i=1;i<=kk;i++)
begin
 for(j=1;j<=4;j++)
 begin
  itoa(no[j+4*(i-1)],p,10);
  fprintf(memco,"%5s",p);
 end;
fprintf(memco,"\n","");
end;
fclose(memco);
/*------------------- TRANSLATE  ' D '  FILE -----------------------------*/
if (!(memco=fopen(name2,"r+b")))
{
printf("file does not exist-66---");
getch();exit(1);
}
for(i=1;i<=exnod;i++)
begin
 fread(&jr,sizeof(int),1,memco);
 no[i]=jr;
end;
fclose(memco);
memco=fopen(name2,"w+");
for(i=1;i<=exnod;i++)
begin
itoa(no[i],p,10);
fprintf(memco,"%5s",p);
fprintf(memco,"\n","");
end;
fclose(memco);
free(no);
end;






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

