1#include <stdio.h>
#include <math.h>
#include <graphics.h>//包含图形库
#include <conio.h>
#include<mmsystem.h>
#include"MHQX.h"
#include"Media.h"

//已完成的函数
int MouseDection(RECT* areas, int n);
void MainMenu(void);
void Guidebook(void);
void GameEnd(void);
void InitGame(void);
void Options(void);

void MainGame(void);

//未实现的函数
void TheRank(void);
void TheAuthorsPage(void);


/*
* 这是游戏的主循环，负责游戏整体的打印。
* 它调用的函数是平级关系。
* theinterface是一个判断的值，主循环中根据这个值来打印不同的界面
* 这里的被调用函数会获得一个theinterface指针的值，
* 当需要调换到其它页面时，这个就可以改变这个指针值来最终实现页面改变的操作
*/
extern int theInterface = 0;
int main(void) {
	initgraph(1290, 860, EW_SHOWCONSOLE);
	setbkcolor(WHITE);
	setbkmode(TRANSPARENT);
	HWND Easyx = GetHWnd();
	Video_Play(Easyx, ".\\01.mp4");
	cleardevice();
	bool quit_game = 0;
	MediaPlay_bkMusic("add", 0, ".\\bkMusic.mp3");
	MediaPlay_bkMusic("set_v", 40);
	MediaPlay_bkMusic("play");
	while (!quit_game) {
		switch (theInterface) {
		case 0://开始菜单
			MainMenu();
			break;
		case 1://初始化界面
			InitGame();
			break;
		case 2://游戏界面
			MainGame();
			break;
		case 3://游戏说明界面
			Guidebook();
			break;
		case 4://历史战绩界面
			break;
		case 5://游戏设置界面
			Options();
			break;
		case 6://制作人名单界面
			break;
		case 7://退出游戏
			quit_game = 1;
			break;
		case 8://游戏结算界面
			GameEnd();
			break;
		}
	}
	return 0;
}