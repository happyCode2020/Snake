#include<iostream>
#include"menu.h"
#include"Snake.h"
using namespace std;

void test0() {//�¹��ܲ���
	menu::setCursorVisible(false);
	Map map;
	Snake snake(map);
	map.show();
	snake.show();
	snake.move();
	while (true) {

	}
}

int main() {
	//SetConsoleTitle("̰����");//��ȡ���ڱ���
	//system("mode con cols=80 lines=30");//�ı���
	//menu::show();
	//menu::choice();
	test0();
}
