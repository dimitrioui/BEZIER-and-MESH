#include <stdlib.h>
#include <graphics.h>
#include <stdio.h>
#include <math.h>
#define  begin {
#define  end  }

void change_sec_surf(),
     save_sec_surf();


FILE *mem ;
float bxf[4][4],byf[4][4],bzf[4][4];
float bxs[4][4],bys[4][4],bzs[4][4];

main()
begin
clrscr();
if(load_first_surf()!=0);
if(load_sec_surf()!=0);
change_sec_surf();
save_sec_surf();
end


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
end

for(i=0;i<=3;i++)
 begin
for(j=0;j<=3;j++)
  begin
 fscanf(mem,"%10s",px); bxf[i][j]=atof(px);
 fscanf(mem,"%10s",py); byf[i][j]=atof(py);
 fscanf(mem,"%10s",pz); bzf[i][j]=atof(pz);
  end
 end
fclose(mem);
return(1);
end


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
end

for(i=0;i<=3;i++)
 begin
for(j=0;j<=3;j++)
  begin
 fscanf(mem,"%10s",px); bxs[i][j]=atof(px);
 fscanf(mem,"%10s",py); bys[i][j]=atof(py);
 fscanf(mem,"%10s",pz); bzs[i][j]=atof(pz);
   end
  end
fclose(mem);

return(1);


end




void change_sec_surf()
begin
char name[16],px[10],py[10],pz[10] ;
int side,side_sec ;
int side_u1,side_u2,side_u3,side_u4,side_u5,side_u6,side_u7,side_u8 ;
int side_v1,side_v2,side_v3,side_v4,side_v5,side_v6,side_v7,side_v8 ;
int side_sec_u1,side_sec_u2,side_sec_u3,side_sec_u4 ;
int side_sec_v1,side_sec_v2,side_sec_v3,side_sec_v4 ;
int i,j ;
float l,m0,m1 ;

printf("Give the number of side of the 1st patch you want to compose:");
scanf("%d",&side);
printf("Give the number of side of the 2nd patch you want to compose:");
scanf("%d",&side_sec);


    if(side==1)
    begin
     side_u1=side_u2=side_u3=side_u4=0;
     side_u5=side_u6=side_u7=side_u8=1;
     side_v1=side_v5=3;
     side_v2=side_v6=2;
     side_v3=side_v7=1;
     side_v4=side_v8=0;
    end


    if(side==2)
    begin
     side_v1=side_v2=side_v3=side_v4=0;
     side_v5=side_v6=side_v7=side_v8=1;
     side_u1=side_u5=0;
     side_u2=side_u6=1;
     side_u3=side_u7=2;
     side_u4=side_u8=3;
    end


    if(side==3)
    begin
     side_v1=side_v2=side_v3=side_v4=3;
     side_v5=side_v6=side_v7=side_v8=2;
     side_u1=side_u5=3;
     side_u2=side_u6=2;
     side_u3=side_u7=1;
     side_u4=side_u8=0;
    end


    if(side==4)
    begin
     side_u1=side_u2=side_u3=side_u4=3;
     side_u5=side_u6=side_u7=side_u8=2;
     side_v1=side_v5=0;
     side_v2=side_v6=1;
     side_v3=side_v7=2;
     side_v4=side_v8=3;
    end

	 if(side_sec==1)
	 begin
	  side_sec_u1=side_sec_u2=side_sec_u3=side_sec_u4=1;
	  side_sec_v1=0;side_sec_v2=1;side_sec_v3=2;side_sec_v4=3;
	 end

	 if(side_sec==2)
	 begin
	  side_sec_v1=side_sec_v2=side_sec_v3=side_sec_v4=1;
	  side_sec_u1=3;side_sec_u2=2;side_sec_u3=1;side_sec_u4=0;
	 end

	  if(side_sec==4)
	 begin
	  side_sec_u1=side_sec_u2=side_sec_u3=side_sec_u4=2;
	  side_sec_v1=3;side_sec_v2=2;side_sec_v3=1;side_sec_v4=0;
	 end

	 if(side_sec==3)
	 begin
	  side_sec_v1=side_sec_v2=side_sec_v3=side_sec_v4=2;
	  side_sec_u1=0;side_sec_u2=1;side_sec_u3=2;side_sec_u4=3;
	 end


printf("Give l:");  scanf("%f",&l);
printf("Give m0:"); scanf("%f",&m0);
printf("Give m1:"); scanf("%f",&m1);

	     /*  TRANSFORMATION OF X COORDINATES  */

bxs[side_sec_u1][side_sec_v1]=bxf[side_u1][side_v1]+
			      l*(bxf[side_u1][side_v1]-
			      bxf[side_u5][side_v5])+
			      m0*(bxf[side_u2][side_v2]-
			      bxf[side_u1][side_v1]) ;
bxs[side_sec_u2][side_sec_v2]=bxf[side_u2][side_v2]+
			      l*(bxf[side_u2][side_v2]-
			      bxf[side_u6][side_v6])+
			      (1/3)*m0*(2*bxf[side_u3][side_v3]-
			      bxf[side_u2][side_v2]-
			      bxf[side_u1][side_v1])+
			      (1/3)*m1*(bxf[side_u2][side_v2]-
			      bxf[side_u1][side_v1]);
bxs[side_sec_u3][side_sec_v3]=bxf[side_u3][side_v3]+
			      l*(bxf[side_u3][side_v3]-
			      bxf[side_u7][side_v7])+
			      (1/3)*m0*(bxf[side_u4][side_v4]+
			      bxf[side_u3][side_v3]-
			      2*bxf[side_u2][side_v2])+
			      (2/3)*m1*(bxf[side_u3][side_v3]-
			      bxf[side_u2][side_v2]);
bxs[side_sec_u4][side_sec_v4]=bxf[side_u4][side_v4]+
			      l*(bxf[side_u4][side_v4]-
			      bxf[side_u8][side_v8])+
			      (m0+m1)*(bxf[side_u4][side_v4]-
			      bxf[side_u3][side_v3]);

	     /*  TRANSFORMATION OF Y COORDINATES  */

bys[side_sec_u1][side_sec_v1]=byf[side_u1][side_v1]+
			      l*(byf[side_u1][side_v1]-
			      byf[side_u5][side_v5])+
			      m0*(byf[side_u2][side_v2]-
			      byf[side_u1][side_v1]) ;
bys[side_sec_u2][side_sec_v2]=byf[side_u2][side_v2]+
			      l*(byf[side_u2][side_v2]-
			      byf[side_u6][side_v6])+
			      (1/3)*m0*(2*byf[side_u3][side_v3]-
			      byf[side_u2][side_v2]-
			      byf[side_u1][side_v1])+
			      (1/3)*m1*(byf[side_u2][side_v2]-
			      byf[side_u1][side_v1]);
bys[side_sec_u3][side_sec_v3]=byf[side_u3][side_v3]+
			      l*(byf[side_u3][side_v3]-
			      byf[side_u7][side_v7])+
			      (1/3)*m0*(byf[side_u4][side_v4]+
			      byf[side_u3][side_v3]-
			      2*byf[side_u2][side_v2])+
			      (2/3)*m1*(byf[side_u3][side_v3]-
			      byf[side_u2][side_v2]);
bys[side_sec_u4][side_sec_v4]=byf[side_u4][side_v4]+
			      l*(byf[side_u4][side_v4]-
			      byf[side_u8][side_v8])+
			      (m0+m1)*(byf[side_u4][side_v4]-
			      byf[side_u3][side_v3]);

	     /*  TRANSFORMATION OF Z COORDINATES  */

bzs[side_sec_u1][side_sec_v1]=bzf[side_u1][side_v1]+
			      l*(bzf[side_u1][side_v1]-
			      bzf[side_u5][side_v5])+
			      m0*(bzf[side_u2][side_v2]-
			      bzf[side_u1][side_v1]) ;
bzs[side_sec_u2][side_sec_v2]=bzf[side_u2][side_v2]+
			      l*(bzf[side_u2][side_v2]-
			      bzf[side_u6][side_v6])+
			      (1/3)*m0*(2*bzf[side_u3][side_v3]-
			      bzf[side_u2][side_v2]-
			      bzf[side_u1][side_v1])+
			      (1/3)*m1*(bzf[side_u2][side_v2]-
			      bzf[side_u1][side_v1]);
bzs[side_sec_u3][side_sec_v3]=bzf[side_u3][side_v3]+
			      l*(bzf[side_u3][side_v3]-
			      bzf[side_u7][side_v7])+
			      (1/3)*m0*(bxf[side_u4][side_v4]+
			      bxf[side_u3][side_v3]-
			      2*bxf[side_u2][side_v2])+
			      (2/3)*m1*(bxf[side_u3][side_v3]-
			      bxf[side_u2][side_v2]);
bzs[side_sec_u4][side_sec_v4]=bzf[side_u4][side_v4]+
			      l*(bzf[side_u4][side_v4]-
			      bzf[side_u8][side_v8])+
			      (m0+m1)*(bzf[side_u4][side_v4]-
			      bzf[side_u3][side_v3]);


end

void save_sec_surf()
begin
char name[16],bname[16],px[10],py[10],pz[10] ;
int i,j ;
clrscr();
printf("   Give the name of the changed file\n") ;
scanf("%s",&name) ;
/*strcpy(name,"c");*/
/*strcat(name,bname); printf("%s\n",name);*/getch();
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
  end
   end
fclose(mem);

end



