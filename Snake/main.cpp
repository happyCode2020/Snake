#include<iostream>
#include"menu.h"
using namespace std;

void test0() {//新功能测试

}

int main() {
	SetConsoleTitle("贪吃蛇");//获取窗口标题
	system("mode con cols=80 lines=30");//改变宽高
	menu::show();
	menu::choice();
	test0();
}
