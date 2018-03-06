// CSocket.cpp : 实现文件
//

#include "stdafx.h"
#include "ts.h"
#include "CSocket.h"
#include "tsDlg.h"
#include "Msg.h"

// CCSocket

CCSocket::CCSocket(CtsDlg* pDlg)
{
	m_pDlg = pDlg;
	m_pFile = NULL;
	m_pArchiveIn = NULL;
	m_pArchiveOut = NULL;
}

CCSocket::~CCSocket()
{
	m_pDlg = NULL;
	if (m_pArchiveOut != NULL) delete m_pArchiveOut;
	if (m_pArchiveIn != NULL) delete m_pArchiveIn;
	if (m_pFile != NULL) delete m_pFile;
}


// CCSocket 成员函数


void CCSocket::Initialize()
{
	m_pFile = new CSocketFile(this, TRUE);
	m_pArchiveIn = new CArchive(m_pFile, CArchive::load);
	m_pArchiveOut = new CArchive(m_pFile, CArchive::store);
}


void CCSocket::SendMessage(CMsg* pMsg)
{
	if (m_pArchiveOut != NULL)
	{
		pMsg->Serialize(*m_pArchiveOut);
		m_pArchiveOut->Flush();
	}
}


void CCSocket::ReceiveMessage(CMsg* pMsg)
{
	pMsg->Serialize(*m_pArchiveIn);
}


void CCSocket::OnReceive(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类

	CSocket::OnReceive(nErrorCode);
	m_pDlg->OnReceive(this);
}
IMPLEMENT_DYNAMIC(CCSocket, CSocket)