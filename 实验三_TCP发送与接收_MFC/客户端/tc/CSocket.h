#pragma once

// CCSocket ����Ŀ��

class CtcDlg;

class CCSocket : public CSocket
{
	DECLARE_DYNAMIC(CCSocket);
public:
	CCSocket(CtcDlg* pDlg);
	virtual ~CCSocket();
	CtcDlg* m_pDlg;
	virtual void OnReceive(int nErrorCode);
};


