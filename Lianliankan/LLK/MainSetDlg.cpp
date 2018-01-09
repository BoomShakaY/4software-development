// MainSetDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "LLK.h"
#include "MainSetDlg.h"
#include "afxdialogex.h"


// CMainSetDlg 对话框

IMPLEMENT_DYNAMIC(CMainSetDlg, CDialogEx)

CMainSetDlg::CMainSetDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMainSetDlg::IDD, pParent)
	, m_radiobtngroup1(FALSE)
	, m_radiobtngroup2(FALSE)
{

}

CMainSetDlg::~CMainSetDlg()
{
}

void CMainSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, m_radiobtngroup1);
	DDX_Radio(pDX, IDC_RADIO3, m_radiobtngroup2);
}


BEGIN_MESSAGE_MAP(CMainSetDlg, CDialogEx)
END_MESSAGE_MAP()


// CMainSetDlg 消息处理程序
