#include<iostream>
#include"menu.h"
#include"Snake.h"
using namespace std;

void test0() {//新功能测试
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
	//SetConsoleTitle("贪吃蛇");//获取窗口标题
	//system("mode con cols=80 lines=30");//改变宽高
	//menu::show();
	//menu::choice();
	test0();
}
