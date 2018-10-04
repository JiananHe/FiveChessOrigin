// SetupDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FiveChess.h"
#include "FiveChessDlg.h"
#include "SetupDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetupDlg dialog


CSetupDlg::CSetupDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSetupDlg::IDD, pParent)
	, m_setname(_T(""))
{
	//{{AFX_DATA_INIT(CSetupDlg)
	m_net_port = 0;
	//}}AFX_DATA_INIT
}

void CSetupDlg::SetRegion(CDC * pDC, UINT BackBitmapID, COLORREF TransColor)
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


void CSetupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetupDlg)
	DDX_Control(pDX, IDC_IP_ADDRESS_EDIT, m_ip_addr);
	DDX_Text(pDX, IDC_NET_PORT_EDIT, m_net_port);
	DDV_MinMaxUInt(pDX, m_net_port, 1, 65000);
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_EDIT_SETNAME, m_setname);
}


BEGIN_MESSAGE_MAP(CSetupDlg, CDialog)
	//{{AFX_MSG_MAP(CSetupDlg)
	ON_BN_CLICKED(IDC_CLIENT_OPTION, OnClientOption)
	ON_BN_CLICKED(IDC_HOST_OPTION, OnHostOption)
	//}}AFX_MSG_MAP
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetupDlg message handlers

void CSetupDlg::OnOK()
{
	CFiveChessDlg * pDlg = (CFiveChessDlg*)AfxGetMainWnd();

	CString strIP, strPort;

	UpdateData(TRUE);
	m_ip_addr.GetWindowText(strIP);
	m_strHostIP = strIP;
	strPort.Format("%d", m_net_port);
	if (m_isHost)
	{
		WritePrivateProfileString("HOST", "PORT", strPort, ".\\config.ini");
	}
	else
	{
		WritePrivateProfileString("CLIENT", "IP", strIP, ".\\config.ini");
		WritePrivateProfileString("CLIENT", "PORT", strPort, ".\\config.ini");
	}

	CDialog::OnOK();
}

void CSetupDlg::OnCancel()
{
	CDialog::OnCancel();
}

void CSetupDlg::OnClientOption()
{
	m_setname = _T("白棋");//初始化用户名的编辑框

	char str[128] = { 0 };
	m_ip_addr.EnableWindow(TRUE);
	GetPrivateProfileString("CLIENT", "IP", "", str, 127, ".\\config.ini");
	m_ip_addr.SetWindowText(str);
	memset(str, 0, 128);
	GetPrivateProfileString("CLIENT", "PORT", "5000", str, 127, ".\\config.ini");
	m_net_port = atoi(str);
	m_isHost = FALSE;
	UpdateData(FALSE);
}

void CSetupDlg::OnHostOption()
{
	m_setname = _T("黑棋");//初始化用户名的编辑框

	char str[128] = { 0 };
	m_ip_addr.EnableWindow(FALSE);
	//GetPrivateProfileString("HOST", "IP", "", str, 127, ".\\config.ini");
	////////////////////////////////////////////////////////////////////////
	char    HostName[100];
	gethostname(HostName, sizeof(HostName));// 获得本机主机名.
	hostent* hn;
	hn = gethostbyname(HostName);//根据本机主机名得到本机ip
	CString strip = inet_ntoa(*(struct in_addr *)hn->h_addr_list[0]);//把ip换成字符串形式
																	 ////////////////////////////////////////////////////////////////////////
	m_ip_addr.SetWindowText(strip);
	memset(str, 0, 128);
	GetPrivateProfileString("HOST", "PORT", "5000", str, 127, ".\\config.ini");
	m_net_port = atoi(str);
	m_isHost = TRUE;
	UpdateData(FALSE);
}

BOOL CSetupDlg::OnInitDialog()
{
	//根据双色图片设置窗口形状（非黑色区域有效）  
	SetRegion(GetDC(), IDB_BMP_SETUPBACK, RGB(0, 0, 0));

	//居中  
	CenterWindow();

	CDialog::OnInitDialog();
	((CButton*)GetDlgItem(IDC_HOST_OPTION))->SetCheck(1);
	OnHostOption();
	return TRUE;
}

HBRUSH CSetupDlg::OnCtlColor(CDC * pDC, CWnd * pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if (CTLCOLOR_STATIC == nCtlColor)
	{
		pDC->SetTextColor(RGB(0, 0, 0));    //文字前景色
		pDC->SetBkMode(TRANSPARENT);    //设置透明
		hbr = (HBRUSH)GetStockObject(NULL_BRUSH);  //获取画笔颜色混合后的画笔，完成透明 
	}
	return hbr;
}

void CSetupDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialog::OnPaint()
	CRect  rect;
	GetWindowRect(&rect);
	CDC  dcMem;
	dcMem.CreateCompatibleDC(&dc);
	CBitmap  bmpBackground;
	bmpBackground.LoadBitmap(IDB_BMP_SETUPBACK);  //背景图  
	BITMAP  bitmap;
	bmpBackground.GetBitmap(&bitmap);
	CBitmap  *pbmpOld = dcMem.SelectObject(&bmpBackground);
	dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcMem, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
}

void CSetupDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));//使窗口可拖动
}
