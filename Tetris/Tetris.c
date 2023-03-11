#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define ENTER 13
#define SPACE 32
#define p 112
#define z 122
#define Z 90
#define c 99
#define C 67

// ←,→: 좌우이동 | ↑시계방향으로 돌리기 | z 반시계방향으로 돌리기 | ↓소프트드랍 | space 하드드랍 | c 홀드 //


int ts;
int key;
int titleexit = 0;
int i, j;
int ran;
int ran2;int block_x;
int block_y;
int block_l;
int block_t;
int l;
int next = 0;
int bbxy[10][27];
int bcxy[10][27];
int ci;
int ci2;
int ci3;
int ci4;
int i2;
int i22;
int bl;
int br[7];
int sstop;
int sby;
int i222;
int nextblock = 10;
int score = 0;
int sblock = 0;
float playtime;
int restart;
float pausetime = 0;
int hold = 10;

int bmir = 0;
int bmil = 0;
int bmiu = 0;
int bmid = 0;

clock_t start, over, pstart, pend;

int blocks[7][4][4][4]={
{{0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0},{0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0},
 {0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0},{0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0}},
{{0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0},{0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0},
 {0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0},{0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0}},
{{0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0},{0,0,0,0,0,0,1,0,0,1,1,0,0,1,0,0},
 {0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0},{0,0,0,0,0,0,1,0,0,1,1,0,0,1,0,0}},
{{0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0},{0,0,0,0,1,0,0,0,1,1,0,0,0,1,0,0},
 {0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0},{0,0,0,0,1,0,0,0,1,1,0,0,0,1,0,0}},
{{0,0,0,0,0,0,1,0,1,1,1,0,0,0,0,0},{0,0,0,0,1,1,0,0,0,1,0,0,0,1,0,0},
 {0,0,0,0,0,0,0,0,1,1,1,0,1,0,0,0},{0,0,0,0,0,1,0,0,0,1,0,0,0,1,1,0}},
{{0,0,0,0,1,0,0,0,1,1,1,0,0,0,0,0},{0,0,0,0,0,1,0,0,0,1,0,0,1,1,0,0},
 {0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,0},{0,0,0,0,0,1,1,0,0,1,0,0,0,1,0,0}},
{{0,0,0,0,0,1,0,0,1,1,1,0,0,0,0,0},{0,0,0,0,0,1,0,0,0,1,1,0,0,1,0,0},
 {0,0,0,0,0,0,0,0,1,1,1,0,0,1,0,0},{0,0,0,0,0,1,0,0,1,1,0,0,0,1,0,0}}
};

void shadowblockremove();

void blockrandom();

void gotoxy(int x, int y){
	COORD pos = {x*2,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void gotoxy2(int x, int y){
	COORD pos = {x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void outline(){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0C);
	gotoxy(4,5);
	printf("────────────────────");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
} 

void room(){
	system("cls");
	for(i=0;i<24;i++){
		gotoxy(3,3+i);
		printf("▩");
		gotoxy(14,3+i);
		printf("▩");
	}
	outline();
	gotoxy(3,27);
	printf("▩▩▩▩▩▩▩▩▩▩▩▩");
	gotoxy(17,23);
	printf("  ┌────────────────┐");
	gotoxy(17,24);
	printf("  │ Next:          │");
	gotoxy(17,25);
	printf("  │                │");
	gotoxy(17,26);
	printf("  │                │");
	gotoxy(17,27);
	printf("  └────────────────┘");
	gotoxy(18,14);
	printf("┌─────────────────────────┐");
	gotoxy(18,15);
	printf("│                         │");
	gotoxy(18,16);
	printf("│                         │");
	gotoxy(18,17);
	printf("│                         │");
	gotoxy(18,18);
	printf("│                         │");
	gotoxy(18,19);
	printf("│                         │");
	gotoxy(18,20);
	printf("│                         │");
	gotoxy(18,21);
	printf("│                         │");
	gotoxy(18,22);
	printf("└─────────────────────────┘");
	gotoxy(17,3);
	printf("  ┌────────────────┐");
	gotoxy(17,4);
	printf("  │ Hold:          │");
	gotoxy(17,5);
	printf("  │                │");
	gotoxy(17,6);
	printf("  │                │");
	gotoxy(17,7);
	printf("  └────────────────┘");
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			if(blocks[hold][0][i][j]==1){
				gotoxy(19+j+3,4+i);
				printf("■");
			}
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
	gotoxy(17,8);
	printf("  ┌────────────────────┐");
	gotoxy(17,9);
	printf("  │  ←, →: Move      │");
	gotoxy(17,10);
	printf("  │  ↑, z : Turn      │");
	gotoxy(17,11);
	printf("  │  ↓, Space : drop  │");
	gotoxy(17,12);
	printf("  │   C : Hold         │");
	gotoxy(17,13);
	printf("  └────────────────────┘");
}
// 세로 22 가로 12

// ←,→: 좌우이동 | ↑시계방향으로 돌리기 | z 반시계방향으로 돌리기 | ↓소프트드랍 | space 하드드랍 | c 홀드 //

void title(){
	char highscore[100];
	unsigned int highs;
	unsigned int highs2;
	char numbersize = 0;
	FILE *ff;
	ff = fopen("D:\\Tetris High Score.txt", "r");
	if(ff == NULL){
		gotoxy(12,15);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0C);
		printf("High Score File Open Failed");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
	}
	else{
		fgets(highscore,200,ff);
		highs = atoi(highscore);
		highs2 = highs;
		while(highs2 != 0){
			highs2 /= 10;
			++numbersize;
		}
		gotoxy(12,14);
		printf("┌────────────────────────┐");
		gotoxy(12,15);
		printf("│                        │");
		gotoxy(12,16);
		printf("└────────────────────────┘");
		gotoxy2(31-numbersize/2,15);
		printf("High Score: %d", highs);
	}
	fclose(ff);
	gotoxy(16,10);
	printf("ＴＥＴＲＩＳ");
	ts = 1;
	while(1){
		if(ts==1){
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0C);
			gotoxy(16,18);
			printf(" ┌ ");
			gotoxy(17,19);
			printf(" START ");
			gotoxy(16,20);
			printf("        ┘ ");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
			gotoxy(16,20);
			printf("   ");
			gotoxy(15,21);
			printf("     EXIT ");
			gotoxy(16,22);
			printf("          ");
		}
		else if(ts==2){
			gotoxy(16,18);
			printf("   ");
			gotoxy(15,19);
			printf("     START ");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0C);
			gotoxy(16,20);
			printf(" ┌       ");
			gotoxy(15,21);
			printf("     EXIT ");
			gotoxy(16,22);
			printf("       ┘ ");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
		}
		if(_kbhit()){
			key = _getch();
			if(key==UP){
				if(ts==1){
					ts = 2;
				}
				else{
					ts--;
				}
			}
			else if(key==DOWN){
				if(ts==2){
					ts = 1;
				}
				else{
					ts++;
				}
			}
			else if(key==ENTER){
				if(ts==2){
					titleexit = 1;
					break;
				}
				else if(ts==1){
					break;
				}
			}
		}
	}
}
// a b c d f 8
int whatcolor(int cn){
	if(cn == 0){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0A);
	}
	else if(cn == 1){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0B);
	}
	else if(cn == 2){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0C);
	}
	else if(cn == 3){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0D);
	}
	else if(cn == 4){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0E);
	}
	else if(cn == 5){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x08);
	}
	else if(cn == 6){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x06);
	}
	return 0;
}

void block(){
	whatcolor(block_t);
	//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0B);
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			if(blocks[block_t][block_l][i][j]==1){
				gotoxy(4+j+block_x,i+block_y);
				printf("■");
			}
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
}

void blockclear(){
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			if(blocks[block_t][block_l][i][j]==1){
				gotoxy(4+j+block_x,i+block_y);
				printf("  ");
			}
		}
	}
}

void pause(){
	pstart = clock();
	int pi = 0;
	gotoxy(18,2);
	printf(" ＰＡＵＳＥ");
	while(!_kbhit()){
		if(pi==5){
			gotoxy(18,2);
			printf("             ");
		}
		else if(pi==10){
			gotoxy(18,2);
			printf(" ＰＡＵＳＥ");
			pi = 0;
		}
		Sleep(100);
		pi++;
	}
	gotoxy(18,2);
	printf("           ");
	pend = clock();
	pausetime += (float)(pend-pstart)/1000;
	while (_kbhit()) _getch();
}

int blockmove(){
	if(_kbhit()){
		
		key = _getch();
		
		
		if(key == p){
			pause();
		}
		
		else if(key == RIGHT){
			for(i=0;i<4;i++){
				for(j=0;j<4;j++){
					if(blocks[block_t][block_l][i][j]==1){
						if(4+j+block_x+1 == 14){
							return 0;
						}
						if(bbxy[j+block_x+1][i+block_y-1] == 1){
							return 0;
						}
					}
				}
			}
			shadowblockremove();
			blockclear();
			outline();
			block_x++;
			block();

		}
		else if(key == LEFT){

			for(i=0;i<4;i++){
				for(j=0;j<4;j++){
					if(blocks[block_t][block_l][i][j]==1){
						if(4+j+block_x-1 == 3){
							return 0;
						}
						if(bbxy[j+block_x-1][i+block_y-1] == 1){
							return 0;
						}
					}
				}
			}
			shadowblockremove();
			blockclear();
			outline();
			block_x--;
			block();

		}
		else if(key == UP){
			bl = block_l;
			bl++;
			if(bl == 4) bl = 0;
			for(i=0;i<4;i++){
				for(j=0;j<4;j++){
					if(blocks[block_t][bl][i][j]==1){
						if(4+j+block_x == 3){
							return 0;
						}
						else if(bbxy[j+block_x][i+block_y] == 1){
							return 0;
						}
						else if(4+j+block_x == 14){
							return 0;
						}
						else if(bbxy[j+block_x][i+block_y] == 1){
							return 0;
						}
					}
				} 
			}
			shadowblockremove();
			blockclear();
			outline();
			block_l++;
			if(block_l == 4) block_l = 0;
			block();
		}
		else if(key == DOWN){

			outline();
			for(i=0;i<4;i++){
				for(j=0;j<4;j++){
					if(blocks[block_t][block_l][i][j]==1){
						if(i+block_y+1 == 27){
							score+=1;
							next = 1;
							break;
						}
						else if(bbxy[j+block_x][i+block_y] == 1){
							score+=1;
							next = 1;
							break;
						}
					}
				}
			}
			if(next!=1){
				shadowblockremove();
				blockclear();
				outline();
				block_y++;
				block();
				l = 0;
			}

		}
				
		else if(key == Z || key == z){
			bl = block_l;
			bl--;
			if(bl == -1) bl = 3;
			for(i=0;i<4;i++){
				for(j=0;j<4;j++){
					if(blocks[block_t][bl][i][j]==1){
						if(4+j+block_x == 3){
							return 0;
						}
						else if(bbxy[j+block_x][i+block_y] == 1){
							return 0;
						}
						else if(4+j+block_x == 14){
							return 0;
						}
						else if(bbxy[j+block_x][i+block_y] == 1){
							return 0;
						}
					}
				} 
			}
			shadowblockremove();
			blockclear();
			outline();
			block_l--;
			if(block_l == -1) block_l = 3;
			block();
		}
		else if(key == C || key == c){
			for(i=0;i<4;i++){
				for(j=0;j<4;j++){
					if(blocks[hold][bl][i][j]==1){
						if(4+j+block_x == 3){
							return 0;
						}
						else if(bbxy[j+block_x][i+block_y] == 1){
							return 0;
						}
						else if(4+j+block_x == 14){
							return 0;
						}
						else if(bbxy[j+block_x][i+block_y] == 1){
							return 0;
						}
					}
				} 
			}
			blockclear();
			shadowblockremove();
			outline();
			if(hold != 10){
				int ahold = hold;
				hold = block_t;
				block_t = ahold;
			}
			else{
				hold = block_t;
				blockrandom();
			}
			gotoxy(17,5);
			printf("  │                │");
			gotoxy(17,6);
			printf("  │                │");
			whatcolor(hold);
			for(i=0;i<4;i++){
				for(j=0;j<4;j++){
					if(blocks[hold][0][i][j]==1){
						gotoxy(19+j+3,4+i);
						printf("■");
					}
				}
			}
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
			block();
		}
		else if(key == 32){
			for(i2=0;i2<25;i2++){
				for(i=0;i<4;i++){
					for(j=0;j<4;j++){
						if(blocks[block_t][block_l][i][j]==1){
							if(i+block_y+1 == 27){
								outline();
								next = 1;
								break;
							}
							else if(bbxy[j+block_x][i+block_y] == 1){
								outline();
								next = 1;
								break;
							}
						}
					}
				}
				if(next!=1){
					shadowblockremove();
					blockclear();
					block_y++;
					block();
					l = 0;
				}
				if(next==1){
					score+=2;
					return 0;
				}
				
			}
			
		}
	}
	return 0;
}
//int bbxy[10][27];
//아래서부터 설정되게 하기. 
void checkline(){
	ci3 = 0;
	int sss = 0;
	int lcc = 0;
	for(ci=0;ci<23;ci++){
		ci3 = 0;
		for(ci2=0;ci2<10;ci2++){
			if(bbxy[ci2][ci+3]==1){
				ci3++;
			}
		}
		if(ci3==10){
			sss+=10;
			lcc++;
			if(lcc==2){
				sss+=25;
			}
			else if(lcc==3){
				sss+=45;
			}
			else if(lcc==4){
				sss+=65;
			}
			shadowblockremove();
			ci4 = ci;
			for(ci2=0;ci2<10;ci2++){
				bbxy[ci2][ci+3]=0;
				gotoxy(ci2+4,ci+4);
				whatcolor(bcxy[ci2][ci+3]);
				printf("□");
			}
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
			Sleep(100);
			for(ci2=0;ci2<10;ci2++){
				bbxy[ci2][ci+3]=0;
				gotoxy(ci2+4,ci+4);
				Sleep(10);
				printf("  ");
				sss++;
				gotoxy(19,18);
				printf(" Score: %d", score);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0E);
				printf(" + %d       ", sss);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
			}
			//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0B);
			for(ci=ci4;ci>0;ci--){
				for(ci2=0;ci2<10;ci2++){
					i222 = 1;
					for(i22=ci-1;i22>0;i22--){
						if(bbxy[ci2][i22+3] != 0){
							i222 = 1;
							break;
						}
						else{
							i222 = 0;
						}
					}
					//*/
					//if(ci==ci4){
					//	bbxy[ci2][ci+3] = bbxy[ci2][ci+2];
					//}
					if(i222 == 1){
						bbxy[ci2][ci+3] = bbxy[ci2][ci+2];
						bcxy[ci2][ci+3] = bcxy[ci2][ci+2];
					}
					//bbxy[ci2][ci+3] = bbxy[ci2][ci+2];
					gotoxy(ci2+4,ci+4);
					if(bbxy[ci2][ci+3]==1){
						whatcolor(bcxy[ci2][ci+3]);
						printf("■");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
					}
					else{
						printf("  ");
					}
				}
			}
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
			for(ci2=0;ci2<10;ci2++){
				for(ci=0;ci<ci4;ci++){
					if(bbxy[ci2][ci+3]==1){
						bbxy[ci2][ci+3] = 0;
						gotoxy(ci2+4,ci+4);
						printf("  ");
						break;
					}
				}
			}
				
		}
		
	}
	if(lcc>0){
		Sleep(100);
		score += sss;
		gotoxy(19,18);
		printf(" Score: %d     ", score);
		for(ci=ci4;ci>0;ci--){
			for(ci2=0;ci2<10;ci2++){
				gotoxy(ci2+4,ci+4);
				if(bbxy[ci2][ci+3]==1){
					whatcolor(bcxy[ci2][ci+3]);
					printf("■");
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
				}
				else{
					printf("  ");
				}
			}
		}
	}
}

void randomnextblock(){
	if(br[0] == 1&&br[1] == 1&&br[2] == 1&&br[3] == 1&&br[4] == 1&&br[5] == 1&&br[6] == 1){
		for(i=0;i<7;i++){
			br[i] = 0;
		}
	}
	nextblock = rand()%7;
	if(br[nextblock] == 0){
		br[nextblock] = 1;
	}
	else if(nextblock == block_t){
		randomnextblock();
	}
	else{
		randomnextblock();
	}
}

void blockrandom(){ // 0 ~ 6
	if(nextblock==10){
		nextblock = rand()%7;
		br[nextblock] = 1;
	}
	block_t = nextblock;
	randomnextblock();
	gotoxy(17,25);
	printf("  │                │");
	gotoxy(17,26);
	printf("  │                │");
	whatcolor(nextblock);
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			if(blocks[nextblock][0][i][j]==1){
				gotoxy(19+j+3,24+i);
				printf("■");
			}
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
}

void shadowblockremove(){
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			if(blocks[block_t][block_l][i][j]==1){
				gotoxy(4+j+block_x,i+sby);
				printf("  ");
			}
		}
	}
}

void shadowblock(){
	sby = block_y;
	sstop = 0;
	for(i2=0;i2<25;i2++){
		for(i=0;i<4;i++){
			for(j=0;j<4;j++){
				if(blocks[block_t][block_l][i][j]==1){
					if(i+sby+1 == 27){
						sstop = 1;
						break;
					}
					if(bbxy[j+block_x][i+sby] == 1){
						sstop = 1;
						break;
					}
				}
			}
			if(sstop==1){
				break; 
			}
		}
		if(sstop==1){
			if(block_y < sby-5){
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x08);
				for(i=0;i<4;i++){
					for(j=0;j<4;j++){
						if(blocks[block_t][block_l][i][j]==1){
							gotoxy(4+j+block_x,i+sby);
							printf("□");
						}
					}
				}
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
			}
			break;
		}
		else{
			sby++;
		}
				
	}
}

void gameover(){
	char highscore[100];
	int highs = 0;
	char* ascore;
	char buff[100];
	FILE *ff;
	ff = fopen("D:\\Tetris High Score.txt", "r");
	fgets(highscore,200,ff);
	highs = atoi(highscore);
	fclose(ff);
	if(score > highs){
		ff = fopen("D:\\Tetris High Score.txt", "w");
		ascore = itoa(score, buff, 10);
		fputs(ascore ,ff);
		fclose(ff);
	}
	system("cls");
	gotoxy(15,9);
	printf("ＧＡＭＥ ＯＶＥＲ");
	int gs = 0;
	Sleep(500);
	while (_kbhit()) _getch();
	while(!_kbhit()){
		gotoxy(16,12);
		printf("Score: %d ", gs);
		if(gs >= score){
			break;
		}
		else if(score / 10 < 1){
			++gs;
		}
		else{
			gs += score / 10;
		}
		Sleep(20);
	}
	gotoxy(16,12);
	printf("Score: %d", score);
	gs = 0;
	Sleep(200);
	while (_kbhit()) _getch();
	while(!_kbhit()){
		gotoxy(16,14);
		printf("Block: %d", gs);
		if(gs >= sblock){
			break;
		}
		else if(sblock / 10 < 1){
			++gs;
		}
		else{
			gs += sblock / 10;
		}
		Sleep(20);
	}
	gotoxy(16,14);
	printf("Block: %d", sblock);
	gs = 0;
	while (_kbhit()) _getch();
	while(!_kbhit()){
		gotoxy(16,16);
		printf("Playtime: %d/s", gs);
		if(gs >= playtime-pausetime){
			break;
		}
		else if((playtime-pausetime) / 10 < 1){
			++gs;
		}
		else{
			gs += (playtime-pausetime) / 10;
		}
		Sleep(20);
	}
	int hour = 0;
	int minute = 0;
	int second = 0;
	over = clock();
	playtime = (float)(over-start)/1000;
	gotoxy(16,16);
	if(playtime-pausetime>59){
		second = (int)(playtime-pausetime)%60;
		minute = (int)(playtime-pausetime)/60;
		if(minute > 59){
			minute = minute%60;
			hour = minute/60;
		}
	}
	else{
		second = (int)(playtime-pausetime);
	}
	gotoxy(16,16);
	printf("Playtime: %dh %dm %ds", hour, minute, second);
	gotoxy(16,18);
	printf("High Score: %d", highs);
	while (_kbhit()) _getch();
	gs = 0;
	gotoxy(13,21);
	printf(" Press Any Key To Replay");
	while(!_kbhit()){
		if(gs==6){
			gotoxy(13,21);
			printf("                         ");
		}
		else if(gs==10){
			gotoxy(13,21);
			printf(" Press Any Key To Replay");
			gs = 0;
		}
		Sleep(100);
		gs++;		
	}
	block_x = 5;
	block_y = 0;
	block_l = 0;
	for(i=0;i<7;i++){
		br[i] = 0;
	}
	start = clock();
	int rei, rei2;
	for(rei=0;rei<10;rei++){
		for(rei2=0;rei2<27;rei2++){
			bbxy[rei][rei2] = 0;
			bcxy[rei][rei2] = 0;
		}
	}
	sblock = 0;
	score = 0;
	system("cls");
	room();
	l = 0;
	next = 0;
	nextblock = 10;
	pausetime = 0;
	hold = 10;
	while (_kbhit()) _getch();
}

int main(){
	system("title Tetris");
	system("mode con: cols=75 lines=31");
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.bVisible = 0;
	cursorInfo.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	srand(time(NULL));
	title();
	if(titleexit == 1){
		return 0;
	}
	room();
	for(i=0;i<7;i++){
		br[i] = 0;
	}
	start = clock();
	restart = 0;
	while(1){
		block_x = 3;
		block_y = 0;
		block_l = 0;
		//block_t = 1;
		blockrandom();
		shadowblock();
		l = 0;
		block();
		gotoxy(19,16);
		printf(" Block: %d", sblock);
		gotoxy(19,18);
		printf(" Score: %d", score);
		while(1){
			int hour = 0;
			int minute = 0;
			int second = 0;
			over = clock();
			playtime = (float)(over-start)/1000;
			gotoxy(19,20);
			if(playtime-pausetime>59){
				second = (int)(playtime-pausetime)%60;
				minute = (int)(playtime-pausetime)/60;
				if(minute > 59){
					minute = minute%60;
					hour = minute/60;
				}
			}
			else{
				second = (int)(playtime-pausetime);
			}
			printf(" Playtime: %dh %dm %ds ", hour, minute, second);
			shadowblock();
			checkline();
			if(next==1){
				next = 0;
				Beep(750, 100);
				for(i=0;i<4;i++){
					for(j=0;j<4;j++){
						if(blocks[block_t][block_l][i][j]==1){
							bbxy[j+block_x][i+block_y-1] = 1;
							bcxy[j+block_x][i+block_y-1] = block_t;
							if(i+block_y==5){
								gameover();
								restart = 1;
								break;
							}
						}
					}
					if(restart==1){
						break;
					}
				}
				if(restart==1){
					break;
				}
				sblock++;
				score+=2;
				break;
			}
			if(restart==1){
				restart = 0;
				system("cls");
				room();
				break;
			} 
			if(l==70){
				if(next!=1){
					for(i=0;i<4;i++){
						for(j=0;j<4;j++){
							if(blocks[block_t][block_l][i][j]==1){
								if(i+block_y+1 == 27){
									next = 1;
									break;
								}
								else if(bbxy[j+block_x][i+block_y] == 1){
									next = 1;
									break;
								}
							}
						}
					}
					
					if(next!=1){
						blockclear();
						outline();
						block_y++;
						block();
						l = 0;
					}
				}
			}
			blockmove();
			l++;
			
			if(bmir > 0){
				--bmir;
			}
			if(bmil > 0){
				--bmil;
			}
			if(bmiu > 0){
				--bmiu;
			}
			if(bmid > 0){
				--bmid;
			}
			Sleep(10);
		}
	}
	return 0;
} 


	//for(i=0;i<4;i++){
		//for(j=0;j<4;j++){
			//if(blocks[2][1][i][j]==1){
				//gotoxy(3+j,3+i);
				//printf("■");
			//}
		//}
	//}	
