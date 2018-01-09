
// LLKDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LLK.h"
#include "LLKDlg.h"
#include "afxdialogex.h"
#include "resource.h"  
#include "GameDlg.h"
#include "GameDlg_Relax.h"
#include "GameDlg_Level.h"
#include "MainSetDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CLLKDlg �Ի���




CLLKDlg::CLLKDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLLKDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLLKDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CLLKDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_BASIC, &CLLKDlg::OnClickedButtonBasic)
	ON_BN_CLICKED(IDC_BUTTON_RELAX, &CLLKDlg::OnClickedButtonRelax)
	ON_BN_CLICKED(IDC_BUTTON_LEVEL, &CLLKDlg::OnClickedButtonLevel)
	ON_BN_CLICKED(IDC_BUTTON_HELP, &CLLKDlg::OnClickedBtnHelp)
	ON_BN_CLICKED(IDC_BUTTON_SETTING, &CLLKDlg::OnBnClickedButtonSetting)
END_MESSAGE_MAP()


// CLLKDlg ��Ϣ�������

BOOL CLLKDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	InitBackground();
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CLLKDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CLLKDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//����CPaint����
		CPaintDC dc(this);
		dc.BitBlt(0,0,800,600,&m_DCMem,0,0,SRCCOPY);

		CDialogEx::OnPaint();
	}

}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CLLKDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CLLKDlg::InitBackground(void){
	//����λͼ

	CBitmap bmpMian;
	bmpMian.LoadBitmap(IDB_MAIN_BG);


	//��������DC
	CClientDC dc(this);
	m_DCMem.CreateCompatibleDC(&dc);
	// ��λͼѡ��DC
	m_DCMem.SelectObject(bmpMian);

}

void CLLKDlg::OnClickedButtonBasic()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->ShowWindow(SW_HIDE);
	CGameDlg dlg;
	dlg.DoModal();
	this->ShowWindow(SW_SHOW);
}


void CLLKDlg::OnClickedButtonRelax()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->ShowWindow(SW_HIDE);
	CGameDlg_Relax dlgR;
	dlgR.DoModal();
	this->ShowWindow(SW_SHOW);
}


void CLLKDlg::OnClickedButtonLevel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
    this->ShowWindow(SW_HIDE);
	GameDlg_Level dlgR;
	dlgR.DoModal();
	this->ShowWindow(SW_SHOW);
}

void CLLKDlg::OnClickedBtnHelp()
{
	MessageBox(_T("��Ϸ��Ϊ����ģʽ:\n�ٻ���ģʽ:\n��ʱ�����ƣ�����ʾ����Ҫ��\n������ģʽ\n��ʱ�����ƣ�����ʾ����Ҫ��\n�۹ؿ�ģʽ\n���׵��ѣ��Ѷ��𽥼Ӵ���ʾ�����𽥼���\n"),_T("����"));
}


void CLLKDlg::OnBnClickedButtonSetting()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CMainSetDlg slg;
	slg.DoModal();
}
