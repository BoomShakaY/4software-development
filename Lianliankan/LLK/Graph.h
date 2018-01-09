#pragma once

#define MAX_ROW  12        //10+2游戏地图行数
#define MAX_COL  12        //10+2游戏地图列数
#define MAX_VERTAX_NUM 144 //顶点数
//图 数据结构类
class CGraph
{
public:
	CGraph(void);
	~CGraph(void);
    typedef int Vertices [MAX_VERTAX_NUM] ;
	typedef bool AdjMatrix[MAX_VERTAX_NUM][MAX_VERTAX_NUM];

	Vertices   m_Vertices ; //顶点数组
	AdjMatrix  m_AdjMarix ; //关系矩阵
	int        m_nVennum  ; //顶点数
	int        m_nArcnum  ; //边数 
	void InitGraph(void);
	int AddVertex(int info);
	void AddArc(int nV1Index, int nV2Index);
	int GetVertex(int nIndex);
	void UpdateVertex(int nIndex, int info);
	bool GetArc(int nV1Index, int nV2Index);
	int GetVexnum(void);
	void ClearGraph(void);
};

