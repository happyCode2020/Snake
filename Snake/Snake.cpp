#include "Snake.h"

Snake::Snake(Map &theMap)
{
	map = &theMap;//����ʵ�ͼ���ֲ��������ﴴ����ͼ
	srand((unsigned int)time(0));//����ʱ��Ϊ���������
	Position head(rand()%30+5,rand()%20+5),t;
	theSnake.addData(head);//��ͷ����
	speed = 2;//�ٶ�
	theDirection.snakeHeadDirection = Direction::RIGHT;
	theDirection.directionTemp = theDirection.snakeHeadDirection;
	t.setY(head.getY());
	for (int i = 0; i < 3;i++) {
		t.setX(head.getX()+i+1);
		theSnake.addData(t);
	}
}

void Snake::setSpeed(int speed)
{
	this->speed = speed;
}

void Snake::setSnakeHeadDirection(Direction& t)
{
	theDirection.snakeHeadDirection = t;
	theDirection.directionTemp = theDirection.snakeHeadDirection;
}

void Snake::show()
{
	Link<Position>* h = theSnake.getHeadP();
	Link<Position>* e = theSnake.getEndP();
	while (h!=e) {
		menu::setCursorPosition(h->data.getAbsoluteX(),h->data.getY());
		cout <<"��";
		h = h->next;
	}
	menu::setCursorPosition(e->data.getAbsoluteX(), e->data.getY());
	cout <<"��";
}

bool Snake::movePossible(int x, int y)
{
	if (map->posType(x, y) == Terrain::PosBlock)
		return false;
	else
		return true;
}

bool Snake::move()
{
	HANDLE hThread = CreateThread(NULL, 0, KeyDown, &theDirection, 0, NULL);//�����µ��߳�
	//�ݴ�ÿ���ƶ�ʱ��ͷβ��
	Position* snakeHead = &(theSnake.getHeadP()->data);
	Position* snakeEnd = &(theSnake.getEndP()->data);

	while (true) {
		
		//����β����
		menu::setCursorPosition(snakeEnd->getAbsoluteX(), snakeEnd->getY());
		cout << "  ";
		//����β����ŵ���ͷǰ��
		theDirection.snakeHeadDirection = theDirection.directionTemp;
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
		cout << "��";
		Sleep(1000/speed);
	}
	if (hThread != NULL) {
		CloseHandle(hThread);//�����߳�
	}
	return false;
}

//��Ԫ����
DWORD __stdcall KeyDown(LPVOID snakeHeadDirection)
{
	bool flag = true;
	int i = 0;
	SnakeHeadDirection*direction = (SnakeHeadDirection *)snakeHeadDirection;
	while (true) {
		if (KEY_DOWN('W') && direction->snakeHeadDirection != Direction::DOWN) {
			direction->directionTemp = Direction::UP;
			flag = false;
		}
		else if (KEY_DOWN('S') && direction->snakeHeadDirection != Direction::UP)
		{
			direction->directionTemp = Direction::DOWN;
			flag = false;
		}
		else if (KEY_DOWN('A') && direction->snakeHeadDirection != Direction::RIGHT)
		{
			direction->directionTemp = Direction::LEFT;
			flag = false;
		}
		else if (KEY_DOWN('D') && direction->snakeHeadDirection != Direction::LEFT)
		{
			direction->directionTemp = Direction::RIGHT;
			flag = false;
		}
		else if (!KEY_DOWN('W')&& !KEY_DOWN('D')&&!KEY_DOWN('S')&& !KEY_DOWN('A'))
		{
			flag = true;
		}
	}
	return 0;
}
