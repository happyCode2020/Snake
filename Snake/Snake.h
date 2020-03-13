#pragma once
#include"include.h"
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
struct SnakeHeadDirection
{
	Direction snakeHeadDirection;//����
	Direction directionTemp;//���򻺳���
};
class Map;
enum class Terrain;
class Snake
{
	//���ڳ�ʼ���ĳ���
	static const int IL = 4;	//InitialLength
	static const int IS = 3;	//InitialSpeed
	static const Direction ID = Direction::LEFT; //InitialDirection

	ReLink<Position> theSnake;//��
	int speed;//�ٶ�
	int length;//����
	SnakeHeadDirection theDirection;
	//��ͷβ��
	Position* snakeHead;
	Position* snakeEnd;
	Map *map;
public:
	Snake(Map &p);
	void setSpeed(int speed);//�����ٶ�
	int getSpeed();
	SnakeHeadDirection& getSnakeHeadDirection();//��ȡ����
	void show();
	void printPoint(Position* pos, string str, Terrain posT);//���һ��
	Terrain move();//�ƶ�
	friend DWORD WINAPI KeyDown(LPVOID snakeHeadDirection);//ת��
};

