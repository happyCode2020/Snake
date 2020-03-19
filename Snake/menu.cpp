#include "menu.h"

int menu::choiceNum = 0;
int menu::speed = 3;
bool menu::flagUP = true;
bool menu::menuFlag = true;
bool menu::game = true;
bool menu::music = true;
void menu::show()
{
	setCursorPosition(0, 0);
	setOutputColor(F_WHITE);
	for (int i = 0; i < 30;i++) {
		if (i==0||i==29) {
			cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■";
		}
		else
		{
			cout << "\n■                                                                            ■";
		}
		Sleep(10);
	}
	setCursorPosition(36,8);
	setOutputColor(F_BLUE | F_RED | F_LIGHT);
	cout << "贪吃蛇" << endl;
	setCursorPosition(MENU_FIRST_X, MENU_FIRST_Y);
	setOutputColor(F_WHITE);//白色
	cout << "*开始游戏" << endl;
	setCursorPosition(MENU_FIRST_X, MENU_FIRST_Y+1);
	cout << "*双人游戏" << endl;
	setCursorPosition(MENU_FIRST_X, MENU_FIRST_Y+2);
	cout << "*地图编辑" << endl;
	setCursorPosition(MENU_FIRST_X, MENU_FIRST_Y+3);
	cout << "*设置" << endl;
	setCursorPosition(MENU_FIRST_X, MENU_FIRST_Y+4);
	cout << "*退出" << endl;
	setCursorPosition(MENU_FIRST_X - 1, MENU_FIRST_Y+ choiceNum);
	cout << "->";
}

void menu::choice()
{
	menuFlag = true;
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
		setCursorPosition(0,0);
		cout << "未完成！";
		break;
	case 2:
		//地图编辑
		setCursorPosition(0, 0);
		cout << "未完成！";
		break;
	case 3:
		//设置
		setShow();
		break;
	case 4:
		//退出
		exit(0);
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

DWORD __stdcall menu::setFun(LPVOID lpParamter)
{
	int *set=(int *)lpParamter;
	while (true) {
		if (KEY_DOWN('W') && (*set) !=0 && flagUP) {
			Sleep(10);
			setCursorPosition(33, 12 + (*set));
			cout << " *";
			(*set)--;
			Sleep(10);
			setCursorPosition(33, 12 + (*set));
			cout << "->";
			flagUP = false;
		}
		else if (KEY_DOWN('S') && (*set) != 2 && flagUP)
		{
			Sleep(10);
			setCursorPosition(33, 12 + (*set));
			cout << " *";
			(*set)++;
			Sleep(10);
			setCursorPosition(33, 12 + (*set));
			cout << "->";
			flagUP = false;
		}
		else if (KEY_DOWN('J') && flagUP) {
			setCursorPosition(35, 12 + (*set));
			if ((*set) == 0 && music) {
				cout << "音乐:关";
				music = false;
			}
			else if ((*set) == 0 && !music) {
				cout << "音乐:开";
				music = true;
			}
			else if ((*set) == 1 && speed!=5) {
				speed++;
				cout << "速度:"<<speed;
			}
			else if ((*set) == 1 && speed == 5) {
				speed=1;
				cout << "速度:"<<speed;
			}
			else if( (*set)==2 )
			{
				*set = -1;
				for (int i = 0; i < 4;i++) {
					setCursorPosition(33, 11 + i);
					cout << "          ";
				}
				return 0;
			}
			flagUP = false;
		}
		else if (!KEY_DOWN('S') && !KEY_DOWN('W')&& !KEY_DOWN('J')) {
			flagUP = true;
		}
	}
	return 0;
}

void menu::setGame(bool setIt)
{
	game = setIt;
}

void menu::setShow()
{
	int set = 0;
	bool theMuFlag=music;
	setCursorPosition(24, 10);
	cout << "■■■■■■■■■■■■■■■";
	Sleep(10);
	setCursorPosition(24, 11);
	cout << "■           设置           ■";
	Sleep(10);
	setCursorPosition(24, 12);
	cout << "■       ->音乐:开          ■";
	Sleep(10);
	setCursorPosition(24, 13);
	cout << "■        *速度:3           ■";
	Sleep(10);
	setCursorPosition(24, 14);
	cout << "■        *返回             ■";
	Sleep(10);
	setCursorPosition(24, 15);
	cout << "■■■■■■■■■■■■■■■";
	Sleep(10);
	HANDLE theThread = CreateThread(NULL, 0, setFun, &set, 0, NULL);//创建新的线程
	while (set!=-1) {
		setCursorPosition(33, 12+set);
		cout << "  ";
		if (!music&&theMuFlag) {//保证只执行一次改变
			mciSendString("stop music", nullptr, 0, nullptr);
			theMuFlag = music;
		}
		else if (music&&!theMuFlag) {
			mciSendString("play music repeat", nullptr, 0, nullptr);
			theMuFlag = music;
		}
		Sleep(500);
		setCursorPosition(33, 12+set);
		cout << "->";
		Sleep(500);
	}
	setCursorPosition(33, 12 + set);
	cout << "  ";
	if (theThread != NULL) {
		CloseHandle(theThread);//销毁线程
	}
	menu::show();
	menu::choice();
}

void menu::startGame()
{
	menu::setCursorVisible(false);
	Map map;//创建地图
	Snake snake(map);//创建蛇
	Apple *apple;//食物指针
	apple = new Apple(map);
	//显示
	map.show();
	//snake.show();//因为加入地图里了初始不需要画
	//apple->show();
	snake.setSpeed(speed);
	menu::setCursorPosition(38, 1);
	cout << "预备!";
	Sleep(1000);
	menu::setCursorPosition(38, 1);
	cout << "开始!";
	Sleep(500);
	menu::setCursorPosition(38, 1);
	cout << "     ";
	HANDLE hThread = CreateThread(NULL, 0, KeyDown,&snake.getSnakeHeadDirection(), 0, NULL);//创建新的线程
	Terrain temp;
	while (true) {//主循环
		temp=snake.move();
		if (temp==Terrain::PosGround||temp == Terrain::PosApple) {
			snake.setSpeed(snake.getSnakeHeadDirection().speed);
			Sleep(1000 / snake.getSpeed());
			switch (temp) {
			case Terrain::PosApple:
				delete apple;
				apple = new Apple(map);
				apple->show();
				break;
			}
		}
		else
		{
			//游戏结束
			cout << "gameover";
			break;
		}
	}
	if (hThread != NULL) {
		CloseHandle(hThread);//销毁线程
	}
	Sleep(1000);
	show();
	choice();
}
