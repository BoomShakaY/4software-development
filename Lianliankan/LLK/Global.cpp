#include "stdafx.h"
#include "Global.h"

void CTest ::Output(CGraph &g){
	//�½���־�ļ�
	CStdioFile file (_T("log.txt"),CFile::modeCreate | CFile::modeReadWrite);

	CString strTmp;
	//���������Ϣ
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

	//�����ϵ����
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
	//�ر��ļ�
	file.Close();

}