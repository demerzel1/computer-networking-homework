
// tcDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include  "CSocket.h"

// CtcDlg �Ի���
class CtcDlg : public CDialogEx
{
// ����
public:
	CtcDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TC_DIALOG };
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
	CString m_strCName;
	CString m_strSName;
	UINT m_nPort;
	CString m_strMsg;
	CButton m_btnConn;
	CButton m_Send;
	CButton m_btnClose;
	CListBox m_listMsg;
	afx_msg void OnSend();
	afx_msg void OnButtonConn();
	afx_msg void OnButtonClose();
	afx_msg void OnDestroy();
	CCSocket* m_pSocket;
	CSocketFile* m_pFile;
	CArchive* m_pArchiveIn;
	CArchive* m_pArchiveOut;
	void OnReceive();
	void ReceiveMsg();
	void SendMsg(CString& strText, bool st);
};
