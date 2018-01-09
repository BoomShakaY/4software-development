#include "stdafx.h"
#include "Global.h"

void CTest ::Output(CGraph &g){
	//新建日志文件
	CStdioFile file (_T("log.txt"),CFile::modeCreate | CFile::modeReadWrite);

	CString strTmp;
	//输出顶点信息
	for (int i = 0; i<g.m_nVennum ;i++)
	{
		if (i%12 ==0)
		{
			strTmp = "\n";
			file.WriteString(strTmp);
		}
		strTmp.Format(_T("%d\t"),g.GetVertex(i));
		file.WriteString(strTmp);
	}

	//输出关系矩阵
	for (int i =0; i<MAX_VERTAX_NUM ; i++)
	{
		strTmp = "\n";
	file.WriteString(strTmp);
		for (int j = 0; j<MAX_VERTAX_NUM ;j++)
		{
			strTmp.Format(_T("%d\t"),g.GetArc(i,j));
			file.WriteString(strTmp);
		}
		
	}
	//关闭文件
	file.Close();

}