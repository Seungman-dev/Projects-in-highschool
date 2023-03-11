#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>

//====== 월, 화, 목, 금 =====
#define UD1S 550 //1교시 시작
#define UD1E 595 //1교시 끝

#define UD2S 605 //2교시 시작
#define UD2E 650 //2교시 끝

#define UD3S 660 //3교시 시작
#define UD3E 705 //3교시 끝

#define UD4S 715 //4교시 시작
#define UD4E 760 //4교시 끝

#define UD5S 840 //5교시 시작
#define UD5E 885 //5교시 끝

#define UD6S 895 //6교시 시작
#define UD6E 940 //6교시 끝

#define UD7S 950 //7교시 시작
#define UD7E 995 //7교시 끝

#define UDBS 760 //점심시간 시작
#define UDBE 840 //점심시간 끝

//===== 수 =====
#define WD1S 550 //1교시 시작
#define WD1E 595 //1교시 끝

#define WD2S 605 //2교시 시작
#define WD2E 650 //2교시 끝

#define WD3S 660 //3교시 시작
#define WD3E 705 //3교시 끝

#define WD4S 780 //4교시 시작
#define WD4E 825 //4교시 끝

#define WD5S 835 //5교시 시작
#define WD5E 880 //5교시 끝

#define WD6S 890 //6교시 시작
#define WD6E 935 //6교시 끝

#define WDBS 705 //점심시간 시작
#define WDBE 780 //점심시간 끝

// 월,화,목,금
	// 9시 10분 ~ 9시 55분  
	// 10시 5분 ~ 10시 50분  
	// 11시 ~ 11시 45분  
	// 11시 55분 ~ 12시 40분
	// 점심: 12시 40분 ~ 2시
	// 2시 ~ 2시 45분
	// 2시 55분 ~ 3시 40분
	// 3시 50분 ~ 4시 35분

	// 수
	// 9시 10분 ~ 9시 55분
	// 10시 5분 ~ 10시 50분
	// 11시 ~ 11시 45분
	// 점심: 11시 45분 ~ 1시
	// 1시 ~ 1시 45분
	// 1시 55분 ~ 2시 40분
	// 2시 50분 ~ 3시 35

/*
char schedule[5][7][6] = { 
	{ {"미술"}, {"한문"}, {"영독A"}, {"스생"}, {"확통"}, {"생2"}, {"인공"} },
	{ {"미적"}, {"영독B"}, {"확통"}, {"물2"}, {"논술"}, {"진로"}, {"독서"} },
	{ {"문학"}, {"물2"}, {"생2"}, {"창체"}, {"창체"}, {"창체"}, {"없음"} },
	{ {"영독A"}, {"확통"}, {"물2"}, {"독서"}, {"미술"}, {"스생"}, {"미적"} },
	{ {"문학"}, {"한문"}, {"미적"}, {"생2"}, {"영독B"}, {"인공"}, {"확통"} } };
*/

// 미술 0 / 한문 1 / 영독A 2 / 스생 3 / 확통 4 / 생2 5 / 인공 6 / 미적 7 / 영독B 8 / 물2 9 / 논술 10 / 진로 11 /
// 독서 12 / 문학 13 / 창체 14 / 없음 15
int schedule[5][7] = {
	/*월*/{ {0}, {1}, {2}, {3}, {4}, {5}, {6} },
	/*화*/{ {7}, {8}, {4}, {9}, {10}, {11}, {12} },
	/*수*/{ {13}, {9}, {5}, {14}, {14}, {14}, {15} },
	/*목*/{ {2}, {4}, {9}, {12}, {0}, {3}, {7} },
	/*금*/{ {13}, {1}, {7}, {5}, {8}, {6}, {4} } };

int year, month, day, hour, min, sec = 0;
char Aweek[7][3] = { "일", "월", "화", "수", "목", "금", "토" };
int week = 0;
char s = 0;
int total_minute = 0;
int current_class = 0;

void Time();
void gotoxy(short int x, short int y);
void ScheduleCheck();
void ShowTimetable();
void ClassNamePrint(int classnum);
void StartClassLink(int classnum);

int main()
{
	int check_mouse = 1;
	system("title AutoZoomJoin - 고3");
	system("mode con: cols=70 lines=18");
	int lastsecond = NULL;
	int lasttotalmin = NULL;
	
	bool Lclick = false;
	while (1)
	{
		
		total_minute = 60 * hour + min;
		if (GetKeyState(VK_LBUTTON) < 0 && check_mouse == 1) { // 좌클릭 누르기
			check_mouse = 0;
		}
		else if (GetKeyState(VK_LBUTTON) >= 0 && check_mouse == 0)
		{
			check_mouse = 1;
			Lclick = true;
		}
		Time();
		if (lastsecond != sec) // 초가 달라질 떄마다
		{
			
			CONSOLE_CURSOR_INFO cursorInfo = { 0, };
			cursorInfo.bVisible = 0;
			cursorInfo.dwSize = 1;
			SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
			if (Lclick == true) //좌클릭을 눌렀으면
			{
				system("mode con: cols=70 lines=18");
				//SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_WINDOWED_MODE, 0);
				Lclick = false;
			}
			lastsecond = sec;
			ShowTimetable();
			ScheduleCheck();
		}
		if (lasttotalmin != total_minute) // 분이 달라질 때마다
		{
			lasttotalmin = total_minute;
			if (week != 0 and week != 6)
			{
				if (week == 3)
				{
					if (total_minute == WD1S - 2 or total_minute == WD2S - 2 or total_minute == WD3S - 2 or
						total_minute == WD4S - 2 or total_minute == WD5S - 2 or total_minute == WD6S - 2)
					{
						StartClassLink(schedule[week - 1][current_class - 1]);
					}
				}
				else
				{
					if (total_minute == UD1S - 2 or total_minute == UD2S - 2 or total_minute == UD3S - 2 or
						total_minute == UD4S - 2 or total_minute == UD5S - 2 or total_minute == UD6S - 2 or total_minute == UD7S - 2)
					{
						StartClassLink(schedule[week - 1][current_class - 1]);
					}
				}
			}
		}
		Sleep(100);

	}

	

	return 0;
}

void ShowTimetable()
{
	gotoxy(2, 1);
	printf("DATE:  %04d년  %02d월  %02d일", year, month, day);
	gotoxy(2, 2);
	printf("TIME:    %02d시  %02d분  %02d초", hour, min, sec);
	gotoxy(2, 3);
	printf("DAY OF THE WEEK:   %s요일", Aweek[week]);
	gotoxy(0, 6);
	printf("                     ");
	gotoxy(2, 6);
	printf("오늘의 시간표");
	gotoxy(2, 8);
	if (week == 0 or week == 6)
	{
		printf("%s요일에는 수업이 없습니다.", &Aweek[week]);
	}
	else
	{
		for (int i = 0; i < 7; i++)
		{
			gotoxy(3, 8 + i);
			printf("%d. ", i + 1);
			ClassNamePrint(schedule[week - 1][i]);

		}
	}
}

void Time()
{
	time_t t = time(NULL);
	struct tm* lt = localtime(&t);
	year = lt->tm_year + 1900;
	month = lt->tm_mon + 1;
	day = lt->tm_mday;
	hour = lt->tm_hour;
	min = lt->tm_min;
	week = lt->tm_wday;
	sec = lt->tm_sec;
}

void gotoxy(short int x, short int y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void ScheduleCheck()
{
	// 월,화,목,금
	// 9시 10분 ~ 9시 55분  
	// 10시 5분 ~ 10시 50분  
	// 11시 ~ 11시 45분  
	// 11시 55분 ~ 12시 40분
	// 점심: 12시 40분 ~ 2시
	// 2시 ~ 2시 45분
	// 2시 55분 ~ 3시 40분
	// 3시 50분 ~ 4시 35분

	// 수
	// 9시 10분 ~ 9시 55분
	// 10시 5분 ~ 10시 50분
	// 11시 ~ 11시 45분
	// 점심: 11시 45분 ~ 1시
	// 1시 ~ 1시 45분
	// 1시 55분 ~ 2시 40분
	// 2시 50분 ~ 3시 35

	int ntime = 0;
	bool studying = false;
	bool breaktime = false;
	bool lunchtime = false;
	bool classbefore = false;
	bool allend = false;
	gotoxy(25, 6);
	printf("                                           ");
	gotoxy(25, 7);
	printf("                                           ");
	if (week == 0 or week == 6) //주말
	{
		/*gotoxy(25, 7);
		printf("주말에는 예약된 시간표가 없습니다.");*/
	}
	else if (week == 3) //수요일은 수업 시간이 다름
	{
		// == 수업중 ==
		if (total_minute >= WD1S and total_minute < WD1E) { current_class = 1; ntime = WD1E - total_minute; studying = true; }
		else if (total_minute >= WD2S and total_minute < WD2E) { current_class = 2; ntime = WD2E - total_minute; studying = true; }
		else if (total_minute >= WD3S and total_minute < WD3E) { current_class = 3; ntime = WD3E - total_minute; studying = true; }
		else if (total_minute >= WD4S and total_minute < WD4E) { current_class = 4; ntime = WD4E - total_minute; studying = true; }
		else if (total_minute >= WD5S and total_minute < WD5E) { current_class = 5; ntime = WD5E - total_minute; studying = true; }
		else if (total_minute >= WD6S and total_minute < WD6E) { current_class = 6; ntime = WD6E - total_minute; studying = true; }

		// == 쉬는시간 ==
		else if (total_minute >= WD1E and total_minute < WD2S) { current_class = 2; ntime = WD2S - total_minute; breaktime = true; }
		else if (total_minute >= WD2E and total_minute < WD3S) { current_class = 3; ntime = WD3S - total_minute; breaktime = true; }
		else if (total_minute >= WD4E and total_minute < WD5S) { current_class = 4; ntime = WD4S - total_minute; breaktime = true; }
		else if (total_minute >= WD5E and total_minute < WD6S) { current_class = 6; ntime = WD6S - total_minute; breaktime = true; }

		// == 점심시간 ==
		else if (total_minute >= WD3E and total_minute < WD4S) { current_class = 5; ntime = WD4S - total_minute; lunchtime = true; }

		// == 1교시 시작 전 ==
		else if (total_minute < WD1S) { current_class = 1;  ntime = WD1S - total_minute; classbefore = true; }

		// == 수업 다 끝나고 난 후 ==
		else if (total_minute >= WD6S) { allend = true; }
	}
	else //월,화,목,금
	{
		// == 수업중 ==
		if (total_minute >= UD1S and total_minute < UD1E) { current_class = 1; ntime = UD1E - total_minute; studying = true; }
		else if (total_minute >= UD2S and total_minute < UD2E) { current_class = 2; ntime = UD2E - total_minute; studying = true; }
		else if (total_minute >= UD3S and total_minute < UD3E) { current_class = 3; ntime = UD3E - total_minute; studying = true; }
		else if (total_minute >= UD4S and total_minute < UD4E) { current_class = 4; ntime = UD4E - total_minute; studying = true; }
		else if (total_minute >= UD5S and total_minute < UD5E) { current_class = 5; ntime = UD5E - total_minute; studying = true; }
		else if (total_minute >= UD6S and total_minute < UD6E) { current_class = 6; ntime = UD6E - total_minute; studying = true; }
		else if (total_minute >= UD7S and total_minute < UD7E) { current_class = 7; ntime = UD7E - total_minute; studying = true; }

		// == 쉬는시간 ==
		else if (total_minute >= UD1E and total_minute < UD2S) { current_class = 2; ntime = UD2S - total_minute; breaktime = true; }
		else if (total_minute >= UD2E and total_minute < UD3S) { current_class = 3; ntime = UD3S - total_minute; breaktime = true; }
		else if (total_minute >= UD3E and total_minute < UD4S) { current_class = 4; ntime = UD4S - total_minute; breaktime = true; }
		else if (total_minute >= UD5E and total_minute < UD6S) { current_class = 6; ntime = UD6S - total_minute; breaktime = true; }
		else if (total_minute >= UD6E and total_minute < UD7S) { current_class = 7; ntime = UD7S - total_minute; breaktime = true; }

		// == 점심시간 ==
		else if (total_minute >= UD4E and total_minute < UD5S) { current_class = 5; ntime = UD5S - total_minute; lunchtime = true; }

		// == 1교시 시작 전 ==
		else if (total_minute < UD1S) { current_class = 1;  ntime = UD1S - total_minute; classbefore = true; }

		// == 수업 다 끝나고 난 후 ==
		else if (total_minute >= UD7S) { allend = true; }
	}
	if (classbefore == true)
	{
		gotoxy(25, 6);
		printf("현재 1교시 ");
		ClassNamePrint(schedule[week - 1][0]);
		printf(" 수업 시작 전입니다.");
		gotoxy(25, 7);
		if (ntime >= 60)
		{
			int temp_hour = ntime / 60;
			ntime -= temp_hour * 60;
			if (ntime == 0)
			{
				printf("수업 시작까지 %d시간 남음", temp_hour);
			}
			else
			{
				printf("수업 시작까지 %d시간 %d분 남음", temp_hour, ntime);
			}
		}
		else
		{
			printf("수업 시작까지 %d분 남음", ntime);
		}
	}
	else if (studying == true)
	{
		gotoxy(25, 6);
		printf("현재 %d교시 ", current_class);
		ClassNamePrint(schedule[week - 1][current_class - 1]);
		printf(" 수업 시간 중입니다.");
		
		gotoxy(25, 7);
		printf("수업 종료까지 %d분 남음", ntime);
	}
	else if (breaktime == true)
	{
		gotoxy(25, 6);
		printf("현재 쉬는 시간 중입니다.");
		gotoxy(25, 7);
		printf("%d교시 ", current_class);
		ClassNamePrint(schedule[week - 1][current_class - 1]);
		printf(" 수업 시작까지 %d분 남음", ntime);
	}
	else if (lunchtime == true)
	{
		gotoxy(25, 6);
		printf("현재 점심 시간 중입니다.");
		gotoxy(25, 7);
		printf("%d교시 ", current_class);
		ClassNamePrint(schedule[week - 1][current_class - 1]);
		printf(" 수업 시작까지 %d분 남음", ntime);
	}
	else if (allend == true)
	{
		gotoxy(25, 7);
		printf("모든 수업이 끝났습니다..");
	
	}
}

// 미술 0 / 한문 1 / 영독A 2 / 스생 3 / 확통 4 / 생2 5 / 인공 6 / 미적 7 / 영독B 8 / 물2 9 / 논술 10 / 진로 11 /
// 독서 12 / 문학 13 / 창체 14 / 없음 15

void StartClassLink(int classnum)
{
	if (classnum == 0) { system("start https://zoom.us/j/9597789673?pwd=MFFhbFVaMExjelB6Qml5b1ZjamFRQT09"); }
	else if (classnum == 1) { system("start https://us04web.zoom.us/j/76769390524?pwd=WPBHeqvCNTH7oLXkzFnUqetrL4HBHE.1"); }
	else if (classnum == 2) { system("start https://meet.google.com/qte-fzga-egj"); }
	else if (classnum == 3) { system("start "); }
	else if (classnum == 4) { system("start https://us02web.zoom.us/j/5636111757?pwd=SkxmT2NJaEQ3Mnc4Wmk0Wi9hem8yUT09"); }
	else if (classnum == 5) { system("start https://us05web.zoom.us/j/82450594755?pwd=d0U2d1NETXQ0WXl5Rng3WVdSeEJQQT09"); }
	else if (classnum == 6) { system("start https://us02web.zoom.us/j/4337205300?pwd=dVR5eEhZeVVudEpidlIvRkFTaVhpQT09"); }
	else if (classnum == 7) { system("start https://us02web.zoom.us/j/4879181025?pwd=V1g1NzZCUnMrclNOUlBZb01WbHkzZz09"); }
	else if (classnum == 8) { system("start https://zoom.us/j/2726707820?pwd=RDQyQ1FKVHFRY2ZtY0lqd3VuUUZnZz09"); }
	else if (classnum == 9) { system("start https://us02web.zoom.us/j/4158796485?pwd=Y0VadkEwRXVzeGhGZEFsWkh5WkVzUT09"); }
	else if (classnum == 10) { system("start https://zoom.us/j/5436817395?pwd=QjBsWFNWR2pGaEM1ZG1JUTgzQTNUdz09"); }
	else if (classnum == 11) { system("start "); }
	else if (classnum == 12) { system("start https://zoom.us/j/93229483329?pwd=VlVxNmcvUGl2K3RpU21DTmRrNERsUT09"); }
	else if (classnum == 13) { system("start https://zoom.us/j/2313174820?pwd=OUJUN3pua0l2MEFwc2hEOTdsNUM5UT09"); }
	else if (classnum == 14) { system("start "); }
	else if (classnum == 15) { system("start "); }
	if (classnum >= 0 and classnum <= 14)
	{
		gotoxy(25, 11);
		ClassNamePrint(classnum);
		printf(" 줌 링크를 실행했습니다.");
	}
}
// 미술 0 / 한문 1 / 영독A 2 / 스생 3 / 확통 4 / 생2 5 / 인공 6 / 미적 7 / 영독B 8 / 물2 9 / 논술 10 / 진로 11 /
// 독서 12 / 문학 13 / 창체 14 / 없음 15
void ClassNamePrint(int classnum)
{
	if (classnum == 0) { printf("미술"); }
	else if (classnum == 1) { printf("한문"); }
	else if (classnum == 2) { printf("영독A"); }
	else if (classnum == 3) { printf("스생"); }
	else if (classnum == 4) { printf("확통"); }
	else if (classnum == 5) { printf("생2"); }
	else if (classnum == 6) { printf("인공"); }
	else if (classnum == 7) { printf("미적"); }
	else if (classnum == 8) { printf("영독B"); }
	else if (classnum == 9) { printf("물2"); }
	else if (classnum == 10) { printf("논술"); }
	else if (classnum == 11) { printf("진로"); }
	else if (classnum == 12) { printf("독서"); }
	else if (classnum == 13) { printf("문학"); }
	else if (classnum == 14) { printf("창체"); }
}
