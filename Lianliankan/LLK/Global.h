#pragma once
#include "Graph.h"
#define  BLANK -1
#define MAX_ROW  12        //10+2��Ϸ��ͼ����
#define MAX_COL  12        //10+2��Ϸ��ͼ����
#define MAX_VERTAX_NUM 144 //������
#define MAX_PIC_NUM 16     //ͼƬ��ɫ
#define REPEAT_NUM 6       //ÿ�ֻ�ɫͼƬ��ࣨ6*16= 96 ��4����
#define REPEAT_MAX_NUM 10  //ͼƬ��ɫ���Ϊ10����һ����
#define MAX_TOP 50         //��Ϸ��ͼ���Ͻ�������
#define MAX_LEFT 50        //��Ϸ��ͼ���ϽǺ�����
#define PIC_WIDTH  40      //��ϷͼƬ���
#define PIC_HEIGHT     40  //��ϷͼƬ�߶�
#define PLAY_TIMER_ID  1   //���ü�ʱ�����
#define GAME_LOSE -1       //ʧ��
#define GAME_SUCCESS 0     //��ʤ
#define GAME_PLAY 1        //��Ϸ���ڽ���
typedef struct Vertex
{
	int row;
	int col;
	int info;
}Vertex;


class CTest
{
public:
     void Output(CGraph &g);
};