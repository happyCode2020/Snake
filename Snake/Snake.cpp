#include "Snake.h"

Snake::Snake(Map &theMap)
{
	map = &theMap;//想访问地图，又不该在这里创建地图
	srand((unsigned int)time(0));//设置时间为随机数种子
	Position head(rand()%30+5,rand()%20+5),t;
	theSnake.addData(head);//蛇头加入
	speed = 1;//速度
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
	HANDLE hThread = CreateThread(NULL, 0, KeyDown, &snakeHeadDirection, 0, NULL);//创建新的线程
	//暂存每次移动时蛇头尾点
	Position* snakeHead = &(theSnake.getHeadP()->data);
	Position* snakeEnd = &(theSnake.getEndP()->data);

	while (true) {
		
		//将蛇尾擦掉
		menu::setCursorPosition(snakeEnd->getAbsoluteX(), snakeEnd->getY());
		cout << "  ";
		
		//将蛇尾方块放到蛇头前面
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

		theSnake.moveFrontP();//蛇尾变蛇头，蛇尾前移
		snakeHead = &(theSnake.getHeadP()->data);//更新蛇头点
		snakeEnd = &(theSnake.getEndP()->data);//更新蛇尾点

		//显示新蛇头位置
		menu::setCursorPosition(snakeHead->getAbsoluteX(), snakeHead->getY());
		cout << "■";
		Sleep(500);
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
