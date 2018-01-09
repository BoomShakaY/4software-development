#pragma once
#include "Global.h"
#include "GameControl.h"
#include "Graph.h"

// GameDlg_Level �Ի���
class GameDlg_Level : public CDialogEx
{
	DECLARE_DYNAMIC(GameDlg_Level)

public:
	GameDlg_Level(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~GameDlg_Level();

// �Ի�������
	enum { IDD = IDD_DIALOG_LEVEL };

	//���û�ˢ����
	CBrush brush;
	//���û��ʶ���
	CPen penLine;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	HICON m_hIcon;
	CDC m_DCMem;
	CDC m_dcElement;
	CDC m_dcMask ;
	CDC m_BGround;
	CDC m_dcPause;
	bool m_bFirstPoint;
	
	
	//��ʾ��Ķ���
	CToolTipCtrl m_Mytip;

	//λ�ó�Ա
	CPoint m_ptGameTop; //��Ϸ��ʼ�㣬����Ϸ��һ��ͼƬ�Ķ������꣬��������ڴ��ڿͻ���
	CSize m_sizeElem;	//Ԫ��ͼƬ�Ĵ�С


	//����gameControl�Ķ���
	CGameControl m_gameControl;

	//��ʾ��Ϸ�Ƿ����ڽ��еĳ�Ա
	bool m_bPlaying;
	//��ʾ��Ϸ�Ƿ�����ͣ״̬
	bool m_bPause ;

	//������ʾ��ʹ�ô���
	int TipCount;
	CRect m_rtGameRect;   //��Ϸ�����С ��������Ϊ��Ϸ��������Ĵ�С�����ǵ����滭���ߣ����ܻᳬ��ͼƬ����һ����Χ
	
	//��ʼ������
	void InitBackground(void);
	void InitElement(void);
	void DrawTipFrame(int nRow, int nCol);
	void DrawTipLine(Vertex v1,Vertex v2);
	void UpdateMap(void);
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedBtnStart();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnClickedBtnPrompt();
	afx_msg void OnClickedBtnReset();
	CProgressCtrl m_GameProgress;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void DrawGameTime(void);
	void JudgeWin(void);
	afx_msg void OnClickedBtnStop();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnClickedButtonHelp();
	afx_msg void OnBnClickedLevelButton5();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};