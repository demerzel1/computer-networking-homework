#pragma once

// CMsg ����Ŀ��

class CMsg : public CObject
{
	DECLARE_DYNCREATE(CMsg);
public:
	CMsg();
	virtual ~CMsg();
	virtual void Serialize(CArchive& ar);
	CString m_strText;
	BOOL m_bClose;
};


