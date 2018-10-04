#include "board.h"
#include "Resource.h"
#include "ConnectData.h"
#include "Rule.h"
#include "FiveChessDlg.h"
#include "SetMenu.h"
#include "FiveChess.h"
#include "Computer.h"

#define MAX_LEN 256				/*������󳤶�*/
//////////////////////////////////////////////////////////////////////////
// ���캯������ʼ�����������Լ�ͼ������
//////////////////////////////////////////////////////////////////////////
CBoard::CBoard()
{
	// ��ʼ��ͼ���б�
	m_iml.Create(24, 24, ILC_COLOR24 | ILC_MASK, 0, 2);
	// ����ڡ�����������λͼ
	CBitmap bmpBlack, bmpWhite, bmpBlack2, bmpWhite2;
	bmpBlack.LoadBitmap(IDB_BMP_BLACK);
	m_iml.Add(&bmpBlack, 0xff00ff);
	bmpWhite.LoadBitmap(IDB_BMP_WHITE);
	m_iml.Add(&bmpWhite, 0xff00ff);
	bmpBlack2.LoadBitmap(IDB_BITMAP1);
	m_iml.Add(&bmpBlack2, 0xff00ff);
	bmpWhite2.LoadBitmap(IDB_BITMAP3);
	m_iml.Add(&bmpWhite2, 0xff00ff);
}
//////////////////////////////////////////////////////////////////////////
// ��������
//////////////////////////////////////////////////////////////////////////
CBoard::~CBoard()
{

}

// ��Ϣӳ���
BEGIN_MESSAGE_MAP(CBoard, CWnd)
	//{{AFX_MSG_MAP(CBoard)
	ON_WM_PAINT()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////
// ����WM_PAINT��Ϣ
//////////////////////////////////////////////////////////////////////////
void CBoard::OnPaint()
{
	CPaintDC dc(this);
	CDC MemDC;
	MemDC.CreateCompatibleDC(&dc);
	// װ������
	CBitmap bmp;
	CPen pen;

	if (backint == 1)
		bmp.LoadBitmap(IDB_BMP_QP1);
	else if (backint == 2)
		bmp.LoadBitmap(IDB_BMP_QP2);
	else if (backint == 3)
		bmp.LoadBitmap(IDB_BMP_QP3);

	pen.CreatePen(PS_SOLID, 1, 0xff);
	MemDC.SelectObject(&bmp);
	MemDC.SelectObject(&pen);
	MemDC.SetROP2(R2_NOTXORPEN);
	// �����������ݻ�������
	int x, y;
	POINT pt;
	for (y = 0; y < 15; y++)
	{
		for (x = 0; x < 15; x++)
		{
			if (-1 != m_data[x][y])
			{
				pt.x = 225 + 25 * x;
				pt.y = 82 + 25 * y;
				m_iml.Draw(&MemDC, m_data[x][y] + 2, pt, ILD_TRANSPARENT);
			}
		}
	}
	if (a != -1 && b != -1)
	{
		pt.x = 225 + 25 * a;
		pt.y = 82 + 25 * b;
		m_iml.Draw(&MemDC, m_data[a][b], pt, ILD_TRANSPARENT);
	}
	if (c != -1 && d != -1 && quit == 1)
	{
		pt.x = 225 + 25 * c;
		pt.y = 82 + 25 * d;
		m_iml.Draw(&MemDC, m_data[c][d], pt, ILD_TRANSPARENT);
	}

	// ��ɻ���
	dc.BitBlt(0, 0, 825, 470, &MemDC, 0, 0, SRCCOPY);
}

//////////////////////////////////////////////////////////////////////////
// �������������Ϣ��Ϊ�������֮��
//////////////////////////////////////////////////////////////////////////
void CBoard::OnLButtonUp(UINT nFlags, CPoint point)
{
	/////////////////////   �˻�ģʽ   ////////////////////
	if (isCompter)
	{
		Computer m_computer;
		CRule  rule;
		CFiveChessDlg * pDlg = (CFiveChessDlg*)AfxGetMainWnd();

		if (m_bWait)
		{
			//
			if (a == -1)
			{
				MessageBox(_T("���� �� ����->����Ϸ �� ��ʼ��Ϸ!"), _T("��ʾ"), MB_ICONWARNING);
				return;
			}

			MessageBeep(MB_OK);
			return;
		}

		int x, y;
		x = (point.x - 225) / 25;
		y = (point.y - 82) / 25;
		// �����(0, 0)��(14, 14)��Χ�ڣ��Ҹ�����û�����ӣ�
		// �������ڴˣ����������沢�˳�����
		if (x < 0 || x > 14 || y < 0 || y > 14 || m_data[x][y] != -1)
		{
			MessageBeep(MB_OK);
			return;
		}
		else
		{
			// ���λ�úϷ���������
			SetData(x, y, 0);
			Draw(x, y, BLACK);//����ǵĺ���
							  //������������
			init();
			play();

			//��¼����λ��
			c = x;
			d = y;

			//ȥ����һ�����ӵı��
			if (m_data[a][b] == 1 && a >= 0 && b >= 0)
			{
				Draw(a, b, WHITE2);
			}
		}

		if (rule.Win(0, x, y) == _WIN)
		{// ʤ��
			pDlg->whoTurn = 4;
			pDlg->MessageBox(_T("��ϲ���������ʤ����"), _T("ʤ��"), MB_ICONINFORMATION);
			pDlg->newhistory(_WIN);
			pDlg->SetMenuState(TRUE, 2);
			pDlg->SetMenuState(TRUE, 0);

			SetWait(TRUE);
			return;
		}
		else if (rule.Win(0, x, y) == _LOST)
		{//	���ֽ���
			pDlg->whoTurn = 4;
			pDlg->MessageBox(_T("ִ�ڽ���, �����ˣ�"), _T("ʧ��"), MB_ICONINFORMATION);
			pDlg->newhistory(_LOST);
			pDlg->SetMenuState(TRUE, 2);
			pDlg->SetMenuState(TRUE, 0);

			SetWait(TRUE);
			return;
		}
		SetWait(TRUE);

		//�ֵ����������
		int computer_x = 0;
		int computer_y = 0;
		//�������꣬����
		m_computer.computerPoint(computer_x, computer_y);
		SetData(computer_x, computer_y, 1);
		Draw(computer_x, computer_y, WHITE);//����ǵİ���
											//��¼����λ��
		a = computer_x;
		b = computer_y;

		//ȥ����һ�����ӵı��
		if (m_data[c][d] == 0)
		{
			Draw(c, d, BLACK2);
		}

		SetWait(FALSE);
		//���û���ѡ��Ϊ����״̬
		pDlg->SetMenuState(NULL, 1);

		if (rule.Win(1, computer_x, computer_y) == _WIN)
		{// ʤ��
			pDlg->whoTurn = 4;
			pDlg->MessageBox(_T("�����ʤ�������ˣ�"), _T("ʧ��"), MB_ICONINFORMATION);
			pDlg->newhistory(_LOST);
			pDlg->SetMenuState(TRUE, 2);
			pDlg->SetMenuState(TRUE, 0);

			SetWait(TRUE);
		}

		return;
	}
	/////////////////   �˻�ģʽ����   /////////////////////////



	MSGSTRUCT msg;
	CRule rule;
	CFiveChessDlg * pDlg = (CFiveChessDlg*)AfxGetMainWnd();
	BYTE buf[MAX_LEN] = { 0 };

	if ((point.x > 40 && point.x < 190 && point.y>50 && point.y < 230)
		|| (point.x > 640 && point.x < 790 && point.y>50 && point.y < 230))
	{
		msg.msgType = MSG_SEE_HISTORY;
		pDlg->m_sock.Send((LPCVOID)&msg, sizeof(MSGSTRUCT));
	}
	else
	{
		pDlg->showwindow(FALSE);
	}

	if (m_bWait)
	{
		MessageBeep(MB_OK);
		return;
	}

	if (pDlg->m_bIsConnect)
	{
		int x, y;
		x = (point.x - 225) / 25;
		y = (point.y - 82) / 25;
		// �����(0, 0)��(14, 14)��Χ�ڣ��Ҹ�����û�����ӣ�
		// �������ڴˣ����������沢�˳�����
		if (x < 0 || x > 14 || y < 0 || y > 14 || m_data[x][y] != -1)
		{
			MessageBeep(MB_OK);
			return;
		}
		else
		{
			// ���λ�úϷ���������
			SetData(x, y, m_color);
			pDlg->initSetTimer();
			msg.color = m_color;
			if (quit == 0)
			{
				if (num > 1)
				{
					if (m_color == 0)
					{
						Draw(a, b, WHITE2);
					}
					if (m_color == 1)
					{
						Draw(a, b, BLACK2);
					}
				}
				c = a;
				d = b;
			}
			if (quit == 1)
			{
				if (num > 1)
				{
					if (m_color == 0)
					{
						Draw(c, d, WHITE2);
					}
					if (m_color == 1)
					{
						Draw(c, d, BLACK2);
					}
				}
			}
			quit = 0;
			a = x;
			b = y;
			msg.x = x;
			msg.y = y;
			//��ʼ����������������
			init();
			play();
		}
		// ��ʼ�ȴ�
		m_bWait = TRUE;
		msg.msgType = MSG_PUTSTEP;
		pDlg->Send(&msg);
		
		if (rule.Win(m_color, msg.x, msg.y) == _WIN)
		{// ʤ��
			pDlg->whoTurn = 4;
			pDlg->MessageBox(_T("��ϲ���������ʤ����"), _T("ʤ��"), MB_ICONINFORMATION);
			pDlg->newhistory(_WIN);
			pDlg->SetMenuState(TRUE, 2);
			pDlg->SetMenuState(TRUE, 0);

			SetWait(TRUE);
		}
		else if (rule.Win(m_color, msg.x, msg.y) == _LOST)
		{//	���ֽ���
			pDlg->whoTurn = 4;
			pDlg->MessageBox(_T("ִ�ڽ���, �����ˣ�"), _T("ʧ��"), MB_ICONINFORMATION);
			pDlg->newhistory(_LOST);
			pDlg->SetMenuState(TRUE, 2);
			pDlg->SetMenuState(TRUE, 0);

			SetWait(TRUE);
		}
	}

}

//////////////////////////////////////////////////////////////////////////
// �������
//////////////////////////////////////////////////////////////////////////
void CBoard::Clear(BOOL bWait)
{
	int x, y;
	for (y = 0; y < 15; y++)
	{
		for (x = 0; x < 15; x++)
		{
			m_data[x][y] = -1;
		}
	}
	// ���õȴ���־
	m_bWait = bWait;
	c = d = -1;
	a = b = -1;
	num = 0;
	quit = 0;
	CFiveChessDlg a;
	a.Invali();
}

//���أ����ڻ�����ػ����̣�����������m_data����
void CBoard::Draw2()
{
	quit = 1;
	CFiveChessDlg a;
	a.Invali();
}

//////////////////////////////////////////////////////////////////////////
// ���������ɫ
//////////////////////////////////////////////////////////////////////////
void CBoard::SetColor(int color)
{
	m_color = color;
}

//////////////////////////////////////////////////////////////////////////
// ��ȡ�����ɫ
//////////////////////////////////////////////////////////////////////////
int CBoard::GetColor() const
{
	return m_color;
}

//////////////////////////////////////////////////////////////////////////
// ���õȴ���־
//////////////////////////////////////////////////////////////////////////
void CBoard::SetWait(BOOL bWait)
{
	m_bOldWait = m_bWait;
	m_bWait = bWait;
}

//////////////////////////////////////////////////////////////////////////
// �����������ݣ�����������
//////////////////////////////////////////////////////////////////////////
void CBoard::SetData(int x, int y, int color)
{
	m_data[x][y] = color;
	num++;
	Draw(x, y, color);
}

//////////////////////////////////////////////////////////////////////////
// ��ָ���������괦����ָ����ɫ������
//////////////////////////////////////////////////////////////////////////
void CBoard::Draw(int x, int y, int color)
{
	POINT pt;
	pt.x = 225 + 25 * x;
	pt.y = 82 + 25 * y;
	CDC *pDC = GetDC();
	CPen pen;
	pen.CreatePen(PS_SOLID, 1, 0xff);
	pDC->SelectObject(&pen);
	pDC->SetROP2(R2_NOTXORPEN);
	m_iml.Draw(pDC, color, pt, ILD_TRANSPARENT);
	ReleaseDC(pDC);
}

//////////////////////////////////////////////////////////////////////////
// �������ԶԷ�������
//////////////////////////////////////////////////////////////////////////
void CBoard::Receive()
{
	CFiveChessDlg * pDlg = (CFiveChessDlg*)AfxGetMainWnd();
	MSGSTRUCT msg;
	CStdioFile myfile;
	CFileException fileException;
	CString temp;
	if (pDlg->m_sock.Receive((LPVOID)&msg, sizeof(MSGSTRUCT)) == SOCKET_ERROR)
	{
		AfxGetMainWnd()->MessageBox(_T("��������ʱ�����������������������ӡ�"), _T("����"), MB_ICONSTOP);
		return;
	}

	CString recvword = _T("");

	switch (msg.msgType)
	{
	case MSG_PUTSTEP:
		pDlg->SetMenuState(NULL, 0);
		pDlg->initSetTimer();
		SetData(msg.x, msg.y, msg.color);
		if (quit == 0)
		{
			if (num > 1)
			{
				if (msg.color == 0)
				{
					Draw(a, b, WHITE2);
				}
				if (msg.color == 1)
				{
					Draw(a, b, BLACK2);
				}
			}
			c = a;
			d = b;
		}
		if (quit == 1)
		{
			if (num > 1)
			{
				if (msg.color == 0)
				{
					Draw(c, d, WHITE2);
				}
				if (msg.color == 1)
				{
					Draw(c, d, BLACK2);
				}
			}
		}
		quit = 0;
		a = msg.x;
		b = msg.y;
		Over(msg.x, msg.y);
		break;
	case MSG_SEE_HISTORY:
		if (myfile.Open("D:\\myFile.txt", CFile::shareDenyWrite, &fileException))
		{
			MSGSTRUCT msg;
			CString num1;
			CString num2;
			CString num3;
			msg.msgType = MSG_AREE_SEE;
			myfile.ReadString(num1);
			myfile.ReadString(num2);
			myfile.ReadString(num3);
			msg.win = atoi(num1);
			msg.lost = atoi(num2);
			msg.draw = atoi(num3);
			pDlg->m_sock.Send((LPCVOID)&msg, sizeof(MSGSTRUCT));
		}
		else
		{
			MSGSTRUCT msg;
			msg.msgType = MSG_AREE_SEE;
			msg.win = 0;
			msg.lost = 0;
			msg.draw = 0;
			pDlg->m_sock.Send((LPCVOID)&msg, sizeof(MSGSTRUCT));
		}
		break;
	case MSG_AREE_SEE:
		pDlg->showhistory(msg.win, msg.lost, msg.draw);
		pDlg->showwindow(TRUE);
		break;
	case MSG_DRAW:
		if (IDYES == GetParent()->MessageBox(_T("�Է�������壬�������������"),
			_T("����"), MB_ICONQUESTION | MB_YESNO))
		{
			// �������������Ϣ
			MSGSTRUCT msg;
			msg.msgType = MSG_AGREE_DRAW;
			pDlg->m_sock.Send((LPCVOID)&msg, sizeof(MSGSTRUCT));
			SetWait(TRUE);
			// ʹ�����桱�˵���Ч
			pDlg->newhistory(MSG_AGREE_DRAW);
			pDlg->SetMenuState(TRUE, 2);
			pDlg->SetMenuState(TRUE, 0);
			pDlg->whoTurn = 0;
			SetWait(TRUE);
		}
		else
		{
			// ���;ܾ�������Ϣ
			MSGSTRUCT msg;
			msg.msgType = MSG_REFUSE_DRAW;
			pDlg->m_sock.Send((LPCVOID)&msg, sizeof(MSGSTRUCT));
		}
		break;
	case MSG_AGREE_DRAW:
		pDlg->whoTurn = 0;
		pDlg->MessageBox(_T("�������������֣��Է����������ĺ�������"), _T("����"), MB_ICONINFORMATION);
		// �����ʹ�����桱�˵���Ч
		pDlg->newhistory(MSG_AGREE_DRAW);
		pDlg->SetMenuState(TRUE, 2);
		pDlg->SetMenuState(TRUE, 0);
		SetWait(TRUE);
		break;
	case MSG_REFUSE_DRAW:
		pDlg->MessageBox(_T("�����Է���������ȡ��ʤ�������Ծܾ������ĺ�������"),
			_T("����"), MB_ICONINFORMATION);
		RestoreWait();
		pDlg->SetMenuState(FALSE, 2);
		break;
	case MSG_BACK:
		if (IDYES == GetParent()->MessageBox(_T("�Է�������壬�������������"),
			_T("����"), MB_ICONQUESTION | MB_YESNO))
		{
			// �������������Ϣ
			MSGSTRUCT msg;
			msg.msgType = MSG_AGREE_BACK;
			pDlg->m_sock.Send((LPCVOID)&msg, sizeof(MSGSTRUCT));
			m_data[a][b] = -1;
			Draw2();
			pDlg->initSetTimer();//��������ü�ʱ��
			SetWait(TRUE);
			// ʹ�����桱�˵���Ч
			//pDlg->SetMenuState(TRUE);
		}
		else
		{
			// ���;ܾ�������Ϣ
			MSGSTRUCT msg;
			msg.msgType = MSG_REFUSE_BACK;
			pDlg->m_sock.Send((LPCVOID)&msg, sizeof(MSGSTRUCT));
		}
		break;
	case MSG_AGREE_BACK:
		pDlg->initSetTimer();//��������ü�ʱ��
		pDlg->MessageBox(_T("�Է����������Ļ�������"), _T("����"), MB_ICONINFORMATION);
		//�����һ����������
		m_data[a][b] = -1;
		Draw2();
		SetWait(FALSE);
		// �����ʹ�����桱�˵���Ч
		//pDlg->SetMenuState(TRUE);
		break;
	case MSG_REFUSE_BACK:
		pDlg->MessageBox(_T("�Է��ܾ������Ļ�������"),
			_T("����"), MB_ICONINFORMATION);
		RestoreWait();
		pDlg->SetMenuState(FALSE, 2);
		break;
	case MSG_NEW_GAME:
		if (IDYES == GetParent()->MessageBox(_T("�Է�����ʼ����Ϸ���������������"),
			_T("����Ϸ"), MB_ICONQUESTION | MB_YESNO))
		{
			// ������������Ϸ��Ϣ
			MSGSTRUCT msg;
			msg.msgType = MSG_AGREE_NEW;
			pDlg->m_sock.Send((LPCVOID)&msg, sizeof(MSGSTRUCT));
			//SetWait(TRUE);
			// ʹ�����桱�˵�ʧЧ,�����塱ʧЧ
			pDlg->SetMenuState(FALSE, 2);
			pDlg->SetMenuState(FALSE, 0);
			Clear(!(pDlg->m_isHost));
			pDlg->whoTurn = 3;
		}
		else
		{
			// ���;ܾ�������Ϣ
			MSGSTRUCT msg;
			msg.msgType = MSG_REFUSE_NEW;
			pDlg->m_sock.Send((LPCVOID)&msg, sizeof(MSGSTRUCT));
		}
		break;
	case MSG_AGREE_NEW:
		pDlg->MessageBox(_T("�Է���������������"), _T("����Ϸ"), MB_ICONINFORMATION);
		// ʹ�����桱�˵�ʧЧ,�����塱ʧЧ
		pDlg->SetMenuState(FALSE, 2);
		pDlg->SetMenuState(FALSE, 0);
		Clear(!(pDlg->m_isHost));
		pDlg->whoTurn = 3;
		break;
	case MSG_REFUSE_NEW:
		pDlg->MessageBox(_T("�Է��ܾ�����������"), _T("����Ϸ"), MB_ICONINFORMATION);
		RestoreWait();
		break;
	case MSG_EXTERN:
		recvword = msg.byMsg;
		pDlg->newshowedit();
		pDlg->UpdateShow(recvword);
		break;
	default:
		break;
	}

}

//////////////////////////////////////////////////////////////////////////
// �������
//////////////////////////////////////////////////////////////////////////
void CBoard::DrawGame()
{
	CFiveChessDlg * pDlg = (CFiveChessDlg*)AfxGetMainWnd();
	// ���õȴ���־
	SetWait(TRUE);
	MSGSTRUCT msg;
	msg.msgType = MSG_DRAW;
	pDlg->m_sock.Send((LPCVOID)&msg, sizeof(MSGSTRUCT));
}

//////////////////////////////////////////////////////////////////////////
// ����Է����Ӻ�Ĺ���
//////////////////////////////////////////////////////////////////////////
void CBoard::Over(int x, int y)
{
	CRule rule;
	CFiveChessDlg *pDlg = (CFiveChessDlg *)GetParent();
	// �ж϶Է��Ƿ�ʤ��
	if (rule.Win(1 - m_color, x, y) == _WIN)
	{
		pDlg->whoTurn = 4;
		pDlg->MessageBox(_T("�����ˣ��ٽ������ɣ�"), _T("ʧ��"), MB_ICONINFORMATION);
		pDlg->newhistory(_LOST);
		// ����������ս������Ч�����桱
		if (pDlg->m_bIsConnect)
		{
			pDlg->SetMenuState(TRUE, 2);
			pDlg->SetMenuState(TRUE, 0);
			pDlg->whoTurn = 4;
		}
		SetWait(TRUE);
		return;
	}
	//�ж϶Է��Ƿ���ֽ���
	else if (rule.Win(1 - m_color, x, y) == _LOST)
	{
		pDlg->whoTurn = 4;
		pDlg->MessageBox(_T("��ϲ��, �Է����ֽ������ˣ�"), _T("ʤ��"), MB_ICONINFORMATION);
		pDlg->newhistory(_WIN);
		// ����������ս������Ч�����桱
		if (pDlg->m_bIsConnect)
		{
			pDlg->SetMenuState(TRUE, 2);
			pDlg->SetMenuState(TRUE, 0);
			pDlg->whoTurn = 4;
		}
		SetWait(TRUE);
		return;
	}
	m_bWait = FALSE;
}

/////////////////////////////////////////////////////////////
//������Ƶ��Դ
////////////////////////////////////////////////////////////
bool CBoard::ExtractResource(LPCTSTR strDstFile, LPCTSTR strResType, LPCTSTR strResName)
{
	//�м���ú�							  
	// �����ļ�
	HANDLE hFile = ::CreateFile(strDstFile, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_TEMPORARY, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return false;

	// ������Դ�ļ��С�������Դ���ڴ桢�õ���Դ��С
	HRSRC    hRes = ::FindResource(NULL, strResName, strResType);
	HGLOBAL    hMem = ::LoadResource(NULL, hRes);
	DWORD    dwSize = ::SizeofResource(NULL, hRes);

	// д���ļ�
	DWORD dwWrite = 0;      // ����д���ֽ�
	::WriteFile(hFile, hMem, dwSize, &dwWrite, NULL);
	::CloseHandle(hFile);

	return true;
}

/////////////////////////////////////////////////////////////
//��ʼ��������Ч
////////////////////////////////////////////////////////////
void CBoard::init()
{
	//��ʼ������
	// ������ʱ�ļ����ļ���
	TCHAR tmpwav[_MAX_PATH];
	::GetTempPath(_MAX_PATH, tmpwav);
	_tcscat_s(tmpwav, _T("testapp_background.wav"));
	// ��wav ��Դ��ȡΪ��ʱ�ļ�
	ExtractResource(tmpwav, _T("WAVE"), MAKEINTRESOURCE(IDR_WAVE_BTNDOWN));
	// ������
	//TCHAR mcicmd[300];
	_stprintf_s(mcicmd, _T("open \"%s\" alias mymusic"), tmpwav);
}

/////////////////////////////////////////////////////////////
//����������Ч
////////////////////////////////////////////////////////////
void CBoard::play()
{
	if (BtnDownFlg == TRUE)
	{
		mciSendString(_T("close mymusic"), NULL, 0, NULL);//�ȹ��ٿ���ע��˳�򣡣���
		mciSendString(mcicmd, NULL, 0, NULL);
		mciSendString(_T("play mymusic"), NULL, 0, NULL);
	}
}

//////////////////////////////////////////////////////////////////////////
// ����������ǰ�ĵȴ���־
//////////////////////////////////////////////////////////////////////////
void CBoard::RestoreWait()
{
	SetWait(m_bOldWait);
}
