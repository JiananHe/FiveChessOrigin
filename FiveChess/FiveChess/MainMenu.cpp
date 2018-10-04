// MainMenu.cpp : 实现文件
//

#include "stdafx.h"
#include "FiveChess.h"
#include "FiveChessDlg.h"
#include "MainMenu.h"
#include "afxdialogex.h"
#include "SetMenu.h"


// MainMenu 对话框

IMPLEMENT_DYNAMIC(MainMenu, CDialog)

MainMenu::MainMenu(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_MAINMENU, pParent)
{

}

MainMenu::~MainMenu()
{
}

void MainMenu::SetRegion(CDC * pDC, UINT BackBitmapID, COLORREF TransColor)
{
	CDC dcMem;
	if (!dcMem.CreateCompatibleDC(pDC))
	{
		MessageBox(_T("创建兼容DC失败！"));
	}

	CBitmap bitmap;
	if (!bitmap.LoadBitmap(BackBitmapID))
	{
		MessageBox(_T("加载位图失败！"));
	}

	if (!dcMem.SelectObject(&bitmap))
	{
		MessageBox(_T("选进设备描述表失败！"));
	}

	BITMAP bitmapinfo;
	bitmap.GetBitmap(&bitmapinfo);
	//把窗口设为图片的大小,去掉这个的话，那么程序分割会不正确  
	MoveWindow(0, 0, bitmapinfo.bmWidth, bitmapinfo.bmHeight, true);
	//整体区域  
	CRgn rgn;
	CRgn tmpRgn;
	rgn.CreateRectRgn(0, 0, bitmapinfo.bmWidth, bitmapinfo.bmHeight);
	//从整体区域中剔除所有黑色像素区域  
	for (int i = 0; i<bitmapinfo.bmWidth; i++)
	{
		for (int j = 0; j<bitmapinfo.bmHeight; j++)
		{
			COLORREF cl = dcMem.GetPixel(i, j);
			if (cl == TransColor)
			{
				tmpRgn.CreateRectRgn(i, j, i + 1, j + 1);
				rgn.CombineRgn(&rgn, &tmpRgn, RGN_XOR);
				tmpRgn.DeleteObject();
			}
		}
	}
	//设置窗口显示区域  
	SetWindowRgn(rgn, true);
}

void MainMenu::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(MainMenu, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &MainMenu::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &MainMenu::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &MainMenu::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &MainMenu::OnBnClickedButton4)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// MainMenu 消息处理程序


//人机模式
void MainMenu::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

	//设为人机模式
	isCompter = TRUE;

	CFiveChessDlg dlg;
	AfxGetApp()->m_pMainWnd = &dlg;
	DestroyWindow();
	dlg.DoModal();

}


//联机模式
void MainMenu::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码	

	//设为人机模式
	isCompter = FALSE;

	CFiveChessDlg dlg;
	AfxGetApp()->m_pMainWnd = &dlg;
	DestroyWindow();
	dlg.DoModal();
}

//设置
void MainMenu::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	setMenu m_setMenu;
	m_setMenu.DoModal();
}

//退出游戏
void MainMenu::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	exit(0);
}


HBRUSH MainMenu::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


void MainMenu::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialog::OnPaint()
	CRect  rect;
	GetWindowRect(&rect);
	CDC  dcMem;
	dcMem.CreateCompatibleDC(&dc);
	CBitmap  bmpBackground;
	bmpBackground.LoadBitmap(IDB_BMP_MAINMENUBACK);  //背景图  
	BITMAP  bitmap;
	bmpBackground.GetBitmap(&bitmap);
	CBitmap  *pbmpOld = dcMem.SelectObject(&bmpBackground);
	dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcMem, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
}


void MainMenu::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CDialog::OnLButtonDown(nFlags, point);
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));//使窗口可拖动
}


BOOL MainMenu::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//根据双色图片设置窗口形状（非黑色区域有效）  
	SetRegion(GetDC(), IDB_BMP_MAINMENUBACK, RGB(0, 0, 0));

	//居中  
	CenterWindow();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
