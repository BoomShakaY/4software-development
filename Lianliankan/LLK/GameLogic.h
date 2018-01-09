#pragma once
#include "Global.h"
#include "Graph.h"
class CGameLogic
{
public:
	CGameLogic(void);
	~CGameLogic(void);
	 
protected:
	Vertex m_avPath[MAX_VERTAX_NUM];//保存在连接时判断所经过的顶点
	int m_nVexNum; //顶点数
	

public:
	void InitMap(CGraph &g);
	void Clear(CGraph &g , Vertex v1, Vertex v2);
	bool IsLink(CGraph &g,Vertex v1,Vertex v2);
	int GetVexPath(Vertex avPath[MAX_VERTAX_NUM]);
	void DeleteVertex();
	int m_nPathNum; //临时数组m_anPath的数目
protected:
	void AddVertex(Vertex v);

public:
	void UpdateArc(CGraph &g, int nRow, int nCol);
	void PushVertex(int v);
	void PopVextex(void);
	int m_anPath[MAX_VERTAX_NUM];//保存连通路径的顶点索引
	int m_nConer; //连接路径数据m_anPath中的拐点数
	bool SearchPath(CGraph& g, int nV0, int nV1);
	bool IsExsit(int nVi);
	bool IsConer(void);
	bool SearchValidPath(CGraph &g);
	void ResetGraph(CGraph &g);
	bool IsBlank(CGraph& g);
};

