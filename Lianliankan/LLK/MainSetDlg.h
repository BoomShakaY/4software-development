#pragma once
#include "resource.h"

// CMainSetDlg 对话框

class CMainSetDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMainSetDlg)

public:
	CMainSetDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMainSetDlg();

// 对话框数据
	enum { IDD = IDD_MSET_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// //关联变量
	BOOL m_radiobtngroup1;
	// //关联变量2
	BOOL m_radiobtngroup2;
};
