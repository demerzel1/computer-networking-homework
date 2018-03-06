// CSocket.cpp : 实现文件
//

#include "stdafx.h"
#include "tc.h"
#include "CSocket.h"
#include "tcDlg.h"

// CCSocket

IMPLEMENT_DYNAMIC(CCSocket, CSocket)

CCSocket::CCSocket(CtcDlg* pDlg)
{
	m_pDlg = pDlg;
}

CCSocket::~CCSocket()
{
	m_pDlg = NULL;
}


// CCSocket 成员函数


void CCSocket::OnReceive(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类

	CSocket::OnReceive(nErrorCode);
	if (nErrorCode == 0) m_pDlg->OnReceive();
}
