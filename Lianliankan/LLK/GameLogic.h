#pragma once
#include "Global.h"
#include "Graph.h"
class CGameLogic
{
public:
	CGameLogic(void);
	~CGameLogic(void);
	 
protected:
	Vertex m_avPath[MAX_VERTAX_NUM];//����������ʱ�ж��������Ķ���
	int m_nVexNum; //������
	

public:
	void InitMap(CGraph &g);
	void Clear(CGraph &g , Vertex v1, Vertex v2);
	bool IsLink(CGraph &g,Vertex v1,Vertex v2);
	int GetVexPath(Vertex avPath[MAX_VERTAX_NUM]);
	void DeleteVertex();
	int m_nPathNum; //��ʱ����m_anPath����Ŀ
protected:
	void AddVertex(Vertex v);

public:
	void UpdateArc(CGraph &g, int nRow, int nCol);
	void PushVertex(int v);
	void PopVextex(void);
	int m_anPath[MAX_VERTAX_NUM];//������ͨ·���Ķ�������
	int m_nConer; //����·������m_anPath�еĹյ���
	bool SearchPath(CGraph& g, int nV0, int nV1);
	bool IsExsit(int nVi);
	bool IsConer(void);
	bool SearchValidPath(CGraph &g);
	void ResetGraph(CGraph &g);
	bool IsBlank(CGraph& g);
};

