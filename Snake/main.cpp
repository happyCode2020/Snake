#include<iostream>
#include"menu.h"
using namespace std;

void test0() {//�¹��ܲ���

}

int main() {
	SetConsoleTitle("̰����");//��ȡ���ڱ���
	system("mode con cols=80 lines=30");//�ı���
	menu::show();
	menu::choice();
	test0();
}
