
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <graphics.h>
#include <random>
#include"MHQX.h"

#define NAME_LIM 30
#define CARDS_TYPES 4

#define MAP_SIZE 32

extern int phase;


//=======================================玩家信息=====================================

/*
	对于玩家的状态，如下，
	0				死亡
	1				默认，正常
	2				第一回合状态，开局玩家的默认状态
	3				交付租金状态，玩家交付租金后给予的状态，该状态下购买房产价格会变高
	4				监狱状态。
*/


/*
	这是一组玩家数据，它反应玩家的状态
	0为无主
*/
PLAYER player1 = {
	"P1",
	BLUE,
	2,
	1,
	0,
	15000,
	{0,0,0,0}
};
PLAYER player2 = {
	"P1",
	RED,
	2,
	1,
	0,
	15000,
	{0,0,0,0}
};
PLAYER players[2] = { player1,player2 };

extern int hostId = 1;			//当前进行回合的玩家


//==============================地皮数据=============================================




//这是一组土地的数据，即游戏中的棋盘(待初始化）
static LAND map[32] = {
	//type,price,rent,level,Id,x,y
	   { 0,    0,    0,1,0, 400,   7},
	   { 1, 2000, 1000,1,0, 494,   7},
	   { 1, 2000, 1000,1,0, 588,   7},
	   { 2,    0,    0,0,0, 682,   7},
	   { 1, 3000, 1500,1,0, 776,   7},
	   { 1, 2000, 1000,1,0, 870,   7},
	   { 2,    0,    0,0,0, 964,   7},
	   { 1, 5000, 2500,1,0,1058,   7},
	   { 1, 2000, 1000,1,0,1152,   7},
	   { 3,    0, 3000,0,0,1152, 101},
	   { 1, 3000, 1500,1,0,1152, 195},
	   { 2,    0,    0,0,0,1152, 289},
	   { 1, 2000, 1000,1,0,1152, 383},
	   { 1, 3000, 1500,1,0,1152, 477},
	   { 2,    0,    0,0,0,1152, 571},
	   { 1, 2000, 1000,1,0,1152, 655},
	   { 1, 8000, 4000,1,0,1152, 749},
	   { 1, 2000, 1000,1,0,1058, 749},
	   { 1, 5000, 2500,1,0, 964, 749},
	   { 2,    0,    0,0,0, 870, 749},
	   { 1, 3000, 1500,1,0, 776, 749},
	   { 1, 2000, 1000,1,0, 682, 749},
	   { 2,    0,    0,0,0, 588, 749},
	   { 1, 2000, 1000,1,0, 494, 749},
	   { 1, 3000, 1500,1,0, 400, 749},
	   { 3,    0, 3000,0,0, 400, 655},
	   { 1, 2000, 1000,1,0, 400, 571},
	   { 2,    0,    0,0,0, 400, 477},
	   { 1, 2000, 1000,1,0, 400, 283},
	   { 1, 5000, 2500,1,0, 400, 289},
	   { 2,    0,    0,0,0, 400, 195},
	   { 1, 3000, 1500,1,0, 400, 101}

};


//============================其它数据=============================================

extern int stage = 1;						//当前的回合数,在每轮玩家交换时使用


static char(*EventsDescription)[10];						//这个是储存描述事件的字面量数组，


//===============================函数====================================


//7--kind,ownnerId,price,rent,level,x,y;
//该函数用于访问对应地产格的信息
int* getlandinfol(int ps) {
	static int infol[7] = { 0 };
	infol[0] = map[ps].kind;
	infol[1] = map[ps].ownnerId;
	infol[2] = map[ps].price;
	infol[3] = map[ps].rent;
	infol[4] = map[ps].level;
	infol[5] = map[ps].x;
	infol[6] = map[ps].y;

	return infol;
}

//该函数用于访问玩家信息
int* getplayermsg(int Id) {
	Id--;
	static int buffer[8] = { 0 };

	buffer[0] = map[players[Id].position].ownnerId;//玩家所在地的拥有者Id
	buffer[1] = players[Id].position;
	buffer[2] = players[Id].states;
	buffer[3] = players[Id].money;
	buffer[4] = players[Id].bags[0];
	buffer[5] = players[Id].bags[1];
	buffer[6] = players[Id].bags[2];
	buffer[7] = players[Id].bags[3];

	return buffer;
}

//该函数用于访问玩家对应颜色，并返回较灰的对应颜色
int* getplayercolor(int Id) {
	static int colors[3] = { 0 };
	colors[0] = GetBValue(players[Id].color) / 3;
	colors[1] = GetRValue(players[Id].color) / 3;
	colors[2] = GetGValue(players[Id].color) / 3;

	return colors;
}

//该函数用于获取玩家对应颜色
COLORREF getplayercolorrgb(int Id) {
	return players[Id].color;
}

//该函数用于初始化玩家数据
void InitGameIndex(int money) {
	players[0].money = money;
	players[0].states = 2;
	players[1].money = money;
	players[0].states = 2;
	for (int i = 0; i < MAP_SIZE; i++) {
		map[i].level = 0;
		map[i].ownnerId = 0;
	}
	stage = 1;

	PLAYER player1 = {
	"P1",
	BLUE,
	2,
	1,
	0,
	15000,
	{0,0,0,0}
	};
	PLAYER player2 = {
		"P2",
		RED,
		2,
		1,
		0,
		15000,
		{0,0,0,0}
	};
	PLAYER players[2] = { player1,player2 };
}

//该函数用于进行租金结算
void RentPayment(int Id) {
	Id--;
	int ps = players[Id].position;
	//renttrans用于获取对应地产格的租金
	int tax = renttrans(map[ps].price, map[ps].rent, map[ps].level);
	players[Id].money -= tax;
	if (players[Id].money <= 0) // 若玩家支付租金后资金不足，则游戏结束
	{
		players[Id].states = 0;
	}
	//players[Id].states = 3;
	//以下获取对应地产格的拥有者，并增加拥有者的资金（收租）
	int land_lord = map[ps].ownnerId - 1;
	players[land_lord].money += tax;
}


//该函数用于返回对应地产格的地产类型从而判断是否在监狱
int Is_At_Prison()
{
	return map[players[hostId-1].position].kind;
}

//该函数用于罚金结算
void MucltCheck(int Id) {//罚金
	Id--;
	int ps = players[Id].position;
	players[Id].money -= 1000;
	//若玩家支付罚金后资金不足，则游戏结束
	if (players[Id].money <= 0)
		players[Id].states = 0;
}

//该函数用于地产升级判断
bool UpgradePayment(int Id) {
	Id--;
	bool upgrade = 0;
	int ps = players[Id].position;
	unsigned int tax = renttrans(map[ps].price, map[ps].rent, map[ps].level);
	if (players[Id].money <= tax) {
		//如果玩家支付不起升级费用则没有任何事发生
	}
	else if (players[Id].money > tax) {
		//如果玩家支付起升级费用则减少玩家资金并提升地产等级
		players[Id].money -= tax;
		map[ps].level++;
		upgrade = 1;
	}
	return upgrade;
}

//该函数用于道具生效判断
bool CardEffect(int Id, int cardId) {
	Id--;
	if (players[Id].bags[cardId] <= 0) {
		return 0;//如果玩家拥有的道具数为0或小于0则无法使用道具卡
	}
	int ps = players[Id].position;
	switch (cardId) {
	case 0://地产升级
		map[ps].level++;
		players[Id].bags[0]--;
		break;
	case 1://吃席吃席
		players[0].money -= 1000;
		players[1].money -= 1000;
		players[Id].money += 1000;
		players[Id].bags[1]--;
		break;
	case 2://巧取豪夺
		for (int i = 0; i < MAP_SIZE; i++) {
			if (map[i].price <= 3000 && map[i].ownnerId != Id) {
				map[i].ownnerId = Id;
				players[Id].bags[2]--;
				break;
			}
		}
		break;
	case 3://五谷丰登
		players[0].money += 1000;
		players[1].money += 1000;
		players[Id].bags[3]--;
		break;
	default:
		break;
	}
	return 1;
}


/*
	对于玩家的状态，如下，
	0				死亡
	1				默认，正常
	2				第一回合状态，开局玩家的默认状态
	3				交付租金状态，玩家交付租金后给予的状态，该状态下购买房产价格会变高
	4				监狱中
*/
//该函数通过判断玩家状态，在view层调用把返回值赋值给phase，从而跳转至下一步的对话框
int StartSituation(int Id) {
	Id--;
	int next_start = 0;
	switch (players[Id].states) {
	case 0:
		printf("%d dead\n", Id);
		next_start = 7;
		break;
	case 1://玩家对话框将跳转至道具使用对话框
		next_start = 2;
		break;
	case 2://玩家对话框将跳转至投掷骰子对话框
		next_start = 1;
		break;
	case 3://玩家对话框将跳转至道具使用对话框
		next_start = 2;
		break;
	case 4://玩家对话框将跳转至收租对话框
		next_start = 5;
		break;
	default://玩家对话框将跳转至投掷骰子对话框
		next_start = 1;
		break;
	}
	return next_start;
}

//该函数用于判断玩家移动后所到达的位置以及事件
int terminal(int Id) {
	Id--;
	int terminal_point = players[Id].position;
	int result = 7;
	switch (map[terminal_point].kind) {//地产种类（起点0，地产1，事件2，监狱3）
	case 0://到起点
		result = 7;
		break;
	case 1://到房产
		if (map[terminal_point].ownnerId - 1 == Id)//如果房产是你的，升级
			result = 8;
		else if (map[terminal_point].ownnerId == 0)//如果房产无主，购房
			result = 4;
		else if (map[terminal_point].ownnerId != Id + 1)//如果房产为别人的，收租
			result = 5;
		/*else {//意外
			result = 7;
			printf("wrong kind of land\n");
		}*/
		break;
	case 2:
		result = 3;
		break;
	case 3:
		result = 7;
		break;
	default:
		printf("terminal wrong\n");
		break;
	}
	return result;
}


//================================================这里是控制色子点数的===================================

int Dicing(int Id) {
	srand((unsigned)time(NULL));
	int rand_int = (rand() % 6) + 1;
	if (players[Id].position + rand_int <= MAP_SIZE) {
		players[Id].position += rand_int;
	}
	if (players[Id].position + rand_int > MAP_SIZE) {
		players[Id].position -= (MAP_SIZE - rand_int);
		players[Id].money += 2000;
	}

	return rand_int;
}

//该函数用于随机事件的选择
int EventHappen(int Id) {

	Id--;
	srand((unsigned)time(NULL));
	int rand_int = rand() % 5;
	unsigned int rand_int_1 = rand();
	switch (rand_int) {//这里的case对应上面的description的随机事件的位置
	case 0:
		//蹲监狱：直接传送到随机的监狱
		rand_int_1 = rand_int_1 % 2;
		if (rand_int_1 == 1) {
			players[Id].position = 9;
		}
		else {
			players[Id].position = 25;
		}
		break;
	case 1:
		//外挂get：获取随机道具
		rand_int_1 = rand_int_1 % 4;
		(players[Id].bags)[rand_int_1] ++;
		break;
	case 2:
		//中彩票：直接获得2000元
		players[Id].money += 3000;
		break;
	case 3:
		//风平浪静：无事发生
		break;
	case 4:
		//梭哈：到澳门赌场梭哈（玩家现金减少百分之二十）
		players[Id].money = players[Id].money * 0.8;
		break;
	default:
		printf("报错\n");
		break;
	}
	return rand_int;
}

//该函数用于回合结束的结算
void PhaseEnd(void) {
	//以下将玩家的状态设置为默认状态
	int Id = hostId - 1;
	if (players[Id].states == 3) {
		players[Id].states = 1;
	}
	if (players[Id].states == 2) {
		players[Id].states = 1;
	}
	//回合数增加
	stage++;

	//交换当局玩家
	if (hostId == 1)
	{
		hostId = 2;
}
	else if (hostId == 2)
	{
		hostId = 1;
	}
}

//该函数用于进行地产购买
bool PurchaseLand(int Id) {
	Id--;
	bool check = 0;
	int ps = players[Id].position;
	//判断玩家的资金是否足够购买地产
	if (players[Id].money <= map[ps].price) {
		check = 0;
	}
	else if (players[Id].money > map[ps].price) {
		players[Id].money -= map[ps].price;
		map[ps].ownnerId = Id + 1;
		check = 1;
	}
	return check;
}

//该函数用于判断该局胜利者并返回对应胜利玩家id
int GameOver(void) {
	//判断哪个玩家资金数大从而确定胜利者
	if (players[0].money < 0 || players[1].money < 0)
	{
		if (players[0].money > players[1].money)
			return players[0].Id;
		else
			return players[1].Id;
	}
	//如果回合数超过30，游戏结束
	if (stage > 30) {
		if (players[0].money > players[1].money)
			return players[0].Id;
		else
			return players[1].Id;
	}
	else if (players[0].states == 0 && players[1].states != 0) {
		return players[1].Id;
	}
	else if (players[0].states != 0 && players[1].states == 0) {
		return players[0].Id;
	}
	else
		return 0;
}

//该函数用于获取对应地产格的租金
int renttrans(int ori, int tax, int level) {
	int result = tax + level * 300;
	return result;
}

//该函数用于获取对应地产格信息，在view层调用
int rentcalculate(int ps,int plus) {
	int tax = renttrans(
		getlandinfol(ps)[2],//地产格价格
		getlandinfol(ps)[3],//地产格租金
		getlandinfol(ps)[4] + plus);//地产格等级
	return tax;
}