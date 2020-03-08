#include"Map.h"

Map::Map()	//��ͼ�๹�췽������ʱ��
{
	int posW, posH;
	//��ʱ�Ĳ�����ĵ�ͼ
	for (posH = 0; posH < MapSizeY; posH++)
	{
		for (posW = 0; posW < MapSizeX; posW++)
		{
			if (posW == 0 || posW == MapSizeX - 1)
				this->mapGraph[posH][posW] = PosBlock;
			else if (posH == 0 || posH == MapSizeY - 1)
				this->mapGraph[posH][posW] = PosBlock;
			else
				this->mapGraph[posH][posW] = PosGround;
		}
	}
}

int Map::posType(int posH, int posW)	//���ض�Ӧλ�õ����
{
	return this->mapGraph[posH][posW];
}

