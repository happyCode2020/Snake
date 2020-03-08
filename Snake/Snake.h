#pragma once
#include<cstdlib>
#include<ctime>
#include"reLink.h"
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
	void setX(int x) { this->x = x; }
	void setY(int y) { this->y = y; }
	int getX() { return x; }
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
public:
	Snake();
	void setSpeed(int speed);//�����ٶ�
	void setSnakeHeadDirection(Direction &t);//���÷���
};

