#include "Snake.h"

Snake::Snake()
{
	//srand((unsigned int)time(0));//����ʱ��Ϊ���������
	Position head(rand()%30+5,rand()%20+5),t;
	theSnake.addData(head);//��ͷ����
	speed = 2;//�ٶ�
	length = 4;//����
	theDirection.snakeHeadDirection = Direction::RIGHT;
	theDirection.directionTemp = theDirection.snakeHeadDirection;
	t.setY(head.getY());
	for (int i = 0; i < length-1;i++) {
		t.setX(head.getX()+i+1);
		theSnake.addData(t);
	}
	//��ͷβ��
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
		std::cout <<"��";
		h = h->next;
	}
	menu::setCursorPosition(e->data.getAbsoluteX(), e->data.getY());
	std::cout <<"��";
}

bool Snake::move(Map map)
{
	int m[4][2] = { { 0,-1} ,{0,1} ,{-1,0} ,{1,0} };
	if (true) {
		//����β����
		menu::setCursorPosition(snakeEnd->getAbsoluteX(), snakeEnd->getY());
		std::cout << "  ";
		//����β����ŵ���ͷǰ��
		theDirection.snakeHeadDirection = theDirection.directionTemp;//ת��0
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

		theSnake.moveFrontP();//��β����ͷ����βǰ��
		snakeHead = &(theSnake.getHeadP()->data);//������ͷ��
		snakeEnd = &(theSnake.getEndP()->data);//������β��

		//��ʾ����ͷλ��
		menu::setCursorPosition(snakeHead->getAbsoluteX(), snakeHead->getY());
		std::cout << "��";
	}
	return true;
}
//��Ԫ����
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
