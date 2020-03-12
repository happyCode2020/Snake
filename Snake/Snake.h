#pragma once
#include<cstdlib>
#include<ctime>
#include"reLink.h"
#include"Map.h"
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0) //����Ƿ���VK_NONAME��

DWORD __stdcall KeyDown(LPVOID snakeHeadDirection);//����
//����ĵ���
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
//����
enum class Direction
{
	UP, DOWN, LEFT, RIGHT
};
class Snake
{
	ReLink<Position> theSnake;//��
	int speed;//�ٶ�
	Direction snakeHeadDirection;//����
	Map* map;
public:
	Snake(Map &theMap);
	void setSpeed(int speed);//�����ٶ�
	void setSnakeHeadDirection(Direction &t);//���÷���
	void show();
	bool movePossible(int x,int y);//�Ƿ���ƶ�
	bool move();//�ƶ�
	friend DWORD WINAPI KeyDown(LPVOID snakeHeadDirection);//ת��
};

