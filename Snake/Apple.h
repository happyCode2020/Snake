#pragma once
#include"include.h"
class Map;
class Apple
{
	int x;
	int y;
	static int num;//食物总数
	Map *map;
public:
	Apple(Map &p);
	~Apple();
	void show();
};

