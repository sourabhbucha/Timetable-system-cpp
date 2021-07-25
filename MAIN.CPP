#include <iostream.h>
#include <fstream.h>
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <graphics.h>
#include <dos.h>

#define  up     72
#define  down   80
#define  left   75
#define  right  77

void drawRectangle(int x1,int y1,int x2,int y2){                       //x1,y1,x2,y2
    int i, j;
    gotoxy(x1,y1);
    printf("%c",201);                       //upper left corner
    for(i = x1+1; i < x2; i++){
        gotoxy(i, y1);
        printf("%c",205);                   //straight line horizontal top
    }
    gotoxy(x2,y1);
    printf("%c",187);                       //upper right corner
    for(i = y1+1; i < y2; i++){
        gotoxy(x2, i);
        printf("%c",186);                   //straight line vertical right
    }

    gotoxy(x2, y2);
    printf("%c",188);                       //lower right corner
    for(i = x2-1; i > x1; i--){
        gotoxy(i,y2);
            printf("%c",205);               //straight horizontal bottom
    }
    gotoxy(x1,y2);
    printf("%c",200);                       //lower lift corner
    for(i = y2-1; i > y1; i--){
        gotoxy(x1,i);
            printf("%c",186);               //vertical straight left
    }

}



void displayclasswise(char b[4][8]);
void displaydaywise(char b[4][8]);
void subsitution();
void daywise();
void arrow(int a,int b);
void teacherwise();
void menu();
void mod(int x,int y,char e[15]);

void background(){
  int gd = DETECT, gm,x=60,y=200;
  initgraph(&gd, &gm, "C:\\TurboC3\\BGI");
    settextstyle(0,0,4);
    outtextxy(x, y, "TIMETABLE PROJECT");
     settextstyle(0,0,2);
    outtextxy(x+90, y+40, "BY- SOURABH BUCHA");
    getch();
  closegraph();

}


//To conform change in modification
int conform(){
int pos=1;
char k;
while(k!=13){
  clrscr();
  drawRectangle(22,9,60,15);
  gotoxy(30,11);arrow(1,pos);cout<<"CONFORM CHANGE"<<endl;
  gotoxy(30,13);arrow(2,pos);cout<<"CANCEL CHANGE"<<endl;
k = getch();
if(k == 80 && pos != 2){
    pos++;
}
else if(k == 72 && pos !=1){
    pos--;
}
}
return pos;
}


//function to convert character code to subject
char* name(char a) {
    char str[15];
    switch(a){
	case 'a':
	    strcpy(str,"Physics");
	break;
	 case 'b':
	    strcpy(str,"Chemistry");
	break;
	 case 'c':
	    strcpy(str,"Maths");
	break;
	 case 'd':
	    strcpy(str,"Biology");
	break;
	 case 'e':
	    strcpy(str,"Computer");
	break;
	 case 'f':
	    strcpy(str,"English");
	break;
	 case 'g':
	    strcpy(str,"Games");
	break;
	 case 'h':
	    strcpy(str,"Library");
	break;
	 case 'k':
	    strcpy(str,"Practical");
	break;
	case 'j':
	    strcpy(str,"Lifeskill");
	break;
	 case 'i':
	    strcpy(str,"Psyc");
	break;

    }
    char* cp = str;
    return cp;
}



//function to make a moving cursor
void move(char e[15]){
  char ch;
  int x=2,y=2;
   start:
    if(x<2)
     x=2;
    if(y<2)
     y=2;
    if(x>78)
     x=78;
    if(y>32)
     y=32;
    gotoxy(x,y);
    ch=getch();
    switch(ch){
	case up: 		y--; 		break;
	case down: 		y++; 		break;
	case left: 		x--; 		break;
	case right: 		x++; 		break;
	case 13:
 if((x-12)%15==0  &&  (y-9)%2==0  && ((x-12)/15)<4
	&&  ((x-2)/15)>=0  &&  (y-9)/2<8){
			mod(x,y,e);
			}
		else{
			goto start;
		}
	    break;
    }
    if(ch!=13)
 goto start;
 }



//function to modify the timetable
void mod(int x,int y,char e[15]){
clrscr();
char A,B,C,D,M,a1,a2,a3,a4;
 x=(x-12)/15;
 y=(y-9)/2;
int i=0;
 ifstream dat(e);
 ofstream dat1("temp.dat");
	while(dat>>A>>B>>C>>D) {
		   if(i==x){
		  a1=A;
		 a2=B;
		a3=C;
		a4=D;
	i++;
    }
 }
 sel:
 clrscr();
 char name1[30];
 for(int m=0;m<11;m++){
	   strcpy(name1,name(char(m+97)));
	gotoxy(40,3+(m*2));
	 cout<<char(m+97)<<'\t'<<name1;
 }
 gotoxy(3,3);
 cout<<"Enter subsitution teacher :";
 cin>>M;
 if(int(M)>107||int(M)<97){
 cout<<"Enter valid teacher code ";
	getch();
 goto sel;
 }
 if(M==a1||M==a2||M==a3||M==a4){
	cout<<"Select diffrent teacher ";
	 getch();
	goto sel;
 }
 int x1=conform();
   if(x1==2){
      clrscr();
      menu();
    }
 i=0;
 dat.clear();
 dat.seekg(0, ios::beg);
 while(dat>>A>>B>>C>>D){
		if(i!=y){
		dat1<<A<<'\t'<<B<<'\t'<<C<<'\t'<<D<<endl;
}
	else{
			if(x==0){
				dat1<<M<<'\t'<<B<<'\t'<<C<<'\t'<<D<<endl;
				}
			if(x==1){
			   dat1<<A<<'\t'<<M<<'\t'<<C<<'\t'<<D<<endl;
			}
			if(x==2){
			    dat1<<A<<'\t'<<B<<'\t'<<M<<'\t'<<D<<endl;
			}
			if(x==3){
			    dat1<<A<<'\t'<<B<<'\t'<<C<<'\t'<<M<<endl;
			}
    }
    i++;
 }
 dat.close();
 dat1.close();
 remove(e);
 rename("temp.dat", e);
 clrscr();
 gotoxy(5,4); cout<<"Time Table updated!!!";
 getch();
 menu();
 }




//class for class details
class classdetail{
int grade;
char sec;
int student,room_no;
char classteacher[30];

public:
void input();				//input details from .dat file
void displaydetails();		//display selected class detail
};


void classdetail::input(){
char b;
int a;
gotoxy(3,3);
cout<<"Enter class :";
cin>>a;
gotoxy(3,5);
cout<<"Enter section :";
cin>>b;

ifstream dat("classdat.dat");
while(dat>>grade>>sec>>student>>room_no>>classteacher){
    if(grade==a&&sec==b){
		    break;
	}
    }
}


void classdetail::displaydetails(){
    clrscr();
  gotoxy(20,7);
	cout<<"Class : "<<grade<<"-"<<sec;
	gotoxy(20,9);
cout<<"Class teacher : "<<classteacher;
	gotoxy(20,11);
cout<<"Number of student : "<<student;
	gotoxy(20,13);
cout<<"Room no. : "<<room_no<<endl;
     getch();
  menu();
 }



//display function for daywise display
void displaydaywise(char b[4][8]){
char n[15];
gotoxy(12,6);
cout<<"XI-A";
gotoxy(12+15,6);
cout<<"XI-B";
gotoxy(12+30,6);
cout<<"XII-A";
gotoxy(12+45,6);
cout<<"XII-B";
    for(int j=0;j<8;j++){
       gotoxy(3,9+(j*2));
	cout<<j+1;
    }
for(int i=0;i<4;i++){
    for(int j=0;j<8;j++){
       gotoxy(12+(i*15),9+(j*2));
       strcpy(n,name(b[i][j]));
       cout<<n;
    }
}
}



//function for display classwise
void displayclasswise(char b[4][8]){
char n[15];
gotoxy(7,6);
cout<<"Day:1";
	 gotoxy(7+12,6);
cout<<"Day:2";
gotoxy(7+24,6);
cout<<"Day:3";
gotoxy(7+36,6);
cout<<"Day:4";
gotoxy(7+48,6);
cout<<"Day:5";
gotoxy(7+60,6);
cout<<"Day:6";
 for(int j=0;j<8;j++){
       gotoxy(2,9+(j*2));
		      cout<<j+1;
	   }
for(int i=0;i<6;i++){
    for(int j=0;j<8;j++){
       gotoxy(7+(i*12),9+(j*2));
	    strcpy(n,name(b[i][j]));
	 cout<<n;
    }
}
getch();
menu();
}




//function for substitution of teachers
void subsitution(){
    char a[5],b[4][8],file[10],c;
    char A,B,C,D;
    int n;
    gotoxy(2,3);
		cout<<"Enter no. of absent teachers :";
		 cin>>n;

    for(int i=0;i<n;i++){
	gotoxy(2,5+i*2);
		cout<<"Absent teacher code :";
		 cin>>a[i];
	}
    day:
    gotoxy(2,5+i*2);
	cout<<"Enter day :";
	cin>>c;
    strcpy(file,"dayl.dat");
    file[3]=c;
    ifstream dat(file);
	int n1=0;
	 while(dat>>A>>B>>C>>D){
		    if(A==a[0]||A==a[1]||A==a[2]||A==a[3]||A==a[4]){
		       lable:
		       int p=rand()%10;
		       if(char(97+p)==A||char(97+p)==B||char(97+p)==C||char(97+p)==D||char(97+p)==a[0]||char(97+p)==a[1]||char(97+p)==a[2]||char(97+p)==a[3]||char(97+p)==a[4]) {
			goto lable;
		       }
	    b[0][n1]=char(97+p);
	    A=b[0][n1];

		}
	    else{
		b[0][n1]=A;

	    }
	     if(B==a[0]||B==a[1]||B==a[2]||B==a[3]||B==a[4]){
		       lable1:
		       int p=rand()%10;
		       if(char(97+p)==A||char(97+p)==B||char(97+p)==C||char(97+p)==D||char(97+p)==a[0]||char(97+p)==a[1]||char(97+p)==a[2]||char(97+p)==a[3]||char(97+p)==a[4]) {
			goto lable1;
		       }
	    b[1][n1]=char(97+p);
	    B=b[1][n1];
		}
	    else{
		b[1][n1]=B;
	    }

	     if(C==a[0]||C==a[1]||C==a[2]||C==a[3]||C==a[4]){
		       lable2:
		       int p=rand()%10;
		       if(char(97+p)==A||char(97+p)==B||char(97+p)==C||char(97+p)==D||char(97+p)==a[0]||char(97+p)==a[1]||char(97+p)==a[2]||char(97+p)==a[3]||char(97+p)==a[4]) {
			goto lable2;
		       }
	    b[2][n1]=char(97+p);
	    C=b[2][n1];
		}
	    else{
		b[2][n1]=C;
	    }

	     if(D==a[0]||D==a[1]||D==a[2]||D==a[3]||D==a[4]){
		       lable3:
		       int p=rand()%10;
		       if(char(97+p)==A||char(97+p)==B||char(97+p)==C||char(97+p)==D||char(97+p)==a[0]||char(97+p)==a[1]||char(97+p)==a[2]||char(97+p)==a[3]||char(97+p)==a[4]) {
			  goto lable3;
		       }
	    b[3][n1]=char(97+p);
	    D=b[3][n1];
		}
	    else{
		b[3][n1]=D;
	    }
	    n1++;
    }
clrscr();
gotoxy(35,2);cout<<"DAY "<<c;
displaydaywise(b);
getch();
menu();

}


//function to display timetable teacherwise
void teacherwise(){
clrscr();
char a,b,c,d,n,e[10];
strcpy(e,"day1.dat");
char name1[30];
startn:
clrscr();
for(int m=0;m<11;m++){
    strcpy(name1,name(char(m+97)));
    gotoxy(50,3+(m*2));
		cout<<char(m+97)<<'\t'<<name1;
}
gotoxy(2,1);
cout<<"Enter teacher code :";
cin>>n;
if(n>'k'||n<'a'){
cout<<"Enter valid teacher code ";
getch();
goto startn;
}
clrscr();
ifstream dat;
for(int i=0;i<8;i++){
		 gotoxy(7,7+i*2);
		 cout<<i+1;
	  }

for(i=1;i<7;i++){
    gotoxy(10*i,5);
	 cout<<"DAY: "<<i<<'\t';
	e[3]=char(i+48);
	dat.open(e);
	int l=1;
while(dat>>a>>b>>c>>d){
			if(a==n)    {
gotoxy(10*i,5+2*l);
cout<<"XI-A";
}
			if(b==n)    {
gotoxy(10*i,5+2*l);
cout<<"XI-B";
}
			if(c==n)    {
gotoxy(10*i,5+2*l);
cout<<"XII-A";
}
			if(d==n)    {
gotoxy(10*i,5+2*l);
cout<<"XII-B";
}
		 l++;
	 }
    cout<<endl;
    dat.close();
}
gotoxy(35,2);
strcpy(name1,name(n));
cout<<name1;
    getch();
    menu();
}




//function to input data from daywise timetable data file
void daywise(){
    char n;
    char B[4][8];
    gotoxy(3,2);
	  cout<<"Enter day to display timetable :";
		cin>>n;
    ifstream day;
	char m[10];
	strcpy(m,"dayn.dat");
	 m[3]=n;
	day.open(m);
	int i=0;
	char a,b,c,d;
    while(day>>a>>b>>c>>d){
		B[0][i]=a;
		B[1][i]=b;
		B[2][i]=c;
		B[3][i]=d;
	i++;
       }
    clrscr();
    gotoxy(35,1);
    cout<<"DAY "<<n;
    displaydaywise(B);
    getch();
    day.close();
 }




//function for option selection arrows
void arrow(int k,int n){
if(k==n){
		cout<<"-->";
}
else{
		cout<<"   ";
	}
  }



//function to import data from data files according to classes
void classwise(){
 int j;
clrscr();
int pos=1;
char k;
while(k!=13){
 cout<<"Select class :"<<endl;
 drawRectangle(10,4,50,16);
 gotoxy(18,6); arrow(1,pos);cout<<"XI-A"<<endl;
 gotoxy(18,8); arrow(2,pos);cout<<"XI-B"<<endl;
 gotoxy(18,10); arrow(3,pos);cout<<"XII-A"<<endl;
 gotoxy(18,12); arrow(4,pos);cout<<"XII-B"<<endl;
 gotoxy(18,14); arrow(5,pos);cout<<"GO BACK"<<endl;
 k = getch();
 clrscr();
if(k == 80 && pos != 5){
    pos++;
}
else if(k == 72 && pos !=1){
    pos--;
}
}
if(pos==5){
	menu();
}
   clrscr();
   char e[15],a,b,c,d,m[6][8];
   ifstream dat;
   strcpy(e,"day1.dat");
for(int i=0;i<6;i++){
	e[3]=char(i+49);
	 dat.open(e);

	   for(j=0;dat>>a>>b>>c>>d;j++){
	    if(pos==1){
		m[i][j]=a;
	    }
	    if(pos==2){
		m[i][j]=b;
	    }
	    if(pos==3){
		m[i][j]=c;
	    }
	    if(pos==4){
		m[i][j]=d;
	    }
	    cout<<j;
	}
cout<<endl;
dat.close();
}
clrscr();
gotoxy(35,1);
switch(pos){
case 1:
cout<<"XI-A";
break;
case 2:
cout<<"XI-B";
break;
case 3:
cout<<"XII-A";
break;
case 4:
cout<<"XII-B";
break;
}
displayclasswise(m);
getch();

}
void classdetails(){
classdetail cls;
cls.input();
cls.displaydetails();
getch();
}



//function for interface of data modification
void modify(){
int n;
loop:
clrscr();
gotoxy(3,2);
cout<<"Enter day to modify : ";
cin>>n;
if(n>6||n<1){
    cout<<"\nENTER VALID DAY !! ";
    getch();
    goto loop;
}
char A,B,C,D;
char b[4][8];
ifstream dat;
char e[15];
strcpy(e,"day1.dat");
e[3]=char(n+48);
dat.open(e);
int i=0;
while(dat>>A>>B>>C>>D){
b[0][i]=A;
b[1][i]=B;
b[2][i]=C;
b[3][i]=D;
		    i++;
}
clrscr();
gotoxy(35,2);cout<<"DAY "<<n;
displaydaywise(b);
move(e);
}



//function for menu driven setup
void menu(){
int pos=1;
char k;
while(k!=13){
  clrscr();
  drawRectangle(15,4,60,20);
  gotoxy(24,6);arrow(1,pos);cout<<"DAY WISE TIMETABLE"<<endl;
  gotoxy(24,8);arrow(2,pos);cout<<"CLASS WISE TIMETABLE"<<endl;
  gotoxy(24,10);arrow(3,pos);cout<<"TEACHER WISE TIMETABLE"<<endl;
  gotoxy(24,12);arrow(4,pos);cout<<"SUBSITUTIONS"<<endl;
  gotoxy(24,14);arrow(5,pos);cout<<"CLASS DETAILS"<<endl;
  gotoxy(24,16);arrow(6,pos);cout<<"MODIFY TIMETABLE"<<endl;
  gotoxy(24,18);arrow(7,pos);cout<<"EXIT"<<endl;
k = getch();
if(k == 80 && pos != 7){
    pos++;
}
else if(k == 72 && pos !=1){
    pos--;
}
}
clrscr();
switch(pos){
case 1:daywise();
       menu();
    break;
case 2:classwise();
    break;
case 3:teacherwise();
    break;
case 4:subsitution();
    break;
case 5:classdetails();
    break;
case 6:modify();
    break;
case 7:exit(0);
    break;
}
}


//main for calling menu
void main(){
background();
textbackground(WHITE);
textcolor(BLACK);

menu();
}
 
