#include "Snake.h"

Snake::Snake()
{
	int a[4][2] = {{0,-1},{0,1},{-1,0},{1,0}};
	srand((unsigned int)time(0));
	Position head(rand()%39+1,rand()%29+1),t;
	theSnake.addData(head);
	speed = 1;
	snakeHeadDirection = (Direction)(rand() % 4);
	
}

void Snake::setSpeed(int speed)
{
	this->speed = speed;
}

void Snake::setSnakeHeadDirection(Direction& t)
{
	snakeHeadDirection = t;
}
