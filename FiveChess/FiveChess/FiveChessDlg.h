// FiveChessDlg.h : header file
//

#if !defined(AFX_FIVECHESSDLG_H__E2C58E22_5D6D_4059_A0AF_CE86F297AF00__INCLUDED_)
#define AFX_FIVECHESSDLG_H__E2C58E22_5D6D_4059_A0AF_CE86F297AF00__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CFiveChessDlg dialog

#include "SetupDlg.h"
#include "Connect.h"
#include "ConnectData.h"
#include "Board.h"
#include <mmsystem.h>
#include "afxwin.h"

class CFiveChessDlg : public CDialog
{
	// Construction
public:
	void NewGameStart(BOOL isHost);
	void SetMenuState(BOOL bEnable, int m_bWait);		//设置菜单状态
	void Accept();							//服务器端口申请连接成功时调用
	void Connect();							//客户机申请连接成功调用
	void Send(MSGSTRUCT * pmsg);			//发送数据
	void Restart();							//重新开始游戏

	CFiveChessDlg(CWnd* pParent = NULL);	// standard constructor

											// Dialog Data
											//{{AFX_DATA(CFiveChessDlg)
	enum { IDD = IDD_FIVECHESS_DIALOG };
	CBoard    m_board;			//主棋盘对象
								//}}AFX_DATA

								// ClassWizard generated virtual function overrides
								//{{AFX_VIRTUAL(CFiveChessDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
														//}}AFX_VIRTUAL

public:
	CConnect m_conncet;			//监听套接字
	CConnect m_sock;			//使用套接字
	BOOL m_bIsConnect;			//连接标志
	BOOL m_isHost;				//主机标志

	CFont font1;				//字体类型
	CFont font2;
	CFont font3;

	int whoTurn;				// 1为黑棋，2为白棋，3显示提示信息
	CEdit m_Time;				//倒计时编辑框绑定变量
	CString m_history;			//历史记录编辑框绑定变量

	CEdit m_show;
	CString strName;			//用户名
	int m_TimeCount;			//倒计时计数变量

								// Implementation
protected:
	HICON m_hIcon;				//图标对象
	CMenu m_main_menu;			//主菜单对象
	CSetupDlg m_setup_dlg;		//设置对话框对象
	const char * pszFileName = "";	//历史记录文件名
	CStdioFile myFile;			//历史记录文件对象
	CFileException fileException;

	CString m_win;				//用于暂时存储历史数据
	CString m_lost;
	CString m_draw;

	// Generated message map functions
	//{{AFX_MSG(CFiveChessDlg)
	//virtual BOOL OnInitDialog();

	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnUpdateNewGameMenu(CCmdUI* pCmdUI);
	afx_msg void OnUpdateExitGameMenu(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDrawGameMenu(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnSetMenu();
	afx_msg void OnBackMenu();
	afx_msg void OnBnClickedButtonSend();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	void UpdateShow(CString str);	//输出消息到聊天记录框
	void SendWord(CString str);		//发送消息

	void showhistory();				//显示历史记录
	void showhistory(int, int, int);
	void newhistory(int);			//主机标志
	void showwindow(BOOL);			//显示历史记录窗口
	void RefreshControl(UINT);		//刷新控件

	void CFiveChessDlg::newshowedit();//刷新聊天消息显示框

	void initSetTimer();			//初始化倒计时
	void Invali();					//刷新整个窗口
	afx_msg void OnClose();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FIVECHESSDLG_H__E2C58E22_5D6D_4059_A0AF_CE86F297AF00__INCLUDED_)
