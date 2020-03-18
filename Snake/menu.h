#pragma once
#include"include.h"
#define MENU_FIRST_X 34 //菜单的水平位置
#define MENU_FIRST_Y 10 //菜单的竖直位置
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0) //检测是否按下VK_NONAME键
using namespace std;
class menu
{
	static bool menuFlag;
	static bool flagUP;
	static int choiceNum;
	static bool game;
	static bool music;
	static int speed;//速度
public:
	static void show();//显示菜单
	static void choice();//选择
	static void setCursorVisible(bool visible);//光标可见性
	static void setCursorPosition(int x,int y);//光标位置
	static void setOutputColor(WORD color);//接下来打印的文字颜色
	static void setGame(bool setIt);//允许暂停
	static void setShow();
private:
	static void startGame();//开始游戏
	static DWORD WINAPI Fun(LPVOID lpParamter);//按键检测以及确认效果(线程函数)
	static DWORD WINAPI setFun(LPVOID lpParamter);//设置(线程函数)
};

