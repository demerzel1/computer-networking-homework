// Msg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ts.h"
#include "Msg.h"


// CMsg

CMsg::CMsg()
{
	m_strText = _T("");
	m_bClose = FALSE;
}

CMsg::~CMsg()
{
}


// CMsg ��Ա����


void CMsg::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	// storing code
		ar << (WORD)m_bClose;
		ar << m_strText;
	}
	else
	{	// loading code
		WORD wd;
		ar >> wd;
		m_bClose = (BOOL)wd;
		ar >> m_strText;
	}
}

IMPLEMENT_DYNAMIC(CMsg, CObject)
