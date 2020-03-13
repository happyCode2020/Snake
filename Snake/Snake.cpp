#include "Snake.h"


Snake::Snake(Map &p)
{
	//��Ϸ��ͼ
	map = &p;

	//����ʱ��Ϊ���������
	srand((unsigned int)time(0));
	
	//��ͷλ�����
	int x = rand() % (MapSizeX - 2*IL - 2) + IL + 1;
	int y = rand() % (MapSizeY - 2*IL - 2) + IL + 1;
	
	//��ͷ������ĸ�����ʼ������
	Position head(x,y),t;	

	//.................UP....down....left...right
	int m[4][2] = { { 0,-1} ,{0,1} ,{-1,0} ,{1,0} };

	//��ͷ����
	theSnake.addData(head);
	map->setMap(x,y,Terrain::PosSnake);

	//�������
	for (int i = 1; i <= IL - 1; i++) {
		t.setX(head.getX() + i* m[(int)ID][0]);
		t.setY(head.getY() + i* m[(int)ID][1]);
		theSnake.addData(t);
		map->setMap(t.getX(), t.getY(), Terrain::PosSnake);
	}

	//�߲�����ʼ��
	theDirection.snakeHeadDirection = ID;	//����
	theDirection.directionTemp = ID;	//���򻺴�
	speed = IS;//�ٶ�
	length = IL;//����

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

void Snake::printPoint(Position* pos, string str, Terrain posT)
{
	menu::setCursorPosition(pos->getAbsoluteX(), pos->getY());
	map->setMap(pos->getX(),pos->getY(), posT);
	std::cout << str;
}

Terrain Snake::move()
{	
	//�����»�������д����㣬��Ȼ��һ�������ж���ײ ��
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
		printPoint(snakeEnd, "  ", Terrain::PosGround);
		//����β����ŵ���ͷǰ��
		snakeEnd->setX(x);
		snakeEnd->setY(y);
		theSnake.moveFrontP();//��β����ͷ����βǰ��
		snakeHead = &(theSnake.getHeadP()->data);//������ͷ��
		snakeEnd = &(theSnake.getEndP()->data);//������β��
		//��ʾ����ͷλ��
		printPoint(snakeHead, "��", Terrain::PosSnake);
		return Terrain::PosGround;
	case Terrain::PosApple:
		theSnake.addData(t);
		snakeHead = &(theSnake.getHeadP()->data);//������ͷ��
		length++;
		printPoint(snakeHead, "��", Terrain::PosSnake);
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
