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
				this->mapGraph[posW][posH] = Terrain::PosBlock;
			else
				this->mapGraph[posW][posH] = Terrain::PosGround;
		}
	}
}
Terrain Map::posType(int posH, int posW)	//返回对应位置点地形
{
	return this->mapGraph[posH][posW];
}

void Map::show()
{
	for (int i = 0; i < MapSizeY;i++) {
		menu::setCursorPosition(0, i);
		for (int j = 0; j < MapSizeX;j++) {
			switch (mapGraph[j][i]) {
			case Terrain::PosGround:
				cout<<"  ";
				break;
			case Terrain::PosBlock:
				cout << "■";
				break;
			case Terrain::PosSnake:
				cout << "■";
				break;
			case Terrain::PosApple:
				cout << "●";
				break;
			}
		}
	}
}

