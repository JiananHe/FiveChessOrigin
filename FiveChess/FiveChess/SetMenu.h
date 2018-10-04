#pragma once


class setMenu : public CDialog
{
	DECLARE_DYNAMIC(setMenu)

public:
	setMenu(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~setMenu();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SET_MENU_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
