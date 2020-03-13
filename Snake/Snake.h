#pragma once
#include"include.h"
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
struct SnakeHeadDirection
{
	Direction snakeHeadDirection;//方向
	Direction directionTemp;//方向缓冲量
};
class Map;
enum class Terrain;
class Snake
{
	//用于初始化的常量
	static const int IL = 4;	//InitialLength
	static const int IS = 3;	//InitialSpeed
	static const Direction ID = Direction::LEFT; //InitialDirection

	ReLink<Position> theSnake;//蛇
	int speed;//速度
	int length;//长度
	SnakeHeadDirection theDirection;
	//蛇头尾点
	Position* snakeHead;
	Position* snakeEnd;
	Map *map;
public:
	Snake(Map &p);
	void setSpeed(int speed);//设置速度
	int getSpeed();
	SnakeHeadDirection& getSnakeHeadDirection();//获取方向
	void show();
	void printPoint(Position* pos, string str, Terrain posT);//输出一点
	Terrain move();//移动
	friend DWORD WINAPI KeyDown(LPVOID snakeHeadDirection);//转向
};

