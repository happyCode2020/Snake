#include "Apple.h"
int Apple::num = 0;
Apple::Apple(Map &p)
{
	map = &p;
	num++;
	srand((unsigned int)time(0));
	x = rand() % 39 + 1;
	y = rand() % 29 + 1;
	while(map->posType(x,y)!=Terrain::PosGround) {
		 x = rand() % 39 + 1;
		 y = rand() % 29 + 1;
	}
	map->setMap(x,y,Terrain::PosApple);
}

Apple::~Apple()
{
	map->setMap(x, y, Terrain::PosGround);
	num--;
}

void Apple::show()
{
	menu::setCursorPosition(x*2,y);
	cout << "¡ñ";
}
