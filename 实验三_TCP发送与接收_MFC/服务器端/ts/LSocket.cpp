// LSocket.cpp : ʵ���ļ�
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


// CLSocket ��Ա����


void CLSocket::OnAccept(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���

	CSocket::OnAccept(nErrorCode);
	m_pDlg->OnAccept();
}
IMPLEMENT_DYNAMIC(CLSocket, CSocket)