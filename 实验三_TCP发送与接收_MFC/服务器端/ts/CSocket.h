#pragma once

// CCSocket ÃüÁîÄ¿±ê

class  CtsDlg;
class  CMsg;


class CCSocket : public CSocket
{
	DECLARE_DYNAMIC(CCSocket);
public:
	CCSocket(CtsDlg* pDlg);
	virtual ~CCSocket();
	CtsDlg* m_pDlg;
	void Initialize();
	void SendMessage(CMsg* pMsg);
	void ReceiveMessage(CMsg* pMsg);
	CSocketFile* m_pFile;
	CArchive* m_pArchiveIn;
	CArchive* m_pArchiveOut;
protected:
	virtual void OnReceive(int nErrorCode);
};


