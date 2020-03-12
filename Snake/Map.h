#pragma once
#include<iostream>
#include"menu.h"
#define MapSizeX 40	//地图横尺寸
#define MapSizeY 30	//纵尺寸
using namespace std;
//#define PosGround 0	//平地
//#define PosBlock 1	//障碍物
//#define PosSnake 2	//蛇身
//#define PosApple 3	//食物

enum class Terrain {//地形枚举
	PosGround, PosBlock, PosSnake, PosApple//(PosGround平地，PosBlock障碍物，PosSnake蛇身，PosApple食物)方便多文件访问,有些时候宏定义多文件可能会找不到定义(主要是想这么写试试)
};

class Map
{
	Terrain mapGraph[MapSizeX][MapSizeY] = { Terrain::PosGround };	//地图点阵
public:
	Map();	//构造方法，调用初始化函数？
	Terrain posType(int posH, int posW);	//返回位置点类型
	void show();
	//int mapEdit();	//地图编辑（包含新建、读取、编辑、存储？）
};

