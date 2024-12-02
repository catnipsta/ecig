#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <ncurses.h>

char c;
int cig = 840;
unsigned int ash = 0;
unsigned int mash;
unsigned int md;
unsigned int csmoked = 0;
int tsmoked = 0;
char ttsmoked[16];
FILE *fcigs;
bool stl = false;
bool lit = false;
bool cs = false;
bool autodrag = false;
bool autoflick = false;
time_t start, a1;
char cigloc[64];
char *rank;
char *ranks[16]={
"Rookie",
"Social Smoker",
"Casual Smoker",
"Daily Smoker",
"Normie",
"Stinker",
"Hooked",
"Pack-a-Day",
"Addict",
"Nicotine Fiend",
"Chain Smoker",
"Full Timer",
"Snoop Dogg",
"Lung Cancer God",
"The Tar Tornado",
"The Human Ashtray"};

void draw(void){
	if(tsmoked >= 1000000)rank=ranks[15];
	else if(tsmoked >= 500000)rank=ranks[14];
	else if(tsmoked >= 250000)rank=ranks[13];
	else if(tsmoked >= 100000)rank=ranks[12];
	else if(tsmoked >= 50000)rank=ranks[11];
	else if(tsmoked >= 25000)rank=ranks[10];
	else if(tsmoked >= 10000)rank=ranks[9];
	else if(tsmoked >= 5000)rank=ranks[8];
	else if(tsmoked >= 2500)rank=ranks[7];
	else if(tsmoked >= 1000)rank=ranks[6];
	else if(tsmoked >= 750)rank=ranks[5];
	else if(tsmoked >= 500)rank=ranks[4];
	else if(tsmoked >= 250)rank=ranks[3];
	else if(tsmoked >= 100)rank=ranks[2];
	else if(tsmoked >= 20)rank=ranks[1];
	else rank=ranks[0];
	clear();
	if(stl && lit){
        	mvprintw(0,5+floor(cig/60)+ceil(ash/60)," )");
        	mvprintw(1,5+floor(cig/60)+ceil(ash/60),"( ");
        	mvprintw(2,5+floor(cig/60)+ceil(ash/60)," )");}
	else if(lit){
        	mvprintw(0,5+floor(cig/60)+ceil(ash/60),"( ");
        	mvprintw(1,5+floor(cig/60)+ceil(ash/60)," )");
        	mvprintw(2,5+floor(cig/60)+ceil(ash/60),"( ");}
	mvprintw(3,2,"____");
	mvprintw(4,0,"()___)");
	for(int i = 1; i < 15; i++){
		if(cig >= i*60 && i < 14){
			mvprintw(3,i+5,"_");
			mvprintw(4,i+5,"_");}
		else if(cig == 840 && i == 14)
			mvprintw(4,19,")");
		else if(i <= (int)(floor((float)cig/60)+ceil((float)ash/60))){
			mvprintw(3,i+5," ");
			mvprintw(4,i+5,"#");}
		else
			mvprintw(4,i+5," ");
	}
	mvprintw(6,0,"Smoked %i cigs this session.",csmoked);
	mvprintw(7,0,"Smoked %i cigs in total.",tsmoked);
	mvprintw(8,0,"Rank: %s",rank);
	refresh();
}

int main(void){
	srand(time(NULL));
	initscr();
	cbreak();
	timeout(0);
	noecho();
	curs_set(0);
	strcpy(cigloc,getenv("HOME"));
	strcat(cigloc,"/.cigs");
	fcigs = fopen(cigloc,"ab+");
	fscanf(fcigs,"%d",&tsmoked);
	fclose(fcigs);
	draw();
	mash = 60*(2.7+rand()/700000000);
	md = 8+rand()/1000000000*3;
	start = time(NULL);
	a1 = time(NULL);
	while(1){
		c=getch();
		if(c == 'l'){cs=false;lit=true;}
		else if(c == 'c'){cs=true;lit=true;}
		else if(c == 's'){cs=false;lit=false;ash=60-(cig-floor(cig/60)*60);}
		else if(c == 'd' && lit){cig--;ash++;autodrag=false;}
		else if(c == 'a')autodrag = true;
		else if(c == 'f'){autoflick=false;ash = 60-(cig-floor(cig/60)*60);}
		else if(c == 'x')autoflick = true;
		if(time(NULL)-start != 0){
			start = time(NULL);
			if(lit){
				cig--;
				ash++;
				stl = !stl;}
			if(cig <= 0){lit=false;csmoked++;tsmoked++;cig=840;ash=0;fcigs=fopen(cigloc,"w");sprintf(ttsmoked,"%d",tsmoked);fputs(ttsmoked,fcigs);fclose(fcigs);fcigs=fopen(cigloc,"ab+");fscanf(fcigs,"%d",&tsmoked);fclose(fcigs);}
			if(ash > mash){
				ash = 60-(cig-floor(cig/60)*60);
				mash = 60*(2.5+rand()/700000000);}
			if(cs && !lit)lit = true;
			if(autodrag && lit && time(NULL)-a1 > md){a1=time(NULL);md=8+rand()/1000000000*3;cig-=13;ash+=13;}
			if(autoflick && ash >= 60*2)ash=60-(cig-floor(cig/60)*60);
			draw();
		}
	}
	free(rank);
	free(ranks);
	endwin();
	return 0;
}
