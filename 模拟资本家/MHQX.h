#ifndef MHQX
#define MHQX
#include<windows.h>

#define NAME_LIM 30
#define CARDS_TYPES 4

int* getplayermsg(int Id);
int* getplayercolor(int Id);


//view层函数

//骰子点数控制
void DialogDice(void);
//打印随机事件
void EventPrint(void);
//玩家道具
void PlayerBags(void);
//购买土地
void PayForLand(void);
//交付罚金
void PayForMulct(void);
//支付租金
void PayForRent(void);
//升级土地
void UpgradeLand(void);
//打印地图
bool PrintMap(void);
void mapPrint(COLORREF color, int position);//PrintMap的次级函数
bool PrintPawn(void);
//打印玩家信息
void PrintPlayerMsg(void);
extern int Is_in_Prison[2];


//service层的数据操作函数

void InitGameIndex(int money);
//掷骰子函数
int Dicing(int Id);
//使相应事件作用游戏效果
int EventHappen(int Id);
//购买土地
bool PurchaseLand(int Id);
//回合结束
void PhaseEnd(void);
//游戏结束
int GameOver(void);
//回合中的步骤跳转
int StartSituation(int Id);
//支付租金
void RentPayment(int Id);
//罚金支付
void MucltCheck(int Id);
//道具作用效果
bool CardEffect(int Id, int cardId);
//租金计算
int renttrans(int ori, int tax, int level);
//等级相关的租金计算
int rentcalculate(int ps, int plus);

//判断是否在监狱里
int Is_At_Prison();

typedef struct __land {
	unsigned int kind;						//地产种类（起点0，地产1，事件2，监狱3）
	unsigned int price;						//地产价格
	unsigned int rent;						//地产租金(1级）,如果时监狱，则为罚金
	unsigned int level;						//地产当前等级
	int ownnerId;							//拥有者ID，无主默认为0.
	unsigned int x;				//该地产在屏幕中的位置
	unsigned int y;				//该地产在屏幕中的位置
}LAND;

typedef struct __player {
	char name[NAME_LIM];					//玩家名字
	COLORREF color;							//代表玩家的颜色
	int states;								//玩家状态(监狱中，收益增加，破产退出游戏，第一回合，交付租金状态)
	int Id;									//玩家的id
	unsigned int position;					//玩家位置
	 int money;						//玩家现有资金
	unsigned int bags[CARDS_TYPES];			//玩家拥有的道具卡，数组的每个位置代表不同的卡，而int值代表道具数量
}PLAYER;


#endif
