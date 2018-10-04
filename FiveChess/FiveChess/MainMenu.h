#pragma once


// MainMenu 对话框

class MainMenu : public CDialog
{
	DECLARE_DYNAMIC(MainMenu)

public:
	MainMenu(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~MainMenu();

	void SetRegion(CDC* pDC, UINT BackBitmapID, COLORREF TransColor);//设置对话框样式

																	 // 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAINMENU };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();		//人机模式
	afx_msg void OnBnClickedButton2();		//联机模式
	afx_msg void OnBnClickedButton3();		//设置
	afx_msg void OnBnClickedButton4();		//退出游戏
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	virtual BOOL OnInitDialog();
};
