#pragma once
#include "Global.h"
#include "GameLogic.h"
#include "Graph.h"
class CGameControl
{
    public:
	CGameControl(void);
	~CGameControl(void);

		CGraph m_graph ;  //初始化地图为10+2行10+2列
		Vertex m_ptSelFirst; //第一个点
		Vertex m_ptSelSec;   //第二个点
		int s_nCols;
		int s_nRows;
		CGameLogic gameLogic;

		int GetRest(int nRow, int nCol);
		void StartGame();
		int GetElement(int nRow, int nCol);
		void SetFirstPoint(int nRow, int nCol);
		void SetSecPoint(int nRow, int nCol);
		bool Link(Vertex avPath[MAX_VERTAX_NUM],int &nVertex);
		bool Help(Vertex avPath[MAX_VERTAX_NUM], int& nVexnum);
		void Reset(void);
		int IsWin(int nTime);
};

