#pragma once

// CLSocket ÃüÁîÄ¿±ê

class CtsDlg;
class CLSocket : public CSocket
{
	DECLARE_DYNAMIC(CLSocket);
public:
	CLSocket(CtsDlg* pDlg);
	virtual ~CLSocket();
	CtsDlg* m_pDlg;	
protected:
	virtual void OnAccept(int nErrorCode);
};


