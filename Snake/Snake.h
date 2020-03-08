#pragma once
#include<cstdlib>
#include<ctime>
#include"reLink.h"
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
	void setX(int x) { this->x = x; }
	void setY(int y) { this->y = y; }
	int getX() { return x; }
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
public:
	Snake();
	void setSpeed(int speed);//设置速度
	void setSnakeHeadDirection(Direction &t);//设置方向
};

