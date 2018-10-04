// SetMenu.cpp : ʵ���ļ�
//

#include "board.h"
#include "stdafx.h"
#include "FiveChess.h"
#include "SetMenu.h"
#include "afxdialogex.h"
#include<mmsystem.h>

// SetMenu �Ի���

IMPLEMENT_DYNAMIC(setMenu, CDialog)

setMenu::setMenu(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_SET_MENU_DLG, pParent)
{
}

setMenu::~setMenu()
{
}

void setMenu::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(setMenu, CDialog)
	ON_BN_CLICKED(IDOK, &setMenu::OnBnClickedOk)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// SetMenu ��Ϣ�������
void setMenu::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	int music = GetCheckedRadioButton(IDC_RADIO_MSCON, IDC_RADIO_MSCOFF);
	if (music == IDC_RADIO_MSCON && BackmusicFlg == FALSE)
	{
		//���ű�������
		BackmusicFlg = TRUE;
		sndPlaySound((LPCSTR)IDR_WAVE_CSL, SND_NOWAIT | SND_LOOP | SND_ASYNC | SND_RESOURCE);
	}
	else if (music == IDC_RADIO_MSCOFF && BackmusicFlg == TRUE)
	{
		//�رձ�������
		BackmusicFlg = FALSE;
		sndPlaySound(NULL, SND_PURGE);
	}


	int btnDown = GetCheckedRadioButton(IDC_RADIO_DOWNON, IDC_RADIO_DOWNOFF);
	if (btnDown == IDC_RADIO_DOWNON)
	{
		BtnDownFlg = TRUE;
	}
	else if (btnDown == IDC_RADIO_DOWNOFF)
	{
		BtnDownFlg = FALSE;
	}

	CBoard* board = (CBoard*)AfxGetMainWnd();
	int back = GetCheckedRadioButton(IDC_RADIO_QPMM, IDC_RADIO_QPGS);

	if (back == IDC_RADIO_QPMM)
	{
		backint = 1;
		if (BackmusicFlg)
			sndPlaySound((LPCSTR)IDR_WAVE_CSL, SND_NOWAIT | SND_LOOP | SND_ASYNC | SND_RESOURCE);
	}
	else if (back == IDC_RADIO_QPXK)
	{
		backint = 2;
		if (BackmusicFlg)
			sndPlaySound((LPCSTR)IDR_WAVE_YDGQQ, SND_NOWAIT | SND_LOOP | SND_ASYNC | SND_RESOURCE);
	}
	else if (back == IDC_RADIO_QPGS)
	{
		backint = 3;
		if (BackmusicFlg)
			sndPlaySound((LPCSTR)IDR_WAVE_MTHFQM, SND_NOWAIT | SND_LOOP | SND_ASYNC | SND_RESOURCE);
	}
	board->Invalidate();

	CDialog::OnOK();
}




BOOL setMenu::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	if (BackmusicFlg == TRUE)
		((CButton *)GetDlgItem(IDC_RADIO_MSCON))->SetCheck(true);
	if (BackmusicFlg == FALSE)
		((CButton *)GetDlgItem(IDC_RADIO_MSCOFF))->SetCheck(true);

	if (BtnDownFlg == TRUE)
		((CButton *)GetDlgItem(IDC_RADIO_DOWNON))->SetCheck(true);
	if (BtnDownFlg == FALSE)
		((CButton *)GetDlgItem(IDC_RADIO_DOWNOFF))->SetCheck(true);

	if (backint == 1)
		((CButton *)GetDlgItem(IDC_RADIO_QPMM))->SetCheck(true);
	else if (backint == 2)
		((CButton *)GetDlgItem(IDC_RADIO_QPXK))->SetCheck(true);
	else if (backint == 3)
		((CButton *)GetDlgItem(IDC_RADIO_QPGS))->SetCheck(true);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void setMenu::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: �ڴ˴������Ϣ����������
					   // ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()
					   // ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()
	CRect  rect;
	GetWindowRect(&rect);
	CDC  dcMem;
	dcMem.CreateCompatibleDC(&dc);
	CBitmap  bmpBackground;
	bmpBackground.LoadBitmap(IDB_BMP_SETBACK);  //����ͼ  
	BITMAP  bitmap;
	bmpBackground.GetBitmap(&bitmap);
	CBitmap  *pbmpOld = dcMem.SelectObject(&bmpBackground);
	dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcMem, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
}


HBRUSH setMenu::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
