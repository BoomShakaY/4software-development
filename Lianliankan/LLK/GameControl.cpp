#include "StdAfx.h"
#include "GameControl.h"
#include "GameLogic.h"

CGameControl::CGameControl(void)
{
	s_nCols = MAX_COL;
	s_nRows = MAX_ROW;
}


CGameControl::~CGameControl(void)
{
}


void CGameControl::StartGame()
{
	gameLogic.InitMap(m_graph);

}


int CGameControl::GetElement(int nRow, int nCol)
{
	return m_graph.GetVertex(nRow * MAX_ROW + nCol );
}


void CGameControl::SetFirstPoint(int nRow, int nCol)
{
	m_ptSelFirst.row = nRow;
	m_ptSelFirst.col = nCol;
}


void CGameControl::SetSecPoint(int nRow, int nCol)
{
	m_ptSelSec.row = nRow;
	m_ptSelSec.col = nCol;
}



bool CGameControl::Link(Vertex avPath[MAX_VERTAX_NUM],int &nVertex)
{
	int Index = m_ptSelFirst.row *12 + m_ptSelFirst.col;
	int Index1 = m_ptSelSec.row *12 +m_ptSelSec.col;
	//��ͼƬ�Ƿ���һ��
	if (Index == Index1 )
	{
		return false;
	}
   	//����ͼƬ�Ƿ�����һ��
	if (m_graph.m_Vertices[Index] != m_graph.m_Vertices[Index1])
	{
		return false;
	}

	else if (gameLogic.IsLink(m_graph,m_ptSelFirst,m_ptSelSec))
	{
		//����
		gameLogic.Clear(m_graph,m_ptSelFirst,m_ptSelSec);
		//����·������
		nVertex = gameLogic.GetVexPath(avPath);
		gameLogic.DeleteVertex();
		return true;
	}
	return false;
}


bool CGameControl::Help(Vertex avPath[MAX_VERTAX_NUM], int& nVexnum)
{
	//�����ж��Ƿ�Ϊ��ͼ������isBlank ��������ûд����
     if (gameLogic.IsBlank(m_graph))
     {
		 return false;
     }
	 if (gameLogic.SearchValidPath(m_graph))
     {
		 //����·������
		 nVexnum = gameLogic.GetVexPath(avPath);
		 gameLogic.m_nPathNum = 0;
		 gameLogic.m_nConer = 0;
		 return true;
     }
	 return false;
}


void CGameControl::Reset(void)
{
	gameLogic.ResetGraph(m_graph);
}


int CGameControl::IsWin(int nTime)
{
	if (nTime <= 0)
	{
		m_graph.ClearGraph();

		return GAME_LOSE ;
	}
	if (gameLogic.IsBlank(m_graph))
	{
		m_graph.ClearGraph();
		return GAME_SUCCESS;
	}
	return GAME_PLAY;
}
