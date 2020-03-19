#include "Snake.h"

Snake::Snake(Map &p)
{
	map = &p;
	srand((unsigned int)time(0));//����ʱ��Ϊ���������
	int x=rand() % 30 + 5;
	int y= rand() % 20 + 5;
	Position head(x,y),t;
	theSnake.addData(head);//��ͷ����
	map->setMap(x,y,Terrain::PosSnake);
	speed = 3;//�ٶ�
	length = 4;//����
	theDirection.snakeHeadDirection = Direction::RIGHT;
	theDirection.directionTemp = theDirection.snakeHeadDirection;
	theDirection.speed = speed;
	t.setY(head.getY());
	for (int i = 0; i < length-1;i++) {
		t.setX(head.getX()+i+1);
		theSnake.addData(t);
		map->setMap(t.getX(), t.getY(), Terrain::PosSnake);
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

Terrain Snake::move()
{	
	//�����»�������д����㣬��Ȼ��һ�������ж���ײ
	//.................UP....down....left...right
	int m[4][2] = { { 0,-1} ,{0,1} ,{-1,0} ,{1,0} };
	theDirection.snakeHeadDirection = theDirection.directionTemp;//ת��0
	//����ǰ����x,y
	int x = snakeHead->getX() + m[(int)theDirection.snakeHeadDirection][0];
	int y = snakeHead->getY() + m[(int)theDirection.snakeHeadDirection][1];
	Position t(x,y);//��ʳ������ӵ����
	switch(map->posType(x,y)){
	case Terrain::PosGround:
		//����β����
		menu::setCursorPosition(snakeEnd->getAbsoluteX(), snakeEnd->getY());
		map->setMap(snakeEnd->getX(),snakeEnd->getY(),Terrain::PosGround);
		std::cout << "  ";
		//����β����ŵ���ͷǰ��
		snakeEnd->setX(x);
		snakeEnd->setY(y);
		theSnake.moveFrontP();//��β����ͷ����βǰ��
		snakeHead = &(theSnake.getHeadP()->data);//������ͷ��
		snakeEnd = &(theSnake.getEndP()->data);//������β��
		//��ʾ����ͷλ��
		menu::setCursorPosition(snakeHead->getAbsoluteX(), snakeHead->getY());
		map->setMap(snakeHead->getX(), snakeHead->getY(), Terrain::PosSnake);
		std::cout << "��";
		return Terrain::PosGround;
	case Terrain::PosApple:
		theSnake.addData(t);
		snakeHead = &(theSnake.getHeadP()->data);//������ͷ��
		length++;
		menu::setCursorPosition(snakeHead->getAbsoluteX(), snakeHead->getY());
		map->setMap(snakeHead->getX(), snakeHead->getY(), Terrain::PosSnake);
		std::cout << "��";
		return Terrain::PosApple;
	case Terrain::PosBlock:
		return Terrain::PosBlock;
	case Terrain::PosSnake:
		return Terrain::PosSnake;
	}
	return Terrain::PosGround;
}
//��Ԫ����
DWORD __stdcall KeyDown(LPVOID snakeHeadDirection)
{
	int i = 0;
	bool flag=true;
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
		if (KEY_DOWN('J')&&flag) {
			direction->speed *= 2;
			flag = false;
		}
		else if(!KEY_DOWN('J')&&!flag)
		{
			direction->speed /= 2;
			flag = true;
		}
	}
	return 0;
}
