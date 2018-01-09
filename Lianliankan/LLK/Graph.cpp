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
	//��ʼ������ͱߵ���Ϣ
	for (int i = 0 ; i<MAX_VERTAX_NUM ;i++)
	{
		//��ʼ������Ԫ�ض�Ϊ -1��û��ͼƬ��
		m_Vertices[i] = -1;

		for (int j = 0; j<MAX_VERTAX_NUM ;j++)
		{
			//��ʼ���߳����ĸ����ϵĶ�Ϊ1������ ��Ϊ0 ��û�й�ϵ��
			 m_AdjMarix[i][j] = 0;
		}
	}

}

int CGraph::AddVertex(int info)
{
	//����������info���浽����������
   if (m_nVennum >= MAX_VERTAX_NUM)
   {
	   return MAX_VERTAX_NUM;
   }
   m_Vertices[m_nVennum] = info ;
   m_nVennum ++;
   return m_nVennum;

	//���ض��������ж���ĸ���

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
		//��ʼ������Ԫ�ض�Ϊ -1��û��ͼƬ��
		m_Vertices[i] = -1;

		for (int j = 0; j<MAX_VERTAX_NUM ;j++)
		{
			//��ʼ���߳����ĸ����ϵĶ�Ϊ1������ ��Ϊ0 ��û�й�ϵ��
			m_AdjMarix[i][j] = 0;
		}
	}
}
