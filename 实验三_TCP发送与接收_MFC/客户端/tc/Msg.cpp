// Msg.cpp : 实现文件
//

#include "stdafx.h"
#include "tc.h"
#include "Msg.h"


// CMsg

CMsg::CMsg()
{
	m_strBuf = _T("");
	m_bClose = FALSE;
}

CMsg::~CMsg()
{
}


// CMsg 成员函数


void CMsg::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << (WORD)m_bClose;
		ar << m_strBuf;
	}
	else
	{
		WORD wd;
		ar >> wd;
		m_bClose = (BOOL)wd;
		ar >> m_strBuf;
	}
}

IMPLEMENT_DYNAMIC(CMsg, CObject)