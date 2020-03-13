#include"Map.h"

Map::Map()	//��ͼ�๹�췽������ʱ��
{
	int posW, posH;
	//��ʱ�Ĳ�����ĵ�ͼ
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
Terrain Map::posType(int posH, int posW)	//���ض�Ӧλ�õ����
{
	return this->mapGraph[posH][posW];
}

void Map::show()
{
	menu::setOutputColor(F_GREEN);
	for (int i = 0; i < MapSizeX;i++) {
		for (int j = 0; j < MapSizeY;j++) {
			menu::setCursorPosition(i*2, j);
			switch (mapGraph[i][j]) {
			case Terrain::PosGround:
				cout<<"  ";
				break;
			case Terrain::PosBlock:
				cout << "��";
				break;
			case Terrain::PosSnake:
				cout << "��";
				break;
			case Terrain::PosApple:
				cout << "��";
				break;
			}
		}
		Sleep(10);
	}
}

void Map::setMap(int x,int y, Terrain t)
{
	mapGraph[x][y] = t;
}

