#include "StdAfx.h"
#include "Graph.h"


CGraph::CGraph(void)
{
	InitGraph();
}


CGraph::~CGraph(void)
{
}


void CGraph::InitGraph(void)
{
	m_nVennum = 0;
	//初始化顶点和边的信息
	for (int i = 0 ; i<MAX_VERTAX_NUM ;i++)
	{
		//初始化顶点元素都为 -1（没有图片）
		m_Vertices[i] = -1;

		for (int j = 0; j<MAX_VERTAX_NUM ;j++)
		{
			//初始化边除了四个边上的都为1其他的 都为0 （没有关系）
			 m_AdjMarix[i][j] = 0;
		}
	}

}

int CGraph::AddVertex(int info)
{
	//将顶点数据info保存到顶点数组中
   if (m_nVennum >= MAX_VERTAX_NUM)
   {
	   return MAX_VERTAX_NUM;
   }
   m_Vertices[m_nVennum] = info ;
   m_nVennum ++;
   return m_nVennum;

	//返回顶点数组中顶点的个数

}


void CGraph::AddArc(int nV1Index, int nV2Index)
{
	m_AdjMarix[nV1Index][nV2Index] = true ;
	m_AdjMarix[nV2Index][nV1Index] = true ;
}


int CGraph::GetVertex(int nIndex)
{
	return m_Vertices[nIndex];
}


void CGraph::UpdateVertex(int nIndex, int info)
{
	m_Vertices[nIndex]  = info;
}


bool CGraph::GetArc(int nV1Index, int nV2Index)
{
	return m_AdjMarix[nV1Index][nV2Index];
}


int CGraph::GetVexnum(void)
{
	return m_nVennum;
}


void CGraph::ClearGraph(void)
{
	m_nVennum = 0;
	for (int i = 0 ; i<MAX_VERTAX_NUM ;i++)
	{
		//初始化顶点元素都为 -1（没有图片）
		m_Vertices[i] = -1;

		for (int j = 0; j<MAX_VERTAX_NUM ;j++)
		{
			//初始化边除了四个边上的都为1其他的 都为0 （没有关系）
			m_AdjMarix[i][j] = 0;
		}
	}
}
