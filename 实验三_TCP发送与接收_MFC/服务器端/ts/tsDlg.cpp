
// tsDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ts.h"
#include "tsDlg.h"
#include "afxdialogex.h"
#include "Msg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CtsDlg 对话框



CtsDlg::CtsDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TS_DIALOG, pParent)
	, m_nPort(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_pLSocket = NULL;
}

void CtsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_NUM, m_staNum);
	DDX_Text(pDX, IDC_EDIT_PORT, m_nPort);
	DDX_Control(pDX, IDC_BUTTON_LISTEN, m_btnListen);
	DDX_Control(pDX, IDOK, m_btnClose);
	DDX_Control(pDX, IDC_LIST_MSG, m_listMsg);
}

BEGIN_MESSAGE_MAP(CtsDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CtsDlg::OnClose)
	ON_BN_CLICKED(IDC_BUTTON_LISTEN, &CtsDlg::OnButtonListen)
END_MESSAGE_MAP()


// CtsDlg 消息处理程序

BOOL CtsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	m_nPort = 23333;
	UpdateData(FALSE);
	GetDlgItem(IDOK)->EnableWindow(FALSE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CtsDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CtsDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CtsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CtsDlg::OnClose()
{
	// TODO: 在此添加控件通知处理程序代码
	CMsg  msg;
	msg.m_strText = "服务器终止服务!";
	//
	delete m_pLSocket;
	m_pLSocket = NULL;
	int cnt = 0;
	while (!m_connList.IsEmpty())
	{
		cnt++;
		CCSocket* pSocket
			= (CCSocket*)m_connList.RemoveHead();
		pSocket->SendMessage(&msg);
		delete pSocket;
	}
	while (m_listMsg.GetCount() != 0)
		m_listMsg.DeleteString(0);
	GetDlgItem(IDC_EDIT_PORT)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_LISTEN)->EnableWindow(TRUE);
	GetDlgItem(IDOK)->EnableWindow(FALSE);
}


void CtsDlg::OnButtonListen()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);   
	m_pLSocket = new CLSocket(this);
	if (!m_pLSocket->Create(m_nPort))
	{
		delete m_pLSocket;
		m_pLSocket = NULL;
		AfxMessageBox(_T("创建监听套接字错误"));
		return;
	}
	if (!m_pLSocket->Listen())
	{
		delete m_pLSocket;
		m_pLSocket = NULL;
		AfxMessageBox(_T("启动监听错误"));
		return;
	}
	GetDlgItem(IDC_EDIT_PORT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_LISTEN)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(TRUE);
}


void CtsDlg::OnAccept()
{
	CCSocket* pSocket = new CCSocket(this);
	if (m_pLSocket->Accept(*pSocket)) 
	{
		pSocket->Initialize();
		m_connList.AddTail(pSocket);
		CString strTemp;
		strTemp.Format(_T("在线人数：%d"), m_connList.GetCount());
		m_staNum.SetWindowText(strTemp);
	}
	else delete pSocket;
}


void CtsDlg::OnReceive(CCSocket* pSocket)
{
	static CMsg  msg;
	do {
		pSocket->ReceiveMessage(&msg);
		m_listMsg.AddString(msg.m_strText);
		backClients(&msg);
		if (msg.m_bClose)
		{
			pSocket->Close();
			POSITION pos, temp;
			for (pos = m_connList.GetHeadPosition(); pos != NULL;)
			{
				temp = pos;
				CCSocket* pSock = (CCSocket*)m_connList.GetNext(pos);
				if (pSock == pSocket)
				{
					m_connList.RemoveAt(temp);
					CString strTemp;
					strTemp.Format(_T("在线人数：%d"), m_connList.GetCount());
					m_staNum.SetWindowText(strTemp);
					break;
				}
			}
			delete pSocket;
			break;
		}
	} while (!pSocket->m_pArchiveIn->IsBufferEmpty());
}


void CtsDlg::backClients(CMsg* pMsg)
{
	for (POSITION pos = m_connList.GetHeadPosition(); pos != NULL;)
	{
		CCSocket* pSocket
			= (CCSocket*)m_connList.GetNext(pos);
		pSocket->SendMessage(pMsg);
	}
}
