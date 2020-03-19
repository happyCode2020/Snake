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
	setCursorPosition(MENU_FIRST_X, MENU_FIRST_Y);
	setOutputColor(F_WHITE);//��ɫ
	cout << "*��ʼ��Ϸ" << endl;
	setCursorPosition(MENU_FIRST_X, MENU_FIRST_Y+1);
	cout << "*˫����Ϸ" << endl;
	setCursorPosition(MENU_FIRST_X, MENU_FIRST_Y+2);
	cout << "*��ͼ�༭" << endl;
	setCursorPosition(MENU_FIRST_X, MENU_FIRST_Y+3);
	cout << "*����" << endl;
	setCursorPosition(MENU_FIRST_X, MENU_FIRST_Y+4);
	cout << "*�˳�" << endl;
	setCursorPosition(MENU_FIRST_X - 1, MENU_FIRST_Y+ choiceNum);
	cout << "->";
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
		setCursorPosition(0,0);
		cout << "δ��ɣ�";
		break;
	case 2:
		//��ͼ�༭
		setCursorPosition(0, 0);
		cout << "δ��ɣ�";
		break;
	case 3:
		//����
		setShow();
		break;
	case 4:
		//�˳�
		exit(0);
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
				cout << "����:��";
				music = false;
			}
			else if ((*set) == 0 && !music) {
				cout << "����:��";
				music = true;
			}
			else if ((*set) == 1 && speed!=5) {
				speed++;
				cout << "�ٶ�:"<<speed;
			}
			else if ((*set) == 1 && speed == 5) {
				speed=1;
				cout << "�ٶ�:"<<speed;
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
	cout << "������������������������������";
	Sleep(10);
	setCursorPosition(24, 11);
	cout << "��           ����           ��";
	Sleep(10);
	setCursorPosition(24, 12);
	cout << "��       ->����:��          ��";
	Sleep(10);
	setCursorPosition(24, 13);
	cout << "��        *�ٶ�:3           ��";
	Sleep(10);
	setCursorPosition(24, 14);
	cout << "��        *����             ��";
	Sleep(10);
	setCursorPosition(24, 15);
	cout << "������������������������������";
	Sleep(10);
	HANDLE theThread = CreateThread(NULL, 0, setFun, &set, 0, NULL);//�����µ��߳�
	while (set!=-1) {
		setCursorPosition(33, 12+set);
		cout << "  ";
		if (!music&&theMuFlag) {//��ִֻ֤��һ�θı�
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
		CloseHandle(theThread);//�����߳�
	}
	menu::show();
	menu::choice();
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
	snake.setSpeed(speed);
	menu::setCursorPosition(38, 1);
	cout << "Ԥ��!";
	Sleep(1000);
	menu::setCursorPosition(38, 1);
	cout << "��ʼ!";
	Sleep(500);
	menu::setCursorPosition(38, 1);
	cout << "     ";
	HANDLE hThread = CreateThread(NULL, 0, KeyDown,&snake.getSnakeHeadDirection(), 0, NULL);//�����µ��߳�
	Terrain temp;
	while (true) {//��ѭ��
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
