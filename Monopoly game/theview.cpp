#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <graphics.h>//����ͼ�ο�
#include <conio.h>
#include<stdlib.h>
#include"MHQX.h"
#include"Media.h"

#define	CH_LEN_LIM		30					//��ť�����ı�չʾ����󳤶ȣ����峤�������밴ť��С�й�
#define CELL_SIZE		94					//���̸��ӵĴ�С�����أ�
#define PAWN_SIZE		CELL_SIZE/2			//���Ӵ�С
#define	TEXT_HEIGHT		40					//����߶�
#define TEXT_WIDTH      0					//������
#define NAME_LIM		30


const int centerx = 820;//�Ի�������
const int centery = 430;//�Կ������
static int Volume_bkMusic = 40;//��������
 RECT talksBox = { 494, 101, 1152, 759 };//�����жԻ���
 RECT middleBottom = { 494, 101, 1152, 759 };//�����м�ƫ�²���
 IMAGE description;
 IMAGE board;
 IMAGE P1, P2;//��ǰ�����ʾ


 static bool gameEnd = 0;//�ж���Ϸ�Ƿ����
 int phase = 1;



int MouseDection(RECT* areas, int n);	//�����İ�����⹦��
int MainDailogBox(void);				//�Ի��򣬸ĺ���û��ѭ���ṹ��������MainGameˢ��
int Is_in_Prison[2] = { 0 };

//�Ի���ҳ��



int terminal(int Id);

//���ڷ���service�����ݵĺ���

int* getplayermsg(int Id);
int* getplayercolor(int Id);
COLORREF getplayercolorrgb(int Id);
int* getlandinfol(int ps);



extern int hostId;//��ǰ�غϵ���ң������ڶԻ�������
extern int stage;//�غ�����������Ϸ����ʱ���ڴ�ӡ��
extern int theInterface;

void MainMenu(void) {//���˵�

	RECT buttons[7] = {
		{  0,  0,  0,  0},//Ĭ�Ϸ���ֵ
		{552,302,740,378},//�µ���Ϸ
		{552,378,740,460},//������Ϸ
		{552,460,740,538},//��Ϸ˵��
		{552,537,740,622},//��Ϸ����
		{552,622,740,706},//��ʷս��
		{552,706,740,778},//�˳���Ϸ
	};

	IMAGE img;
	loadimage(&img, ".\\ͼƬ�ز�\\�˵�ҳ��.png", 1290, 860, TRUE);

	//��ѭ������������Ϸ�˵���ҳ����ת��quitΪѭ��������quit=1ʱѭ��ֹͣ,��ת����һ������
	bool quit = 0;
	while (!quit) {
		BeginBatchDraw();
		cleardevice();
		putimage(0, 0, &img);
		//�����ж���ҵ���ĸ���ť
		switch (MouseDection(buttons, 7)) {
		case 0:
			break;
		case 1://����Ϸ
			quit = 1;
			theInterface = 1;
			break;
		case 2://������Ϸ
			break;
		case 3://��Ϸ˵��
			quit = 1;
			theInterface = 3;
			break;
		case 4://��Ϸ����
			quit = 1;
			theInterface = 5;
			break;
		case 5://��ʷս��
			break;
		case 6://�˳���Ϸ
			theInterface = 7;
			quit = 1;
			break;
		default:
			printf("Main menu wrong!");
			break;
		}
		Sleep(30);
		//�����������ڻ�����Ϸ�˵�����
		FlushBatchDraw();
		EndBatchDraw();
	}

}


void InitGame(void) {//��ʼ�˵�

	//�����������ڼ��ػ��Ƴ�ʼ������ͼƬ
	IMAGE New_Game_Setting;
	ExMessage New_Game_Setting_Clik;
	loadimage(&New_Game_Setting, ".\\ͼƬ�ز�\\����Ϸ���ý���.png");

	//���û�����ɫ
	setfillstyle(BS_NULL);
	setlinecolor(BLUE);

	//������Ϸ��ʼ�ʽ�Ĭ��Ϊ15000
	int money = 15000;

	//��ѭ���������Ƴ�ʼ����Ϸ����Ļ��ƺ���ת��quitΪѭ��������quit=1ѭ��ֹͣ����ת���¸�ҳ��
	bool quit = 0;
	while (!quit){
		BeginBatchDraw();
		//�ʽ�
		if (peekmessage(&New_Game_Setting_Clik, EM_MOUSE))
		{
			//ˢ��ҳ��
			putimage(0, 0, &New_Game_Setting);

			//��������if��������ʽ�ѡ������Ϊ15000,20000��30000
			if (New_Game_Setting_Clik.message == WM_LBUTTONDOWN &&
				New_Game_Setting_Clik.x >= 621 &&
				New_Game_Setting_Clik.x <= 731 &&
				New_Game_Setting_Clik.y >= 330 &&
				New_Game_Setting_Clik.y <= 388)
			{
				money = 15000;
			}
			else if (New_Game_Setting_Clik.message == WM_LBUTTONDOWN &&
				New_Game_Setting_Clik.x >= 786 &&
				New_Game_Setting_Clik.x <= 895 &&
				New_Game_Setting_Clik.y >= 330 &&
				New_Game_Setting_Clik.y <= 388)
			{
				money = 20000;
			}
			else if (New_Game_Setting_Clik.message == WM_LBUTTONDOWN &&
				New_Game_Setting_Clik.x >= 948 &&
				New_Game_Setting_Clik.x <= 1066 &&
				New_Game_Setting_Clik.y >= 330 &&
				New_Game_Setting_Clik.y <= 388)
			{
				money = 30000;
			}

			//������һ��
			//��if������ڿ�ʼ��Ϸ������ҵ����ʼ��Ϸ��theinterface��ֵ��Ϊ2����ת����Ϸ����
			else if (New_Game_Setting_Clik.message == WM_LBUTTONDOWN &&
				New_Game_Setting_Clik.x >= 313 &&
				New_Game_Setting_Clik.x <= 524 &&
				New_Game_Setting_Clik.y >= 751 &&
				New_Game_Setting_Clik.y <= 828)
			{
				theInterface = 2;
				quit = 1;
			}
			//��if������ڷ��ز˵�������ҵ����ʼ��Ϸ��theinterface��ֵ��Ϊ0����ת���˵�����
			else if (New_Game_Setting_Clik.message == WM_LBUTTONDOWN &&
				New_Game_Setting_Clik.x >= 747 &&
				New_Game_Setting_Clik.x <= 950 &&
				New_Game_Setting_Clik.y >= 751 &&
				New_Game_Setting_Clik.y <= 828)
			{
				theInterface = 0;
				quit = 1;
			}
			//��switch����жϳ�ʼ�ʽ����ֵ�Ӷ��ڶ�Ӧ���ʽ𴦻��Ʒ�����ʾ���
			switch (money)
			{
			case 15000:
				fillroundrect(621, 330, 731, 388, 10, 10);
				break;
			case 20000:
				fillroundrect(786, 330, 895, 388, 10, 10);
				break;
			case 30000:
				fillroundrect(948, 330, 1066, 388, 10, 10);
				break;
			default:
				break;
			}
		}
		FlushBatchDraw();
		Sleep(10);
	}
	//�ú���Ϊservice��ĺ��������ڳ�ʼ����ҵ�����
	InitGameIndex(money);
}




void MainGame(void) {//����Ϸ���棬����Ϸ�����л�һֱͣ���ڸ�ҳ��
	//��ӡǰ׼��
	int theTalks = 0;
	cleardevice();
	//ѭ��ˢ����Ϸҳ��
	int quit = 0;
	while (quit == 0) {//������Ϸ�е�ѭ��������Ϸδ����ʱ�����˳�
		BeginBatchDraw();
		loadimage(&board, ".\\ͼƬ�ز�\\��Ϸ����.png", 1290, 860, TRUE);
		cleardevice();
		putimage(0, 0, &board);	//��ӡ��Ϸ����
		PrintPawn();			//Ȼ���ӡ����
		PrintMap();				//�ȴ�ӡ��ͼ
		PrintPlayerMsg();		//Ȼ���ӡ�����Ϣ
		quit = MainDailogBox();	//Ȼ���ӡ�Ի�������Ի��򻹸�������Ϸ�������жϣ���Ϸ����ʱ����1��ƽʱ����0
		EndBatchDraw();
		Sleep(20);

	}
	theInterface = 8;//����Ϸ����ʱ��ת��������棨��ת�����μ�������˵��

}


void Guidebook(void) {//˵��ҳ��

	//���尴ť�ķ�Χ
	RECT buttons[2] = {
		{   0,  0,   0,  0},
		{1074,744,1274,833}
	};
	//���ػ�����Ϸ˵����ͼƬ
	IMAGE img;
	loadimage(&img, ".\\ͼƬ�ز�\\��Ϸ˵������.png", 1290, 860, TRUE);
	//��ѭ�����ڿ��ƽ�����ת��quitΪѭ����������quitΪ1ʱѭ��ֹͣ����ת���¸�����
	bool quit = 0;
	while (!quit) {
		cleardevice();
		BeginBatchDraw();
		putimage(0, 0, &img);
		//����ҵ����Ӧ��ť��MouseDection�᷵�ض�Ӧ��ֵ�Ӷ��ж���ҵ�����Ǹ���ť
		switch (MouseDection(buttons, 2)) {
		case 0:
			break;
		//������ֵΪ1ʱ˵������˷��ز˵���ť
		case 1:
			theInterface = 0;
			quit = 1;
			break;
		//�������ֵΪ������˵�����д���
		default:
			printf("Guidebook wrong!");
			break;
		}
		//�������ڻ���
		EndBatchDraw();
	}
}


void TheRank(void);//==========================================δ���


void Options(void) {//����
	//���尴ť�ķ�Χ
	RECT buttons[4] = {
		{0,0,0,0},
		{500,700,800,800},
		{830,280,870,320},
		{670,280,710,320}
	};

	//���ػ�����Ϸ���õ�ͼƬ
	IMAGE Setting;
	loadimage(&Setting, ".\\ͼƬ�ز�\\���ý���.png", 1290, 860, TRUE);
	
	//��ѭ�������������ý���Ļ��ƺ���ת��quitΪѭ��������quit=1ѭ��ֹͣ����ת���¸�ҳ��
	bool quit = 0;
	while (!quit) {
		BeginBatchDraw();
		putimage(0, 0, &Setting);
		settextcolor(BLACK);
		settextstyle(44, 25, "����", 0, 0, 50, 0, 0, 0);
		outtextxy(760, 275, _T('0' + Volume_bkMusic / 20));

		//����ҵ����Ӧ��ť��MouseDection�᷵�ض�Ӧ��ֵ�Ӷ��ж���ҵ�����Ǹ���ť
		switch (MouseDection(buttons, 4)) {
		case 0:
			break;
		case 1://������ֵΪ1ʱ˵�������������ɰ�ť��������Ϸ�˵�	
			quit = 1;
			theInterface = 0;
			break;
		case 2://������ֵΪ2ʱ˵������ˡ�+����ť��������������
			if (Volume_bkMusic < 100)
			{
				Volume_bkMusic += 20;
			}
			MediaPlay_bkMusic("set_v", Volume_bkMusic);
			break;
		case 3://������ֵΪ3ʱ˵������ˡ�-����ť��������������
			if (Volume_bkMusic > 0)
			{
				Volume_bkMusic -= 20;
			}
			MediaPlay_bkMusic("set_v", Volume_bkMusic);
			break;
		defualt:
			break;
		}
		EndBatchDraw();
		Sleep(20);
	}
}


void TheAuthorsPage(void);//========================================δ���

//�ú�������չʾ��Ϸ�������
void GameEnd(void) {
	//���尴ť�ķ�Χ
	RECT buttons[2] = {
		{   0,  0,   0,  0},
		{ 510,745, 784,812}
	};
	//������Ϸ���õ�ͼƬ
	IMAGE img;
	loadimage(&img, ".\\ͼƬ�ز�\\�������.png", 1290, 860, TRUE);
	//������ɫ����ʽ
	settextstyle(40, 0, "����");
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);

	hostId = GameOver();//GameOverΪservice��ĺ����������жϸþ�ʤ���߲����ض�Ӧʤ�����id
	TCHAR score[10];//score���ڴ洢ʤ����ҵ��ʽ���
	_itoa_s(*(getplayermsg(1) + 3), score, 10);//getplayermsgΪservice��ĺ���,���ڻ�ȡ������ݣ��˴���ȡ��ʤ����ҵ��ʽ�����_itoa_s�������ʽ���ת��Ϊsorce�ַ�����
	TCHAR end_stage[10];//end_stage���ڴ洢��Ϸ�����Ļغ���
	_itoa_s(stage, end_stage, 10);//_itoa_s�������غ���ת��Ϊend_stage�ַ�����

	//��ѭ������������Ϸ�������Ļ��ƺ���ת��quitΪѭ��������quit=1ѭ��ֹͣ����ת���¸�ҳ��
	bool quit = 0;
	while (!quit) {
		BeginBatchDraw();
		cleardevice();
		putimage(0, 0, &img);

		//��hostId=1��ʤ�����Ϊp1������Ϊp2
		if(hostId ==1)
			outtextxy(711, 223, "P1");
		else 
			outtextxy(711, 223, "P2");

		//�������ڻ���ʤ����ҵ��ʽ�������Ϸ�����Ļغ���
		outtextxy(711, 353, score);
		outtextxy(711, 482, end_stage);

		//����ҵ����Ӧ��ť��MouseDection�᷵�ض�Ӧ��ֵ�Ӷ��ж���ҵ�����Ǹ���ť
		switch (MouseDection(buttons, 2)) {
		case 0:
			break;
		case 1://��ҵ���ص��˵���theinterface��ֵ��Ϊ0����ת���˵�����
			theInterface = 0;
			quit = 1;
			break;
		}
		FlushBatchDraw();
		EndBatchDraw();
	}
}


//=============================================�Ի�����======================

/*
	������ڼ�¼��ҵ�ǰ���ڵĶԻ���
		phase ��ֵ��Ӧ��ҳ�棺
		Ͷ�����ӶԻ���					1
		���߱����Ի���					2
		�¼�չʾ�Ի���					3
		����ҳ��Ի���					4
		�����ɶԻ���					5
		������ɶԻ���					6
		�غϽ���								7
		���������Ի���					8
*/
int MainDailogBox(void) {//��Ϸ�Ի����������Ϸ�е���Ҫ�������棬����ʾ�������м�ķ�����
	int ends = 0;//�öԻ���ķ���ֵ��ƽʱ����0�����ж���Ϸ����ʱ����1

	loadimage(&P1, ".\\ͼƬ�ز�\\1P.png");
	loadimage(&P2, ".\\ͼƬ�ز�\\2P.png");


	//��Ϸ�Ի���ѡ��ṹ����Ϸ�е���Ҫ�ṹ��
	//phase�����жϣ��������phaseֵѡ���ӡ��ͬ�ĶԻ���
	// �����õĶԻ�����������ָ��ı�phaseֵ��Ӱ����һ�ε�ˢ�½���
	// ˢ�µ�ѭ����MainGame�н���
	// phaseΪstatic���������Ա����ϴε��޸�ֵ�����´εĺ������������ڽ����ж�
	//��Щ�Ի���������ѭ���ṹ
	Sleep(5);
	if (phase == 1)
	{
		DialogDice();//Ͷ��ɫ��
	}
	else if (phase == 2)
	{
		PlayerBags();//��ҵ���
	}
	else if (phase == 3)
	{
		EventPrint();//�¼�
	}
	if (phase == 4)
	{
		PayForLand();//����
	}
	else if (phase == 5)
	{
		PayForRent();//����
	}
	if ( Is_in_Prison[hostId - 1] ==3)
	{
		PayForMulct();//����
		phase = 7;
	}
	if (phase == 7)
	{
		//Is_in_Prison����洢�������ֶ�Ӧplayer1��player2���ڵĵز������ͣ�����Ӧ����Ϊ3ʱ˵����Ӧ����ڼ���
		if (Is_in_Prison[hostId - 1] != 3)
		{
			//Is_At_PrisonΪservice��ĺ���������������ڵĵز������ͣ��˴��ǵ�����ڼ���ʱ��������ڵĵز������͸�Ϊ��������
			Is_in_Prison[hostId - 1] = Is_At_Prison();
		}
		else if (Is_in_Prison[hostId - 1] == 3)
		{
			Is_in_Prison[hostId - 1] = 0; //�˴��ǵ�����ڳ���ʱ��������ڵĵز������͸�Ϊ�Ǽ�������
			phase = 1;;//Ȼ��phase��Ϊ1����ҿ����ٴ�Ͷ����
		}
		PhaseEnd();//�غϽ���
		phase = StartSituation(hostId);//StartSituationΪservice��ĺ���,ͨ���ж����״̬����ֵ��phase���Ӷ���ת����һ���ĶԻ���

		//GameOverΪservice��ĺ��������ж���Ϸ�Ƿ����������Ϸ���з���ֵΪ0����Ϸ�������ض�Ӧʤ�����id
		if (GameOver() != 0) {
			phase = 9;
		}
	}
	if (phase == 8)
	{
		UpgradeLand();//����
	}
	if (phase == 9)//��phase=9ʱ˵����Ϸ����
	{
		ends = 1;//��end��ֵΪ1ֹͣ��Ϸ����
	}


	return ends;
}

//================================MainDailogBox���ú���============================


static char name[36][12] = {//�ز�����
	"���",
	"����",
	"��ͷ",
	"����¼�",
	"�Ͼ�",
	"տ��",
	"����¼�",
	"����",
	"��ͷ",
	"����",
	"����",
	"����¼�",
	"����",
	"����",
	"����¼�",
	"����",
	"ͼ��Ժ",
	"����",
	"�Ϻ�",
	"����¼�",
	"�人",
	"��ͨ",
	"����¼�",
	"����",
	"���",
	"����",
	"����",
	"����¼�",
	"����",
	"����",
	"����¼�",
	"����",
};

//��Ϸ����ɫ�ӶԻ���
void DialogDice(void) 
{
	//click��ť�İ뾶
	int clickbutton_r = 85;
	//����click��ť
	RECT click [2] =
	{
		{0,0,0,0},
		{centerx - clickbutton_r,
		 centery - clickbutton_r,
		 centerx + clickbutton_r,
		 centery + clickbutton_r}
	};

	//��ʼ��
	TCHAR step = L'0';

	settextcolor(BLACK);
	setlinecolor(getplayercolorrgb(hostId));
	setfillcolor(getplayercolorrgb(hostId));
	int click_down = 1;
	int turned = 0;
	while (click_down == 1){
		BeginBatchDraw();
		clearrectangle(494, 101, 1152, 758);
		if (hostId == 1) {
			putimage(talksBox.left, talksBox.top, &P1);
		}
		if (hostId == 2) {
			putimage(talksBox.left, talksBox.top, &P2);
		}
		fillellipse(click[1].left, click[1].top, click[1].right, click[1].bottom);
		if (MouseDection(click, 2) == 1){//�����ť������
			step=_T(Dicing(hostId-1)+'0');//ʹ��dicing���ı�������ݣ��������ƶ��Ĳ���������ת��Ϊ�ַ���
			cleardevice();
			loadimage(&board, ".\\ͼƬ�ز�\\��Ϸ����.png", 1290, 860, TRUE);
			putimage(0, 0, &board);	//��ӡ��Ϸ����
			PrintPawn();			//Ȼ���ӡ����
			PrintMap();				//�ȴ�ӡ��ͼ
			PrintPlayerMsg();		//Ȼ���ӡ�����Ϣ
			fillellipse(click[1].left, click[1].top, click[1].right, click[1].bottom);
			drawtext(step, click + 1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			FlushBatchDraw();
			EndBatchDraw();
			click_down = 0;//�˳�ѭ��

			phase = terminal(hostId);//�ж���ҵ��յ��λ�ã���һ���Ի��������

			Sleep(800);
		}
		else {
			drawtext("click", click + 1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
		EndBatchDraw();
		Sleep(5);
	}

}


void PlayerBags(void) {
	RECT button[6] = {
		{0,0,0,0},
		{564,411,794,451},//����1
		{564,521,794,561},//����2
		{854,411,1084,451},//����3
		{854,521,1084,561},//����4
		{773,614,962,759}//��ѡ�����
	};
	int choice = 0;

	IMAGE Player_Bags;
	loadimage(&Player_Bags, ".\\ͼƬ�ز�\\2.png");

	bool changed = 0;
	while (!changed) {
		BeginBatchDraw();
		putimage(494, 101, &Player_Bags);
		if (hostId == 1) {
			putimage(talksBox.left, talksBox.top, &P1);
		}
		if (hostId == 2) {
			putimage(talksBox.left, talksBox.top, &P2);
		}
		switch (choice = MouseDection(button, 6)) {
		case 0:
			break;
		case 1:
		case 2:
		case 3:
		case 4:
			if (CardEffect(hostId, choice - 1) == 1) {//���õ���ʹ�õĺ���
				changed = 1;//���������ʣ�࣬�����ѭ�������򲻷����κ���
				phase = 1;
			}
			break;
		case 5:
			changed = 1;//��ʹ�õ��ߣ�ֱ���˳���
			phase = 1;//���۵���ʹ����񣬽����󶼽�����ɫ�ӽ���
			break;
		default:
			printf("bags wrong !");
			break;
		}
		EndBatchDraw();
		Sleep(5);
	}
}


TCHAR descriptions[5][60] = {
		"��׼��������㽫�ƶ������һ�������",
		"���get������һ��������ߡ�",
		"�в�Ʊ�����3000Ԫ��",
		"��ƽ�˾������·�����",
		"�����ʮ�ľ��䣬����ʽ����20%��"
};


void EventPrint(void) {//�¼��Ի��򣬽����������ɫ���ƶ����¼���Ƥʱ��Ч��
	//��ȡ����¼�����TCHAR* EventHappen(int Id);�������Ҳ������ݲ�������
	int random_event = EventHappen(hostId);
	//��ӡ����¼�
	RECT buttons[2] = {
		{0,0,0,0},
		middleBottom
	};
	RECT text_print = {
		talksBox.left + 71 ,middleBottom.top + 387,
		talksBox.left + 598,middleBottom.top + 509
	};
	IMAGE rand_event_pic;
	loadimage(&rand_event_pic, ".\\ͼƬ�ز�\\����¼�.png", 658, 658, TRUE);

	bool change = 0;
	while (!change) {
		BeginBatchDraw();
		settextstyle(30, 0, "����");
		//��������¼�f
		putimage(talksBox.left, talksBox.top, &rand_event_pic);
		if (hostId == 1) {
			putimage(talksBox.left, talksBox.top, &P1);
		}
		if (hostId == 2) {
			putimage(talksBox.left, talksBox.top, &P2);
		}
		settextcolor(BLACK);
		outtextxy(text_print.left, text_print.top, descriptions[random_event]);
		FlushBatchDraw();
		switch (MouseDection(buttons, 2))
		{
		case 0:
			break;
		case 1:
			//�ڵ��ȷ���������һغ�
			change = 1;
			phase = 7;//�غϽ���
			Sleep(1000);
			break;
		default:
			break;
		}
		EndBatchDraw();
		Sleep(5);
	}

}


void PayForLand(void) {//�ز�����Ի��򣬵������ɫ���ƶ���������Ƥ�����������������ҵ�Ƥ���ύ���ʱ��ӡ
	//����������ť
	RECT buttons[3] = {
		{0,0,0,0},
		{140 + talksBox.left,540 + talksBox.top,240 + talksBox.left,580 + talksBox.top},
		{420 + talksBox.left,540 + talksBox.top,520 + talksBox.left,580 + talksBox.top}
	};
	RECT text_print[2] = {
		{ talksBox.left,240 + talksBox.top,655 + talksBox.left,310 + talksBox.top},
		{ talksBox.left,310 + talksBox.top,557 + talksBox.left,464 + talksBox.top}
	};
	bool change = 0;
	while (!change) {
		BeginBatchDraw();
		char path[100] = ".\\ͼƬ�ز�\\";
		strcat_s(path, 50, name[getplayermsg(hostId)[1]]);
		strcat_s(path, 50, ".png");
		loadimage(&description, path);
		putimage(talksBox.left, talksBox.top, &description);
		if (hostId == 1) {
			putimage(talksBox.left, talksBox.top, &P1);
		}
		if (hostId == 2) {
			putimage(talksBox.left, talksBox.top, &P2);
		}
		//drawtext(name[getplayermsg(hostId)[1]], text_print, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		//drawtext(descrips[getplayermsg(hostId)[1]], text_print + 1, DT_LEFT | DT_WORDBREAK);
		switch (MouseDection(buttons, 3)) {
		case 0:
			break;
		case 1:
			if (PurchaseLand(hostId)) {//��������ɹ���ת�Ƶ���������
				phase = 8;//8����������
				change = 1;
				break;
			}
			else {}
		case 2://��ȡ���������Ļغϣ��ֵ���һ�����
			phase = 7;
			change = 1;
			break;
		default:
			break;
		}
		EndBatchDraw();
		Sleep(5);
	}
}

//�ú���������ȡ���
void PayForRent(void) {
	settextstyle(TEXT_HEIGHT, 0, "����");
	TCHAR taxes[20];
	_itoa_s(rentcalculate(getplayermsg(hostId)[1], 0), taxes, 12,10);
	RECT text_print[2] = {
		{ talksBox.left,240 + talksBox.top,655 + talksBox.left,310 + talksBox.top},
		{ talksBox.left,310 + talksBox.top,557 + talksBox.left,464 + talksBox.top}
	};
	RECT button[2] = {
		{0,0,0,0},
		middleBottom
	};

	IMAGE logo;
	loadimage(&logo, ".\\ͼƬ�ز�\\��������.png");

	bool change = 0;
	while (!change) {
		BeginBatchDraw();
		putimage(494, 101, &logo);
		drawtext(name[getplayermsg(hostId)[1]], text_print, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		//drawtext(name[getplayermsg(hostId)[1]], text_print + 1, DT_LEFT | DT_WORDBREAK);
		drawtext(taxes, &middleBottom, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		if (hostId == 1) {
			putimage(talksBox.left, talksBox.top, &P1);
		}
		if (hostId == 2) {
			putimage(talksBox.left, talksBox.top, &P2);
		}
		switch (MouseDection(button, 2)) {
		case 0:
			break;
		case 1:
			RentPayment(hostId);
			change = 1;
			phase = 4;
			break;
		}
		EndBatchDraw();
		Sleep(5);
	}
}


void PayForMulct(void) {
	settextstyle(TEXT_HEIGHT, TEXT_HEIGHT, "����");
	TCHAR taxes[20];
	_itoa_s(rentcalculate(getplayermsg(hostId)[1], 0), taxes, 12,10);//�˴���ͨ��getplayermsg��ȡ������ڵز���Ȼ����ͨ��rentcalculate��ȡ��Ӧ�ز�����Ϣ
	RECT text_print[2] = {
		{ talksBox.left,240 + talksBox.top,655 + talksBox.left,310 + talksBox.top},
		{ talksBox.left,310 + talksBox.top,557 + talksBox.left,464 + talksBox.top}
	};
	RECT button[2] = {
		{0,0,0,0},
		middleBottom
	};

	IMAGE comfirmation;
	loadimage(&comfirmation, ".\\ͼƬ�ز�\\��������.png");

	 int change = 0;
	while (change!=1) {
		BeginBatchDraw();
		char path[100] = ".\\ͼƬ�ز�\\";
		strcat_s(path, 50, name[getplayermsg(hostId)[1]]);
		strcat_s(path, 50, ".png");
		loadimage(&description, path);
		putimage(talksBox.left, talksBox.top, &description);
		if (hostId == 1) {
			putimage(talksBox.left, talksBox.top, &P1);
		}
		if (hostId == 2) {
			putimage(talksBox.left, talksBox.top, &P2);
		}
		//putimage(494, 101, &comfirmation);
		//drawtext(name[getplayermsg(hostId)[1]], text_print, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		//drawtext(name[getplayermsg(hostId)[1]], text_print + 1, DT_LEFT | DT_WORDBREAK);
		//drawtext(taxes, &middleBottom, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		switch (MouseDection(button, 2)) {
		case 0:
			break;
		case 1:
			MucltCheck(hostId);//�ú���Ϊservice��ĺ�����������ҷ���Ľ���
			change = 1;
			phase = 7;
			break;
		}
		EndBatchDraw();
		Sleep(5);
	}
}


void UpgradeLand(void) {//�������棬����ҽ����Լ��ĵ�Ƥʱ���롣
	settextstyle(TEXT_HEIGHT, 0, "����");
	RECT buttons[3] = {
		{0,0,0,0},
		{140 + talksBox.left,540 + talksBox.top,240 + talksBox.left,580 + talksBox.top},
		{420 + talksBox.left,540 + talksBox.top,520 + talksBox.left,580 + talksBox.top}
	};
	RECT text_print[2] = {
		{ talksBox.left,240 + talksBox.top,655 + talksBox.left,310 + talksBox.top},
		{ talksBox.left,310 + talksBox.top,557 + talksBox.left,464 + talksBox.top}
	};
	//TCHAR* price_before;
	//TCHAR* price_after;============================��δ��ɵĹ��ܡ�

	bool change = 0;
	while (!change) {
		char path[100]= ".\\ͼƬ�ز�\\";
		BeginBatchDraw();
		strcat_s(path, 50, name[getplayermsg(hostId)[1]]);
		strcat_s(path, 50, ".png");
		loadimage(&description, path);
		putimage(talksBox.left, talksBox.top, &description);
		//drawtext(name[getplayermsg(hostId)[1]], text_print, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		//drawtext(description[getplayermsg(hostId)[1]], text_print + 1, DT_LEFT | DT_WORDBREAK);
		clearrectangle(494, 500, 1152, 759);
		drawtext("����", buttons + 1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		drawtext("ȡ��", buttons + 2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		FlushBatchDraw();
		switch (MouseDection(buttons, 3)) {
		case 0:
			break;
		case 1:
			if (PurchaseLand(hostId)) {
				//���������ť����������ɹ���PurchaseLand(hostId)����1����
				//�������˳�ѭ��ˢ�½��棬���½�����������
				change = 1;
				break;
			}
			else {}
		case 2:
			//���ȡ���������غϣ��ж���һ����ҵ�״̬���ı�MainDailogBox�е�phaseֵ��
			phase = 7;
			change = 1;
			break;
		default:
			break;
		}
		EndBatchDraw();
		Sleep(5);
	}
	printf("done\n");
}

//=============================================================================

bool PrintMap(void){

	int player_land_color_b1 = getplayercolor(1)[0] / 3;
	int player_land_color_r1 = getplayercolor(1)[1] / 3;
	int player_land_color_g1 = getplayercolor(1)[2] / 3;
	COLORREF player_land_color1 = RGB(player_land_color_r1, player_land_color_g1, player_land_color_b1);
	int player_land_color_b2 = getplayercolor(2)[0] / 3;
	int player_land_color_r2 = getplayercolor(2)[1] / 3;
	int player_land_color_g2 = getplayercolor(2)[2] / 3;
	COLORREF player_land_color2 = RGB(player_land_color_r2, player_land_color_g2, player_land_color_b2);

	for (int i = 0; i < 24; i++) {
		//��switch����жϵز��Ƿ������ˣ��Ӷ�ȷ�ϵ�Ƥ�߿���ɫ
		switch (*(getplayermsg(hostId))) {
		case 0:
			break;
		case 1:
			//��ȡ�ز���Ӧ��ҵ���ɫrgb��������rgbֵ�Ӷ�ʵ�ֵ���Ч��
			mapPrint(player_land_color1, i);
			break;
		case 2:
			//��ȡ�ز���Ӧ��ҵ���ɫrgb��������rgbֵ�Ӷ�ʵ�ֵ���Ч��
			mapPrint(player_land_color2, i);
			break;
		default:
			break;
		}
	}
	return 1;
}

//�ú������ڻ��Ƶز���ı�ʶɫ�������ǵز��������Сɫ��
void mapPrint(COLORREF color, int position) {
	setlinecolor(color);
	int* p = getlandinfol(position);
	line(p[5], p[6], p[5] + CELL_SIZE, p[6]);
}

//�ú������ڻ����������
bool PrintPawn(void){
	//����Ϊplayer1��player2�ķ�Χ����
	//service���getplayermsg���ڻ�ȡ�����Ϣ��getlandinfol���ڻ�ȡ�ز���Ϣ
	int ps = getplayermsg(1)[1];
	int* ps_in_map = getlandinfol(ps);
	int player1_x = ps_in_map[5];
	int player1_y = ps_in_map[6];
	ps = getplayermsg(2)[1];
	ps_in_map = getlandinfol(ps);
	int player2_x = ps_in_map[5];
	int player2_y = ps_in_map[6];

	int r = CELL_SIZE / 4;

	BeginBatchDraw();
	setlinecolor(RGB(178,232,255));
	fillcircle(player1_x + r, player1_y + r, r);
	FlushBatchDraw();
	setlinecolor(RGB(241, 122,122));
	fillcircle(player2_x + 3*r, player2_y + 3*r, r);
	FlushBatchDraw();
	EndBatchDraw();

	return true;
}


//�����Ϸ���������������Ϣ
void PrintPlayerMsg(void) {
	settextstyle(30, 15, "����");
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);

	//�����ǻ�ȡ��ҵ���ϢȻ��ת��Ϊ�ַ������������Ļ��
	TCHAR temp[10];
	_itoa_s(1, temp, 20);
	outtextxy(267, 51, temp);
	_itoa_s(*(getplayermsg(1) + 3), temp, 10,10);
	outtextxy(267, 112, temp);

	_itoa_s(*(getplayermsg(1) + 4), temp, 10,10);
	outtextxy(212, 187, temp);
	_itoa_s(*(getplayermsg(1) + 5), temp, 10, 10);
	outtextxy(212, 248, temp);
	_itoa_s(*(getplayermsg(1) + 6), temp, 10, 10);
	outtextxy(212,305, temp);
	_itoa_s(*(getplayermsg(1) + 7), temp, 10, 10);
	outtextxy(212,362, temp);

	_itoa_s(2, temp, 10);
	outtextxy(243, 469, temp);
	_itoa_s(*(getplayermsg(2) + 3), temp, 10, 10);
	outtextxy(279, 533, temp);

	_itoa_s(*(getplayermsg(2) + 4), temp, 10, 10);
	outtextxy(212, 605, temp);
	_itoa_s(*(getplayermsg(2) + 5), temp, 10, 10);
	outtextxy(212, 665, temp);
	_itoa_s(*(getplayermsg(2) + 6), temp, 10, 10);
	outtextxy(212, 724, temp);
	_itoa_s(*(getplayermsg(2) + 7), temp,10, 10);
	outtextxy(212, 783, temp);

}


//=============================================================================

int MouseDection(RECT* areas, int n)
{//����һϵ�о������򣬷�������⵽����
	ExMessage msg;
	int result = 0;
	if (peekmessage(&msg, EM_MOUSE))
		{//�������Ϣ
			for (int i = 0; i < n; i++)
			{//������
				if (msg.message == WM_LBUTTONDOWN &&
					msg.x > areas[i].left &&
					msg.x < areas[i].right &&
					msg.y > areas[i].top &&
					msg.y < areas[i].bottom)
				{
					result = i;
					break;
				}
			}
			flushmessage(EM_MOUSE);
		}
		return result;
}
