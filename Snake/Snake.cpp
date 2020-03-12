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
	int m[4][2] = { {0,-1} ,{0,1}, {-1,0}, {1,0} };
	HANDLE hThread = CreateThread(NULL, 0, KeyDown, &snakeHeadDirection, 0, NULL);//�����µ��߳�
	Position *snakeEnd;//�ݴ�ÿ���ƶ�ʱ��β�ĵ�

	while (true) {
		snakeEnd = &(theSnake.getEndP()->data);//������β��


		//����β����
		menu::setCursorPosition(snakeEnd->getAbsoluteX, theSnake.getEndP()->data.getY());
		cout << "  ";
		//����β����ŵ���ͷǰ��
		theSnake.getEndP()->data.setX(theSnake.getHeadP()->data.getX() + m[(int)snakeHeadDirection][0]);
		theSnake.getEndP()->data.setY(theSnake.getHeadP()->data.getY() + m[(int)snakeHeadDirection][1]);
		theSnake.moveFrontP();//��β����ͷ����βǰ��
		//��������ͷ
		menu::setCursorPosition(theSnake.getHeadP()->data.getAbsoluteX(), theSnake.getHeadP()->data.getY());
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
