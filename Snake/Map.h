#pragma once

#define MapSizeX 40	//��ͼ��ߴ�
#define MapSizeY 30	//�ݳߴ�

///////////��ͼ����////////////
#define PosGround 0	//ƽ��
#define PosBlock 1	//�ϰ���
#define PosSnake 2	//����
#define PosApple 3	//ʳ��

class Map
{
	int mapGraph[MapSizeX][MapSizeY];	//��ͼ����
public:
	Map();	//���췽�������ó�ʼ��������	
	int posType(int posH, int posW);	//����λ�õ�����
	//int mapEdit();	//��ͼ�༭�������½�����ȡ���༭���洢����
};