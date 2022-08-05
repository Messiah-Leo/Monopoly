
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


//=======================================�����Ϣ=====================================

/*
	������ҵ�״̬�����£�
	0				����
	1				Ĭ�ϣ�����
	2				��һ�غ�״̬��������ҵ�Ĭ��״̬
	3				�������״̬����ҽ�����������״̬����״̬�¹��򷿲��۸����
	4				����״̬��
*/


/*
	����һ��������ݣ�����Ӧ��ҵ�״̬
	0Ϊ����
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

extern int hostId = 1;			//��ǰ���лغϵ����


//==============================��Ƥ����=============================================




//����һ�����ص����ݣ�����Ϸ�е�����(����ʼ����
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


//============================��������=============================================

extern int stage = 1;						//��ǰ�Ļغ���,��ÿ����ҽ���ʱʹ��


static char(*EventsDescription)[10];						//����Ǵ��������¼������������飬


//===============================����====================================


//7--kind,ownnerId,price,rent,level,x,y;
//�ú������ڷ��ʶ�Ӧ�ز������Ϣ
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

//�ú������ڷ��������Ϣ
int* getplayermsg(int Id) {
	Id--;
	static int buffer[8] = { 0 };

	buffer[0] = map[players[Id].position].ownnerId;//������ڵص�ӵ����Id
	buffer[1] = players[Id].position;
	buffer[2] = players[Id].states;
	buffer[3] = players[Id].money;
	buffer[4] = players[Id].bags[0];
	buffer[5] = players[Id].bags[1];
	buffer[6] = players[Id].bags[2];
	buffer[7] = players[Id].bags[3];

	return buffer;
}

//�ú������ڷ�����Ҷ�Ӧ��ɫ�������ؽϻҵĶ�Ӧ��ɫ
int* getplayercolor(int Id) {
	static int colors[3] = { 0 };
	colors[0] = GetBValue(players[Id].color) / 3;
	colors[1] = GetRValue(players[Id].color) / 3;
	colors[2] = GetGValue(players[Id].color) / 3;

	return colors;
}

//�ú������ڻ�ȡ��Ҷ�Ӧ��ɫ
COLORREF getplayercolorrgb(int Id) {
	return players[Id].color;
}

//�ú������ڳ�ʼ���������
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

//�ú������ڽ���������
void RentPayment(int Id) {
	Id--;
	int ps = players[Id].position;
	//renttrans���ڻ�ȡ��Ӧ�ز�������
	int tax = renttrans(map[ps].price, map[ps].rent, map[ps].level);
	players[Id].money -= tax;
	if (players[Id].money <= 0) // �����֧�������ʽ��㣬����Ϸ����
	{
		players[Id].states = 0;
	}
	//players[Id].states = 3;
	//���»�ȡ��Ӧ�ز����ӵ���ߣ�������ӵ���ߵ��ʽ����⣩
	int land_lord = map[ps].ownnerId - 1;
	players[land_lord].money += tax;
}


//�ú������ڷ��ض�Ӧ�ز���ĵز����ʹӶ��ж��Ƿ��ڼ���
int Is_At_Prison()
{
	return map[players[hostId-1].position].kind;
}

//�ú������ڷ������
void MucltCheck(int Id) {//����
	Id--;
	int ps = players[Id].position;
	players[Id].money -= 1000;
	//�����֧��������ʽ��㣬����Ϸ����
	if (players[Id].money <= 0)
		players[Id].states = 0;
}

//�ú������ڵز������ж�
bool UpgradePayment(int Id) {
	Id--;
	bool upgrade = 0;
	int ps = players[Id].position;
	unsigned int tax = renttrans(map[ps].price, map[ps].rent, map[ps].level);
	if (players[Id].money <= tax) {
		//������֧����������������û���κ��·���
	}
	else if (players[Id].money > tax) {
		//������֧���������������������ʽ������ز��ȼ�
		players[Id].money -= tax;
		map[ps].level++;
		upgrade = 1;
	}
	return upgrade;
}

//�ú������ڵ�����Ч�ж�
bool CardEffect(int Id, int cardId) {
	Id--;
	if (players[Id].bags[cardId] <= 0) {
		return 0;//������ӵ�еĵ�����Ϊ0��С��0���޷�ʹ�õ��߿�
	}
	int ps = players[Id].position;
	switch (cardId) {
	case 0://�ز�����
		map[ps].level++;
		players[Id].bags[0]--;
		break;
	case 1://��ϯ��ϯ
		players[0].money -= 1000;
		players[1].money -= 1000;
		players[Id].money += 1000;
		players[Id].bags[1]--;
		break;
	case 2://��ȡ����
		for (int i = 0; i < MAP_SIZE; i++) {
			if (map[i].price <= 3000 && map[i].ownnerId != Id) {
				map[i].ownnerId = Id;
				players[Id].bags[2]--;
				break;
			}
		}
		break;
	case 3://��ȷ��
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
	������ҵ�״̬�����£�
	0				����
	1				Ĭ�ϣ�����
	2				��һ�غ�״̬��������ҵ�Ĭ��״̬
	3				�������״̬����ҽ�����������״̬����״̬�¹��򷿲��۸����
	4				������
*/
//�ú���ͨ���ж����״̬����view����ðѷ���ֵ��ֵ��phase���Ӷ���ת����һ���ĶԻ���
int StartSituation(int Id) {
	Id--;
	int next_start = 0;
	switch (players[Id].states) {
	case 0:
		printf("%d dead\n", Id);
		next_start = 7;
		break;
	case 1://��ҶԻ�����ת������ʹ�öԻ���
		next_start = 2;
		break;
	case 2://��ҶԻ�����ת��Ͷ�����ӶԻ���
		next_start = 1;
		break;
	case 3://��ҶԻ�����ת������ʹ�öԻ���
		next_start = 2;
		break;
	case 4://��ҶԻ�����ת������Ի���
		next_start = 5;
		break;
	default://��ҶԻ�����ת��Ͷ�����ӶԻ���
		next_start = 1;
		break;
	}
	return next_start;
}

//�ú��������ж�����ƶ����������λ���Լ��¼�
int terminal(int Id) {
	Id--;
	int terminal_point = players[Id].position;
	int result = 7;
	switch (map[terminal_point].kind) {//�ز����ࣨ���0���ز�1���¼�2������3��
	case 0://�����
		result = 7;
		break;
	case 1://������
		if (map[terminal_point].ownnerId - 1 == Id)//�����������ģ�����
			result = 8;
		else if (map[terminal_point].ownnerId == 0)//�����������������
			result = 4;
		else if (map[terminal_point].ownnerId != Id + 1)//�������Ϊ���˵ģ�����
			result = 5;
		/*else {//����
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


//================================================�����ǿ���ɫ�ӵ�����===================================

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

//�ú�����������¼���ѡ��
int EventHappen(int Id) {

	Id--;
	srand((unsigned)time(NULL));
	int rand_int = rand() % 5;
	unsigned int rand_int_1 = rand();
	switch (rand_int) {//�����case��Ӧ�����description������¼���λ��
	case 0:
		//�׼�����ֱ�Ӵ��͵�����ļ���
		rand_int_1 = rand_int_1 % 2;
		if (rand_int_1 == 1) {
			players[Id].position = 9;
		}
		else {
			players[Id].position = 25;
		}
		break;
	case 1:
		//���get����ȡ�������
		rand_int_1 = rand_int_1 % 4;
		(players[Id].bags)[rand_int_1] ++;
		break;
	case 2:
		//�в�Ʊ��ֱ�ӻ��2000Ԫ
		players[Id].money += 3000;
		break;
	case 3:
		//��ƽ�˾������·���
		break;
	case 4:
		//����������Ŷĳ����������ֽ���ٰٷ�֮��ʮ��
		players[Id].money = players[Id].money * 0.8;
		break;
	default:
		printf("����\n");
		break;
	}
	return rand_int;
}

//�ú������ڻغϽ����Ľ���
void PhaseEnd(void) {
	//���½���ҵ�״̬����ΪĬ��״̬
	int Id = hostId - 1;
	if (players[Id].states == 3) {
		players[Id].states = 1;
	}
	if (players[Id].states == 2) {
		players[Id].states = 1;
	}
	//�غ�������
	stage++;

	//�����������
	if (hostId == 1)
	{
		hostId = 2;
}
	else if (hostId == 2)
	{
		hostId = 1;
	}
}

//�ú������ڽ��еز�����
bool PurchaseLand(int Id) {
	Id--;
	bool check = 0;
	int ps = players[Id].position;
	//�ж���ҵ��ʽ��Ƿ��㹻����ز�
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

//�ú��������жϸþ�ʤ���߲����ض�Ӧʤ�����id
int GameOver(void) {
	//�ж��ĸ�����ʽ�����Ӷ�ȷ��ʤ����
	if (players[0].money < 0 || players[1].money < 0)
	{
		if (players[0].money > players[1].money)
			return players[0].Id;
		else
			return players[1].Id;
	}
	//����غ�������30����Ϸ����
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

//�ú������ڻ�ȡ��Ӧ�ز�������
int renttrans(int ori, int tax, int level) {
	int result = tax + level * 300;
	return result;
}

//�ú������ڻ�ȡ��Ӧ�ز�����Ϣ����view�����
int rentcalculate(int ps,int plus) {
	int tax = renttrans(
		getlandinfol(ps)[2],//�ز���۸�
		getlandinfol(ps)[3],//�ز������
		getlandinfol(ps)[4] + plus);//�ز���ȼ�
	return tax;
}