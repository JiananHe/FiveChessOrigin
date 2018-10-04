#include "Connect.h"
#include "FiveChessDlg.h"
#include "Board.h"

CConnect::CConnect()
{
}

CConnect::~CConnect()
{
}

/////////////////////////////////////////////////////////////////////////////
// CFiveSocket member functions

void CConnect::OnAccept(int nErrorCode)
{
	CFiveChessDlg * pDlg = (CFiveChessDlg*)AfxGetMainWnd();
	pDlg->Accept();
	pDlg->SetMenuState(FALSE, 2);
}

void CConnect::OnClose(int nErrorCode)
{
	CFiveChessDlg * pDlg = (CFiveChessDlg*)AfxGetMainWnd();

	//pDlg->MessageBox( _T("对方已经离开游戏，改日再较量不迟。"), _T("五子棋"), MB_ICONINFORMATION);
	pDlg->UpdateShow("连接中断,对方已离开游戏!");

	pDlg->SetMenuState(TRUE, 2);

	pDlg->m_board.SetWait(TRUE);

	pDlg->m_conncet.ShutDown();

	pDlg->m_sock.ShutDown();

	pDlg->m_conncet.Close();

	pDlg->m_sock.Close();

	pDlg->m_bIsConnect = FALSE;
	pDlg->whoTurn = 4;
}

void CConnect::OnConnect(int nErrorCode)
{
	CFiveChessDlg * pDlg = (CFiveChessDlg*)AfxGetMainWnd();
	pDlg->Connect();
	pDlg->SetMenuState(FALSE, 2);
}

void CConnect::OnReceive(int nErrorCode)
{
	CBoard *pBoard = (CBoard *)AfxGetMainWnd()->GetDlgItem(IDC_BOARD);
	pBoard->Receive();
}