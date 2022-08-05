#ifndef MHQX
#define MHQX
#include<windows.h>

#define NAME_LIM 30
#define CARDS_TYPES 4

int* getplayermsg(int Id);
int* getplayercolor(int Id);


//view�㺯��

//���ӵ�������
void DialogDice(void);
//��ӡ����¼�
void EventPrint(void);
//��ҵ���
void PlayerBags(void);
//��������
void PayForLand(void);
//��������
void PayForMulct(void);
//֧�����
void PayForRent(void);
//��������
void UpgradeLand(void);
//��ӡ��ͼ
bool PrintMap(void);
void mapPrint(COLORREF color, int position);//PrintMap�Ĵμ�����
bool PrintPawn(void);
//��ӡ�����Ϣ
void PrintPlayerMsg(void);
extern int Is_in_Prison[2];


//service������ݲ�������

void InitGameIndex(int money);
//�����Ӻ���
int Dicing(int Id);
//ʹ��Ӧ�¼�������ϷЧ��
int EventHappen(int Id);
//��������
bool PurchaseLand(int Id);
//�غϽ���
void PhaseEnd(void);
//��Ϸ����
int GameOver(void);
//�غ��еĲ�����ת
int StartSituation(int Id);
//֧�����
void RentPayment(int Id);
//����֧��
void MucltCheck(int Id);
//��������Ч��
bool CardEffect(int Id, int cardId);
//������
int renttrans(int ori, int tax, int level);
//�ȼ���ص�������
int rentcalculate(int ps, int plus);

//�ж��Ƿ��ڼ�����
int Is_At_Prison();

typedef struct __land {
	unsigned int kind;						//�ز����ࣨ���0���ز�1���¼�2������3��
	unsigned int price;						//�ز��۸�
	unsigned int rent;						//�ز����(1����,���ʱ��������Ϊ����
	unsigned int level;						//�ز���ǰ�ȼ�
	int ownnerId;							//ӵ����ID������Ĭ��Ϊ0.
	unsigned int x;				//�õز�����Ļ�е�λ��
	unsigned int y;				//�õز�����Ļ�е�λ��
}LAND;

typedef struct __player {
	char name[NAME_LIM];					//�������
	COLORREF color;							//������ҵ���ɫ
	int states;								//���״̬(�����У��������ӣ��Ʋ��˳���Ϸ����һ�غϣ��������״̬)
	int Id;									//��ҵ�id
	unsigned int position;					//���λ��
	 int money;						//��������ʽ�
	unsigned int bags[CARDS_TYPES];			//���ӵ�еĵ��߿��������ÿ��λ�ô���ͬ�Ŀ�����intֵ�����������
}PLAYER;


#endif
