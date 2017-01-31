#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

#define SBORDERx 10  //Start Border X coordinate
#define SBORDERy 5   //Start Border Y coordinate
#define TBORDERx 70	//TERMINATING Border X coordinate
#define TBORDERy 20 //TERMINATING Border Y coordinate
#define NOP 6 //Number of pipes
#define EASY 3   //i.e  Number of Gaps
#define MEDIUM 2
#define HARD 1
#define LIVES 1

void gotoxy(int,int);  //goto x and y coordinate of screen
void cls();           //clear screen
void read_records();   //from file
void print_scores();   //and print them to file
void respawn(int);   //after brd crash
void modify(int);      //modify scores and lives after checking the conditions
void scores();        //scores and life printer
void border();        // Border [==]
void jump();         //All bird functions and other function calling order is present here
void pipes();           //hooh! after toooooo much calculations I've created  that. so Handle with care
int getrand();           //get random number
void gameover();        //after game is overed
void intro();          //the first script


int is1sttime=1;
int called_from_main;
char name[20]="Anonumous";
int _near=0;
int life=LIVES;
int offset[NOP];
int gap=2; //will be multiplied by 2 after
int _score=0;
struct info{
	int x;
	int y;

};
typedef struct info coordinates;
coordinates bird;
coordinates pipe[NOP]; //NOP=number of pipes

int main()
{
	if(is1sttime)
	{
	_score=0;
	strcpy(name,"");
	life=LIVES;
	intro();
	}
    is1sttime=0;
	bird.x=18;
	bird.y=11;
	fflush(stdin);
	for(int i=0;i<NOP;i++)
	{
	offset[i]=getrand();
	pipe[i].x=TBORDERx+(10*i);
	}
    called_from_main=1;
	jump();
}
void jump()
{
	cls();
	border();
	scores();
	pipes();
	bird.y-=2;
	modify(_near);
	gotoxy(bird.x,bird.y);
	printf("%c",258);
	Sleep(151);
	if(called_from_main==1)
	getch();
	while(!kbhit())
	{

	cls();
	bird.y++;
	border();
	scores();
	pipes();
	gotoxy(bird.x,bird.y);
	printf("%c",258);
	Sleep(40);
    modify(_near);
	}
	char ch=getch();
	if(ch==' '||ch=='j')
	{
	called_from_main=0;
	jump();
}
else
{
printf("PAUSED");
getch();
cls();
jump();
}
}
void border()
{
	for(int i=SBORDERx;i<=TBORDERx;i++)
 	{
		gotoxy(i,SBORDERy-1);
		printf("%c",219);
		gotoxy(i,TBORDERy+1);
		printf("%c",219);
	}
	for(int i=SBORDERy;i<=TBORDERy;i++)
	{
		gotoxy(SBORDERx,i);
		printf("%c",219);
		gotoxy(TBORDERx,i);
		printf("%c",219);
	}

}
void scores()
{
	gotoxy(0,0);
	printf("%20s PLAYING  SCORE =%d       LIVES=%d",name,_score,life);


}
void pipes()
{
for(int i=0;i<NOP;i++)
{
	pipe[i].x--;
	if(pipe[i].x<=20)
	_near=i;
	if(pipe[i].x==SBORDERx)
	{
	offset[i]=getrand();
	pipe[i].x=TBORDERx-2;
}
for(int thadla=SBORDERy+(offset[i]+gap);thadla<=TBORDERy;thadla++)
{

	if(pipe[i].x<=TBORDERx)
	{

	gotoxy(pipe[i].x,thadla);
	printf("%c%c",219,219);

}
}
for(int uparla=SBORDERy+offset[i]-gap;uparla>=SBORDERy;uparla--)
{

	if(pipe[i].x<=TBORDERx)
	{
gotoxy(pipe[i].x,uparla);
printf("%c%c",219,219);
  }
}

}
}
int getrand()
{
	srand(time(0));
	int num=rand()%11;
	if(num<3)
	return 5;
	else
	 return num;
}

void modify(int i)
{
	if(((bird.x==pipe[i].x)||(bird.x==pipe[i].x+1))&&((bird.y>=(SBORDERy+offset[i]+gap))||(bird.y<=(SBORDERy+offset[i]-gap))))
	{
		life--;
		gotoxy(bird.x,bird.y);
    	printf("%c",219);
		while(bird.y++)
		{
		gotoxy(bird.x,bird.y);
    	printf("%c",235);
     	Sleep(100);

		if(bird.y==TBORDERy+1)
		break;
		if(((bird.y>=(SBORDERy+offset[i]+gap))||(bird.y<=(SBORDERy+offset[i]-gap))))
		{
			gotoxy(bird.x,bird.y); 
			printf("%c",219);
		}
		else
		{

		gotoxy(bird.x,bird.y);
		printf("%c",' ');
	}

     }
    
		if(life>=0)
		respawn(1);
		else
		gameover();
	}
		if(((bird.x==pipe[i].x+1))&&!((bird.y>=(SBORDERy+offset[i]+gap))||(bird.y<=(SBORDERy+offset[i]-gap)))) //area b/w pipes
	{    printf("%c",263);
		_score++;
		if(_score%10==0)
		life++;
	}
	if(bird.y>TBORDERy||bird.y<SBORDERy)
	{
	life--;
		gotoxy(bird.x,bird.y);
    	printf("%c",219);
		while(bird.y++)
		{
		gotoxy(bird.x,bird.y);
    	printf("%c",235);
     	Sleep(100);

		if(bird.y>=TBORDERy)
		break;


		gotoxy(bird.x,bird.y);
		printf("%c",' ');


     }
     	getch();
		if(life>=0)
		respawn(3);
		else
		gameover();
	}
}
void respawn(int after_s)
{


 for(int i=after_s;i>=0;i--)
 {
 	cls();
 	border();
 	gotoxy(20,8);
 	printf("DO NOT PRESS ANY KEY"); //OtherWise The keys will be Recorded in Stdin resulting in unwanted Jumps of Bird
 	gotoxy(20,10);
 	printf("RESPAWNING AFTER %ds\n",i);
 	Sleep(1000);
 	fflush(stdin);
 }
 fflush(stdin);
 main();
}
void gameover()
{  cls();
	printf("\n\n  ¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦\n     ¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦ ¦¦¦\n     ¦ ¦¦¦¦¦¦¦¦¦ ¦¦¦¦¦¦¦  ¦¦¦¦¦¦¦ \n     ¦¦¦¦¦¦¦¦¦¦ ¦¦     ¦¦ ¦¦    ¦¦\n     ¦¦¦¦¦¦¦¦¦¦ ¦¦ ¦¦¦ ¦¦ ¦     ¦¦ \n     ¦¦¦¦¦¦¦¦¦¦ ¦¦¦¦¦¦¦ ¦ ¦¦¦¦¦  ¦ \n     ¦¦¦¦¦¦¦¦¦¦ ¦¦¦¦¦¦¦ ¦ ¦¦¦¦¦¦ ¦   \n      ¦¦¦¦¦¦¦¦¦¦ ¦¦¦¦¦¦¦ ¦ ¦¦¦¦¦¦ ¦\n      ¦¦¦¦¦¦¦¦¦¦ ¦¦ ¦¦¦ ¦¦ ¦ ¦¦¦ ¦¦ \n     ¦¦ ¦¦¦¦¦¦¦ ¦¦¦   ¦¦¦ ¦¦¦¦¦¦¦¦ \n     ¦¦  ¦¦¦¦¦¦  ¦¦¦¦¦¦¦ ¦¦¦¦¦¦¦   \n     ¦¦¦ ¦¦¦¦¦  ¦¦¦           ¦ \n     ¦¦¦¦ ¦¦¦  ¦¦¦ ¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦  \n      ¦¦¦¦  ¦  ¦¦¦ ¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦\n      ¦¦¦¦¦   ¦¦¦¦ ¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦ \n     ¦¦¦¦¦¦ ¦¦¦¦¦¦    \n       ¦¦¦¦¦¦¦¦¦¦¦¦¦ ¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦      \n     ¦¦¦¦¦¦¦¦¦¦¦¦¦ ¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦   \n     ¦ ¦¦¦¦¦¦¦¦¦¦¦¦ ¦¦¦¦¦¦¦¦¦¦¦         \n      ¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦          \n     ¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦         \n      ");
	printf("\n\t\t\t\tGAME OVER");
	print_scores();

	getch();
	game_over:
	cls();
	border();
	gotoxy(20,10);
	printf("GAME OVER");
	getch();
	border();
	gotoxy(20,10);
	printf(".SELECT. ");
	gotoxy(20,11);
	printf("1.READ RECORDS");
	gotoxy(20,12);
	printf("2.PLAY AGAIN");
	gotoxy(20,13);
	printf("3.EXIT");
	gotoxy(20,20);
	char choice=getch();
	switch(choice){

	case '1':
		read_records();
	case '2':
		is1sttime=1;
		main();
	case '3':
	cls();
	printf("HOPE YOU ENJOYED!");
	exit(0);
	default:
		goto game_over;
}
}
void intro()
{
	cls();
	printf("\t\t\tFLAPPY_BIRD_IN_C_v1.0\n");
	printf("\n\n\tI was playing that game on Android from last few days on\n\t 4/Jan/2016 [My Winter Vacations were ongoing].\n");
	printf("\n\n\tSo as I know little much \'C\',I created that GAME \n\n\t\t\t\t\t\t--Charanjit_Singh\n\n\n");
	system("pause");
	cls();
	gotoxy(20,3);
	printf("--------ENTER_YOUR_NAME------------\n");
	fflush(stdin);
	gotoxy(20,5);
	gets(name);
	if(strcmp(name,"")==0||strcmp(name," ")==0)
	strcpy(name,"Anonymous");
	select_color:
		fflush(stdin);
		cls();
		border();
		gotoxy(20,6);
	printf("------SELECT_COLOR-------");
	gotoxy(20,7);
	printf("1. Black N White");
	gotoxy(20,8);
	printf("2. White N Black");
	gotoxy(20,9);
	printf("3. Red N White");
	gotoxy(20,10);
	printf("4. Yellow N Black");
	gotoxy(20,13);
	printf("PRESS [SPACEBAR] when Selected.");
		gotoxy(20,15);
	char choice=getch();

	switch(choice)
	{
	case '1':
		system("color 07");
	goto select_color;
		case '2':
			system("color f0");
			goto select_color;
			case '3':
			system("color 4f");
			goto select_color;
			case '4':
				system("color e0");
			goto select_color;
			case ' ':
				break;
				default:
					goto select_color;


	}
	select_difficulty:
	cls();
	printf("\n\n\t\tSelect Difficulty..\n");
	printf("\t1.HARD\n\t2.MEDIUM\n\t3.EASY\n");
	gap=getch();
	gap-=48;
	if(gap>3||gap<1)
	goto select_difficulty;
	int loading_temp=0;
	char loading_string[6][300]={
							"All Done.."	,
							"Building HQ-3D Bird..",
							"Loading Fonts..",
							"Loading World..",
							"Loading Pipes..",
							"Creating List of files to be Loaded"};
	for(int sec=5;sec>=0;sec--)
	{
	cls();
	printf("\n\n\t\tPress [SPACEBAR] or 'j' to JUMP\n\n\t\t\n\t\t\tGame will Start in %ds\n\n\t\t%25s",sec,loading_string[sec]);

	gotoxy(20,10);
	for(int i=0;i<(5-sec)*(!!loading_temp);i++)  //Loading Animation Algo-
	{
		printf("%c%c%c%c%c",177,177,177,177,177);
	}
	gotoxy(20+loading_temp,10);
	for(int i=0;i<5;i++)
	{
	printf("%c",177);
	loading_temp++;
	Sleep(200);
}

}
}
void print_scores()
{
	char level[7]="";
	if(gap==1)
	strcpy(level,"HARD");
		if(gap==2)
	strcpy(level,"MEDIUM");
		if(gap==3)
	strcpy(level,"EASY");

	open_again:
	FILE *fp;
	fp=fopen("flappy_scores.txt","r");
	if(fp==NULL)
	{
		fp=fopen("flappy_scores.txt","w");
		fprintf(fp,"    <<<<<<<FLAPPY SCORES>>>>>\n\n");
		goto open_again;
	}
	fclose(fp);

     fp=fopen("flappy_scores.txt","a");
		fprintf(fp,"------------------------------------------\n");
		fprintf(fp,"%20s scored %3d in %s Difficulty.\n\n",name,_score,level);
		 time_t mytime;
    mytime = time(NULL);
    fprintf(fp,"  Played Date:%s",ctime(&mytime));
		fprintf(fp,"------------------------------------------\n");
		fclose(fp);

}
void read_records()
{
	FILE *fp;
	fp=fopen("flappy_scores.txt","r");
	while(1)
	{
		char rea=fgetc(fp);
		if(rea==EOF)
		break;
		else
		printf("%c",rea);

	}
	fclose(fp);
	getch();

}
void gotoxy(int x, int y)
{

    COORD coord;

    coord.X = x;

    coord.Y = y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

}
void cls()
{
	system("cls");
}
