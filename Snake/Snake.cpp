#include "Snake.h"

Snake::Snake(Map &theMap)
{
	map = &theMap;//想访问地图，又不该在这里创建地图
	srand((unsigned int)time(0));//设置时间为随机数种子
	Position head(rand()%30+5,rand()%20+5),t;
	theSnake.addData(head);//蛇头加入
	speed = 2;//速度
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
		cout <<"■";
		h = h->next;
	}
	menu::setCursorPosition(e->data.getAbsoluteX(), e->data.getY());
	cout <<"■";
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
	HANDLE hThread = CreateThread(NULL, 0, KeyDown, &theDirection, 0, NULL);//创建新的线程
	//暂存每次移动时蛇头尾点
	Position* snakeHead = &(theSnake.getHeadP()->data);
	Position* snakeEnd = &(theSnake.getEndP()->data);

	while (true) {
		
		//将蛇尾擦掉
		menu::setCursorPosition(snakeEnd->getAbsoluteX(), snakeEnd->getY());
		cout << "  ";
		//将蛇尾方块放到蛇头前面
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

		theSnake.moveFrontP();//蛇尾变蛇头，蛇尾前移
		snakeHead = &(theSnake.getHeadP()->data);//更新蛇头点
		snakeEnd = &(theSnake.getEndP()->data);//更新蛇尾点

		//显示新蛇头位置
		menu::setCursorPosition(snakeHead->getAbsoluteX(), snakeHead->getY());
		cout << "■";
		Sleep(1000/speed);
	}
	if (hThread != NULL) {
		CloseHandle(hThread);//销毁线程
	}
	return false;
}

//友元函数
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
