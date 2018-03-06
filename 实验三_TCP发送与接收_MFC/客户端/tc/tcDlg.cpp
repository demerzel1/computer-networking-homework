
// tcDlg.cpp : ʵ���ļ�
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


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CtcDlg �Ի���



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


// CtcDlg ��Ϣ�������

BOOL CtcDlg::OnInitDialog()
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_strCName = "�ͻ� 1";
	m_nPort = 23333;
	m_strSName = _T("localhost");
	GetDlgItem(IDC_EDIT_MSG)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CLOSE)->EnableWindow(FALSE);
	UpdateData(FALSE);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CtcDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CtcDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




void CtcDlg::OnSend()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);       //ȡ���û��������Ϣ
	if (!m_strMsg.IsEmpty())
	{
		CTime time;
		time = CTime::GetCurrentTime();
		CString strTime = time.Format(_T("%Y-%m-%d %H:%M:%S  "));
		this->SendMsg(strTime+m_strCName + ":" + m_strMsg, FALSE);
		//m_listMsg.AddString(m_strMsg);
		m_strMsg = _T("");
		UpdateData(FALSE);  //�����û����棬���û��������Ϣɾ����
	}
}


void CtcDlg::OnButtonConn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	m_pSocket = new CCSocket(this);
	if (!m_pSocket->Create())
	{
		delete m_pSocket;
		m_pSocket = NULL;
		AfxMessageBox(_T("�׽��ִ�������"));
		return;
	}
	if (!m_pSocket->Connect(m_strSName, m_nPort))
	{
		delete m_pSocket;
		m_pSocket = NULL;
		AfxMessageBox(_T("�޷����ӷ���������"));
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
	strTemp =strTime+ m_strCName + _T(":TCP���ӳɹ�");
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CString strTemp;
	strTemp = m_strCName + _T(":�Ͽ�TCP����");
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

	//����б��
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

	// TODO: �ڴ˴������Ϣ����������
	if ((m_pSocket != NULL) && (m_pFile != NULL) && (m_pArchiveOut != NULL))
	{
		
		CMsg msg;
		CString strTemp;
		strTemp = ":�Ͽ�����";
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
		strTemp = "�������������ӣ����ӹرգ�";
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
