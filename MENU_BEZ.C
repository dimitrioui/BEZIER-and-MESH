#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <dir.h>
#include <process.h>
#include <ctype.h>
#define begin {
#define end   }


void read_parametric_file(),
     open_message_window(),
     close_message_window(),
     make_window(),
     menu1();

void *buf;
FILE *mem ;
char filename[16],prg_dir[79],file_dir[79];






main()

begin
loopmenu1:
menu1();
open_message_window(20,20,60,24,5);
 close_message_window(20,20,60,24,5);
 goto loopmenu1;

end


void menu1()
{
char ch;int i,j,epilogh;char name[20],menu[10][40];
/*-------------------------- ORISMOS  EPILOGWN --------------------------*/
loop1:window(1,1,80,25);textbackground(4);clrscr();textcolor(0);
window(1,1,80,25);
textbackground(3);
gotoxy(1,2);
cprintf("                            BEZIER THREE DIMENSIONAL CAD                        ");
textbackground(0);
strcpy(menu[1]," BEZIER SURF ");
strcpy(menu[2]," STICKIT     ");
strcpy(menu[3]," COMPOSE     ");
strcpy(menu[4]," TEST GRAPH  ");
strcpy(menu[5]," MAKE MESH   ");
strcpy(menu[6]," GRAPH MESH  ");
strcpy(menu[7]," MAKE IGES3D ");
strcpy(menu[8]," BEZIER CURVE");
strcpy(menu[9]," QUIT        ");
/*------------------------------------------------------------------------*/
textcolor(15);
make_window(20,5,60,23,3);
/*------------------------------------------------------------------------*/
for(i=9;i>=1;i--)
 {
   if (i==1) textbackground(1);
   else      textbackground(3);
   gotoxy(10,2*i);cprintf("%s",menu[i]);
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
		    gotoxy(10,epilogh*2);cprintf("%s",menu[epilogh]);
		    epilogh+=-1;
		    textbackground(1);
		    gotoxy(10,epilogh*2);cprintf("%s",menu[epilogh]);
		  }
	   break;
case 80 : if (epilogh<9)
		 {
		    textbackground(3);
		    gotoxy(10,epilogh*2);cprintf("%s",menu[epilogh]);
		    epilogh+=1;
		    textbackground(1);
		    gotoxy(10,epilogh*2);cprintf("%s",menu[epilogh]);
		  }
	   break;
case 71 : if (epilogh!=1)
		 {
		    textbackground(3);
		    gotoxy(10,epilogh*2);cprintf("%s",menu[epilogh]);
		    epilogh=1;
		    textbackground(1);
		    gotoxy(10,epilogh*2);cprintf("%s",menu[epilogh]);
		  }
	   break;
case 79 : if (epilogh!=9)
		 {
		    textbackground(3);
		    gotoxy(10,epilogh*2);cprintf("%s",menu[epilogh]);
		    epilogh=9;
		    textbackground(1);
		    gotoxy(10,epilogh*2);cprintf("%s",menu[epilogh]);
		  }
	   break;
default :  break;
}
}
}
while(toascii(ch)!=13);

switch(epilogh)
{
case 1:system("bezier.exe");break;
case 2:system("stickit.exe");break;
case 3:system("compose.exe");break;
case 4:system("graph_co.exe");break;
case 5:system("make_mes.exe");break;
case 6:gotoxy(1,24);printf(" filename ? ");scanf("%s",filename);spawnl(P_WAIT,"grbez.exe","",filename,NULL);break;
case 7:gotoxy(1,26);printf(" filename ? ");scanf("%s",filename);spawnl(P_WAIT,"iges3d.exe","",filename,NULL);break;
case 8:system("curvebez.exe");break;
case 9:exit(1);
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
   printf("     Press any key ");getch();
   exit(1);
  }
  fscanf(mem,"%s",prg_dir);
  fscanf(mem,"%s",file_dir);
  fclose(mem);

}




