#pragma once


class setMenu : public CDialog
{
	DECLARE_DYNAMIC(setMenu)

public:
	setMenu(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~setMenu();

	// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SET_MENU_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
