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
	//设置花色 

	for (int i = 0; i<MAX_PIC_NUM ;i++)
	{
		//重复数
		for (int j =0; j<REPEAT_NUM; j++)
		{
			anTemp[i * REPEAT_NUM +j] = i;
		}
	}
	anTemp[96] = 1;
	anTemp[97] = 1;
	anTemp[98] = 15;
	anTemp[99] = 15;
	//设置种子
	srand((int)time(NULL));

	//随机任意交换两个数字
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
			   //太机智了
				g.AddVertex(anTemp[(i-1) * (MAX_ROW-2) +(j-1)]);				
		   }
		   UpdateArc(g,i,j); 
	   }
   }
}


bool CGameLogic::IsLink(CGraph &g,Vertex v1,Vertex v2)
{
    //通过枚举方法实现
    int nV1Index = v1.row *MAX_ROW + v1.col;
	int nV2Index = v2.row *MAX_ROW + v2.col;
	//压入第一个点
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
       //获取顶点索引号
	   int nV1Index = v1.row *MAX_ROW +v1.col;
	   int nV2Index = v2.row *MAX_ROW +v2.col;
       
	   //更新顶点
	   g.UpdateVertex(nV1Index,BLANK);
	   g.UpdateVertex(nV2Index,BLANK);

	   //更新边
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
		//判断与左边相邻 是否有关系
		if (v1 == v2|| v1 == BLANK || v2 == BLANK )
		{
			g.AddArc(nV1Index,nV2Index);
		}

	}
	if (nCol < MAX_COL-1)
	{
		int nV2Index = nV1Index + 1 ;
		int v2 = g.GetVertex(nV2Index);		
		//判断与右边相邻 是否有关系
        if (v1 == v2|| v1 == BLANK || v2 == BLANK )
		{
			g.AddArc(nV1Index,nV2Index);
		}
	}
	if (nRow > 0)
	{
		int nV2Index = nV1Index -MAX_ROW ;
		//判断与上边相邻 是否有关系
		int v2 = g.GetVertex(nV2Index);		
		if (v1 == v2|| v1 == BLANK || v2 == BLANK )		{
			g.AddArc(nV1Index,nV2Index);
		}
	}
	if (nRow < MAX_COL-1)
	{
		int nV2Index = nV1Index + MAX_ROW ;
		//判断与下边相邻 是否有关系
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
			//判断与右边相邻 是否有关系
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
			//判断与下边相邻 是否有关系
			int v2 = g.GetVertex(nV2Index);		
			if (v1 == v2|| v1 == BLANK || v2 == BLANK )		{
				g.AddArc(nV1Index,nV2Index);
			}
		}
	}
}

//在没入之前m_nVemNum = 144; 即数组的最大值
void CGameLogic::PushVertex(int v)
{
	m_anPath[m_nPathNum] = v;	
	m_nPathNum ++;
	//添加之后判断是否是拐点
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

// nV0,nV1 和 nVi 都是索引号
//getVertex 返回的是顶点数组里，图片的号码
//Push 压入的是Vertex类型的值

bool CGameLogic::SearchPath(CGraph& g, int nV0, int nV1)
{
	//获取顶点数
	int nVexnum = g.GetVexnum();
	//遍历图中的nV0行 ，从 0列 到nVexnum列 ，值为ture的点
	for ( int nVi = nVexnum/2; nVi<nVexnum ;nVi++)
	{
		if (g.GetArc(nV0,nVi) && !IsExsit(nVi))
		{
			//压入当前顶点，假设路径为一个有效顶点
			PushVertex(nVi);
			
			//判断拐点数
			if (m_nConer > 2)
			{
				PopVextex();
				continue;
			}

			//当中间点不是nVi时
			if (nVi !=nV1)
			{
				//当中间顶点不为空的时候，表示该路径不通
				if (g.GetVertex(nVi) != BLANK)
				{
					PopVextex(); //取出压入的顶点。与PushVertex（nVi）对应
					continue;
				}
//				m_anPath[m_nPathNum++] =nVi;
				//如果nVi是一个已消除的点，则判断（ nVi，nV1)是否连通
				if (SearchPath(g,nVi,nV1))
				{
					//为真表示已经找到了一条路径，则返回true
					return true;

				}
			}
			else  //如果 nVi == nV1，表示已经找到了一条联通路径则返回true
			{
				return true;
			}
			PopVextex();    ///取出压入的顶点。与PushVertex（nVi）对应
		}
	}
		for ( int nVi = nVexnum/2; nVi>=0 ;nVi--)
	{
		if (g.GetArc(nV0,nVi) && !IsExsit(nVi))
		{
			//压入当前顶点，假设路径为一个有效顶点
			PushVertex(nVi);
			
			//判断拐点数
			if (m_nConer > 2)
			{
				PopVextex();
				continue;
			}

			//当中间点不是nVi时
			if (nVi !=nV1)
			{
				//当中间顶点不为空的时候，表示该路径不通
				if (g.GetVertex(nVi) != BLANK)
				{
					PopVextex(); //取出压入的顶点。与PushVertex（nVi）对应
					continue;
				}
//				m_anPath[m_nPathNum++] =nVi;
				//如果nVi是一个已消除的点，则判断（ nVi，nV1)是否连通
				if (SearchPath(g,nVi,nV1))
				{
					//为真表示已经找到了一条路径，则返回true
					return true;

				}
			}
			else  //如果 nVi == nV1，表示已经找到了一条联通路径则返回true
			{
				return true;
			}
			PopVextex();    ///取出压入的顶点。与PushVertex（nVi）对应
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
		//判断最后三个顶点
		if ((m_anPath[m_nPathNum-1] + m_anPath[m_nPathNum-3])/2 != m_anPath[m_nPathNum-2])
		{
				return true;
		}
	}
	return false;
}

//遍历图找到相同且联通的两张图
bool CGameLogic::SearchValidPath(CGraph &g)
{
	//获得顶点数
	int nVexmnum = g.GetVexnum();
	for (int i = 0; i<nVexmnum ;i++)
	{
		//得到第一个非空顶点
		if (g.GetVertex(i) == BLANK)
		{
			continue;
		}
		//遍历得到第二个同色顶点
		for (int j =0 ;j < nVexmnum ;j++)
		{ 
			if (i != j)
		  {
			//如果第i个点 和第j个点同色
			if (g.GetVertex(i) == g.GetVertex(j))
			{
			//压入第一个点
			PushVertex(i);
		    //搜寻 两点之间的联通路径
			if (g.GetArc(i,j))
			{
				PushVertex(j);
				return true;
			}
			if (SearchPath(g,i,j))
			{
				//此处多加一个pop ， 来防止搜索到路径的情况下，栈内元素没有出栈的情况,
//				PopVextex();
				return true;
			}
			//取出压入的顶点，与PushVertex(vi);对应
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
	//随机交换两个数字
	//如何能够让它只交换图内部10*10范围内的图片呢
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
	//更新弧信息
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
