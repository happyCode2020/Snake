#include "Snake.h"

Snake::Snake(Map &theMap)
{
	map = &theMap;//����ʵ�ͼ���ֲ��������ﴴ����ͼ
	srand((unsigned int)time(0));//����ʱ��Ϊ���������
	Position head(rand()%30+5,rand()%20+5),t;
	theSnake.addData(head);//��ͷ����
	speed = 1;//�ٶ�
	snakeHeadDirection = (Direction)(rand()%4);//��ͷ����

	t.setY(head.getY());
	for (int i = 0; i < 3;i++) {
		t.setX(head.getX()-i-1);
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
	while (true) {
		menu::setCursorPosition(theSnake.getEndP()->data.getAbsoluteX(), theSnake.getEndP()->data.getY());
		cout << "  ";
		theSnake.getEndP()->data.setX(theSnake.getHeadP()->data.getX() - 1);
		theSnake.getEndP()->data.setY(theSnake.getHeadP()->data.getY());
		theSnake.moveFrontP();
		menu::setCursorPosition(theSnake.getHeadP()->data.getAbsoluteX(), theSnake.getHeadP()->data.getY());
		cout << "��";
		Sleep(1000);
	}
	return false;
}
