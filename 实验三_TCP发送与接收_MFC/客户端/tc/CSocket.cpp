// CSocket.cpp : ʵ���ļ�
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


// CCSocket ��Ա����


void CCSocket::OnReceive(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���

	CSocket::OnReceive(nErrorCode);
	if (nErrorCode == 0) m_pDlg->OnReceive();
}
