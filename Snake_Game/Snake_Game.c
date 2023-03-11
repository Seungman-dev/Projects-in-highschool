#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define ESC 27
#define ENTER 13
#define G 103
#define P 112

int lx[500], ly[500];
int sx;
int sy;

char dir;
int food_x, food_y;	
int score;
int i;
int length;
int bx, by;
int gamestart;
float gametime;
int gm = 0;
int key;
int options;
int optionp;
int pexit = 0;
int gxy;

clock_t gst, gov;

void gameover();

void gotoxy(int x, int y){
	COORD pos = {x*2,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void room(){
	system("cls");
	gotoxy(1,1);
	printf("▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦");
	gotoxy(1,26);
	printf("▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦");
	int ri;
	for(ri=1;ri<26;ri++){
		gotoxy(1,ri);
		printf("▦");
		gotoxy(30,ri);
		printf("▦");	
	}
}
//24 

void direction(int w){
	if(gamestart==1){
		switch(w){
			case LEFT:
				if(dir!='R'){     //→ ← ↑ ↓ 
					dir = 'L';
				}
				break;
			case RIGHT:
				if(dir!='L'){
					dir = 'R';
				}
				break;
			case UP:
				if(dir!='D'){
					dir = 'U';
				}
				break;
			case DOWN:
				if(dir!='U'){
					dir = 'D';
				}
				break;	
		}
	}	
}

void food(){
	food_x = rand()%23+2;
	food_y = rand()%24+2;
	gotoxy(food_x,food_y);
	printf("☆");
}


// 먹이 먹으면 발동 
void eat(){
	score+=50;
	length++;
	gotoxy(20,0);
	lx[length-1]=food_x;
	ly[length-1]=food_y;
	food();
}

void move(){
	if(gamestart==1){
		gotoxy(sx,sy);
		printf("  ");
		bx = sx;
		by = sy;
		switch(dir){
			case 'L':
				if(sx==2){
					gameover();
				}
				else{
					sx--;
				}
				break;
			case 'R':
				if(sx==29){
					gameover();
				}
				else{
					sx++;
				}
				break;
			case 'U':
				if(sy==2){
					gameover();
				}
				else{
					sy--;
				}
				break;
			case 'D':
				if(sy==25){
					gameover();
				}
				else{
					sy++;
				}
				break;		
		}
		gotoxy(sx,sy);
		printf("○");
		if(gm==1){
			gotoxy(33,11);
			printf("x:%d  ", sx);
			gotoxy(33,13);
			printf("y:%d  ",sy);
			gotoxy(33,15);
			if (dir=='R') printf("DIRECTION: →");
			else if (dir=='L') printf("DIRECTION: ←");
			else if (dir=='U') printf("DIRECTION: ↑");
			else if (dir=='D') printf("DIRECTION: ↓");
			for(gxy=0;gxy<45;gxy++){
				gotoxy(gxy,0);
				printf("%02d", gxy);
			}
			for(gxy=0;gxy<28;gxy++){
				gotoxy(0,gxy);
				printf("%02d", gxy);
			}
		}
		if(sx==food_x&&sy==food_y){
			eat();
		}
		gotoxy(lx[length-1],ly[length-1]);
		printf("  ");
		gotoxy(bx,by);
		printf("ㅇ");
		int li;
		for(li=length-1;li>0;li--){
			lx[li]=lx[li-1];
			ly[li]=ly[li-1];
			if(lx[li]==food_x&&ly[li]==food_y){
				gotoxy(food_x,food_y);
				printf("ㅇ");
				eat();
			}
			if(lx[li]==sx&&ly[li]==sy){
				gameover();
			}
		}
		lx[0] = bx;
		ly[0] = by;
	}
}
void start(){
	gst = clock();
	sx = 18;
	sy = 14;
	food_x, food_y = 0;	
	score = 0;
	length = 3;
	bx, by = 0;
	dir = 'L';
	int i2 = 0;
	room();
	food();
	move();
}
void gameover(){
	lx[0], lx[1], lx[2], lx[3], ly[0], ly[1], ly[2], ly[3] = 0;
	int go = 0;
	gamestart = 0;   
	room();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0C);
	gotoxy(11,9);
	printf(" G A M E  O V E R !");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
	gotoxy(8,6);
	printf("┌─────────────────────────────┐ ");
	gotoxy(8,20);
	printf("└─────────────────────────────┘ ");
	Sleep(200);
	int gs = 0;
	while(!_kbhit()){
		gotoxy(12,11);
		printf("Score: %d", gs);
		if(gs>score-1){
			break;
		}
		if(gs<101){
			if(gs<51){
				gs++;
			}
			else{
				gs+=10;
			}
		}
		else{
			gs+=50;
		}
		Sleep(5);
	}
	gotoxy(12,11);
	printf("Score: %d", score);
	gs = 0;
	Sleep(200);
	while (_kbhit()) _getch();
	while(!_kbhit()){
		gotoxy(12,13);
		printf("☆: %d", gs);
		if(gs>length-4){
			break;
		}
		gs++;
		Sleep(20);
	}
	gotoxy(12,13);
	printf("☆: %d", length-3);
	gs = 0;
	Sleep(200);
	while (_kbhit()) _getch();
	while(!_kbhit()){
		gotoxy(12,15);
		printf("Playtime: %d/s", gs);
		if(gs>gametime){
			break;
		}
		gs++;
		Sleep(15);
	}
	gotoxy(12,15);
	printf("Playtime: %.3f/s", gametime);
	Sleep(200);
	gotoxy(10,18);
	printf(" Press 'Enter' To Replay");
	while(1){
		gotoxy(10,18);
		if(go==6){
			gotoxy(10,18);
			printf("                        ");
		}
		else if(go==10){
			gotoxy(10,18);
			printf(" Press 'Enter' To Replay");
			go=0;
		}
		if(_kbhit()){
			int rek = _getch();
			if(rek == ENTER){
				break;
			}
		}
		Sleep(100);
		go++;
	}
	while (_kbhit()) _getch();
	gamestart = 1;
	start();
}

void title(){
	system("cls");
	int t =0;
	gotoxy(19,11); 
	printf(" _");
	Sleep(100);
	gotoxy(19,11); 
	printf("T_");
	Sleep(100);
	gotoxy(19,11); 
	printf("TH_");
	Sleep(100);
	gotoxy(19,11); 
	printf("THE_");
	Sleep(100);
	gotoxy(19,11); 
	printf("THE _");
	Sleep(100);
	gotoxy(19,11); 
	printf("THE S_");
	Sleep(100);
	gotoxy(19,11); 
	printf("THE SN_");
	Sleep(100);
	gotoxy(19,11); 
	printf("THE SNA_");
	Sleep(100);
	gotoxy(19,11); 
	printf("THE SNAP_");
	Sleep(100);
	gotoxy(19,11); 
	printf("THE SNAPE_");
	Sleep(100);
	gotoxy(19,11); 
	printf("THE SNAPE ");
	Sleep(100);
	gotoxy(19,11); 
	printf("THE SNAPE_");
	Sleep(100);
	gotoxy(19,11); 
	printf("THE SNAP_  ");
	Sleep(200);
	gotoxy(19,11); 
	printf("THE SNA_  ");
	Sleep(100);
	gotoxy(19,11); 
	printf("THE SNA   ");
	Sleep(100);
	gotoxy(19,11); 
	printf("THE SNA_  ");
	Sleep(100);
	gotoxy(19,11); 
	printf("THE SNAK_");
	Sleep(100);
	gotoxy(19,11); 
	printf("THE SNAKE_");
	Sleep(100);
	gotoxy(19,11); 
	printf("THE SNAKE _");
	Sleep(100);
	gotoxy(19,11); 
	printf("THE SNAKE G_");
	Sleep(100);
	gotoxy(19,11); 
	printf("THE SNAKE GA_");
	Sleep(100);
	gotoxy(19,11); 
	printf("THE SNAKE GAM_");
	Sleep(100);
	gotoxy(19,11); 
	printf("THE SNAKE GAME_");
	Sleep(100);
	gotoxy(19,11); 
	printf("THE SNAKE GAME  ");
	while (_kbhit()) _getch();
	Sleep(300);
	gotoxy(16,20); 
	printf("- Press Any Key To Start -");
	while(!_kbhit()){
		if(t==6){
			gotoxy(16,20); 
			printf("                          ");
		}
		else if(t==10){
			gotoxy(19,11); 
			printf("THE SNAKE GAME");
			gotoxy(16,20); 
			printf("- Press Any Key To Start -");
			t=0;
		}
		t++;
		Sleep(100);
	}
	while (_kbhit()) _getch();
	start();
}

void pause(){
	gotoxy(33,2);
	printf("PAUSE");
	while(1){
		if(_kbhit()){
			int key2;
			key2 = _getch();
			if(key2==P){
				gotoxy(33,2);
				printf("     ");
				break;
			}
		}
	}
}

void optionscreen(){
	if(optionp==1){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0B);
		gotoxy(12,6);
		printf(" O P T I O N S");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x08);
		if(options==1) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
		gotoxy(13,9);
		printf(" Continue       "); //1
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x08);
		if(options==2) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
		gotoxy(13,12);
		printf(" Restart       "); //2
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x08);
		if(options==3) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
		gotoxy(13,15);
		printf(" Title Screen       "); //3
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x08);
		if(options==4) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
		gotoxy(13,18);
		printf(" Setting       "); //4
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x08);
		if(options==5) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
		gotoxy(13,21);
		printf(" Exit       "); //5
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
	}
	else if(optionp==2){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x08);
		if(options==1) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
		gotoxy(13,9);
		printf(" Speed  ◀ 5 ▶       "); //1
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x08);
		if(options==2) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
		gotoxy(13,12);
		printf(" Food  ◀ 1 ▶       "); //2
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x08);
		if(options==3) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
		gotoxy(13,15);
		printf(" Customizing       "); //3
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x08);
		if(options==4) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
		gotoxy(13,18);
		printf(" Map       "); //4
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x08);
		if(options==5) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
		gotoxy(13,21);
		printf(" Back       "); //5
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
	}
	else if(optionp==3){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x08);
		if(options==1) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
		gotoxy(13,9);
		printf(" Head  ◀ ○ ▶       "); //1
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x08);
		if(options==2) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
		gotoxy(13,12);
		printf(" Body  ◀ ㅇ ▶       "); //2
		gotoxy(13,15);
		printf("                      ");
		gotoxy(13,18);
		printf("                      ");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x08);
		if(options==3) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
		gotoxy(13,21);
		printf(" Back       "); //3
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
	}
}


void option(){
	system("cls");
	room();
	gov = clock();
	gametime = (double)(gov-gst)/1000;
	score++;
	gotoxy(33,19);
	printf("Score: %d  ", score);
	gotoxy(33,21);
	printf("Length: %d  ", length);
	gotoxy(33,23);
	printf("☆: %d  ", length-3);
	gotoxy(33,25);
	printf("Time: %.3f  ", gametime);
	Sleep(70);
	gotoxy(8,12);
	printf("┌─────────────────────────────┐ ");
	gotoxy(8,14);
	printf("└─────────────────────────────┘ ");
	Sleep(70);
	gotoxy(8,12);
	printf("                               ");
	gotoxy(8,14);
	printf("                               ");
	gotoxy(8,9);
	printf("┌─────────────────────────────┐ ");
	gotoxy(8,17);
	printf("└─────────────────────────────┘ ");
	Sleep(70);
	gotoxy(8,9);
	printf("                               ");
	gotoxy(8,17);
	printf("                               ");
	gotoxy(8,6);
	printf("┌─────────────────────────────┐ ");
	gotoxy(8,20);
	printf("└─────────────────────────────┘ ");
	Sleep(70);
	gotoxy(8,6);
	printf("                               ");
	gotoxy(8,20);
	printf("                               ");
	gotoxy(8,4);
	printf("┌─────────────────────────────┐ ");
	gotoxy(8,23);
	printf("└─────────────────────────────┘ ");
	options = 1;
	optionp = 1;
	optionscreen();
	while(1){
		if(_kbhit()){
			key = _getch();
			if(key==UP){
				if(optionp==1){
					if(options==1){
						options=5;
					}
					else{
						options--;
					}
				}
				else if(optionp==2){
					if(options==1){
						options=5;
					}
					else{
						options--;
					}
				}
				else if(optionp==3){
					if(options==1){
						options=3;
					}
					else{
						options--;
					}
				}
				optionscreen();
			}
			else if(key==DOWN){
				if(optionp==1){
					if(options==5){
						options=1;
					}
					else{
						options++;
					}
				}
				else if(optionp==2){
					if(options==5){
						options=1;
					}
					else{
						options++;
					}
				}
				else if(optionp==3){
					if(options==3){
						options=1;
					}
					else{
						options++;
					}
				}
				optionscreen();
			}
			else if(key==ENTER){
				if(optionp==1){
					if(options==1){
						Sleep(70);
						gotoxy(8,4);
						printf("┌─────────────────────────────┐ ");
						gotoxy(8,23);
						printf("└─────────────────────────────┘ ");
						Sleep(70);
						gotoxy(8,4);
						printf("                               ");
						gotoxy(8,23);
						printf("                               ");
						gotoxy(13,21);
						printf("                               "); // exit 지우기 
						gotoxy(8,6);
						printf("┌─────────────────────────────┐ ");
						gotoxy(8,20);
						printf("└─────────────────────────────┘ ");
						Sleep(70);
						gotoxy(8,6);
						printf("                               ");
						gotoxy(8,20);
						printf("                               ");
						gotoxy(13,18);
						printf("                               "); // setting 지우기 
						gotoxy(8,9);
						printf("┌─────────────────────────────┐ ");
						gotoxy(8,17);
						printf("└─────────────────────────────┘ ");
						Sleep(70);
						gotoxy(8,9);
						printf("                               ");
						gotoxy(8,17);
						printf("                               ");
						gotoxy(13,15);
						printf("                               "); // restart 지우기
						gotoxy(13,12);
						printf("                               "); // continue 지우기
						gotoxy(8,12);
						printf("┌─────────────────────────────┐ ");
						gotoxy(8,14);
						printf("└─────────────────────────────┘ ");
						Sleep(70);
						room();
						gotoxy(food_x,food_y);
						printf("☆");
						int oi;
						for(oi=length;oi>0;oi--){
							gotoxy(lx[length-1],ly[length-1]);
							printf("ㅇ");
						}
					break;	
					}
					else if(options==2){
						start();
						break;
					}
					else if(options==3){
						title();
						break;
					}
					else if(options==4){
						options=1;
						optionp=2;
						optionscreen();
					}
					else if(options==5){
						pexit = 1;
						break;
					}
				}
				else if(optionp==2){
					if(options==4){
						//맵설정 
					}
					else if(options==5){
						options = 1;
						optionp = 1;
						optionscreen();
					}
					else if(options==3){
						options = 1;
						optionp = 3;
						optionscreen();
					}
				}
				else if(optionp==3){
					if(options==3){
						options = 1;
						optionp = 2;
						optionscreen();
					}
				}
			}
			else if(key==ESC){
				if(optionp==1){
					Sleep(70);
					gotoxy(8,4);
					printf("┌─────────────────────────────┐ ");
					gotoxy(8,23);
					printf("└─────────────────────────────┘ ");
					Sleep(70);
					gotoxy(8,4);
					printf("                               ");
					gotoxy(8,23);
					printf("                               ");
					gotoxy(13,21);
					printf("                               "); // exit 지우기 
					gotoxy(8,6);
					printf("┌─────────────────────────────┐ ");
					gotoxy(8,20);
					printf("└─────────────────────────────┘ ");
					Sleep(70);
					gotoxy(8,6);
					printf("                               ");
					gotoxy(8,20);
					printf("                               ");
					gotoxy(13,18);
					printf("                               "); // setting 지우기 
					gotoxy(8,9);
					printf("┌─────────────────────────────┐ ");
					gotoxy(8,17);
					printf("└─────────────────────────────┘ ");
					Sleep(70);
					gotoxy(8,9);
					printf("                               ");
					gotoxy(8,17);
					printf("                               ");
					gotoxy(13,15);
					printf("                               "); // restart 지우기
					gotoxy(13,12);
					printf("                               "); // continue 지우기
					gotoxy(8,12);
					printf("┌─────────────────────────────┐ ");
					gotoxy(8,14);
					printf("└─────────────────────────────┘ ");
					Sleep(70);
					room();
					gotoxy(food_x,food_y);
					printf("☆");
					int oi;
					for(oi=length;oi>0;oi--){
						gotoxy(lx[length-1],ly[length-1]);
						printf("ㅇ");
					}
					break;	
				}
				else if(optionp==2){
					options = 1;
					optionp = 1;
					optionscreen();
				}
				else if(optionp==3){
					options = 1;
					optionp = 2;
					optionscreen();
				}
			}
		}
	}
}

int main(){
	int l = 0;
	gamestart = 1;
	system("mode con: cols=90 lines=28");
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.bVisible = 0;
	cursorInfo.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	title();
	while(1){
		if(pexit==1){
			system("cls");
			return 0;
		}
		if(gamestart==1){
			if(l%5==0){
				if(_kbhit()){
					key = _getch();
					if(key == P){
						pause();
					}
					else if(key == G){
						if(gm == 0){
							gm = 1;
						}
						else{
							gm = 0;
							gotoxy(33,11);
							printf("               ");
							gotoxy(33,13);
							printf("               ");
							gotoxy(33,15);
							printf("               ");
							gotoxy(0,0);
							printf("                                                                                          ", gxy);
							for(gxy=0;gxy<28;gxy++){
								gotoxy(0,gxy);
								printf("  ", gxy);
							}
						}
					}
					else if(key==ESC){
						option();
					}
					else{
						direction(key);
					}
				}
			}
			if(l==10){
				move();
				l=0;
			}
			Sleep(10);
			l++;
			if(l%10==0){
				gov = clock();
				gametime = (double)(gov-gst)/1000;
				score++;
				gotoxy(33,19);
				printf("Score: %d  ", score);
				gotoxy(33,21);
				printf("Length: %d  ", length);
				gotoxy(33,23);
				printf("☆: %d  ", length-3);
				gotoxy(33,25);
				printf("Time: %.3f  ", gametime);
				if(length-3 == 0){
					if(score>199){
						if(score<401){
							gotoxy(32,5);
							printf("Hey, are you really not");
							gotoxy(32,6);
							printf("going to eat that star?");
						}
						else if(score<601){
							gotoxy(32,5);
							printf("If you eat that star,   ");
							gotoxy(32,6);
							printf("you'll get 50 points.   ");	
						}
						else if(score<801){
							gotoxy(32,5);
							printf("Yeah, whatever you want.   ");
							gotoxy(32,6);
							printf("                       ");	
						}
						else{
							gotoxy(32,5);
							printf("                       ");
							gotoxy(32,6);
							printf("                       ");
						}
					}
				}
				else{
					gotoxy(32,5);
					printf("                       ");
					gotoxy(32,6);
					printf("                       ");
				}
			}
		}
	}	
	return 0;
}
