
// tsDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "CSocket.h"
#include "LSocket.h"

// CtsDlg �Ի���
class CtsDlg : public CDialogEx
{
// ����
public:
	CtsDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CStatic m_staNum;
	UINT m_nPort;
	CButton m_btnListen;
	CButton m_btnClose;
	CListBox m_listMsg;
	afx_msg void OnClose();
	afx_msg void OnButtonListen();
	CLSocket* m_pLSocket;
	CPtrList m_connList;
	void OnAccept();
	void OnReceive(CCSocket* pSocket);
	void backClients(CMsg* pMsg);
};
