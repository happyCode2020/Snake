#pragma once
#include<cstdlib>
#include<ctime>
#include"reLink.h"
#include"Map.h"
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0) //检测是否按下VK_NONAME键

DWORD __stdcall KeyDown(LPVOID snakeHeadDirection);//声明
//特殊的点类
class Position
{
	int x;
	int y;
public:
	Position() {
		x = 0;
		y = 0;
	}
	Position(int xx,int yy) {
		x = xx*2;
		y = yy;
	}
	void setX(int x) { this->x = x*2; }
	void setY(int y) { this->y = y; }
	int getAbsoluteX() { return x; }
	int getX() { return x/2; }
	int getY() { return y; }
	void operator=(const Position &t) {
		x = t.x;
		y = t.y;
	}
};
//方向
enum class Direction
{
	UP, DOWN, LEFT, RIGHT
};
class Snake
{
	ReLink<Position> theSnake;//蛇
	int speed;//速度
	Direction snakeHeadDirection;//方向
	Map* map;
public:
	Snake(Map &theMap);
	void setSpeed(int speed);//设置速度
	void setSnakeHeadDirection(Direction &t);//设置方向
	void show();
	bool movePossible(int x,int y);//是否可移动
	bool move();//移动
	friend DWORD WINAPI KeyDown(LPVOID snakeHeadDirection);//转向
};

