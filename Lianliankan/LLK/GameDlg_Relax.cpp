// GameDlg_Relax.cpp : 实现文件
//

#include "stdafx.h"
#include "LLK.h"
#include "GameDlg_Relax.h"
#include "afxdialogex.h"
#include "resource.h"
#include "GameLogic.h"
#include "Global.h"
#include "SetDlg.h"
// CGameDlg_Relax 对话框

IMPLEMENT_DYNAMIC(CGameDlg_Relax, CDialogEx)

CGameDlg_Relax::CGameDlg_Relax(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGameDlg_Relax::IDD, pParent)
{
	//游戏起始位置
	m_ptGameTop.x = MAX_TOP;
	m_ptGameTop.y = MAX_LEFT;

	//单个元素的图片大小设置
	m_sizeElem.cx = PIC_WIDTH;
	m_sizeElem.cy = PIC_HEIGHT;

	//初始化更新游戏区域
	m_rtGameRect.top = MAX_TOP;
	m_rtGameRect.left = MAX_LEFT;
	m_rtGameRect.right = m_rtGameRect.left +PIC_WIDTH * MAX_ROW;
	m_rtGameRect.bottom = m_rtGameRect.top + PIC_HEIGHT * MAX_COL;

	//初始点的标志
	m_bFirstPoint =true;
	m_bPlaying = false;
	m_bPause = false;
	brush.CreateSolidBrush(RGB(0,240,255));
	penLine.CreatePen(PS_SOLID,2,RGB(0,255,0));
	TipCount = 5;
}

CGameDlg_Relax::~CGameDlg_Relax()
{
}

void CGameDlg_Relax::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RELAX_GAME_TIME, m_GameProgress);
}




void CGameDlg_Relax::InitBackground(void)
{

	//必须加后缀名！写全路径！
	HANDLE bmp = ::LoadImage(NULL,_T("theme\\picture\\relax_bg.bmp"),IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
	//创建兼容DC
	CClientDC dc(this);
	m_BGround.CreateCompatibleDC(&dc);
	m_BGround.SelectObject(bmp);

	// 将位图选入DC
	m_DCMem.CreateCompatibleDC(&dc);

	CBitmap bmpMian;
	bmpMian.CreateCompatibleBitmap(&dc,800,600);
	m_DCMem.SelectObject(&bmpMian);
	m_DCMem.BitBlt(0,0,800,600,&m_BGround,0,0,SRCCOPY);
}

BEGIN_MESSAGE_MAP(CGameDlg_Relax, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_RELAX_BUTTON1, &CGameDlg_Relax::OnBnClickedBtnStart)
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_RELAX_BUTTON3, &CGameDlg_Relax::OnClickedBtnPrompt)
	ON_BN_CLICKED(IDC_RELAX_BUTTON4, &CGameDlg_Relax::OnClickedBtnReset)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_RELAX_BUTTON2, &CGameDlg_Relax::OnClickedBtnStop)
	ON_BN_CLICKED(IDC_RELAX_BUTTON6, &CGameDlg_Relax::OnClickedButtonHelp)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_RELAX_BUTTON5, &CGameDlg_Relax::OnBnClickedRelaxButton5)
END_MESSAGE_MAP()

// CGameDlg_Relax 消息处理程序

BOOL CGameDlg_Relax::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化
	InitBackground();
	InitElement();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CGameDlg_Relax::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	dc.BitBlt(0,0,800,600,&m_DCMem,0,0,SRCCOPY);
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
}

void CGameDlg_Relax::InitElement(void)
{
	//------------------加载bmp图片------------------
	//必须加后缀名！写全路径！
	HANDLE bmp = ::LoadImage(NULL,_T("theme\\picture\\Ball_element.bmp"),IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
	//创建兼容DC

	CBitmap bmpMian;
	bmpMian.LoadBitmap(IDB_BITMAP_BASIC);

  //获取当前地图资源
	CClientDC dc(this);
	m_dcElement.CreateCompatibleDC(&dc);
	// 将位图选入DC
	//m_DCMem.SelectObject(bmpMian);
	m_dcElement.SelectObject(bmp);

	//加载掩码BMP资源
	HANDLE hMask = ::LoadImageW(NULL,_T("theme\\picture\\Ball_element_r.bmp"),IMAGE_BITMAP,0,0,LR_LOADFROMFILE);

	//创建与视频内存兼容的内存DC
	m_dcMask.CreateCompatibleDC(&dc);

	//将位图资源选入DC
	m_dcMask.SelectObject(hMask);

	//加赞暂停图片BMP资源
	HANDLE Pau = ::LoadImage(NULL,_T("theme\\picture\\pause.bmp"),IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
	m_dcPause.CreateCompatibleDC(&dc);
	m_dcPause.SelectObject(Pau);


	m_Mytip.Create(this);
	m_Mytip.SetDelayTime(100); //设置延迟
	m_Mytip.SetTipTextColor( RGB(0,0,255) ); //设置提示文本的颜色
	m_Mytip.SetTipBkColor( RGB(255,255,255)); //设置提示框的背景颜色
	m_Mytip.Activate(TRUE); //设置是否启用提示

}
void CGameDlg_Relax::OnBnClickedBtnStart()
{
	//初始化游戏地图
	m_gameControl.StartGame();	
    //更新地图
	UpdateMap();
	//设置游戏正在进行
	m_bPlaying = true;
	//进制点击开始游戏
	GetDlgItem(IDC_RELAX_BUTTON1)->EnableWindow(FALSE);
	//初始化进度条
	m_GameProgress.SetRange(0,10000);  //设置范围
	m_GameProgress.SetStep(1);         //初始步数值
	m_GameProgress.SetPos(1);        //设置初始值

	//启动定时器
	this->SetTimer(PLAY_TIMER_ID,1000,NULL);
	
	//绘制当前秒数
// 	DrawGameTime();  //直接在消息相应里写了
	GetDlgItem(IDC_RELAX_STATIC)->SetWindowTextW(_T("您已经用了 0 秒"));
	GetDlgItem(IDC_RELAX_STATIC)->ShowWindow(SW_NORMAL);

	m_Mytip.AddTool( GetDlgItem(IDC_RELAX_BUTTON3), _T("你有无数次使用提示的机会"));;
	//刷新
	CRect rtlbl;
	GetDlgItem(IDC_RELAX_STATIC)->GetWindowRect(&rtlbl);
	ScreenToClient(&rtlbl);
	InvalidateRect(&rtlbl);
	UpdateWindow();
	InvalidateRect(m_rtGameRect,FALSE);
}


void CGameDlg_Relax::UpdateMap(void)
{
	int nTop = MAX_TOP;
	int nLeft = MAX_LEFT;
	int nElemH = PIC_HEIGHT;
	int nElenW = PIC_WIDTH ;
	m_DCMem.BitBlt(0,0,800,600,&m_BGround,0,0,SRCCOPY);	
	for (int i = 1; i<11 ;i++)
	{
		for (int j = 1; j<11 ;j++)
		{
			//绘制单张图片
			int info = m_gameControl .GetElement(i,j);

			//背景与掩码相或，边保留，图像区域为1
			m_DCMem.BitBlt(nLeft + j * nElenW , nTop + i * nElenW , nElenW , nElemH , & m_dcMask , 0 ,info * nElemH,SRCPAINT);
			
			//与元素图片相与 边保留，图像区域为元素图片
			m_DCMem.BitBlt(nLeft + j * nElenW , nTop + i * nElenW , nElenW , nElemH , & m_dcElement ,0 , info * nElemH,SRCAND);

		}
	}
}


void CGameDlg_Relax::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (point.x < m_ptGameTop.x || point.y < m_ptGameTop.y )
	{
		return CDialogEx::OnLButtonUp(nFlags, point);
	}
	int nRow = ( point.y - m_ptGameTop.x)/m_sizeElem.cx;
	int nCol = (point.x - m_ptGameTop.y) /m_sizeElem.cy;
	if (nRow > 11 || nCol > 11)
	{
		return CDialogEx::OnLButtonUp(nFlags, point);
	}
	// 判断是否是第一个点
	if (m_bFirstPoint)
	{
		//绘制提示框
   		if (m_gameControl.m_graph.m_Vertices[nRow * 12 + nCol] != BLANK)
		{
            if ((nRow>0&&nRow<MAX_ROW-1) && (nCol>0 && nCol<MAX_COL-1) )
            {
			 DrawTipFrame(nRow,nCol);
		     m_gameControl.SetFirstPoint(nRow,nCol);
            }			
		}
	}
	else
	{
		if (m_gameControl.m_graph.m_Vertices[nRow * MAX_ROW+ nCol] != BLANK)
		{
		   if ((nRow>0&&nRow<MAX_ROW-1) && (nCol>0 && nCol<MAX_COL-1) )
		{	DrawTipFrame(nRow,nCol);
	     	m_gameControl.SetSecPoint(nRow,nCol);
		  }
		//获取顶点路径
		Vertex avPath[MAX_VERTAX_NUM] = {m_gameControl.m_ptSelFirst,m_gameControl.m_ptSelSec};
		//判断是否为同一图片
		int nVertex;
		if (m_gameControl.Link(avPath,nVertex))
		{
//-----------------现在nVertex已经等于144+--------------------
			for (int i = 0;i< nVertex-1 ;i++)
			{
				DrawTipLine(avPath[i],avPath[i+1]);
			}
/***************************************************			
			if (nVertex == 2)
		   {
               DrawTipLine(avPath[0],avPath[1]);	
		   }
		   else if (nVertex == 3)
		   {
			   DrawTipLine(avPath[0],avPath[2]);
			   DrawTipLine(avPath[2],avPath[1]);
		   }
		   else if(nVertex == 4)
		   {
			   DrawTipLine(avPath[0],avPath[2]);
			   DrawTipLine(avPath[2],avPath[3]);
			   DrawTipLine(avPath[3],avPath[1]);
		   }
************************************************/	
     	//更新
	     	UpdateMap();
		}
		Sleep (200);
		InvalidateRect(m_rtGameRect,FALSE);
		//判断是否结束了
		JudgeWin();
		}
	}
     m_bFirstPoint = !m_bFirstPoint;  

}


void CGameDlg_Relax::DrawTipFrame(int nRow, int nCol)
{
	CClientDC dc(this);
//	CBrush brush(RGB(0,240,255));
	CRect rtTipFrame;
	rtTipFrame.left = m_ptGameTop.x + nCol * m_sizeElem.cx;
	rtTipFrame.top = m_ptGameTop.y +nRow * m_sizeElem.cy;
	rtTipFrame.right = rtTipFrame.left + m_sizeElem.cx;
	rtTipFrame.bottom = rtTipFrame.top +  m_sizeElem.cy;
	dc.FrameRect(rtTipFrame,&brush);
}
void CGameDlg_Relax::DrawTipLine(Vertex v1,Vertex v2)
{
	//获取DC
	CClientDC dc(this);
	
	// 设置画笔
//    CPen penLine(PS_SOLID,2,RGB(0,255,0));

	//将画笔选入DC
	CPen *pOldPen = dc.SelectObject(&penLine);

	//绘制连接线
	dc.MoveTo(m_ptGameTop.x + v1.col * m_sizeElem.cx + m_sizeElem.cx/2 ,m_ptGameTop.y + v1.row * m_sizeElem.cy + m_sizeElem.cy/2);
	dc.LineTo(m_ptGameTop.x + v2.col * m_sizeElem.cx + m_sizeElem.cx/2 ,m_ptGameTop.y +v2.row * m_sizeElem.cy + m_sizeElem.cy/2);
	dc.SelectObject(pOldPen);
}



void CGameDlg_Relax::OnClickedBtnPrompt()
{
	Vertex avPath[MAX_VERTAX_NUM];
	int nVexNum;
	
	//查找联通路径
     if(m_gameControl.Help(avPath,nVexNum))
	 {
	 //如果能够联通，绘制提示框和连线并更新游戏地图
	    DrawTipFrame(avPath[0].row,avPath[0].col);
		DrawTipFrame(avPath[nVexNum-1].row,avPath[nVexNum-1].col);
		for (int i = 0; i< nVexNum-1 ; i++)
	   {
		   DrawTipLine(avPath[i],avPath[i+1]);
	   }
		UpdateMap();		
	   //为了使第二个提示框能够看到，暂停200ms，再刷新界面
		Sleep (300);
		InvalidateRect(m_rtGameRect,FALSE);
	 }
}


void CGameDlg_Relax::OnClickedBtnReset()
{
	
	if (m_bPlaying == false)
	{
		return;
	}
	//重排
	m_gameControl.Reset();

	//更新地图
	UpdateMap();

	//重绘界面
	InvalidateRect(m_rtGameRect,FALSE);
}


void CGameDlg_Relax::OnTimer(UINT_PTR nIDEvent)
{
	//当 mbPlaying = ture mbPause = flase 时，才计时
	if (nIDEvent == PLAY_TIMER_ID && m_bPlaying &&!m_bPause)
	{	
		JudgeWin();
		int TestNum = m_GameProgress.GetPos(); 
		CString str;
		str.Format(_T("%d"),TestNum);
		GetDlgItem(IDC_RELAX_STATIC)->SetWindowText(_T("您已经用了 ")+str+_T(" 秒"));
		
		CRect rtlbl;
		GetDlgItem(IDC_RELAX_STATIC)->GetWindowRect(&rtlbl);
		ScreenToClient(&rtlbl);
		InvalidateRect(&rtlbl);
		UpdateWindow();
		//游戏时间加一秒	
		m_GameProgress.StepIt();
		
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CGameDlg_Relax::JudgeWin(void)
{
	BOOL  bGameStatues  = m_gameControl.IsWin(1);

	if (bGameStatues == GAME_PLAY)
	{
		return;
	}
	else
	{
		//将游戏标识改为false
		m_bPlaying = false;
		//提示获胜
		CString str;
		this->GetWindowTextW(str);
		if (bGameStatues == GAME_SUCCESS)
		{
			MessageBox(_T("恭喜您获胜了\n 您可以开始新游戏了"),str);
		}
		//还原开始游戏按钮
		this->GetDlgItem(IDC_RELAX_BUTTON1)->EnableWindow(true);
	}
}


void CGameDlg_Relax::OnClickedBtnStop()
{
	if (!m_bPlaying)
	{
		return;
	}
	if (m_bPause == false)
	{
		this->GetDlgItem(IDC_RELAX_BUTTON2)->SetWindowTextW(_T("恢复游戏"));
		m_DCMem.BitBlt(90,90,400,400,&m_dcPause,0,0,SRCCOPY);
		InvalidateRect(m_rtGameRect,FALSE);
		this->GetDlgItem(IDC_RELAX_BUTTON3)->EnableWindow(FALSE);
		this->GetDlgItem(IDC_RELAX_BUTTON4)->EnableWindow(FALSE);
	}
	else if (m_bPause)
	{
		this->GetDlgItem(IDC_RELAX_BUTTON2)->SetWindowTextW(_T("暂停游戏"));
		UpdateMap();
		InvalidateRect(m_rtGameRect,FALSE);
		this->GetDlgItem(IDC_RELAX_BUTTON3)->EnableWindow(true);
		this->GetDlgItem(IDC_RELAX_BUTTON4)->EnableWindow(true);
	}
	m_bPause = !m_bPause;
}


BOOL CGameDlg_Relax::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类 
	if(pMsg->message==WM_MOUSEMOVE)
	m_Mytip.RelayEvent(pMsg);
	return CDialog::PreTranslateMessage(pMsg);
}

void CGameDlg_Relax::OnClickedButtonHelp()
{
	MessageBox(_T("两张一模一样的图片才有可能消除\n规则如下:（前提是选中两张相同图片）\n①可以是紧邻的\n②直线中间没有其他图片阻挡的\n③直线拐弯1次，有一个拐点的\n④直线拐弯2次，有两个拐点的\n小tips:\n本模式为休闲模式，有无数次使用提示的机会\n快来尽情放松吧！\n将图片全部消除 即为游戏成功!\n\t最后祝您游戏愉快"),_T("帮助"));
}



HBRUSH CGameDlg_Relax::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (nCtlColor == CTLCOLOR_STATIC)
     {
		 pDC->SetBkMode(TRANSPARENT);
		 return (HBRUSH)::GetStockObject(NULL_BRUSH);
     }
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

void CGameDlg_Relax::OnBnClickedRelaxButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	CSetDlg slg;
	slg.DoModal();
	if (slg.PopFrameNum() == 0)
	{
		brush.DeleteObject();
		brush.CreateSolidBrush(RGB(255,0,0));
	}
	if (slg.PopFrameNum() == 1)
	{
		brush.DeleteObject();
		brush.CreateSolidBrush(RGB(0,0,255));
	}
	if (slg.PopFrameNum() == 2)
	{
		brush.DeleteObject();
		brush.CreateSolidBrush(RGB(0,255,0));
	}
	if (slg.PopFrameNum() == 3)
	{
		brush.DeleteObject();
		brush.CreateSolidBrush(RGB(255,0,255));
	}
	if (slg.PopFrameNum() == 4)
	{
		brush.DeleteObject();
		brush.CreateSolidBrush(RGB(0,255,255));
	}
	if (slg.PopFrameNum() == 5)
	{
		brush.DeleteObject();
		brush.CreateSolidBrush(RGB(255,255,255));
	}
	if (slg.PopFrameNum() == 6)
	{
		brush.DeleteObject();
		brush.CreateSolidBrush(RGB(0,0,0));
	}
	//-----------------------------------------------------------
	if (slg.PopLineNum() == 0)
	{
		penLine.DeleteObject();
		penLine.CreatePen(PS_SOLID,2,RGB(255,0,0));
	}
	if (slg.PopLineNum() == 1)
	{
		penLine.DeleteObject();
		penLine.CreatePen(PS_SOLID,2,RGB(0,0,255));
	}
	if (slg.PopLineNum() == 2)
	{
		penLine.DeleteObject();
		penLine.CreatePen(PS_SOLID,2,RGB(0,255,0));
	}
	if (slg.PopLineNum() == 3)
	{
		penLine.DeleteObject();
		penLine.CreatePen(PS_SOLID,2,RGB(255,0,255));
	}
	if (slg.PopLineNum() == 4)
	{
		penLine.DeleteObject();
		penLine.CreatePen(PS_SOLID,2,RGB(0,255,255));
	}
	if (slg.PopLineNum() == 5)
	{
		penLine.DeleteObject();
		penLine.CreatePen(PS_SOLID,2,RGB(255,255,255));
	}
	if (slg.PopLineNum() == 6)
	{
		penLine.DeleteObject();
		penLine.CreatePen(PS_SOLID,2,RGB(0,0,0));
	}
}
