#pragma once
#include<iostream>
#include<Windows.h>
#include<stdlib.h>
#define MENU_FIRST_X 34 //�˵���ˮƽλ��
#define MENU_FIRST_Y 10 //�˵�����ֱλ��
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0) //����Ƿ���VK_NONAME��
using namespace std;
class menu
{
	static bool menuFlag;
	static bool flagUP;
	static int choiceNum;
public:
	static void show();//��ʾ�˵�
	static void choice();//ѡ��
	static void setCursorVisible(bool visible);//���ɼ���
	static void setCursorPosition(int x,int y);//���λ��
	static void setOutputColor(WORD color);//��������ӡ��������ɫ
	static DWORD WINAPI Fun(LPVOID lpParamter);//��������Լ�ȷ��Ч��(�̺߳���)
};

