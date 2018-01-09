#pragma once

#include "Global.h"
#include "GameControl.h"
#include "Graph.h"
// CGameDlg_Relax 对话框
class CGameDlg_Relax : public CDialogEx
{
	DECLARE_DYNAMIC(CGameDlg_Relax)

public:
	CGameDlg_Relax(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CGameDlg_Relax();

// 对话框数据
	enum { IDD = IDD_DIALOG_RELAX };
	//设置画刷对象
	CBrush brush;
	//设置画笔对象
	CPen penLine;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	HICON m_hIcon;
	CDC m_DCMem;
	CDC m_dcElement;
	CDC m_dcMask ;
	CDC m_BGround;
	CDC m_dcPause;
	bool m_bFirstPoint;

	//提示框的对象
	CToolTipCtrl m_Mytip;

	//位置成员
	CPoint m_ptGameTop; //游戏起始点，即游戏第一张图片的顶点坐标，坐标相对于窗口客户区
	CSize m_sizeElem;	//元素图片的大小


	//设置gameControl的对象
	CGameControl m_gameControl;

	//表示游戏是否正在进行的成员
	bool m_bPlaying;
	//表示游戏是否在暂停状态
	bool m_bPause ;

	//设置提示的使用次数
	int TipCount;
	CRect m_rtGameRect;   //游戏区域大小 （该区域为游戏更新区域的大小，考虑到后面画的线，可能会超出图片区域一定范围

	//初始化背景
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
	void DrawGameTime(void);
	void JudgeWin(void);
	afx_msg void OnClickedBtnStop();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnClickedButtonHelp();

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedRelaxButton5();
};
