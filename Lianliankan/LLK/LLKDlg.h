
// LLKDlg.h : ͷ�ļ�
//

#pragma once


// CLLKDlg �Ի���
class CLLKDlg : public CDialogEx
{
// ����
public:
	CLLKDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_LLK_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	CDC m_DCMem;
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	void InitBackground(void);
	void Paint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedButtonBasic();
	afx_msg void OnClickedButtonRelax();
	afx_msg void OnClickedButtonLevel();
	afx_msg void OnClickedBtnHelp();
	afx_msg void OnBnClickedButtonSetting();
};
