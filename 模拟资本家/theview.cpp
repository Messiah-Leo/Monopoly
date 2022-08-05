#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <graphics.h>//包含图形库
#include <conio.h>
#include<stdlib.h>
#include"MHQX.h"
#include"Media.h"

#define	CH_LEN_LIM		30					//按钮允许文本展示的最大长度，具体长度限制与按钮大小有关
#define CELL_SIZE		94					//棋盘格子的大小（像素）
#define PAWN_SIZE		CELL_SIZE/2			//棋子大小
#define	TEXT_HEIGHT		40					//字体高度
#define TEXT_WIDTH      0					//字体宽度
#define NAME_LIM		30


const int centerx = 820;//对话框中心
const int centery = 430;//对跨框中心
static int Volume_bkMusic = 40;//背景音量
 RECT talksBox = { 494, 101, 1152, 759 };//棋盘中对话框
 RECT middleBottom = { 494, 101, 1152, 759 };//棋盘中间偏下部分
 IMAGE description;
 IMAGE board;
 IMAGE P1, P2;//当前玩家显示


 static bool gameEnd = 0;//判断游戏是否结束
 int phase = 1;



int MouseDection(RECT* areas, int n);	//基础的按键检测功能
int MainDailogBox(void);				//对话框，改函数没有循环结构，其依靠MainGame刷新
int Is_in_Prison[2] = { 0 };

//对话框页面



int terminal(int Id);

//用于访问service层数据的函数

int* getplayermsg(int Id);
int* getplayercolor(int Id);
COLORREF getplayercolorrgb(int Id);
int* getlandinfol(int ps);



extern int hostId;//当前回合的玩家，仅用在对话框函数中
extern int stage;//回合数，仅在游戏结束时用于打印。
extern int theInterface;

void MainMenu(void) {//主菜单

	RECT buttons[7] = {
		{  0,  0,  0,  0},//默认返回值
		{552,302,740,378},//新的游戏
		{552,378,740,460},//继续游戏
		{552,460,740,538},//游戏说明
		{552,537,740,622},//游戏设置
		{552,622,740,706},//历史战绩
		{552,706,740,778},//退出游戏
	};

	IMAGE img;
	loadimage(&img, ".\\图片素材\\菜单页面.png", 1290, 860, TRUE);

	//该循环用来控制游戏菜单的页面跳转，quit为循环条件，quit=1时循环停止,跳转至下一个界面
	bool quit = 0;
	while (!quit) {
		BeginBatchDraw();
		cleardevice();
		putimage(0, 0, &img);
		//以下判断玩家点击哪个按钮
		switch (MouseDection(buttons, 7)) {
		case 0:
			break;
		case 1://新游戏
			quit = 1;
			theInterface = 1;
			break;
		case 2://继续游戏
			break;
		case 3://游戏说明
			quit = 1;
			theInterface = 3;
			break;
		case 4://游戏设置
			quit = 1;
			theInterface = 5;
			break;
		case 5://历史战绩
			break;
		case 6://退出游戏
			theInterface = 7;
			quit = 1;
			break;
		default:
			printf("Main menu wrong!");
			break;
		}
		Sleep(30);
		//下面两行用于绘制游戏菜单界面
		FlushBatchDraw();
		EndBatchDraw();
	}

}


void InitGame(void) {//初始菜单

	//以下三行用于加载绘制初始化界面图片
	IMAGE New_Game_Setting;
	ExMessage New_Game_Setting_Clik;
	loadimage(&New_Game_Setting, ".\\图片素材\\新游戏设置界面.png");

	//设置绘制颜色
	setfillstyle(BS_NULL);
	setlinecolor(BLUE);

	//设置游戏初始资金，默认为15000
	int money = 15000;

	//该循环用来控制初始化游戏界面的绘制和跳转，quit为循环条件，quit=1循环停止，跳转至下个页面
	bool quit = 0;
	while (!quit){
		BeginBatchDraw();
		//资金
		if (peekmessage(&New_Game_Setting_Clik, EM_MOUSE))
		{
			//刷新页面
			putimage(0, 0, &New_Game_Setting);

			//以下三个if语句用于资金选择，依次为15000,20000，30000
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

			//最下面一行
			//该if语句用于开始游戏，当玩家点击开始游戏后将theinterface的值改为2，跳转至游戏界面
			else if (New_Game_Setting_Clik.message == WM_LBUTTONDOWN &&
				New_Game_Setting_Clik.x >= 313 &&
				New_Game_Setting_Clik.x <= 524 &&
				New_Game_Setting_Clik.y >= 751 &&
				New_Game_Setting_Clik.y <= 828)
			{
				theInterface = 2;
				quit = 1;
			}
			//该if语句用于返回菜单，当玩家点击开始游戏后将theinterface的值改为0，跳转至菜单界面
			else if (New_Game_Setting_Clik.message == WM_LBUTTONDOWN &&
				New_Game_Setting_Clik.x >= 747 &&
				New_Game_Setting_Clik.x <= 950 &&
				New_Game_Setting_Clik.y >= 751 &&
				New_Game_Setting_Clik.y <= 828)
			{
				theInterface = 0;
				quit = 1;
			}
			//该switch语句判断初始资金的数值从而在对应的资金处绘制方框提示玩家
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
	//该函数为service层的函数，用于初始化玩家的数据
	InitGameIndex(money);
}




void MainGame(void) {//主游戏界面，在游戏过程中会一直停留在该页面
	//打印前准备
	int theTalks = 0;
	cleardevice();
	//循环刷新游戏页面
	int quit = 0;
	while (quit == 0) {//这是游戏中的循环，在游戏未结束时不会退出
		BeginBatchDraw();
		loadimage(&board, ".\\图片素材\\游戏界面.png", 1290, 860, TRUE);
		cleardevice();
		putimage(0, 0, &board);	//打印游戏画面
		PrintPawn();			//然后打印棋子
		PrintMap();				//先打印地图
		PrintPlayerMsg();		//然后打印玩家信息
		quit = MainDailogBox();	//然后打印对话框，这个对话框还附带有游戏结束的判断，游戏结束时返回1，平时返回0
		EndBatchDraw();
		Sleep(20);

	}
	theInterface = 8;//在游戏结束时跳转到结算界面（跳转方法参见主函数说明

}


void Guidebook(void) {//说明页面

	//定义按钮的范围
	RECT buttons[2] = {
		{   0,  0,   0,  0},
		{1074,744,1274,833}
	};
	//加载绘制游戏说明的图片
	IMAGE img;
	loadimage(&img, ".\\图片素材\\游戏说明界面.png", 1290, 860, TRUE);
	//该循环用于控制界面跳转，quit为循环条件，当quit为1时循环停止，跳转至下个界面
	bool quit = 0;
	while (!quit) {
		cleardevice();
		BeginBatchDraw();
		putimage(0, 0, &img);
		//当玩家点击相应按钮后MouseDection会返回对应的值从而判断玩家点击了那个按钮
		switch (MouseDection(buttons, 2)) {
		case 0:
			break;
		//当返回值为1时说明点击了返回菜单按钮
		case 1:
			theInterface = 0;
			quit = 1;
			break;
		//如果返回值为其他，说明运行错误
		default:
			printf("Guidebook wrong!");
			break;
		}
		//以下用于绘制
		EndBatchDraw();
	}
}


void TheRank(void);//==========================================未完成


void Options(void) {//设置
	//定义按钮的范围
	RECT buttons[4] = {
		{0,0,0,0},
		{500,700,800,800},
		{830,280,870,320},
		{670,280,710,320}
	};

	//加载绘制游戏设置的图片
	IMAGE Setting;
	loadimage(&Setting, ".\\图片素材\\设置界面.png", 1290, 860, TRUE);
	
	//该循环用来控制设置界面的绘制和跳转，quit为循环条件，quit=1循环停止，跳转至下个页面
	bool quit = 0;
	while (!quit) {
		BeginBatchDraw();
		putimage(0, 0, &Setting);
		settextcolor(BLACK);
		settextstyle(44, 25, "黑体", 0, 0, 50, 0, 0, 0);
		outtextxy(760, 275, _T('0' + Volume_bkMusic / 20));

		//当玩家点击相应按钮后MouseDection会返回对应的值从而判断玩家点击了那个按钮
		switch (MouseDection(buttons, 4)) {
		case 0:
			break;
		case 1://当返回值为1时说明点击了设置完成按钮，返回游戏菜单	
			quit = 1;
			theInterface = 0;
			break;
		case 2://当返回值为2时说明点击了“+”按钮，音乐声量增加
			if (Volume_bkMusic < 100)
			{
				Volume_bkMusic += 20;
			}
			MediaPlay_bkMusic("set_v", Volume_bkMusic);
			break;
		case 3://当返回值为3时说明点击了“-”按钮，音乐声量减少
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


void TheAuthorsPage(void);//========================================未完成

//该函数用来展示游戏结算界面
void GameEnd(void) {
	//定义按钮的范围
	RECT buttons[2] = {
		{   0,  0,   0,  0},
		{ 510,745, 784,812}
	};
	//加载游戏设置的图片
	IMAGE img;
	loadimage(&img, ".\\图片素材\\结算界面.png", 1290, 860, TRUE);
	//设置颜色和样式
	settextstyle(40, 0, "等线");
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);

	hostId = GameOver();//GameOver为service层的函数，用于判断该局胜利者并返回对应胜利玩家id
	TCHAR score[10];//score用于存储胜利玩家的资金数
	_itoa_s(*(getplayermsg(1) + 3), score, 10);//getplayermsg为service层的函数,用于获取玩家数据，此处获取了胜利玩家的资金数，_itoa_s函数将资金数转换为sorce字符数组
	TCHAR end_stage[10];//end_stage用于存储游戏结束的回合数
	_itoa_s(stage, end_stage, 10);//_itoa_s函数将回合数转换为end_stage字符数组

	//该循环用来控制游戏结算界面的绘制和跳转，quit为循环条件，quit=1循环停止，跳转至下个页面
	bool quit = 0;
	while (!quit) {
		BeginBatchDraw();
		cleardevice();
		putimage(0, 0, &img);

		//当hostId=1，胜利玩家为p1；否则为p2
		if(hostId ==1)
			outtextxy(711, 223, "P1");
		else 
			outtextxy(711, 223, "P2");

		//以下用于绘制胜利玩家的资金数和游戏结束的回合数
		outtextxy(711, 353, score);
		outtextxy(711, 482, end_stage);

		//当玩家点击相应按钮后MouseDection会返回对应的值从而判断玩家点击了那个按钮
		switch (MouseDection(buttons, 2)) {
		case 0:
			break;
		case 1://玩家点击回到菜单后将theinterface的值改为0，跳转至菜单界面
			theInterface = 0;
			quit = 1;
			break;
		}
		FlushBatchDraw();
		EndBatchDraw();
	}
}


//=============================================对话框函数======================

/*
	这个用于记录玩家当前所在的对话框。
		phase 数值对应的页面：
		投掷骰子对话框					1
		道具背包对话框					2
		事件展示对话框					3
		房产页面对话框					4
		租金缴纳对话框					5
		罚金缴纳对话框					6
		回合结束								7
		升级房产对话框					8
*/
int MainDailogBox(void) {//游戏对话框，这个是游戏中的主要交互界面，它显示在棋盘中间的方格内
	int ends = 0;//该对话框的返回值，平时返回0，在判断游戏结束时返回1

	loadimage(&P1, ".\\图片素材\\1P.png");
	loadimage(&P2, ".\\图片素材\\2P.png");


	//游戏对话框选择结构，游戏中的主要结构，
	//phase用于判断，程序根据phase值选择打印不同的对话框
	// 被调用的对话框函数可以用指针改变phase值，影响下一次的刷新界面
	// 刷新的循环在MainGame中进行
	// phase为static变量，可以保存上次的修改值，在下次的函数启动中用于界面判断
	//这些对话框函数具有循环结构
	Sleep(5);
	if (phase == 1)
	{
		DialogDice();//投掷色子
	}
	else if (phase == 2)
	{
		PlayerBags();//玩家道具
	}
	else if (phase == 3)
	{
		EventPrint();//事件
	}
	if (phase == 4)
	{
		PayForLand();//购买
	}
	else if (phase == 5)
	{
		PayForRent();//收租
	}
	if ( Is_in_Prison[hostId - 1] ==3)
	{
		PayForMulct();//监狱
		phase = 7;
	}
	if (phase == 7)
	{
		//Is_in_Prison数组存储两个数字对应player1和player2所在的地产格类型，当对应数字为3时说明对应玩家在监狱
		if (Is_in_Prison[hostId - 1] != 3)
		{
			//Is_At_Prison为service层的函数，返回玩家所在的地产格类型，此处是当玩家在监狱时将玩家所在的地产格类型改为监狱类型
			Is_in_Prison[hostId - 1] = Is_At_Prison();
		}
		else if (Is_in_Prison[hostId - 1] == 3)
		{
			Is_in_Prison[hostId - 1] = 0; //此处是当玩家在出狱时将玩家所在的地产格类型改为非监狱类型
			phase = 1;;//然后将phase设为1，玩家可以再次投骰子
		}
		PhaseEnd();//回合结束
		phase = StartSituation(hostId);//StartSituation为service层的函数,通过判断玩家状态，赋值给phase，从而跳转至下一步的对话框

		//GameOver为service层的函数用于判断游戏是否结束，若游戏进行返回值为0，游戏结束返回对应胜利玩家id
		if (GameOver() != 0) {
			phase = 9;
		}
	}
	if (phase == 8)
	{
		UpgradeLand();//升级
	}
	if (phase == 9)//当phase=9时说明游戏结束
	{
		ends = 1;//将end赋值为1停止游戏交互
	}


	return ends;
}

//================================MainDailogBox调用函数============================


static char name[36][12] = {//地产名字
	"起点",
	"信阳",
	"包头",
	"随机事件",
	"南京",
	"湛江",
	"随机事件",
	"北京",
	"汕头",
	"监狱",
	"沈阳",
	"随机事件",
	"德州",
	"杭州",
	"随机事件",
	"玉林",
	"图灵院",
	"曲阜",
	"上海",
	"随机事件",
	"武汉",
	"南通",
	"随机事件",
	"绍兴",
	"天津",
	"监狱",
	"揭阳",
	"随机事件",
	"沧州",
	"深圳",
	"随机事件",
	"广州",
};

//游戏的掷色子对话框
void DialogDice(void) 
{
	//click按钮的半径
	int clickbutton_r = 85;
	//定义click按钮
	RECT click [2] =
	{
		{0,0,0,0},
		{centerx - clickbutton_r,
		 centery - clickbutton_r,
		 centerx + clickbutton_r,
		 centery + clickbutton_r}
	};

	//初始化
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
		if (MouseDection(click, 2) == 1){//如果按钮被按下
			step=_T(Dicing(hostId-1)+'0');//使用dicing，改变玩家数据，并返回移动的步数，将其转换为字符串
			cleardevice();
			loadimage(&board, ".\\图片素材\\游戏界面.png", 1290, 860, TRUE);
			putimage(0, 0, &board);	//打印游戏画面
			PrintPawn();			//然后打印棋子
			PrintMap();				//先打印地图
			PrintPlayerMsg();		//然后打印玩家信息
			fillellipse(click[1].left, click[1].top, click[1].right, click[1].bottom);
			drawtext(step, click + 1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			FlushBatchDraw();
			EndBatchDraw();
			click_down = 0;//退出循环

			phase = terminal(hostId);//判断玩家的终点的位置，下一个对话框的种类

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
		{564,411,794,451},//道具1
		{564,521,794,561},//道具2
		{854,411,1084,451},//道具3
		{854,521,1084,561},//道具4
		{773,614,962,759}//不选择道具
	};
	int choice = 0;

	IMAGE Player_Bags;
	loadimage(&Player_Bags, ".\\图片素材\\2.png");

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
			if (CardEffect(hostId, choice - 1) == 1) {//调用道具使用的函数
				changed = 1;//如果道具有剩余，则结束循环，否则不发生任何事
				phase = 1;
			}
			break;
		case 5:
			changed = 1;//不使用道具，直接退出。
			phase = 1;//不论道具使用与否，结束后都进入掷色子界面
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
		"你蹲监狱啦，你将移动到随机一个监狱里。",
		"外挂get：你获得一件随机道具。",
		"中彩票：获得3000元。",
		"风平浪静：无事发生。",
		"梭哈：十赌九输，你的资金减少20%。"
};


void EventPrint(void) {//事件对话框，仅仅当玩家掷色子移动到事件地皮时生效。
	//获取随机事件描述TCHAR* EventHappen(int Id);这个函数也兼具数据操作功能
	int random_event = EventHappen(hostId);
	//打印随机事件
	RECT buttons[2] = {
		{0,0,0,0},
		middleBottom
	};
	RECT text_print = {
		talksBox.left + 71 ,middleBottom.top + 387,
		talksBox.left + 598,middleBottom.top + 509
	};
	IMAGE rand_event_pic;
	loadimage(&rand_event_pic, ".\\图片素材\\随机事件.png", 658, 658, TRUE);

	bool change = 0;
	while (!change) {
		BeginBatchDraw();
		settextstyle(30, 0, "等线");
		//描述这个事件f
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
			//在点击确定后结束玩家回合
			change = 1;
			phase = 7;//回合结束
			Sleep(1000);
			break;
		default:
			break;
		}
		EndBatchDraw();
		Sleep(5);
	}

}


void PayForLand(void) {//地产购买对话框，当玩家掷色子移动到无主地皮，或者玩家在其它玩家地皮上提交租金时打印
	//定义两个按钮
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
		char path[100] = ".\\图片素材\\";
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
			if (PurchaseLand(hostId)) {//购买，如果成功，转移到升级界面
				phase = 8;//8是升级界面
				change = 1;
				break;
			}
			else {}
		case 2://在取消后结束你的回合，轮到下一个玩家
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

//该函数用于收取租金
void PayForRent(void) {
	settextstyle(TEXT_HEIGHT, 0, "宋体");
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
	loadimage(&logo, ".\\图片素材\\罚金和租金.png");

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
	settextstyle(TEXT_HEIGHT, TEXT_HEIGHT, "宋体");
	TCHAR taxes[20];
	_itoa_s(rentcalculate(getplayermsg(hostId)[1], 0), taxes, 12,10);//此处先通过getplayermsg获取玩家所在地产格，然后再通过rentcalculate获取对应地产格信息
	RECT text_print[2] = {
		{ talksBox.left,240 + talksBox.top,655 + talksBox.left,310 + talksBox.top},
		{ talksBox.left,310 + talksBox.top,557 + talksBox.left,464 + talksBox.top}
	};
	RECT button[2] = {
		{0,0,0,0},
		middleBottom
	};

	IMAGE comfirmation;
	loadimage(&comfirmation, ".\\图片素材\\罚金和租金.png");

	 int change = 0;
	while (change!=1) {
		BeginBatchDraw();
		char path[100] = ".\\图片素材\\";
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
			MucltCheck(hostId);//该函数为service层的函数，用于玩家罚金的结算
			change = 1;
			phase = 7;
			break;
		}
		EndBatchDraw();
		Sleep(5);
	}
}


void UpgradeLand(void) {//升级界面，在玩家进入自己的地皮时进入。
	settextstyle(TEXT_HEIGHT, 0, "等线");
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
	//TCHAR* price_after;============================还未完成的功能。

	bool change = 0;
	while (!change) {
		char path[100]= ".\\图片素材\\";
		BeginBatchDraw();
		strcat_s(path, 50, name[getplayermsg(hostId)[1]]);
		strcat_s(path, 50, ".png");
		loadimage(&description, path);
		putimage(talksBox.left, talksBox.top, &description);
		//drawtext(name[getplayermsg(hostId)[1]], text_print, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		//drawtext(description[getplayermsg(hostId)[1]], text_print + 1, DT_LEFT | DT_WORDBREAK);
		clearrectangle(494, 500, 1152, 759);
		drawtext("升级", buttons + 1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		drawtext("取消", buttons + 2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		FlushBatchDraw();
		switch (MouseDection(buttons, 3)) {
		case 0:
			break;
		case 1:
			if (PurchaseLand(hostId)) {
				//点击升级按钮，如果升级成功（PurchaseLand(hostId)返回1），
				//则重新退出循环刷新界面，重新进入升级界面
				change = 1;
				break;
			}
			else {}
		case 2:
			//如果取消，结束回合，判断下一个玩家的状态，改变MainDailogBox中的phase值。
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
		//用switch语句判断地产是否有主人，从而确认地皮边框颜色
		switch (*(getplayermsg(hostId))) {
		case 0:
			break;
		case 1:
			//获取地产对应玩家的颜色rgb，并调低rgb值从而实现调灰效果
			mapPrint(player_land_color1, i);
			break;
		case 2:
			//获取地产对应玩家的颜色rgb，并调低rgb值从而实现调灰效果
			mapPrint(player_land_color2, i);
			break;
		default:
			break;
		}
	}
	return 1;
}

//该函数用于绘制地产格的标识色条，就是地产格上面的小色条
void mapPrint(COLORREF color, int position) {
	setlinecolor(color);
	int* p = getlandinfol(position);
	line(p[5], p[6], p[5] + CELL_SIZE, p[6]);
}

//该函数用于绘制玩家棋子
bool PrintPawn(void){
	//以下为player1和player2的范围定义
	//service层的getplayermsg用于获取玩家信息，getlandinfol用于获取地产信息
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


//输出游戏界面左栏中玩家信息
void PrintPlayerMsg(void) {
	settextstyle(30, 15, "等线");
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);

	//以下是获取玩家的信息然后转换为字符串并输出到屏幕上
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
{//输入一系列矩形区域，返回鼠标检测到区域
	ExMessage msg;
	int result = 0;
	if (peekmessage(&msg, EM_MOUSE))
		{//如果有信息
			for (int i = 0; i < n; i++)
			{//逐个检测
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
