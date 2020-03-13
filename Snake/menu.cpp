#include "menu.h"

int menu::choiceNum = 0;
bool menu::flagUP = true;
bool menu::menuFlag = true;
bool menu::game = true;
void menu::show()
{
	setCursorPosition(0, 0);
	setOutputColor(F_WHITE);
	for (int i = 0; i < 30;i++) {
		if (i==0||i==29) {
			cout << "��������������������������������������������������������������������������������";
		}
		else
		{
			cout << "\n��                                                                            ��";
		}
		Sleep(10);
	}
	setCursorPosition(36,8);
	setOutputColor(F_BLUE | F_RED | F_LIGHT);
	cout << "̰����" << endl;
	setCursorPosition(MENU_FIRST_X-1, MENU_FIRST_Y);
	setOutputColor(F_WHITE);//��ɫ
	cout << "->��ʼ��Ϸ" << endl;
	setCursorPosition(MENU_FIRST_X, MENU_FIRST_Y+1);
	cout << "*˫����Ϸ" << endl;
	setCursorPosition(MENU_FIRST_X, MENU_FIRST_Y+2);
	cout << "*��ͼ�༭" << endl;
	setCursorPosition(MENU_FIRST_X, MENU_FIRST_Y+3);
	cout << "*����" << endl;
	setCursorPosition(MENU_FIRST_X, MENU_FIRST_Y+4);
	cout << "*�˳�" << endl;
}

void menu::choice()
{
	menuFlag = true;
	setCursorVisible(false);
	HANDLE hThread = CreateThread(NULL, 0, Fun, NULL, 0, NULL);//�����µ��߳�
	while (menuFlag){
		Sleep(500);
		setCursorPosition(MENU_FIRST_X-1,MENU_FIRST_Y + choiceNum);
		cout << "  ";
		Sleep(500);
		setCursorPosition(MENU_FIRST_X-1, MENU_FIRST_Y + choiceNum);
		cout << "->";
	}
	if (hThread!=NULL) {
		CloseHandle(hThread);//�����߳�
	}
	switch (choiceNum) {
	case 0:
		//��ʼ��Ϸ
		startGame();
		break;
	case 1:
		//˫����Ϸ
		
		break;
	case 2:
		//��ͼ�༭
		
		break;
	case 3:
		//����
		
		break;
	case 4:
		//�˳�
		
		break;
	}
}

void menu::setCursorVisible(bool visible)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);//��ȡ����̨�����Ϣ
	CursorInfo.bVisible = visible; //���ؿ���̨���
	SetConsoleCursorInfo(handle, &CursorInfo);//���ÿ���̨���״̬
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
	wAttributes	��ɫ	��Ӧ��ֵ
	FOREGROUND_BLUE	������ɫ����	1
	FOREGROUND_GREEN	������ɫ����	2
	FOREGROUND_RED	������ɫ����	4
	FOREGROUND_INTENSITY	ǰ��ɫ������ʾ	8
	BACKGROUND_BLUE	������ɫ����	16
	BACKGROUND_GREEN	������ɫ����	32
	BACKGROUND_RED	������ɫ���� 64
	BACKGROUND_INTENSITY	����ɫ������ʾ	128
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
	Map map;//������ͼ
	Snake snake(map);//������
	Apple *apple;//ʳ��ָ��
	apple = new Apple(map);
	//��ʾ
	map.show();
	//snake.show();//��Ϊ�����ͼ���˳�ʼ����Ҫ��
	//apple->show();
	menu::setCursorPosition(38, 1);
	cout << "Ԥ��!";
	Sleep(1000);
	menu::setCursorPosition(38, 1);
	cout << "��ʼ!";
	Sleep(500);
	menu::setCursorPosition(38, 1);
	cout << "     ";
	HANDLE hThread = CreateThread(NULL, 0, KeyDown,&snake.getSnakeHeadDirection(), 0, NULL);//�����µ��߳�
	while (true) {//��ѭ��
		Terrain temp=snake.move();
		if (temp==Terrain::PosGround||temp == Terrain::PosApple) {
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
			//��Ϸ����
			cout << "gameover";
			break;
		}
	}
	if (hThread != NULL) {
		CloseHandle(hThread);//�����߳�
	}
	Sleep(1000);
	show();
	choice();
}
