1#include <stdio.h>
#include <math.h>
#include <graphics.h>//����ͼ�ο�
#include <conio.h>
#include<mmsystem.h>
#include"MHQX.h"
#include"Media.h"

//����ɵĺ���
int MouseDection(RECT* areas, int n);
void MainMenu(void);
void Guidebook(void);
void GameEnd(void);
void InitGame(void);
void Options(void);

void MainGame(void);

//δʵ�ֵĺ���
void TheRank(void);
void TheAuthorsPage(void);


/*
* ������Ϸ����ѭ����������Ϸ����Ĵ�ӡ��
* �����õĺ�����ƽ����ϵ��
* theinterface��һ���жϵ�ֵ����ѭ���и������ֵ����ӡ��ͬ�Ľ���
* ����ı����ú�������һ��theinterfaceָ���ֵ��
* ����Ҫ����������ҳ��ʱ������Ϳ��Ըı����ָ��ֵ������ʵ��ҳ��ı�Ĳ���
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
		case 0://��ʼ�˵�
			MainMenu();
			break;
		case 1://��ʼ������
			InitGame();
			break;
		case 2://��Ϸ����
			MainGame();
			break;
		case 3://��Ϸ˵������
			Guidebook();
			break;
		case 4://��ʷս������
			break;
		case 5://��Ϸ���ý���
			Options();
			break;
		case 6://��������������
			break;
		case 7://�˳���Ϸ
			quit_game = 1;
			break;
		case 8://��Ϸ�������
			GameEnd();
			break;
		}
	}
	return 0;
}