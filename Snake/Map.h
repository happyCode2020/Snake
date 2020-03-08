#pragma once

#define MapSizeX 40	//地图横尺寸
#define MapSizeY 30	//纵尺寸

///////////地图地形////////////
#define PosGround 0	//平地
#define PosBlock 1	//障碍物
#define PosSnake 2	//蛇身
#define PosApple 3	//食物

class Map
{
	int mapGraph[MapSizeX][MapSizeY];	//地图点阵
public:
	Map();	//构造方法，调用初始化函数？	
	int posType(int posH, int posW);	//返回位置点类型
	//int mapEdit();	//地图编辑（包含新建、读取、编辑、存储？）
};