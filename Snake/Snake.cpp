#include "Snake.h"

Snake::Snake(Map &theMap)
{
	map = &theMap;//����ʵ�ͼ���ֲ��������ﴴ����ͼ
	srand((unsigned int)time(0));//����ʱ��Ϊ���������
	Position head(rand()%30+5,rand()%20+5),t;
	theSnake.addData(head);//��ͷ����
	speed = 1;//�ٶ�
	snakeHeadDirection = Direction::RIGHT;
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
	snakeHeadDirection = t;
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
	HANDLE hThread = CreateThread(NULL, 0, KeyDown, &snakeHeadDirection, 0, NULL);//�����µ��߳�
	//�ݴ�ÿ���ƶ�ʱ��ͷβ��
	Position* snakeHead = &(theSnake.getHeadP()->data);
	Position* snakeEnd = &(theSnake.getEndP()->data);

	while (true) {
		
		//����β����
		menu::setCursorPosition(snakeEnd->getAbsoluteX(), snakeEnd->getY());
		cout << "  ";
		
		//����β����ŵ���ͷǰ��
		switch (snakeHeadDirection) {
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
		Sleep(500);
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
	Direction *direction = (Direction *)snakeHeadDirection;
	while (true) {
		if (KEY_DOWN('W')&&(*direction)!=Direction::DOWN) {
			*direction = Direction::UP;
		}
		else if (KEY_DOWN('S')&& (*direction) != Direction::UP)
		{
			*direction = Direction::DOWN;
		}
		else if(KEY_DOWN('A') && (*direction) != Direction::RIGHT)
		{ 
			*direction = Direction::LEFT;
		}
		else if(KEY_DOWN('D') && (*direction) != Direction::LEFT)
		{
			*direction = Direction::RIGHT;
		}
	}
	return 0;
}
