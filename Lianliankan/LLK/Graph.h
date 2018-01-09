#pragma once

#define MAX_ROW  12        //10+2��Ϸ��ͼ����
#define MAX_COL  12        //10+2��Ϸ��ͼ����
#define MAX_VERTAX_NUM 144 //������
//ͼ ���ݽṹ��
class CGraph
{
public:
	CGraph(void);
	~CGraph(void);
    typedef int Vertices [MAX_VERTAX_NUM] ;
	typedef bool AdjMatrix[MAX_VERTAX_NUM][MAX_VERTAX_NUM];

	Vertices   m_Vertices ; //��������
	AdjMatrix  m_AdjMarix ; //��ϵ����
	int        m_nVennum  ; //������
	int        m_nArcnum  ; //���� 
	void InitGraph(void);
	int AddVertex(int info);
	void AddArc(int nV1Index, int nV2Index);
	int GetVertex(int nIndex);
	void UpdateVertex(int nIndex, int info);
	bool GetArc(int nV1Index, int nV2Index);
	int GetVexnum(void);
	void ClearGraph(void);
};

