#include "Snake.h"


Snake::Snake(Map &p)
{
	//游戏地图
	map = &p;

	//设置时间为随机数种子
	srand((unsigned int)time(0));
	
	//蛇头位置随机
	int x = rand() % (MapSizeX - 2*IL - 2) + IL + 1;
	int y = rand() % (MapSizeY - 2*IL - 2) + IL + 1;
	
	//蛇头和蛇身的辅助初始化变量
	Position head(x,y),t;	

	//.................UP....down....left...right
	int m[4][2] = { { 0,-1} ,{0,1} ,{-1,0} ,{1,0} };

	//蛇头加入
	theSnake.addData(head);
	map->setMap(x,y,Terrain::PosSnake);

	//蛇身加入
	for (int i = 1; i <= IL - 1; i++) {
		t.setX(head.getX() + i* m[(int)ID][0]);
		t.setY(head.getY() + i* m[(int)ID][1]);
		theSnake.addData(t);
		map->setMap(t.getX(), t.getY(), Terrain::PosSnake);
	}

	//蛇参数初始化
	theDirection.snakeHeadDirection = ID;	//方向
	theDirection.directionTemp = ID;	//方向缓存
	speed = IS;//速度
	length = IL;//长度

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

void Snake::printPoint(Position* pos, string str, Terrain posT)
{
	menu::setCursorPosition(pos->getAbsoluteX(), pos->getY());
	map->setMap(pos->getX(),pos->getY(), posT);
	std::cout << str;
}

Terrain Snake::move()
{	
	//想了下还是这样写方便点，不然多一个函数判断碰撞 √
	//.................UP....down....left...right
	int m[4][2] = { { 0,-1} ,{0,1} ,{-1,0} ,{1,0} };
	theDirection.snakeHeadDirection = theDirection.directionTemp;//转向0
	//蛇正前方的x,y
	int x = snakeHead->getX() + m[(int)theDirection.snakeHeadDirection][0];
	int y = snakeHead->getY() + m[(int)theDirection.snakeHeadDirection][1];
	Position t(x,y);//吃食物后增加的体节
	switch(map->posType(x,y)){
	case Terrain::PosGround:
		//将蛇尾擦掉
		printPoint(snakeEnd, "  ", Terrain::PosGround);
		//将蛇尾方块放到蛇头前面
		snakeEnd->setX(x);
		snakeEnd->setY(y);
		theSnake.moveFrontP();//蛇尾变蛇头，蛇尾前移
		snakeHead = &(theSnake.getHeadP()->data);//更新蛇头点
		snakeEnd = &(theSnake.getEndP()->data);//更新蛇尾点
		//显示新蛇头位置
		printPoint(snakeHead, "■", Terrain::PosSnake);
		return Terrain::PosGround;
	case Terrain::PosApple:
		theSnake.addData(t);
		snakeHead = &(theSnake.getHeadP()->data);//更新蛇头点
		length++;
		printPoint(snakeHead, "■", Terrain::PosSnake);
		return Terrain::PosApple;
	case Terrain::PosBlock:
		return Terrain::PosBlock;
	case Terrain::PosSnake:
		return Terrain::PosSnake;
	}
	return Terrain::PosGround;
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
