#pragma once
#include "Global.h"
#include "GameLogic.h"
#include "Graph.h"
class CGameControl
{
    public:
	CGameControl(void);
	~CGameControl(void);

		CGraph m_graph ;  //��ʼ����ͼΪ10+2��10+2��
		Vertex m_ptSelFirst; //��һ����
		Vertex m_ptSelSec;   //�ڶ�����
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

