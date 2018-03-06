
// tcDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "tc.h"
#include "tcDlg.h"
#include "afxdialogex.h"
#include "CSocket.h"
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
public:
//	afx_msg void OnSend();
//	afx_msg void OnButtonConn();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_BN_CLICKED(IDOK, &CAboutDlg::OnSend)
//	ON_COMMAND(IDC_BUTTON_CONN, &CAboutDlg::OnButtonConn)
END_MESSAGE_MAP()


// CtcDlg 对话框



CtcDlg::CtcDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TC_DIALOG, pParent)
	, m_strCName(_T(""))
	, m_strSName(_T(""))
	, m_nPort(0)
	, m_strMsg(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CtcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CNAME, m_strCName);
	DDX_Text(pDX, IDC_EDIT_SNAME, m_strSName);
	DDX_Text(pDX, IDC_EDIT_PORT, m_nPort);
	DDX_Text(pDX, IDC_EDIT_MSG, m_strMsg);
	DDX_Control(pDX, IDC_BUTTON_CONN, m_btnConn);
	DDX_Control(pDX, IDOK, m_Send);
	DDX_Control(pDX, IDC_BUTTON_CLOSE, m_btnClose);
	DDX_Control(pDX, IDC_LIST_MSG, m_listMsg);
}

BEGIN_MESSAGE_MAP(CtcDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CtcDlg::OnSend)
	ON_BN_CLICKED(IDC_BUTTON_CONN, &CtcDlg::OnButtonConn)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CtcDlg::OnButtonClose)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CtcDlg 消息处理程序

BOOL CtcDlg::OnInitDialog()
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
	m_strCName = "客户 1";
	m_nPort = 23333;
	m_strSName = _T("localhost");
	GetDlgItem(IDC_EDIT_MSG)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CLOSE)->EnableWindow(FALSE);
	UpdateData(FALSE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CtcDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CtcDlg::OnPaint()
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
HCURSOR CtcDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




void CtcDlg::OnSend()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);       //取回用户输入的信息
	if (!m_strMsg.IsEmpty())
	{
		CTime time;
		time = CTime::GetCurrentTime();
		CString strTime = time.Format(_T("%Y-%m-%d %H:%M:%S  "));
		this->SendMsg(strTime+m_strCName + ":" + m_strMsg, FALSE);
		//m_listMsg.AddString(m_strMsg);
		m_strMsg = _T("");
		UpdateData(FALSE);  //更新用户界面，将用户输入的消息删除。
	}
}


void CtcDlg::OnButtonConn()
{
	// TODO: 在此添加控件通知处理程序代码

	m_pSocket = new CCSocket(this);
	if (!m_pSocket->Create())
	{
		delete m_pSocket;
		m_pSocket = NULL;
		AfxMessageBox(_T("套接字创建错误！"));
		return;
	}
	if (!m_pSocket->Connect(m_strSName, m_nPort))
	{
		delete m_pSocket;
		m_pSocket = NULL;
		AfxMessageBox(_T("无法连接服务器错误！"));
		return;
	}
	m_pFile = new CSocketFile(m_pSocket);
	m_pArchiveIn = new CArchive(m_pFile, CArchive::load);
	m_pArchiveOut = new CArchive(m_pFile, CArchive::store);
	UpdateData(TRUE);
	CString  strTemp;
	CTime time;
	time = CTime::GetCurrentTime();
	CString strTime = time.Format(_T("%Y-%m-%d %H:%M:%S  "));
	strTemp =strTime+ m_strCName + _T(":TCP连接成功");
	SendMsg(strTemp, FALSE);
	GetDlgItem(IDC_EDIT_MSG)->EnableWindow(TRUE);
	GetDlgItem(IDOK)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_CLOSE)->EnableWindow(TRUE);

	GetDlgItem(IDC_EDIT_CNAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_SNAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_PORT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CONN)->EnableWindow(FALSE);
}


void CtcDlg::OnButtonClose()
{
	// TODO: 在此添加控件通知处理程序代码

	CString strTemp;
	strTemp = m_strCName + _T(":断开TCP连接");
	SendMsg(strTemp, TRUE);

	delete m_pArchiveOut; 
	m_pArchiveOut = NULL;
	delete m_pArchiveIn;
	m_pArchiveIn = NULL;
	delete m_pFile;	    
	m_pFile = NULL;
	m_pSocket->Close();  
	delete m_pSocket;	
	m_pSocket = NULL;

	//清除列表框
	while (m_listMsg.GetCount() != 0)
		m_listMsg.DeleteString(0);
	GetDlgItem(IDC_EDIT_MSG)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CLOSE)->EnableWindow(FALSE);

	GetDlgItem(IDC_EDIT_CNAME)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_SNAME)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_PORT)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_CONN)->EnableWindow(TRUE);
}


void CtcDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	if ((m_pSocket != NULL) && (m_pFile != NULL) && (m_pArchiveOut != NULL))
	{
		
		CMsg msg;
		CString strTemp;
		strTemp = ":断开连接";
		msg.m_bClose = TRUE;
		msg.m_strBuf = m_strCName + strTemp;
		msg.Serialize(*m_pArchiveOut);
		m_pArchiveOut->Flush();
	}
	delete m_pArchiveOut;   
	m_pArchiveOut = NULL;
	delete m_pArchiveIn;	
	m_pArchiveIn = NULL;
	delete m_pFile;	     
	m_pFile = NULL;
	if (m_pSocket != NULL)
	{
		BYTE Buffer[50];
		m_pSocket->ShutDown();
		while (m_pSocket->Receive(Buffer, 50)>0);
	}
	delete m_pSocket;
	m_pSocket = NULL;
}


void CtcDlg::OnReceive()
{
	do
	{
		ReceiveMsg();   
		if (m_pSocket == NULL)  return;
	} while (!m_pArchiveIn->IsBufferEmpty());
}


void CtcDlg::ReceiveMsg()
{
	CMsg msg;
	TRY
	{
		msg.Serialize(*m_pArchiveIn);
	m_listMsg.AddString(msg.m_strBuf); 
	}
		CATCH(CFileException, e) 
	{
		CString strTemp;
		strTemp = "服务器重置连接！连接关闭！";
		m_listMsg.AddString(strTemp);
		msg.m_bClose = TRUE;
		m_pArchiveOut->Abort();
		delete m_pArchiveIn;
		m_pArchiveIn = NULL;
		delete m_pArchiveOut;
		m_pArchiveOut = NULL;
		delete m_pFile;
		m_pFile = NULL;
		delete m_pSocket;
		m_pSocket = NULL;
	}
	END_CATCH
}


void CtcDlg::SendMsg(CString& strText, bool st)
{
	if (m_pArchiveOut != NULL)
	{
		CMsg msg;  
		msg.m_strBuf = strText;
		msg.m_bClose = st;
		msg.Serialize(*m_pArchiveOut);
		m_pArchiveOut->Flush();
	}
}
