
// tsDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "CSocket.h"
#include "LSocket.h"

// CtsDlg 对话框
class CtsDlg : public CDialogEx
{
// 构造
public:
	CtsDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
