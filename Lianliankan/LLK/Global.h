#pragma once
#include "Graph.h"
#define  BLANK -1
#define MAX_ROW  12        //10+2游戏地图行数
#define MAX_COL  12        //10+2游戏地图列数
#define MAX_VERTAX_NUM 144 //顶点数
#define MAX_PIC_NUM 16     //图片花色
#define REPEAT_NUM 6       //每种花色图片最多（6*16= 96 差4个）
#define REPEAT_MAX_NUM 10  //图片花色最多为10（就一个）
#define MAX_TOP 50         //游戏地图左上角纵坐标
#define MAX_LEFT 50        //游戏地图左上角横坐标
#define PIC_WIDTH  40      //游戏图片宽度
#define PIC_HEIGHT     40  //游戏图片高度
#define PLAY_TIMER_ID  1   //设置计时器编号
#define GAME_LOSE -1       //失败
#define GAME_SUCCESS 0     //获胜
#define GAME_PLAY 1        //游戏正在进行
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