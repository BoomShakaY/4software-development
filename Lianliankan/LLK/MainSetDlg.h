#pragma once
#include "resource.h"

// CMainSetDlg �Ի���

class CMainSetDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMainSetDlg)

public:
	CMainSetDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMainSetDlg();

// �Ի�������
	enum { IDD = IDD_MSET_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// //��������
	BOOL m_radiobtngroup1;
	// //��������2
	BOOL m_radiobtngroup2;
};
