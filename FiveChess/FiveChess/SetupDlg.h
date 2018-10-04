#if !defined(AFX_SETUPDLG_H__978DA95F_86F1_4C6B_BE9B_5EFD69DADACF__INCLUDED_)
#define AFX_SETUPDLG_H__978DA95F_86F1_4C6B_BE9B_5EFD69DADACF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetupDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetupDlg dialog
#include "stdafx.h"
#include "Resource.h"

class CSetupDlg : public CDialog
{
	// Construction
public:
	CSetupDlg(CWnd* pParent = NULL);   // standard constructor
	void SetRegion(CDC* pDC, UINT BackBitmapID, COLORREF TransColor);

	// Dialog Data
	//{{AFX_DATA(CSetupDlg)
	enum { IDD = IDD_SETUP_DLG };
	CIPAddressCtrl	m_ip_addr;
	UINT	m_net_port;
	//}}AFX_DATA

public:
	BOOL m_isHost;		//主机类型，TRUE:主机 FALSE:客户机
	CString m_strHostIP;//IP 地址

						// Overrides
						// ClassWizard generated virtual function overrides
						//{{AFX_VIRTUAL(CSetupDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
														//}}AFX_VIRTUAL

														// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSetupDlg)

	afx_msg void OnClientOption();//选择加入游戏
	afx_msg void OnHostOption();//选择创建游戏

	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	CString m_setname;//用户名
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETUPDLG_H__978DA95F_86F1_4C6B_BE9B_5EFD69DADACF__INCLUDED_)
