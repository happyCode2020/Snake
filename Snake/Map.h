#pragma once
#define MapSizeX 40	//��ͼ��ߴ�
#define MapSizeY 30	//�ݳߴ�

//#define PosGround 0	//ƽ��
//#define PosBlock 1	//�ϰ���
//#define PosSnake 2	//����
//#define PosApple 3	//ʳ��

enum class Terrain {//����ö��
	PosGround, PosBlock, PosSnake, PosApple//������ļ�����,��Щʱ��궨����ļ����ܻ��Ҳ�������(��Ҫ������ôд����)
};

class Map
{
	Terrain mapGraph[MapSizeX][MapSizeY] = { Terrain::PosGround };	//��ͼ����
public:
	Map();	//���췽�������ó�ʼ��������
	Terrain posType(int posH, int posW);	//����λ�õ�����
	//int mapEdit();	//��ͼ�༭�������½�����ȡ���༭���洢����
};

