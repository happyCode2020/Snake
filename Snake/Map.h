#pragma once
#include<iostream>
#include"menu.h"
#define MapSizeX 40	//��ͼ��ߴ�
#define MapSizeY 30	//�ݳߴ�
using namespace std;
//#define PosGround 0	//ƽ��
//#define PosBlock 1	//�ϰ���
//#define PosSnake 2	//����
//#define PosApple 3	//ʳ��

enum class Terrain {//����ö��
	PosGround, PosBlock, PosSnake, PosApple//(PosGroundƽ�أ�PosBlock�ϰ��PosSnake����PosAppleʳ��)������ļ�����,��Щʱ��궨����ļ����ܻ��Ҳ�������(��Ҫ������ôд����)
};

class Map
{
	Terrain mapGraph[MapSizeX][MapSizeY] = { Terrain::PosGround };	//��ͼ����
public:
	Map();	//���췽�������ó�ʼ��������
	Terrain posType(int posH, int posW);	//����λ�õ�����
	void show();
	//int mapEdit();	//��ͼ�༭�������½�����ȡ���༭���洢����
};

