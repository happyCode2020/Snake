#include"Map.h"

Map::Map()	//地图类构造方法（临时）
{
	int posW, posH;
	//暂时的不随机的地图
	for (posH = 0; posH < MapSizeY; posH++)
	{
		for (posW = 0; posW < MapSizeX; posW++)
		{
			if (posW == 0 || posW == MapSizeX - 1||posH == 0 || posH == MapSizeY - 1)
				this->mapGraph[posH][posW] = Terrain::PosBlock;
			else
				this->mapGraph[posH][posW] = Terrain::PosGround;
		}
	}
}
Terrain Map::posType(int posH, int posW)	//返回对应位置点地形
{
	return this->mapGraph[posH][posW];
}

