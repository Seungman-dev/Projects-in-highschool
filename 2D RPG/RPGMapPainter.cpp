#include <iostream> 
#include <Windows.h>
#include <fstream>

using namespace std;

HANDLE COUT = 0;    // 콘솔 출력 장치
HANDLE CIN = 0;        // 콘솔 입력 장치

ofstream file_write;
ifstream file_read;

string FILE_PATH = "C:\\RPG게임"; //파일 저장 경로

int buttontype = 0; //좌클, 우클 구별 변수 좌1 우2
int menumode = 0; //메뉴 구별 변수
int cuscolor = 15; //커서 색갈 저장 변수
int paint = 'a';

int map[149][43] = { };

int be_input()
{
    INPUT_RECORD input_record;
    DWORD input_count;

    PeekConsoleInput(CIN, &input_record, 1, &input_count);
    return input_count;
}

int get_input(WORD* vkey, COORD* pos)
{
    INPUT_RECORD input_record;
    DWORD input_count;

    ReadConsoleInput(CIN, &input_record, 1, &input_count);
    switch (input_record.EventType) {
    case MOUSE_EVENT:
        if (pos && (input_record.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)) {
            CONSOLE_SCREEN_BUFFER_INFO csbi;

            GetConsoleScreenBufferInfo(COUT, &csbi);

            *pos = input_record.Event.MouseEvent.dwMousePosition;
            pos->X -= csbi.srWindow.Left;
            pos->Y -= csbi.srWindow.Top;

            buttontype = 1;

            return MOUSE_EVENT;
        }
        else if (pos && (input_record.Event.MouseEvent.dwButtonState & RIGHTMOST_BUTTON_PRESSED)) {
            CONSOLE_SCREEN_BUFFER_INFO csbi;

            GetConsoleScreenBufferInfo(COUT, &csbi);

            *pos = input_record.Event.MouseEvent.dwMousePosition;
            pos->X -= csbi.srWindow.Left;
            pos->Y -= csbi.srWindow.Top;
            
            buttontype = 2;

            return MOUSE_EVENT;
        }
        break;


    }

    //    FlushConsoleInputBuffer(CIN);
    return 0;
}

void gotoxy(int x, int y)      // 좌표 보내기 gotoxy
{
    COORD Cur;
    Cur.X = x;
    Cur.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
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

void background()
{
    //system("cls");
    for (int i = 0; i < 40; i++)
    {
        gotoxy(15, i);
        printf("│");
    }

    gotoxy(2, 1);
    printf("색깔 선택");
    gotoxy(2, 3);
    printf("글자 선택");
    gotoxy(2, 5);
    printf("채우기");
    gotoxy(2, 7);
    printf("초기화");
    gotoxy(2, 9);
    printf("저장");
    gotoxy(2, 11);
    printf("불러오기");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
    gotoxy(2, 13);
    printf("그리기:좌클릭");
    gotoxy(2, 15);
    printf("지우기:우클릭");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    for (int i = 0; i < 15; i++)
    {
        gotoxy(i, 17);
        printf("─");
    }
    gotoxy(15, 17);
    printf("┤");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), cuscolor);
    gotoxy(12, 1);
    printf("■");
    gotoxy(12, 3);
    paintcheck(paint);
}


void mapDraw() {
    for (int x = 0; x < 149; x++) {
        for (int y = 0; y < 43; y++) {
            gotoxy(x+17, y);
            paintcheck(map[x][y]);
        }
    }
}

void menuclick(int x, int y)
{   
    if (menumode == 1)
    {
        if (y >= 20 && y <= 34)
        {
            cuscolor = y - 19;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), cuscolor);
            gotoxy(12, 1);
            printf("■");
        }
    }
    else if (menumode == 2)
    {
        if (y == 20 && x >= 2 && x <= 11)
        {
            paint = x - 2;
        }
        if (x == 13 && y == 20)
        {
            paint = 'a';
        }
        if ((x == 2 || x == 2 + 1) && y == 21)
        {
            paint = 'b';
        }
        if ((x == 4 || x == 4+1) && y == 21)
        {
            paint = 'c';
        }
        if ((x == 6|| x == 6+1) && y == 21)
        {
            paint = 'd';
        }
        if ((x == 8|| x == 8+1) && y == 21)
        {
            paint = 'e';
        }
        if ((x == 10|| x == 10+1) && y == 21)
        {
            paint = 'f';
        }
        if ((x == 12|| x == 12+1) && y == 21)
        {
            paint = 'g';
        }


        if ((x == 2 || x == 2 + 1) && y == 22)
        {
            paint = 'h';
        }
        if ((x == 4 || x == 4 + 1) && y == 22)
        {
            paint = 'i';
        }
        if ((x == 6 || x == 6 + 1) && y == 22)
        {
            paint = 'j';
        }
        if ((x == 8 || x == 8 + 1) && y == 22)
        {
            paint = 'k';
        }
        if ((x == 10 || x == 10 + 1) && y == 22)
        {
            paint = 'l';
        }
        if ((x == 12 || x == 12 + 1) && y == 22)
        {
            paint = 'm';
        }


        if ((x == 2 || x == 2 + 1) && y == 23)
        {
            paint = 'n';
        }
        if ((x == 4 || x == 4 + 1) && y == 23)
        {
            paint = 'o';
        }
        if ((x == 6 || x == 6 + 1) && y == 23)
        {
            paint = 'p';
        }
        if ((x == 8 || x == 8 + 1) && y == 23)
        {
            paint = 'q';
        }
        if ((x == 10 || x == 10 + 1) && y == 23)
        {
            paint = 'r';
        }
        if ((x == 12 || x == 12 + 1) && y == 23)
        {
            paint = 's';
        }


        if ((x == 2 || x == 2 + 1) && y == 24)
        {
            paint = 't';
        }
        if ((x == 4 || x == 4 + 1) && y == 24)
        {
            paint = 'u';
        }
        if ((x == 6 || x == 6 + 1) && y == 24)
        {
            paint = 'v';
        }
        if ((x == 8 || x == 8 + 1) && y == 24)
        {
            paint = 'w';
        }
        if ((x == 10 || x == 10 + 1) && y == 24)
        {
            paint = 'x';
        }
        if ((x == 12 || x == 12 + 1) && y == 24)
        {
            paint = 'y';
        }

        if ((x == 2 || x == 2 + 1) && y == 25)
        {
            paint = 'z';
        }
        if ((x == 4 || x == 4 + 1) && y == 25)
        {
            paint = 'A';
        }
        if ((x == 6 || x == 6 + 1) && y == 25)
        {
            paint = 'B';
        }
        if ((x == 8 || x == 8 + 1) && y == 25)
        {
            paint = 'C';
        }
        if ((x == 10 || x == 10 + 1) && y == 25)
        {
            paint = 'D';
        }
        if ((x == 12 || x == 12 + 1) && y == 25)
        {
            paint = 'E';
        }


        if ((x == 2 || x == 2 + 1) && y == 26)
        {
            paint = 'F';
        }
        if ((x == 4 || x == 4 + 1) && y == 26)
        {
            paint = 'G';
        }
        if ((x == 6 || x == 6 + 1) && y == 26)
        {
            paint = 'H';
        }
        if ((x == 8 || x == 8 + 1) && y == 26)
        {
            paint = 'I';
        }
        if ((x == 10 || x == 10 + 1) && y == 26)
        {
            paint = 'J';
        }
        if ((x == 12 || x == 12 + 1) && y == 26)
        {
            paint = 'K';
        }


        if ((x == 2 || x == 2 + 1) && y == 27)
        {
            paint = 'L';
        }
        if ((x == 4 || x == 4 + 1) && y == 27)
        {
            paint = 'M';
        }
        if ((x == 6 || x == 6 + 1) && y == 27)
        {
            paint = 'N';
        }
        if ((x == 8 || x == 8 + 1) && y == 27)
        {
            paint = 'O';
        }
        if ((x == 10 || x == 10 + 1) && y == 27)
        {
            paint = 'P';
        }
        if ((x == 12 || x == 12 + 1) && y == 27)
        {
            paint = 'Q';
        }

        if ((x == 2 || x == 2 + 1) && y == 28)
        {
            paint = 'R';
        }
        if ((x == 4 || x == 4 + 1) && y == 28)
        {
            paint = 'S';
        }
        if ((x == 6 || x == 6 + 1) && y == 28)
        {
            paint = 'T';
        }
        if ((x == 8 || x == 8 + 1) && y == 28)
        {
            paint = 'U';
        }
        if ((x == 10 || x == 10 + 1) && y == 28)
        {
            paint = 'V';
        }
        if ((x == 12 || x == 12 + 1) && y == 28)
        {
            paint = 'W';
        }


        /*if ((x == || x == +1) && y == )
        {
            paint = '';
        }*/
        //＠※＆＃☆★
        gotoxy(12, 3);
        paintcheck(paint);
        cout << " ";
        
    }
    if (y == 1)
    {   
        menumode = 1;
        for (int i = 0; i < 16; i++)
        {
            gotoxy(2, 19 + i);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), i);
            printf("■■■■■■");
        }
        
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        gotoxy(2, 1);
        printf("색깔 선택");
        Sleep(100);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        gotoxy(2, 1);
        printf("색깔 선택");
    }
    else if (y == 3)
    {
        menumode = 2;
        for (int i = 0; i < 16; i++)
        {
            gotoxy(2, 19 + i);
            printf("            ");
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        gotoxy(2, 20);
        printf("0123456789 *");
        gotoxy(2, 21);
        printf("＠※＆＃☆★");
        gotoxy(2, 22);
        printf("○●◎◇◆□");
        gotoxy(2, 23);
        printf("■△▲▽▼→");
        gotoxy(2, 24);
        printf("←↑↓↔〓◁");
        gotoxy(2, 25);
        printf("◀▷▶♤♠♡");
        gotoxy(2, 26);
        printf("♥♧♣⊙◈▣");
        gotoxy(2, 27);
        printf("◐◑▒ ▤▥▨");
        gotoxy(2, 28);
        printf("▧▦▩♨☜☞");
        /*gotoxy(2, 25);
        printf("");
        gotoxy(2, 25);
        printf("");
        gotoxy(2, 25);
        printf("");
        gotoxy(2, 25);
        printf("");*/
        // 
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        gotoxy(2, 3);
        printf("글자 선택");
        Sleep(100);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        gotoxy(2, 3);
        printf("글자 선택");
    }
    else if (y == 5)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        gotoxy(2, 5);
        printf("채우기");
        Sleep(100);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        gotoxy(2, 5);
        printf("채우기");
    }
    else if (y == 7)
    {
        for (int y = 0; y <= 42; y++)
        {
            for (int x = 17; x <= 165; x++) {
                map[x - 17][y] = 'Z';
                gotoxy(x, y);
                printf(" ");
            }
        }
        
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        gotoxy(2, 7);
        printf("초기화");
        Sleep(100);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        gotoxy(2, 7);
        printf("초기화");

    }
    else if (y == 9)
    {
        gotoxy(65, 19);
        cout << "이름을 입력하세요: ";
        string name;
        cin >> name;
        if (name == "취소") return;
        name = "C:\\\\rpg게임\\\\" + name + ".txt";
        file_write.open(name);
        for (int y = 0; y < 43; y++) {
            for (int x = 0; x < 149; x++) {
                if (map[x][y] > 10) {
                    file_write << (char)map[x][y];
                }
                else {
                    file_write << map[x][y];
                }
            }
            file_write << endl;
        }
        file_write.close();
        gotoxy(65, 20);
        cout << "-> " << '"' << name << '"' << "으로 저장됨.";
        gotoxy(65, 22);
        Sleep(2000);
        mapDraw();

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        gotoxy(2, 9);
        printf("저장");
        Sleep(100);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        gotoxy(2, 9);
        printf("저장");
    }
    else if (y == 11)
    {
        gotoxy(65, 19);
        cout << "이름을 입력하세요: ";
        string name;
        cin >> name;
        if (name == "취소") return;
        name = "C:\\\\rpg게임\\\\" + name + ".txt";
        file_read.open(name);
        if (!file_read) {
            gotoxy(65, 20);
            cout << "오류: " << name << "이라는 파일이 없습니다.";
            Sleep(2000);
            mapDraw();
        }
        else {
            gotoxy(65, 20);
            cout << name << "파일에서 맵을 불러옵니다.";
            char temp = 0;
            gotoxy(0, 0);
            for (int y = 0; y < 43; y++) {
                for (int x = 0; x < 149; x++) {
                    file_read >> temp;
                    map[x][y] = temp;
                }
            }
            Sleep(2000);
            mapDraw();
        }
        file_read.close();
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        gotoxy(2, 11);
        printf("불러오기");
        Sleep(100);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        gotoxy(2, 11);
        printf("불러오기");
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), cuscolor);
}

// 색갈선택, 글자선택(입력 or 선택), 채우기, 저장, 불러오기, 초기화, 

void main()
{
    system("mode con: cols=166 lines=43");
    system("title Paint");
    CONSOLE_CURSOR_INFO cursorInfo = { 0, };
    cursorInfo.bVisible = 0;
    cursorInfo.dwSize = 1;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

    string temp = "md " + FILE_PATH;
    system(temp.c_str());
    gotoxy(0, 0);
    cout << "                                                         ";

    DWORD mode;
    WORD key;
    COORD pos;

    int event;        // 마우스 이벤트에 이용
    int x;            // 마우스의 x좌표 저장소
    int y;            // 마우스의 y좌표 저장소

    CIN = GetStdHandle(STD_INPUT_HANDLE);
    COUT = GetStdHandle(STD_OUTPUT_HANDLE);

    // 마우스 활성화
    GetConsoleMode(CIN, &mode);
    SetConsoleMode(CIN, mode | ENABLE_MOUSE_INPUT);

    background();

    for (int x = 0; x < 149; x++) {
        for (int y = 0; y < 43; y++) {
            map[x][y] = 'Z';
        }
    }

    while (1)
    {
        if (be_input())
        {
            if (get_input(&key, &pos) != 0)
            {
                MOUSE_EVENT;
                x = pos.X;    // 마우스클릭값이 x,y변수에 저장되도록함
                y = pos.Y;
                gotoxy(0, 0);
                printf("%d, %d      ", x, y);
                if (buttontype == 1) 
                {
                    if (x >= 17 && x <= 165 && y <= 42)
                    {   
                        if (map[x - 17][y] != 'X') {
                            gotoxy(x, y);
                            if ((paint >= 0 and paint <= 9) or paint == 'a' or paint == 'b') {
                                map[x - 17][y] = paint;
                            }
                            else {
                                if(map[x - 16][y] >= 'a') {
                                    if (x > 17) {
                                        map[x - 18][y] = paint;
                                        map[x - 17][y] = 'X';
                                        gotoxy(x - 1, y);
                                    }
                                    else continue;
                                }
                                else {
                                    map[x - 17][y] = paint;
                                    map[x - 16][y] = 'X';
                                }
                            }
                            paintcheck(paint);
                        }
                    }
                    else
                    {
                        menuclick(x, y);
                    }
                }
                else if (buttontype == 2)
                {
                    if (x >= 17 && x <= 165 && y <= 42)
                    {
                        if ((map[x - 17][y] >= 0 and map[x - 17][y] <= 9) or map[x - 17][y] == 'a' or map[x - 17][y] == 'b') {
                            map[x - 17][y] = 'Z';
                            gotoxy(x, y);
                            printf(" ");
                        }
                        else {
                            if (map[x - 17][y] == 'X') {
                                map[x - 17][y] = 'Z';
                                map[x - 18][y] = 'Z';
                                gotoxy(x - 1, y);
                                printf("  ");
                            }
                            else {
                                map[x - 17][y] = 'Z';
                                map[x - 16][y] = 'Z';
                                gotoxy(x, y);
                                printf("  ");
                            }
                        }
                        
                    }
                }
                
            }
        }
    }
}


//Z: 빈공간, X: 가상블럭
