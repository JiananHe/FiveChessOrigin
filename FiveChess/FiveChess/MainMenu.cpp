// MainMenu.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FiveChess.h"
#include "FiveChessDlg.h"
#include "MainMenu.h"
#include "afxdialogex.h"
#include "SetMenu.h"


// MainMenu �Ի���

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


// MainMenu ��Ϣ�������


//�˻�ģʽ
void MainMenu::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//��Ϊ�˻�ģʽ
	isCompter = TRUE;

	CFiveChessDlg dlg;
	AfxGetApp()->m_pMainWnd = &dlg;
	DestroyWindow();
	dlg.DoModal();

}


//����ģʽ
void MainMenu::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������	

	//��Ϊ�˻�ģʽ
	isCompter = FALSE;

	CFiveChessDlg dlg;
	AfxGetApp()->m_pMainWnd = &dlg;
	DestroyWindow();
	dlg.DoModal();
}

//����
void MainMenu::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	setMenu m_setMenu;
	m_setMenu.DoModal();
}

//�˳���Ϸ
void MainMenu::OnBnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	exit(0);
}


HBRUSH MainMenu::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}


void MainMenu::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: �ڴ˴������Ϣ����������
					   // ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()
	CRect  rect;
	GetWindowRect(&rect);
	CDC  dcMem;
	dcMem.CreateCompatibleDC(&dc);
	CBitmap  bmpBackground;
	bmpBackground.LoadBitmap(IDB_BMP_MAINMENUBACK);  //����ͼ  
	BITMAP  bitmap;
	bmpBackground.GetBitmap(&bitmap);
	CBitmap  *pbmpOld = dcMem.SelectObject(&bmpBackground);
	dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcMem, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
}


void MainMenu::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CDialog::OnLButtonDown(nFlags, point);
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));//ʹ���ڿ��϶�
}


BOOL MainMenu::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//����˫ɫͼƬ���ô�����״���Ǻ�ɫ������Ч��  
	SetRegion(GetDC(), IDB_BMP_MAINMENUBACK, RGB(0, 0, 0));

	//����  
	CenterWindow();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
