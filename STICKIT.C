#define  begin {
#define  end ;  }


	     /* LIBRARIES INCLUDED */

#include <stdlib.h>
#include <graphics.h>
#include <stdio.h>
#include <math.h>


	      /* VOID ROUTINE(S) DEFINITION */

void change_sec_surf(),
     save_sec_surf();


	      /* INT ROUTINE(S) DEFINITION */

int load_first_surf(),
    load_sec_surf();


	     /* GLOBAL VARIABLES */

FILE *mem ;
float bxf[4][4],byf[4][4],bzf[4][4];      /* The points of the first patch */
float bxs[4][4],bys[4][4],bzs[4][4];     /* The points of the second patch */
float dx[4][4][3],dy[4][4][3],dz[4][4][3];   /* Diference between points in */
						   /* the second patch */


main()
begin
clrscr();
if(load_first_surf()!=0);
if(load_sec_surf()!=0);
change_sec_surf();
save_sec_surf();
end ;


	       /* Loading the first patch */

int load_first_surf()
begin
char name[16],px[10],py[10],pz[10] ;
int i,j ;
clrscr();
printf("   Give the name of the first file\n") ;
scanf("%s",&name) ;
if((mem=fopen(name,"r"))==0)
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
 fscanf(mem,"%10s",px); bxf[i][j]=atof(px);
 fscanf(mem,"%10s",py); byf[i][j]=atof(py);
 fscanf(mem,"%10s",pz); bzf[i][j]=atof(pz);
  end ;
 end ;
fclose(mem);
return(1);

end ;

	       /* Loading the second patch */

int load_sec_surf()
begin
char name[16],px[10],py[10],pz[10] ;
int i,j ;
printf("   Give the name of the second file\n") ;
scanf("%s",&name) ;
if((mem=fopen(name,"r"))==0)
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
 fscanf(mem,"%10s",px); bxs[i][j]=atof(px);
 fscanf(mem,"%10s",py); bys[i][j]=atof(py);
 fscanf(mem,"%10s",pz); bzs[i][j]=atof(pz);
   end ;
  end ;
fclose(mem);

return(1);


end ;


	/* Stick the second patch to one side of the first */

void change_sec_surf()
begin
char name[16],px[10],py[10],pz[10] ;
int side,side_sec ;
int u1,u2,u3,u4,u5,u6,u7,u8 ;
int v1,v2,v3,v4,v5,v6,v7,v8 ;
int sec_u1,sec_u2,sec_u3,sec_u4 ;
int sec_v1,sec_v2,sec_v3,sec_v4 ;
int i,j ;
float l,m0,m1 ;

printf("Give the number of side of the 1st patch you want to compose:");
scanf("%d",&side);
printf("Give the number of side of the 2nd patch you want to compose:");
scanf("%d",&side_sec);


    if(side==1)
    begin
     u1=u2=u3=u4=0;
     u5=u6=u7=u8=1;
     v1=v5=3;
     v2=v6=2;
     v3=v7=1;
     v4=v8=0;
    end ;


    if(side==2)
    begin
     v1=v2=v3=v4=0;
     v5=v6=v7=v8=1;
     u1=u5=0;
     u2=u6=1;
     u3=u7=2;
     u4=u8=3;
    end ;


    if(side==3)
    begin
     v1=v2=v3=v4=3;
     v5=v6=v7=v8=2;
     u1=u5=3;
     u2=u6=2;
     u3=u7=1;
     u4=u8=0;
    end ;


    if(side==4)
    begin
     u1=u2=u3=u4=3;
     u5=u6=u7=u8=2;
     v1=v5=0;
     v2=v6=1;
     v3=v7=2;
     v4=v8=3;
    end ;

	 if(side_sec==1)
	 begin
	  sec_u1=sec_u2=sec_u3=sec_u4=1;
	  sec_v1=0;sec_v2=1;sec_v3=2;sec_v4=3;
	 end ;

	 if(side_sec==2)
	 begin
	  sec_v1=sec_v2=sec_v3=sec_v4=1;
	  sec_u1=3;sec_u2=2;sec_u3=1;sec_u4=0;
	 end ;

	  if(side_sec==4)
	 begin
	  sec_u1=sec_u2=sec_u3=sec_u4=2;
	  sec_v1=3;sec_v2=2;sec_v3=1;sec_v4=0;
	 end ;

	 if(side_sec==3)
	 begin
	  sec_v1=sec_v2=sec_v3=sec_v4=2;
	  sec_u1=0;sec_u2=1;sec_u3=2;sec_u4=3;
	 end ;


for( i=0;i<=2;i++)
for (j=0;j<=3;j++)
{
dx[i][j][1]=bxs[i+1][j]-bxs[i][j];
dy[i][j][1]=bys[i+1][j]-bys[i][j];
dz[i][j][1]=bzs[i+1][j]-bzs[i][j];
}

for( i=0;i<=3;i++)
for (j=0;j<=2;j++)
{
dx[i][j][2]=bxs[i][j+1]-bxs[i][j];
dy[i][j][2]=bys[i][j+1]-bys[i][j];
dz[i][j][2]=bzs[i][j+1]-bzs[i][j];
}


	     /*   works    4,1   */
if((side==4) && (side_sec==1))
{
for(i=0;i<=3;i++)
  {
bxs[0][i]=bxf[3][i];
bys[0][i]=byf[3][i];
bzs[0][i]=bzf[3][i];
  }

for(i=0;i<=2;i++)
for (j=0;j<=3;j++)
  {
bxs[i+1][j]=bxs[i][j]+dx[i][j][1];
bys[i+1][j]=bys[i][j]+dy[i][j][1];
bzs[i+1][j]=bzs[i][j]+dz[i][j][1];
  }
}

if((side==4) && (side_sec==2))
{
for(i=0;i<=3;i++)
for(j=3;j>=0;j--)
bxs[j][0]=bxf[3][i];
bys[j][0]=byf[3][i];
bzs[j][0]=bzf[3][i];
}
if((side==4) && (side_sec==3))
{
for(i=0;i<=3;i++)
bxs[i][3]=bxf[3][i];
bys[i][3]=byf[3][i];
bzs[i][3]=bzf[3][i];
}
if((side==4) && (side_sec==4))
{
for(i=0;i<=3;i++)
for(j=3;j>=0;j--)
bxs[0][j]=bxf[3][i];
bys[0][j]=byf[3][i];
bzs[0][j]=bzf[3][i];
}

if((side==3) && (side_sec==1))
{
for(j=3;j>=0;j--)
for(i=0;i<=3;i++)
bxs[0][i]=bxf[j][3];
bys[0][i]=byf[j][3];
bzs[0][i]=bzf[j][3];
}
		  /*   works 3,2   */

if((side==3) && (side_sec==2))
{
for(i=0;i<=3;i++)
  {
bxs[i][0]=bxf[i][3];
bys[i][0]=byf[i][3];
bzs[i][0]=bzf[i][3];
  }
for (i=0;i<=3;i++)
for (j=0;j<=2;j++)
  {
bxs[i][j+1]=bxs[i][j]+dx[i][j][2];
bys[i][j+1]=bys[i][j]+dy[i][j][2];
bzs[i][j+1]=bzs[i][j]+dz[i][j][2];
  }
}
if((side==3) && (side_sec==3))
{
for(i=0;i<=3;i++)
bxs[i][3]=bxf[i][3];
bys[i][3]=byf[i][3];
bzs[i][3]=bzf[i][3];
}
if((side==3) && (side_sec==4))
{
for(i=0;i<=3;i++)
for(j=3;j<=3;j--)
bxs[0][j]=bxf[3][i];
bys[0][j]=byf[3][i];
bzs[0][j]=bzf[3][i];
}

if((side==2) && (side_sec==1))
{
for(i=0;i<=3;i++)
bxs[0][i]=bxf[3][i];
bys[0][i]=byf[3][i];
bzs[0][i]=bzf[3][i];
}

if((side==2) && (side_sec==2))
{
for(i=0;i<=3;i++)
for(j=3;j<=0;j--)
bxs[j][0]=bxf[3][i];
bys[j][0]=byf[3][i];
bzs[j][0]=bzf[3][i];
}
		/*    works 2,3    */

if((side==2) && (side_sec==3))
{
for(i=0;i<=3;i++)
  {
bxs[i][3]=bxf[i][0];
bys[i][3]=byf[i][0];
bzs[i][3]=bzf[i][0];
  }
for(i=0;i<=3;i++)
for (j=2;j>=0;j--)
  {
bxs[i][j]=bxs[i][j+1]-dx[i][j][2];
bys[i][j]=bys[i][j+1]-dy[i][j][2];
bzs[i][j]=bzs[i][j+1]-dz[i][j][2];
  }
}


if((side==2) && (side_sec==4))
{
for(i=0;i<=3;i++)
for(j=3;j<=3;j--)
bxs[0][j]=bxf[3][i];
bys[0][j]=byf[3][i];
bzs[0][j]=bzf[3][i];
}

if((side==1) && (side_sec==1))
{
for(i=0;i<=3;i++)
bxs[0][i]=bxf[3][i];
bys[0][i]=byf[3][i];
bzs[0][i]=bzf[3][i];
}

if((side==1) && (side_sec==2))
{
for(i=0;i<=3;i++)
for(j=3;j<=0;j--)
bxs[j][0]=bxf[3][i];
bys[j][0]=byf[3][i];
bzs[j][0]=bzf[3][i];
}
if((side==1) && (side_sec==3))
{
for(i=0;i<=3;i++)
bxs[i][3]=bxf[3][i];
bys[i][3]=byf[3][i];
bzs[i][3]=bzf[3][i];
}
		/*   works 1,4  */

if((side==1) && (side_sec==4))
{
for(i=0;i<=3;i++)
  {
bxs[3][i]=bxf[0][i];
bys[3][i]=byf[0][i];
bzs[3][i]=bzf[0][i];
  }
for (i=2;i>=0;i--)
for (j=0;j<=3;j++)
  {
bxs[i][j]=bxs[i+1][j]-dx[i][j][1];
bys[i][j]=bys[i+1][j]-dy[i][j][1];
bzs[i][j]=bzs[i+1][j]-dz[i][j][1];
  }
}



end ;

	   /*Saves the new patch with the old geometry */

void save_sec_surf()
begin
char name[16],bname[16],px[10],py[10],pz[10] ;
int i,j ;
clrscr();
printf("   Give the name of the changed file\n") ;
scanf("%s",&name) ;
getch();
mem=fopen(name,"w+");

for(i=0;i<=3;i++)
  begin
for(j=0;j<=3;j++)
   begin
 sprintf(px,"%10.5f",bxs[i][j]);
 fprintf(mem,"%10s",px);
 sprintf(py,"%10.5f",bys[i][j]);
 fprintf(mem,"%10s",py);
 sprintf(pz,"%10.5f",bzs[i][j]);
 fprintf(mem,"%10s",pz);
 fprintf(mem,"\n","");
  end ;
   end ;
fclose(mem);

end ;



