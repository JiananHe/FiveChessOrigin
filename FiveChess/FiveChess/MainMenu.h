#pragma once


// MainMenu �Ի���

class MainMenu : public CDialog
{
	DECLARE_DYNAMIC(MainMenu)

public:
	MainMenu(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~MainMenu();

	void SetRegion(CDC* pDC, UINT BackBitmapID, COLORREF TransColor);//���öԻ�����ʽ

																	 // �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAINMENU };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();		//�˻�ģʽ
	afx_msg void OnBnClickedButton2();		//����ģʽ
	afx_msg void OnBnClickedButton3();		//����
	afx_msg void OnBnClickedButton4();		//�˳���Ϸ
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	virtual BOOL OnInitDialog();
};
