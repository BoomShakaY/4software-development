#pragma once
#include "resource.h"

// SetDlg 对话框

class CSetDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSetDlg)

public:
	CSetDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSetDlg();

// 对话框数据
	enum { IDD = IDD_SETING_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDropdownFrameCombo();
	afx_msg void OnSelchangeFrameCombo();
	CComboBox m_chosecom;
	afx_msg void OnDropdownLineCombo();
	afx_msg void OnSelchangeLineCombo();
	CComboBox m_choseLine;
	int Frame_sel;
	int Line_sel;
	int PopFrameNum(void);
	int PopLineNum(void);
	int countFrame;
	int countLine;
};
