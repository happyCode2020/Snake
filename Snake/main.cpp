#include<iostream>
#include"menu.h"
using namespace std;

void test0() {//�¹��ܲ���

}

int main() {
	mciSendString("open a.mp3 alias music", nullptr, 0, nullptr);
	mciSendString("play music repeat", nullptr, 0, nullptr);
	SetConsoleTitle("̰����");//��ȡ���ڱ���
	system("mode con cols=80 lines=30");//�ı���
	menu::show();
	menu::choice();
	test0();
}
