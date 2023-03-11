#include <iostream>
#include <Windows.h>
#include <fstream>
#define SPACE 32
#define SHIFT 16

using namespace std;

ifstream file_read; //파일 읽기 객체

int map[150][43] = { };

char foot_text[2][3][4] = { {"_^.", "-^.", "_^'"}, {".^_", ".^-", "'^_"}};

void gotoxy(int x, int y) {
	COORD pos = { (short)x ,(short)y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void paintcheck(int paint)
{
	if (paint == 'Z') printf(" ");
	else if (paint >= 0 && paint <= 9) printf("%d", paint);
	else if (paint == 'a') printf("*");
	else if (paint == 'b') printf("@");
	else if (paint == 'c') printf("※");
	else if (paint == 'd') printf("＆");
	else if (paint == 'e') printf("＃");
	else if (paint == 'f') printf("☆");
	else if (paint == 'g') printf("★");

	else if (paint == 'h') printf("○");
	else if (paint == 'i') printf("●");
	else if (paint == 'j') printf("◎");
	else if (paint == 'k') printf("◇");
	else if (paint == 'l') printf("◆");
	else if (paint == 'm') printf("□");

	else if (paint == 'n') printf("■");
	else if (paint == 'o') printf("△");
	else if (paint == 'p') printf("▲");
	else if (paint == 'q') printf("▽");
	else if (paint == 'r') printf("▼");
	else if (paint == 's') printf("→");

	else if (paint == 't') printf("←");
	else if (paint == 'u') printf("↑");
	else if (paint == 'v') printf("↓");
	else if (paint == 'w') printf("↔");
	else if (paint == 'x') printf("〓");
	else if (paint == 'y') printf("◁");

	else if (paint == 'z') printf("◀");
	else if (paint == 'A') printf("▷");
	else if (paint == 'B') printf("▶");
	else if (paint == 'C') printf("♤");
	else if (paint == 'D') printf("♠");
	else if (paint == 'E') printf("♡");

	else if (paint == 'F') printf("♥");
	else if (paint == 'G') printf("♧");
	else if (paint == 'H') printf("♣");
	else if (paint == 'I') printf("⊙");
	else if (paint == 'J') printf("◈");
	else if (paint == 'K') printf("▣");

	else if (paint == 'L') printf("◐");
	else if (paint == 'M') printf("◑");
	else if (paint == 'N') printf("▒");
	else if (paint == 'O') printf("▤");
	else if (paint == 'P') printf("▥");
	else if (paint == 'Q') printf("▨");

	else if (paint == 'R') printf("▧");
	else if (paint == 'S') printf("▦");
	else if (paint == 'T') printf("▩");
	else if (paint == 'U') printf("♨");
	else if (paint == 'V') printf("☜");
	else if (paint == 'W') printf("☞");
}

void mapDraw() {
	for (int x = 0; x < 149; x++) {
		for (int y = 0; y < 43; y++) {
			gotoxy(x, y);
			paintcheck(map[x][y]);
		}
	}
}

void mapLoad(string name) {
	name = "C:\\\\rpg게임\\\\" + name + ".txt";
	file_read.open(name);
	if (!file_read) {
		gotoxy(45, 20);
		cout << "오류: " << name << "이라는 맵 파일이 없습니다.";
		Sleep(1000);
		mapDraw();
	}
	else {
		gotoxy(45, 20);
		cout << name << "파일에서 맵을 불러옵니다.";
		char temp = 0;
		gotoxy(0, 0);
		for (int y = 0; y < 43; y++) {
			for (int x = 0; x < 149; x++) {
				file_read >> temp;
				map[x][y] = temp;
			}
		}
		Sleep(1000);
		mapDraw();
	}
	file_read.close();
}

// O
//o|)
//_^.
//-^.
//_^'
//
// O
//(|o
//.^_
//.^-
//'^_

class Hero {
public:
	int age = 19;
	int hp = 100;
	int level = 0;
	int exp = 0;
	int ad = 10; // 물리공격력
	int ap = 0; // 마법공격력
	int pd = 0; // 물리방어력
	int md = 0; // 마법방어력
	char direction = 'L';
	int speed = 5; //커질수록 느린거
	int jump_power = 8; //점프력
	//x,y 기준은 가운데 발
	int x = 20;
	int y = 10;
	float foot_count = 0; //발 움직임 카운트
	int jump_count = 0; //점프 카운트
	int unGravity_count = 0; //무중력 카운트
	int shift_delay_count = 0;

	//키보드 입력받는 함수 
	//

	void erase() {
		gotoxy(x, y - 2);
		printf(" ");
		gotoxy(x - 1, y - 1);
		printf("   ");
		gotoxy(x - 1, y);
		printf("   ");
	}
	//출력
	void charPrint() {
		if (direction == 'L') {
			gotoxy(x - 1, y - 2);
			printf(" 0");
			gotoxy(x - 1, y - 1);
			printf("o|)");
			gotoxy(x - 1, y);
			cout << foot_text[0][(int)foot_count];
		}
		else if (direction == 'R') {
			gotoxy(x - 1, y - 2);
			printf(" 0");
			gotoxy(x - 1, y - 1);
			printf("(|o");
			gotoxy(x - 1, y);
			cout << foot_text[1][(int)foot_count];
		}
		
	}
	bool move(string direction) {
		if (!GetAsyncKeyState(SHIFT) & 0x8000) shift_delay_count = 0;

		if (direction == "right") {
			if (shift_delay_count > 0) {
				shift_delay_count--;
			}
			else {
				if (map[x + 2][y] == 'Z' and map[x + 2][y - 1] == 'Z' and map[x + 2][y - 2] == 'Z') {
					x++;
					if (GetAsyncKeyState(SHIFT) & 0x8000) shift_delay_count += 3;
				}
				else return false;
			}
		}
		else if (direction == "left") {
			if (shift_delay_count > 0) {
				shift_delay_count--;
			}
			else {
				if (map[x - 2][y] == 'Z' and map[x - 2][y - 1] == 'Z' and map[x - 2][y - 2] == 'Z') {
					x--;
					if (GetAsyncKeyState(SHIFT) & 0x8000) shift_delay_count += 3;
				}
				else return false;
			}
		}
		else if (direction == "up") {
			if (map[x][y - 3] == 'Z' and map[x - 1][y - 2] == 'Z' and map[x + 1][y - 2] == 'Z') y--;
			else return false;
		}
		else if (direction == "down") {
			if (map[x - 1][y + 1] == 'Z' and map[x][y + 1] == 'Z' and map[x + 1][y + 1] == 'Z') y++;
			else return false;
		}
		return true;
	}
	//공격
	void attack() {

	}
	//방어
	void defence() {

	}
	void gravity() {
		move("down");
	}
	void check() {
		erase();
		if (jump_count > 0) {
			move("up");
			jump_count--;
		}
		else {
			if (unGravity_count > 0) unGravity_count--;
			else gravity();
		}
		if (GetAsyncKeyState('A') & 0x8000) {
			direction = 'L';
			foot_count += 0.5;
			if (foot_count >= 3.0) foot_count = 0;
			move("left");
		}
		else if (GetAsyncKeyState('D') & 0x8000) {
			direction = 'R';
			foot_count += 0.5;
			if (foot_count >= 3.0) foot_count = 0;
			move("right");
		}
		else {
			foot_count = 0;
		}

		if (GetAsyncKeyState(SPACE) & 0x8000) {
			if (jump_count <= 0 and (map[x - 1][y + 1] != 'Z' or map[x][y + 1] != 'Z' or map[x + 1][y + 1] != 'Z')) { //점프 중이 아니고, 발 밑이 블럭인지 체크
				unGravity_count += 2;
				jump_count = jump_power;
			}
		}
		
		charPrint();
	}
	

};
// (=O=)--=-  --=-
// ======
//(0_0_0_0)


void setConsole() {
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.bVisible = 0;
	cursorInfo.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	system("mode con: lines=43 cols=150");
}


int main() {
	setConsole();
	Hero me;
	gotoxy(me.x, me.y);
	me.charPrint();
	mapLoad("test");
	int check_count = 0;
	while (1) {
		check_count++;
		if (check_count == 2) {
			me.check();
			check_count = 0;
		}
		Sleep(10);
	}
}





