#include "menu.h"

int menu::choiceNum = 0;
bool menu::flagUP = true;
bool menu::menuFlag = true;
bool menu::game = true;
void menu::show()
{
	for (int i = 0; i < 30;i++) {
		if (i==0||i==29) {
			cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■";
		}
		else
		{
			cout << "\n■                                                                            ■";
		}
	}
	setCursorPosition(36,8);
	setOutputColor(F_BLUE | F_RED | F_LIGHT);
	cout << "贪吃蛇" << endl;
	setCursorPosition(MENU_FIRST_X-1, MENU_FIRST_Y);
	setOutputColor(F_WHITE);//白色
	cout << "->开始游戏" << endl;
	setCursorPosition(MENU_FIRST_X, MENU_FIRST_Y+1);
	cout << "*双人游戏" << endl;
	setCursorPosition(MENU_FIRST_X, MENU_FIRST_Y+2);
	cout << "*地图编辑" << endl;
	setCursorPosition(MENU_FIRST_X, MENU_FIRST_Y+3);
	cout << "*设置" << endl;
	setCursorPosition(MENU_FIRST_X, MENU_FIRST_Y+4);
	cout << "*退出" << endl;
}

void menu::choice()
{
	setCursorVisible(false);
	HANDLE hThread = CreateThread(NULL, 0, Fun, NULL, 0, NULL);//创建新的线程
	while (menuFlag){
		Sleep(500);
		setCursorPosition(MENU_FIRST_X-1,MENU_FIRST_Y + choiceNum);
		cout << "  ";
		Sleep(500);
		setCursorPosition(MENU_FIRST_X-1, MENU_FIRST_Y + choiceNum);
		cout << "->";
	}
	if (hThread!=NULL) {
		CloseHandle(hThread);//销毁线程
	}
	switch (choiceNum) {
	case 0:
		//开始游戏
		startGame();
		break;
	case 1:
		//双人游戏
		
		break;
	case 2:
		//地图编辑
		
		break;
	case 3:
		//设置
		
		break;
	case 4:
		//退出
		
		break;
	}
}

void menu::setCursorVisible(bool visible)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);//获取控制台光标信息
	CursorInfo.bVisible = visible; //隐藏控制台光标
	SetConsoleCursorInfo(handle, &CursorInfo);//设置控制台光标状态
}

void menu::setCursorPosition(int x, int y)
{
	COORD pos = { (short)x,(short)y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void menu::setOutputColor(WORD color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color);
	/*
	wAttributes	颜色	对应的值
	FOREGROUND_BLUE	字体颜色：蓝	1
	FOREGROUND_GREEN	字体颜色：绿	2
	FOREGROUND_RED	字体颜色：红	4
	FOREGROUND_INTENSITY	前景色高亮显示	8
	BACKGROUND_BLUE	背景颜色：蓝	16
	BACKGROUND_GREEN	背景颜色：绿	32
	BACKGROUND_RED	背景颜色：红 64
	BACKGROUND_INTENSITY	背景色高亮显示	128
	*/
}

DWORD __stdcall menu::Fun(LPVOID lpParamter)
{
	while (true) {
		if (KEY_DOWN('W') && choiceNum != 0&&flagUP) {
			Sleep(10);
			setCursorPosition(MENU_FIRST_X-1, MENU_FIRST_Y + choiceNum);
			cout << " *";
			choiceNum--;
			Sleep(10);
			setCursorPosition(MENU_FIRST_X-1, MENU_FIRST_Y + choiceNum);
			cout << "->";
			flagUP = false;
		}
		else if (KEY_DOWN('S') && choiceNum != 4&& flagUP)
		{
			Sleep(10);
			setCursorPosition(MENU_FIRST_X-1, MENU_FIRST_Y + choiceNum);
			cout << " *";
			choiceNum++;
			Sleep(10);
			setCursorPosition(MENU_FIRST_X-1, MENU_FIRST_Y + choiceNum);
			cout << "->";
			flagUP = false;
		}
		else if (KEY_DOWN('J')&& flagUP) {
			menuFlag = false;
			return 0;
		}
		else if(!KEY_DOWN('S')&& !KEY_DOWN('W')){
			flagUP = true;
		}
		//Sleep(100);
	}
	/*for (int i = 0; i < 1000000;i++) {
		setCursorPosition(70, 1);
		cout << i;
		Sleep(100);
	}*/
	return 0;
}

void menu::setGame(bool setIt)
{
	game = setIt;
}

void menu::startGame()
{
	menu::setCursorVisible(false);
	Map map;
	Snake snake;
	map.show();
	snake.show();
	HANDLE hThread = CreateThread(NULL, 0, KeyDown,&snake.getSnakeHeadDirection(), 0, NULL);//创建新的线程
	while (true) {//主循环
		if (snake.move(map)) {
			Sleep(1000 / snake.getSpeed());
		}
		else
		{
			//游戏结束
		}
	}
	if (hThread != NULL) {
		CloseHandle(hThread);//销毁线程
	}
}
