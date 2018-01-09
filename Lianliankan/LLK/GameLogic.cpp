#include "StdAfx.h"
#include "GameLogic.h"
CGameLogic::CGameLogic(void)
{
	m_nVexNum = 0;
	m_nConer = 0;
	m_nPathNum =0;
}


CGameLogic::~CGameLogic(void)
{
}


void CGameLogic::InitMap(CGraph &g)
{
	int VertexNum = (MAX_ROW-2)*(MAX_COL-2);
	int anTemp[(MAX_ROW-2)*(MAX_COL-2)];
	//���û�ɫ 

	for (int i = 0; i<MAX_PIC_NUM ;i++)
	{
		//�ظ���
		for (int j =0; j<REPEAT_NUM; j++)
		{
			anTemp[i * REPEAT_NUM +j] = i;
		}
	}
	anTemp[96] = 1;
	anTemp[97] = 1;
	anTemp[98] = 15;
	anTemp[99] = 15;
	//��������
	srand((int)time(NULL));

	//������⽻����������
	for (int i = 0; i<VertexNum ;i++)
	{
		int nIndex1 =rand() % VertexNum;
		int nIndex2 = rand()% VertexNum;

		int nTemp = anTemp[nIndex1];
		anTemp[nIndex1] = anTemp[nIndex2];
		anTemp[nIndex2] = nTemp;
	}

	for (int i = 0 ;i<MAX_ROW ;i++)
   {
	   for (int j = 0; j<MAX_COL; j++)
	   {
		   if (i==0 || i==11)
		   {
			   g.AddVertex(-1);
		   }
		   else if (j==0 || j==11)
		   {
			   g.AddVertex(-1);
		   }
		   else
		   {
			   //̫������
				g.AddVertex(anTemp[(i-1) * (MAX_ROW-2) +(j-1)]);				
		   }
		   UpdateArc(g,i,j); 
	   }
   }
}


bool CGameLogic::IsLink(CGraph &g,Vertex v1,Vertex v2)
{
    //ͨ��ö�ٷ���ʵ��
    int nV1Index = v1.row *MAX_ROW + v1.col;
	int nV2Index = v2.row *MAX_ROW + v2.col;
	//ѹ���һ����
	PushVertex(nV1Index);
	if (g.GetArc(nV1Index,nV2Index))
	{
		PushVertex(nV2Index);
		return true;
	}
	else if (SearchPath(g,nV1Index,nV2Index) == true)
	{
		PushVertex(nV2Index);
		return true;
	}
	PopVextex();
	return false;
}


void CGameLogic::Clear(CGraph &g, Vertex v1, Vertex v2)
{
       //��ȡ����������
	   int nV1Index = v1.row *MAX_ROW +v1.col;
	   int nV2Index = v2.row *MAX_ROW +v2.col;
       
	   //���¶���
	   g.UpdateVertex(nV1Index,BLANK);
	   g.UpdateVertex(nV2Index,BLANK);

	   //���±�
	   UpdateArc(g,v1.row,v1.col);
	   UpdateArc(g,v2.row,v2.col);
}




void CGameLogic::AddVertex(Vertex v)
{
	m_avPath[m_nVexNum++] = v;
}



void CGameLogic::DeleteVertex()
{
      m_nVexNum = 0;
	  m_nPathNum =0;
	  m_nConer = 0;
}


int CGameLogic::GetVexPath(Vertex avPath[144])
{
	Vertex v;
	for (int i = 0 ; i< m_nPathNum ;i++)	
	{
		v.row = m_anPath[i]/MAX_ROW;
		v.col = m_anPath[i]%MAX_ROW;
		avPath[i] = v;
	}
	return m_nPathNum;
}




void CGameLogic::UpdateArc(CGraph &g, int nRow, int nCol)
{
	int nV1Index = nRow * MAX_ROW +nCol;
	int v1 = g.GetVertex(nV1Index);
	if (nCol >0)
	{
		int nV2Index = nV1Index -1 ;
		int v2 = g.GetVertex(nV2Index);
		//�ж���������� �Ƿ��й�ϵ
		if (v1 == v2|| v1 == BLANK || v2 == BLANK )
		{
			g.AddArc(nV1Index,nV2Index);
		}

	}
	if (nCol < MAX_COL-1)
	{
		int nV2Index = nV1Index + 1 ;
		int v2 = g.GetVertex(nV2Index);		
		//�ж����ұ����� �Ƿ��й�ϵ
        if (v1 == v2|| v1 == BLANK || v2 == BLANK )
		{
			g.AddArc(nV1Index,nV2Index);
		}
	}
	if (nRow > 0)
	{
		int nV2Index = nV1Index -MAX_ROW ;
		//�ж����ϱ����� �Ƿ��й�ϵ
		int v2 = g.GetVertex(nV2Index);		
		if (v1 == v2|| v1 == BLANK || v2 == BLANK )		{
			g.AddArc(nV1Index,nV2Index);
		}
	}
	if (nRow < MAX_COL-1)
	{
		int nV2Index = nV1Index + MAX_ROW ;
		//�ж����±����� �Ƿ��й�ϵ
		int v2 = g.GetVertex(nV2Index);		
		if (v1 == v2|| v1 == BLANK || v2 == BLANK )		{
			g.AddArc(nV1Index,nV2Index);
		}
	}
	if (nRow == 0 || nRow == MAX_COL -1)
	{
		if (nCol != 11)
		{
			int nV2Index = nV1Index + 1 ;
			int v2 = g.GetVertex(nV2Index);		
			//�ж����ұ����� �Ƿ��й�ϵ
			if (v1 == v2|| v1 == BLANK || v2 == BLANK )
			{
				g.AddArc(nV1Index,nV2Index);
			}
		}
	}

	if (nCol == 0 || nCol == MAX_COL -1)
	{
		if (nRow != 11)
		{
			int nV2Index = nV1Index + MAX_ROW ;
			//�ж����±����� �Ƿ��й�ϵ
			int v2 = g.GetVertex(nV2Index);		
			if (v1 == v2|| v1 == BLANK || v2 == BLANK )		{
				g.AddArc(nV1Index,nV2Index);
			}
		}
	}
}

//��û��֮ǰm_nVemNum = 144; ����������ֵ
void CGameLogic::PushVertex(int v)
{
	m_anPath[m_nPathNum] = v;	
	m_nPathNum ++;
	//���֮���ж��Ƿ��ǹյ�
	if (IsConer())
	{
		m_nConer++;
	}

}


void CGameLogic::PopVextex(void)
{
 	if (IsConer())
 	{
		m_nConer --;
 	}
	m_nPathNum --;
}

// nV0,nV1 �� nVi ����������
//getVertex ���ص��Ƕ��������ͼƬ�ĺ���
//Push ѹ�����Vertex���͵�ֵ

bool CGameLogic::SearchPath(CGraph& g, int nV0, int nV1)
{
	//��ȡ������
	int nVexnum = g.GetVexnum();
	//����ͼ�е�nV0�� ���� 0�� ��nVexnum�� ��ֵΪture�ĵ�
	for ( int nVi = nVexnum/2; nVi<nVexnum ;nVi++)
	{
		if (g.GetArc(nV0,nVi) && !IsExsit(nVi))
		{
			//ѹ�뵱ǰ���㣬����·��Ϊһ����Ч����
			PushVertex(nVi);
			
			//�жϹյ���
			if (m_nConer > 2)
			{
				PopVextex();
				continue;
			}

			//���м�㲻��nViʱ
			if (nVi !=nV1)
			{
				//���м䶥�㲻Ϊ�յ�ʱ�򣬱�ʾ��·����ͨ
				if (g.GetVertex(nVi) != BLANK)
				{
					PopVextex(); //ȡ��ѹ��Ķ��㡣��PushVertex��nVi����Ӧ
					continue;
				}
//				m_anPath[m_nPathNum++] =nVi;
				//���nVi��һ���������ĵ㣬���жϣ� nVi��nV1)�Ƿ���ͨ
				if (SearchPath(g,nVi,nV1))
				{
					//Ϊ���ʾ�Ѿ��ҵ���һ��·�����򷵻�true
					return true;

				}
			}
			else  //��� nVi == nV1����ʾ�Ѿ��ҵ���һ����ͨ·���򷵻�true
			{
				return true;
			}
			PopVextex();    ///ȡ��ѹ��Ķ��㡣��PushVertex��nVi����Ӧ
		}
	}
		for ( int nVi = nVexnum/2; nVi>=0 ;nVi--)
	{
		if (g.GetArc(nV0,nVi) && !IsExsit(nVi))
		{
			//ѹ�뵱ǰ���㣬����·��Ϊһ����Ч����
			PushVertex(nVi);
			
			//�жϹյ���
			if (m_nConer > 2)
			{
				PopVextex();
				continue;
			}

			//���м�㲻��nViʱ
			if (nVi !=nV1)
			{
				//���м䶥�㲻Ϊ�յ�ʱ�򣬱�ʾ��·����ͨ
				if (g.GetVertex(nVi) != BLANK)
				{
					PopVextex(); //ȡ��ѹ��Ķ��㡣��PushVertex��nVi����Ӧ
					continue;
				}
//				m_anPath[m_nPathNum++] =nVi;
				//���nVi��һ���������ĵ㣬���жϣ� nVi��nV1)�Ƿ���ͨ
				if (SearchPath(g,nVi,nV1))
				{
					//Ϊ���ʾ�Ѿ��ҵ���һ��·�����򷵻�true
					return true;

				}
			}
			else  //��� nVi == nV1����ʾ�Ѿ��ҵ���һ����ͨ·���򷵻�true
			{
				return true;
			}
			PopVextex();    ///ȡ��ѹ��Ķ��㡣��PushVertex��nVi����Ӧ
		}
	}
	return false;
}


bool CGameLogic::IsExsit(int nVi)
{   
    for (int i = 0; i< m_nPathNum ;i++)
    {
	     if(m_anPath[i] == nVi)
			 return true;
    }
	return false;
}


bool CGameLogic::IsConer(void)
{
	if (m_nPathNum>= 3)
	{
		//�ж������������
		if ((m_anPath[m_nPathNum-1] + m_anPath[m_nPathNum-3])/2 != m_anPath[m_nPathNum-2])
		{
				return true;
		}
	}
	return false;
}

//����ͼ�ҵ���ͬ����ͨ������ͼ
bool CGameLogic::SearchValidPath(CGraph &g)
{
	//��ö�����
	int nVexmnum = g.GetVexnum();
	for (int i = 0; i<nVexmnum ;i++)
	{
		//�õ���һ���ǿն���
		if (g.GetVertex(i) == BLANK)
		{
			continue;
		}
		//�����õ��ڶ���ͬɫ����
		for (int j =0 ;j < nVexmnum ;j++)
		{ 
			if (i != j)
		  {
			//�����i���� �͵�j����ͬɫ
			if (g.GetVertex(i) == g.GetVertex(j))
			{
			//ѹ���һ����
			PushVertex(i);
		    //��Ѱ ����֮�����ͨ·��
			if (g.GetArc(i,j))
			{
				PushVertex(j);
				return true;
			}
			if (SearchPath(g,i,j))
			{
				//�˴����һ��pop �� ����ֹ������·��������£�ջ��Ԫ��û�г�ջ�����,
//				PopVextex();
				return true;
			}
			//ȡ��ѹ��Ķ��㣬��PushVertex(vi);��Ӧ
			PopVextex();
			}
		 }
	  }
	}
    return false;
}


void CGameLogic::ResetGraph(CGraph &g)
{
	int VertexNum = (MAX_ROW-2)*(MAX_COL-2);
	//���������������
	//����ܹ�����ֻ����ͼ�ڲ�10*10��Χ�ڵ�ͼƬ��
	for (int i= 0; i<100 ;i++)
	{
		int nIndex1 =rand() % MAX_VERTAX_NUM;
		int nIndex2 = rand()% MAX_VERTAX_NUM;
		if ((nIndex1/12 ==0 || nIndex1/12 ==11 || nIndex1 % 12 ==0 || nIndex1 %12 ==11 )||(nIndex2/12 ==0 || nIndex2/12 ==11 || nIndex2 % 12 ==0 || nIndex2 %12 ==11 ))
		{
			i--;
			continue;
		}
		
		int nTemp = g.m_Vertices[nIndex1];
		g.m_Vertices[nIndex1] = g.m_Vertices[nIndex2];
		g.m_Vertices[nIndex2] = nTemp;
	}
	//���»���Ϣ
	for (int i = 0 ;i<MAX_ROW ;i++)
	{
		for (int k = 0; k<MAX_COL ;k++)
		{
			UpdateArc(g,i,k);
		}
	}
}


bool CGameLogic::IsBlank(CGraph& g)
{
	for (int i = 0; i <MAX_VERTAX_NUM ;i++)
	{
		if (g.GetVertex(i) != BLANK)
		{
			return false;
		}
	}
	return true;
}
