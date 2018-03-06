// LSocket.cpp : 实现文件
//

#include "stdafx.h"
#include "ts.h"
#include "LSocket.h"
#include "tsDlg.h"



// CLSocket

CLSocket::CLSocket(CtsDlg* pDlg)
{
	m_pDlg = pDlg;
}

CLSocket::~CLSocket()
{
	m_pDlg = NULL;
}


// CLSocket 成员函数


void CLSocket::OnAccept(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类

	CSocket::OnAccept(nErrorCode);
	m_pDlg->OnAccept();
}
IMPLEMENT_DYNAMIC(CLSocket, CSocket)