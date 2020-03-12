#include "Snake.h"

Snake::Snake()
{
	//srand((unsigned int)time(0));//设置时间为随机数种子
	Position head(rand()%30+5,rand()%20+5),t;
	theSnake.addData(head);//蛇头加入
	speed = 2;//速度
	length = 4;//长度
	theDirection.snakeHeadDirection = Direction::RIGHT;
	theDirection.directionTemp = theDirection.snakeHeadDirection;
	t.setY(head.getY());
	for (int i = 0; i < length-1;i++) {
		t.setX(head.getX()+i+1);
		theSnake.addData(t);
	}
	//蛇头尾点
	snakeHead = &(theSnake.getHeadP()->data);
	snakeEnd = &(theSnake.getEndP()->data);
}

void Snake::setSpeed(int speed)
{
	this->speed = speed;
}

int Snake::getSpeed()
{
	return speed;
}

SnakeHeadDirection& Snake::getSnakeHeadDirection()
{
	return theDirection;
}

void Snake::show()
{
	Link<Position>* h = theSnake.getHeadP();
	Link<Position>* e = theSnake.getEndP();
	while (h!=e) {
		menu::setCursorPosition(h->data.getAbsoluteX(),h->data.getY());
		std::cout <<"■";
		h = h->next;
	}
	menu::setCursorPosition(e->data.getAbsoluteX(), e->data.getY());
	std::cout <<"■";
}

bool Snake::move(Map map)
{
	int m[4][2] = { { 0,-1} ,{0,1} ,{-1,0} ,{1,0} };
	if (true) {
		//将蛇尾擦掉
		menu::setCursorPosition(snakeEnd->getAbsoluteX(), snakeEnd->getY());
		std::cout << "  ";
		//将蛇尾方块放到蛇头前面
		theDirection.snakeHeadDirection = theDirection.directionTemp;//转向0
		switch (theDirection.snakeHeadDirection) {
		case Direction::UP:
			snakeEnd->setY(snakeHead->getY() - 1);
			snakeEnd->setX(snakeHead->getX());
			break;
		case Direction::DOWN:
			snakeEnd->setY(snakeHead->getY() + 1);
			snakeEnd->setX(snakeHead->getX());
			break;
		case Direction::LEFT:
			snakeEnd->setX(snakeHead->getX() - 1);
			snakeEnd->setY(snakeHead->getY());
			break;
		case Direction::RIGHT:
			snakeEnd->setX(snakeHead->getX() + 1);
			snakeEnd->setY(snakeHead->getY());
		}

		theSnake.moveFrontP();//蛇尾变蛇头，蛇尾前移
		snakeHead = &(theSnake.getHeadP()->data);//更新蛇头点
		snakeEnd = &(theSnake.getEndP()->data);//更新蛇尾点

		//显示新蛇头位置
		menu::setCursorPosition(snakeHead->getAbsoluteX(), snakeHead->getY());
		std::cout << "■";
	}
	return true;
}
//友元函数
DWORD __stdcall KeyDown(LPVOID snakeHeadDirection)
{
	int i = 0;
	SnakeHeadDirection* direction = (SnakeHeadDirection*)snakeHeadDirection;
	while (true) {
		if (KEY_DOWN('W') && direction->snakeHeadDirection != Direction::DOWN) {
			direction->directionTemp = Direction::UP;
		}
		else if (KEY_DOWN('S') && direction->snakeHeadDirection != Direction::UP)
		{
			direction->directionTemp = Direction::DOWN;
		}
		else if (KEY_DOWN('A') && direction->snakeHeadDirection != Direction::RIGHT)
		{
			direction->directionTemp = Direction::LEFT;
		}
		else if (KEY_DOWN('D') && direction->snakeHeadDirection != Direction::LEFT)
		{
			direction->directionTemp = Direction::RIGHT;
		}
	}
	return 0;
}
