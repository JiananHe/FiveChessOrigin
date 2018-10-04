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
		MessageBox(_T("��������DCʧ�ܣ�"));
	}

	CBitmap bitmap;
	if (!bitmap.LoadBitmap(BackBitmapID))
	{
		MessageBox(_T("����λͼʧ�ܣ�"));
	}

	if (!dcMem.SelectObject(&bitmap))
	{
		MessageBox(_T("ѡ���豸������ʧ�ܣ�"));
	}

	BITMAP bitmapinfo;
	bitmap.GetBitmap(&bitmapinfo);
	//�Ѵ�����ΪͼƬ�Ĵ�С,ȥ������Ļ�����ô����ָ�᲻��ȷ  
	MoveWindow(0, 0, bitmapinfo.bmWidth, bitmapinfo.bmHeight, true);
	//��������  
	CRgn rgn;
	CRgn tmpRgn;
	rgn.CreateRectRgn(0, 0, bitmapinfo.bmWidth, bitmapinfo.bmHeight);
	//�������������޳����к�ɫ��������  
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
	//���ô�����ʾ����  
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
	m_setname = _T("����");//��ʼ���û����ı༭��

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
	m_setname = _T("����");//��ʼ���û����ı༭��

	char str[128] = { 0 };
	m_ip_addr.EnableWindow(FALSE);
	//GetPrivateProfileString("HOST", "IP", "", str, 127, ".\\config.ini");
	////////////////////////////////////////////////////////////////////////
	char    HostName[100];
	gethostname(HostName, sizeof(HostName));// ��ñ���������.
	hostent* hn;
	hn = gethostbyname(HostName);//���ݱ����������õ�����ip
	CString strip = inet_ntoa(*(struct in_addr *)hn->h_addr_list[0]);//��ip�����ַ�����ʽ
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
	//����˫ɫͼƬ���ô�����״���Ǻ�ɫ������Ч��  
	SetRegion(GetDC(), IDB_BMP_SETUPBACK, RGB(0, 0, 0));

	//����  
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
		pDC->SetTextColor(RGB(0, 0, 0));    //����ǰ��ɫ
		pDC->SetBkMode(TRANSPARENT);    //����͸��
		hbr = (HBRUSH)GetStockObject(NULL_BRUSH);  //��ȡ������ɫ��Ϻ�Ļ��ʣ����͸�� 
	}
	return hbr;
}

void CSetupDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: �ڴ˴������Ϣ����������
					   // ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()
	CRect  rect;
	GetWindowRect(&rect);
	CDC  dcMem;
	dcMem.CreateCompatibleDC(&dc);
	CBitmap  bmpBackground;
	bmpBackground.LoadBitmap(IDB_BMP_SETUPBACK);  //����ͼ  
	BITMAP  bitmap;
	bmpBackground.GetBitmap(&bitmap);
	CBitmap  *pbmpOld = dcMem.SelectObject(&bmpBackground);
	dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcMem, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
}

void CSetupDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));//ʹ���ڿ��϶�
}
