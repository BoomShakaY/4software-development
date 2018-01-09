// SetDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "LLK.h"
#include "SetDlg.h"
#include "afxdialogex.h"


// SetDlg 对话框

IMPLEMENT_DYNAMIC(CSetDlg, CDialogEx)

CSetDlg::CSetDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetDlg::IDD, pParent)
{
	countLine = 0;
	countFrame = 0;
}

CSetDlg::~CSetDlg()
{
}

void CSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FRAME_COMBO, m_chosecom);
	DDX_Control(pDX, IDC_LINE_COMBO, m_choseLine);
}


BEGIN_MESSAGE_MAP(CSetDlg, CDialogEx)
	ON_CBN_DROPDOWN(IDC_FRAME_COMBO, &CSetDlg::OnDropdownFrameCombo)
	ON_CBN_SELCHANGE(IDC_FRAME_COMBO, &CSetDlg::OnSelchangeFrameCombo)
	ON_CBN_DROPDOWN(IDC_LINE_COMBO, &CSetDlg::OnDropdownLineCombo)
	ON_CBN_SELCHANGE(IDC_LINE_COMBO, &CSetDlg::OnSelchangeLineCombo)
END_MESSAGE_MAP()


// SetDlg 消息处理程序


void CSetDlg::OnDropdownFrameCombo()
{
	// TODO: 在此添加下拉菜单的内容
	if (countFrame == 0)
	{
	m_chosecom.InsertString(0,_T("红色"));
	m_chosecom.InsertString(1,_T("蓝色"));
	m_chosecom.InsertString(2,_T("绿色"));
	m_chosecom.InsertString(3,_T("粉色"));
	m_chosecom.InsertString(4,_T("青色"));
	m_chosecom.InsertString(5,_T("白色"));
	m_chosecom.InsertString(6,_T("黑色"));
	m_chosecom.SetCurSel(0);
	countFrame ++;
	}
}


void CSetDlg::OnSelchangeFrameCombo()
{
	// TODO: 在此添加选择了以后的操作
	Frame_sel = m_chosecom.GetCurSel();
}


void CSetDlg::OnDropdownLineCombo()
{
	if(countLine == 0){
	m_choseLine.InsertString(0,_T("红色"));
	m_choseLine.InsertString(1,_T("蓝色"));
	m_choseLine.InsertString(2,_T("绿色"));
	m_choseLine.InsertString(3,_T("粉色"));
	m_choseLine.InsertString(4,_T("青色"));
	m_choseLine.InsertString(5,_T("白色"));
	m_choseLine.InsertString(6,_T("黑色"));
	m_choseLine.SetCurSel(0);
	countLine++;
	}
}


void CSetDlg::OnSelchangeLineCombo()
{
	// TODO: 在此添加控件通知处理程序代码
	Line_sel = m_choseLine.GetCurSel();
}


int CSetDlg::PopFrameNum(void)
{
	return Frame_sel;
}


int CSetDlg::PopLineNum(void)
{
	return Line_sel;
}
