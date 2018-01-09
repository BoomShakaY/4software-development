// GameDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LLK.h"
#include "GameDlg.h"
#include "afxdialogex.h"
#include "resource.h"
#include "GameLogic.h"
#include "Global.h"
#include "SetDlg.h"
// CGameDlg �Ի���

IMPLEMENT_DYNAMIC(CGameDlg, CDialogEx)

CGameDlg::CGameDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGameDlg::IDD, pParent)
{
	//��Ϸ��ʼλ��
	m_ptGameTop.x = MAX_TOP;
	m_ptGameTop.y = MAX_LEFT;
	
//����Ԫ�ص�ͼƬ��С����
	m_sizeElem.cx = PIC_WIDTH;
	m_sizeElem.cy = PIC_HEIGHT;

	//��ʼ��������Ϸ����
	m_rtGameRect.top = MAX_TOP;
	m_rtGameRect.left = MAX_LEFT;
	m_rtGameRect.right = m_rtGameRect.left +PIC_WIDTH * MAX_ROW;
	m_rtGameRect.bottom = m_rtGameRect.top + PIC_HEIGHT * MAX_COL;

	//��ʼ��ı�־
	m_bFirstPoint =true;
    m_bPlaying = false;
	m_bPause = false;
	brush.CreateSolidBrush(RGB(233,45,50));
	penLine.CreatePen(PS_SOLID,2,RGB(0,255,0));
	TipCount = 5;
}

CGameDlg::~CGameDlg()
{

}

void CGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GAME_TIME, m_GameProgress);
}

void CGameDlg::InitBackround(){

	//����Ӻ�׺����дȫ·����
    HANDLE bmp = ::LoadImage(NULL,_T("theme\\picture\\fruit_bg.bmp"),IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
	
	//��������DC
	CClientDC dc(this);
	m_BGround.CreateCompatibleDC(&dc);
	m_BGround.SelectObject(bmp);
	
	// ��λͼѡ��DC
	m_DCMem.CreateCompatibleDC(&dc);
	
	CBitmap bmpMian;
    bmpMian.CreateCompatibleBitmap(&dc,800,600);
	m_DCMem.SelectObject(&bmpMian);
	m_DCMem.BitBlt(0,0,800,600,&m_BGround,0,0,SRCCOPY);
}

BEGIN_MESSAGE_MAP(CGameDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON1, &CGameDlg::OnBnClickedBtnStart)
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON3, &CGameDlg::OnClickedBtnPrompt)
	ON_BN_CLICKED(IDC_BUTTON4, &CGameDlg::OnClickedBtnReset)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON2, &CGameDlg::OnClickedBtnStop)
	ON_BN_CLICKED(IDC_BUTTON6, &CGameDlg::OnClickedButtonHelp)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON5, &CGameDlg::OnClickedBtnSet)
END_MESSAGE_MAP()


// CGameDlg ��Ϣ�������


BOOL CGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//����ͼ��
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	InitBackround();
	InitElement();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CGameDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: �ڴ˴������Ϣ����������
	
	dc.BitBlt(0,0,800,600,&m_DCMem,0,0,SRCCOPY);

	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
}




void CGameDlg::InitElement(void)
{
	//------------------����bmpͼƬ------------------
	//����Ӻ�׺����дȫ·����
	HANDLE bmp = ::LoadImage(NULL,_T("theme\\picture\\Ball_element.bmp"),IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
	//��������DC

	CBitmap bmpMian;
	bmpMian.LoadBitmap(IDB_BITMAP_BASIC);

  //��ȡ��ǰ��ͼ��Դ
	CClientDC dc(this);
	m_dcElement.CreateCompatibleDC(&dc);
	// ��λͼѡ��DC
	//m_DCMem.SelectObject(bmpMian);
	m_dcElement.SelectObject(bmp);

	//��������BMP��Դ
	HANDLE hMask = ::LoadImageW(NULL,_T("theme\\picture\\Ball_element_r.bmp"),IMAGE_BITMAP,0,0,LR_LOADFROMFILE);

	//��������Ƶ�ڴ���ݵ��ڴ�DC
	m_dcMask.CreateCompatibleDC(&dc);

	//��λͼ��Դѡ��DC
	m_dcMask.SelectObject(hMask);

	//������ͣͼƬBMP��Դ
	HANDLE Pau = ::LoadImage(NULL,_T("theme\\picture\\pause.bmp"),IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
	m_dcPause.CreateCompatibleDC(&dc);
	m_dcPause.SelectObject(Pau);


	m_Mytip.Create(this);
	m_Mytip.SetDelayTime(100); //�����ӳ�
	m_Mytip.SetTipTextColor( RGB(0,0,255) ); //������ʾ�ı�����ɫ
	m_Mytip.SetTipBkColor( RGB(255,255,255)); //������ʾ��ı�����ɫ
	m_Mytip.Activate(TRUE); //�����Ƿ�������ʾ
}
void CGameDlg::OnBnClickedBtnStart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//��ʼ����Ϸ��ͼ
	m_gameControl.StartGame();
	
	
    //���µ�ͼ
	UpdateMap();
	//������Ϸ���ڽ���
	m_bPlaying = true;
	//���Ƶ����ʼ��Ϸ
	GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
	//��ʼ��������
	m_GameProgress.SetRange(0,60*5);  //���÷�Χ
	m_GameProgress.SetStep(-1);         //��ʼ����ֵ
	m_GameProgress.SetPos(60*5-1);        //���ó�ʼֵ

	//������ʱ��
	this->SetTimer(PLAY_TIMER_ID,1000,NULL);
	
	//���Ƶ�ǰ����
// 	DrawGameTime();  //ֱ������Ϣ��Ӧ��д��

	GetDlgItem(IDC_GAME_TIME)->ShowWindow(SW_NORMAL);
	GetDlgItem(IDC_STATIC)->ShowWindow(SW_NORMAL);

	m_Mytip.AddTool( GetDlgItem(IDC_BUTTON3), _T("�㻹��5��ʹ����ʾ�Ļ���"));
	this->GetDlgItem(IDC_BUTTON3)->SetWindowTextW(_T("��ʾ(5)"));
	//ˢ��
	InvalidateRect(m_rtGameRect,FALSE);
}


void CGameDlg::UpdateMap(void)
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
			//���Ƶ���ͼƬ
			int info = m_gameControl .GetElement(i,j);

			//������������򣬱߱�����ͼ������Ϊ1
			m_DCMem.BitBlt(nLeft + j * nElenW , nTop + i * nElenW , nElenW , nElemH , & m_dcMask , 0 ,info * nElemH,SRCPAINT);
			
			//��Ԫ��ͼƬ���� �߱�����ͼ������ΪԪ��ͼƬ
			m_DCMem.BitBlt(nLeft + j * nElenW , nTop + i * nElenW , nElenW , nElemH , & m_dcElement ,0 , info * nElemH,SRCAND);

		}
	}
}


void CGameDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
	// �ж��Ƿ��ǵ�һ����
	if (m_bFirstPoint)
	{
		//������ʾ��
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
		//��ȡ����·��
		Vertex avPath[MAX_VERTAX_NUM] = {m_gameControl.m_ptSelFirst,m_gameControl.m_ptSelSec};
		//�ж��Ƿ�ΪͬһͼƬ
		int nVertex;
		if (m_gameControl.Link(avPath,nVertex))
		{
//-----------------����nVertex�Ѿ�����144+--------------------
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
     	//����
	     	UpdateMap();
		}
		Sleep (200);
		InvalidateRect(m_rtGameRect,FALSE);
		//�ж��Ƿ������
		JudgeWin();
		}
	}
     m_bFirstPoint = !m_bFirstPoint;  

}


void CGameDlg::DrawTipFrame(int nRow, int nCol)
{
	CClientDC dc(this);
//	CBrush brush(RGB(233,45,50));
	CRect rtTipFrame;
	rtTipFrame.left = m_ptGameTop.x + nCol * m_sizeElem.cx;
	rtTipFrame.top = m_ptGameTop.y +nRow * m_sizeElem.cy;
	rtTipFrame.right = rtTipFrame.left + m_sizeElem.cx;
	rtTipFrame.bottom = rtTipFrame.top +  m_sizeElem.cy;
	dc.FrameRect(rtTipFrame,&brush);
}
void CGameDlg::DrawTipLine(Vertex v1,Vertex v2)
{
	//��ȡDC
	CClientDC dc(this);
	
	// ���û���
 //   CPen penLine(PS_SOLID,2,RGB(0,255,0));

	//������ѡ��DC
	CPen *pOldPen = dc.SelectObject(&penLine);

	//����������
	dc.MoveTo(m_ptGameTop.x + v1.col * m_sizeElem.cx + m_sizeElem.cx/2 ,m_ptGameTop.y + v1.row * m_sizeElem.cy + m_sizeElem.cy/2);
	dc.LineTo(m_ptGameTop.x + v2.col * m_sizeElem.cx + m_sizeElem.cx/2 ,m_ptGameTop.y +v2.row * m_sizeElem.cy + m_sizeElem.cy/2);
	dc.SelectObject(pOldPen);
}



void CGameDlg::OnClickedBtnPrompt()
{
	Vertex avPath[MAX_VERTAX_NUM];
	int nVexNum;
	//��ʾ����С��0 ��ֱ�ӷ���
	if (TipCount<=0)
	{
		MessageBox(_T("���Ѿ�û����ʾ�����ˣ�"),_T("��Ǹ"));
		return;
	}
	
	//������ͨ·��
     if(m_gameControl.Help(avPath,nVexNum))
	 {
	 //����ܹ���ͨ��������ʾ������߲�������Ϸ��ͼ
	    DrawTipFrame(avPath[0].row,avPath[0].col);
		DrawTipFrame(avPath[nVexNum-1].row,avPath[nVexNum-1].col);
		for (int i = 0; i< nVexNum-1 ; i++)
	   {
		   DrawTipLine(avPath[i],avPath[i+1]);
	   }
		UpdateMap();	
		
       //�������ֺ���ʾ��	
		TipCount --;
	    CString str;
	    str.Format(_T("%d"),TipCount);
	    m_Mytip.AddTool( GetDlgItem(IDC_BUTTON3), _T("�㻹��"+str+_T("��ʹ����ʾ�Ļ���")));
	    this->GetDlgItem(IDC_BUTTON3)->SetWindowTextW(_T("��ʾ(")+str+_T(")"));
	   //Ϊ��ʹ�ڶ�����ʾ���ܹ���������ͣ200ms����ˢ�½���
		Sleep (300);
		InvalidateRect(m_rtGameRect,FALSE);
	 }
}


void CGameDlg::OnClickedBtnReset()
{
	
	if (m_bPlaying == false)
	{
		return;
	}
	//����
	m_gameControl.Reset();

	//���µ�ͼ
	UpdateMap();

	//�ػ����
	InvalidateRect(m_rtGameRect,FALSE);
}


void CGameDlg::OnTimer(UINT_PTR nIDEvent)
{
	//�� mbPlaying = ture mbPause = flase ʱ���ż�ʱ
	if (nIDEvent == PLAY_TIMER_ID && m_bPlaying &&!m_bPause)
	{	
		JudgeWin();
		int TestNum = m_GameProgress.GetPos(); 
		CString str;
		str.Format(_T("%d"),TestNum);
		GetDlgItem(IDC_STATIC)->SetWindowText(str);
		
		//ˢ�£�������Ӱ����
		CRect rtlbl;
		GetDlgItem(IDC_STATIC)->GetWindowRect(&rtlbl);
		ScreenToClient(&rtlbl);
		InvalidateRect(&rtlbl);
		UpdateWindow();
		//��Ϸʱ���һ��	
		m_GameProgress.StepIt();
		//�ж���Ϸ�Ƿ����
		
	}

	CDialogEx::OnTimer(nIDEvent);
}


void CGameDlg::JudgeWin(void)
{
	BOOL  bGameStatues  = m_gameControl.IsWin(m_GameProgress.GetPos());

	if (bGameStatues == GAME_PLAY)
	{
		return;
	}
	else
	{
		//����Ϸ��ʶ��Ϊfalse
		m_bPlaying = false;
		KillTimer(PLAY_TIMER_ID);
		//��ʾ��ʤ
		CString str;
		this->GetWindowTextW(str);
		if (bGameStatues == GAME_SUCCESS)
		{
			MessageBox(_T("��ϲ����ʤ��\n �����Կ�ʼ����Ϸ��"),str);
		}
		else if ( bGameStatues == GAME_LOSE)
		{
			MessageBox(_T("��ѽʱ�䵽��\n �����٣�����һ��"),str);
		}
		//��ԭ��ʼ��Ϸ��ť
		this->GetDlgItem(IDC_BUTTON1)->EnableWindow(true);
	}
}


void CGameDlg::OnClickedBtnStop()
{
	if (!m_bPlaying)
	{
		return;
	}
	if (m_bPause == false)
	{
		this->GetDlgItem(IDC_BUTTON2)->SetWindowTextW(_T("�ָ���Ϸ"));
		m_DCMem.BitBlt(90,90,400,400,&m_dcPause,0,0,SRCCOPY);
		InvalidateRect(m_rtGameRect,FALSE);
		this->GetDlgItem(IDC_BUTTON3)->EnableWindow(FALSE);
		this->GetDlgItem(IDC_BUTTON4)->EnableWindow(FALSE);
	}
	else if (m_bPause)
	{
		this->GetDlgItem(IDC_BUTTON2)->SetWindowTextW(_T("��ͣ��Ϸ"));
		UpdateMap();
		InvalidateRect(m_rtGameRect,FALSE);
		this->GetDlgItem(IDC_BUTTON3)->EnableWindow(true);
		this->GetDlgItem(IDC_BUTTON4)->EnableWindow(true);
	}
	m_bPause = !m_bPause;
}


BOOL CGameDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û��� 
	if(pMsg->message==WM_MOUSEMOVE)
	m_Mytip.RelayEvent(pMsg);
	return CDialog::PreTranslateMessage(pMsg);
}

void CGameDlg::OnClickedButtonHelp()
{
	MessageBox(_T("����һģһ����ͼƬ���п�������\n��������:��ǰ����ѡ��������ͬͼƬ��\n�ٿ����ǽ��ڵ�\n��ֱ���м�û������ͼƬ�赲��\n��ֱ�߹���1�Σ���һ���յ��\n��ֱ�߹���2�Σ��������յ��\nСtips:\nÿ����һ��ʼ��5��ʹ����ʾ�Ļ���\n��300���ڽ�ͼƬȫ������ ��Ϊ��Ϸ�ɹ�!\n\t���ף����Ϸ���"),_T("����"));
}


HBRUSH CGameDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH)::GetStockObject(NULL_BRUSH);
	}
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}


void CGameDlg::OnClickedBtnSet()
{
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
