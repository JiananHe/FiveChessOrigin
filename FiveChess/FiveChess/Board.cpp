#include "board.h"
#include "Resource.h"
#include "ConnectData.h"
#include "Rule.h"
#include "FiveChessDlg.h"
#include "SetMenu.h"
#include "FiveChess.h"
#include "Computer.h"

#define MAX_LEN 256				/*定义最大长度*/
//////////////////////////////////////////////////////////////////////////
// 构造函数，初始化棋盘数据以及图像数据
//////////////////////////////////////////////////////////////////////////
CBoard::CBoard()
{
	// 初始化图像列表
	m_iml.Create(24, 24, ILC_COLOR24 | ILC_MASK, 0, 2);
	// 载入黑、白棋子掩码位图
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
// 析构函数
//////////////////////////////////////////////////////////////////////////
CBoard::~CBoard()
{

}

// 消息映射表
BEGIN_MESSAGE_MAP(CBoard, CWnd)
	//{{AFX_MSG_MAP(CBoard)
	ON_WM_PAINT()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////
// 处理WM_PAINT消息
//////////////////////////////////////////////////////////////////////////
void CBoard::OnPaint()
{
	CPaintDC dc(this);
	CDC MemDC;
	MemDC.CreateCompatibleDC(&dc);
	// 装载棋盘
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
	// 根据棋盘数据绘制棋子
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

	// 完成绘制
	dc.BitBlt(0, 0, 825, 470, &MemDC, 0, 0, SRCCOPY);
}

//////////////////////////////////////////////////////////////////////////
// 处理左键弹起消息，为玩家落子之用
//////////////////////////////////////////////////////////////////////////
void CBoard::OnLButtonUp(UINT nFlags, CPoint point)
{
	/////////////////////   人机模式   ////////////////////
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
				MessageBox(_T("请点击 “ 操作->新游戏 ” 开始游戏!"), _T("提示"), MB_ICONWARNING);
				return;
			}

			MessageBeep(MB_OK);
			return;
		}

		int x, y;
		x = (point.x - 225) / 25;
		y = (point.y - 82) / 25;
		// 如果在(0, 0)～(14, 14)范围内，且该坐标没有落子，
		// 则落子于此，否则发声警告并退出过程
		if (x < 0 || x > 14 || y < 0 || y > 14 || m_data[x][y] != -1)
		{
			MessageBeep(MB_OK);
			return;
		}
		else
		{
			// 如果位置合法，则落子
			SetData(x, y, 0);
			Draw(x, y, BLACK);//被标记的黑子
							  //播放落子声音
			init();
			play();

			//记录落子位置
			c = x;
			d = y;

			//去掉上一步棋子的标记
			if (m_data[a][b] == 1 && a >= 0 && b >= 0)
			{
				Draw(a, b, WHITE2);
			}
		}

		if (rule.Win(0, x, y) == _WIN)
		{// 胜利
			pDlg->whoTurn = 4;
			pDlg->MessageBox(_T("恭喜，您获得了胜利！"), _T("胜利"), MB_ICONINFORMATION);
			pDlg->newhistory(_WIN);
			pDlg->SetMenuState(TRUE, 2);
			pDlg->SetMenuState(TRUE, 0);

			SetWait(TRUE);
			return;
		}
		else if (rule.Win(0, x, y) == _LOST)
		{//	出现禁手
			pDlg->whoTurn = 4;
			pDlg->MessageBox(_T("执黑禁手, 您输了！"), _T("失败"), MB_ICONINFORMATION);
			pDlg->newhistory(_LOST);
			pDlg->SetMenuState(TRUE, 2);
			pDlg->SetMenuState(TRUE, 0);

			SetWait(TRUE);
			return;
		}
		SetWait(TRUE);

		//轮到计算机落子
		int computer_x = 0;
		int computer_y = 0;
		//计算坐标，落子
		m_computer.computerPoint(computer_x, computer_y);
		SetData(computer_x, computer_y, 1);
		Draw(computer_x, computer_y, WHITE);//被标记的白子
											//记录落子位置
		a = computer_x;
		b = computer_y;

		//去掉上一步棋子的标记
		if (m_data[c][d] == 0)
		{
			Draw(c, d, BLACK2);
		}

		SetWait(FALSE);
		//设置悔棋选项为可用状态
		pDlg->SetMenuState(NULL, 1);

		if (rule.Win(1, computer_x, computer_y) == _WIN)
		{// 胜利
			pDlg->whoTurn = 4;
			pDlg->MessageBox(_T("白棋获胜，您输了！"), _T("失败"), MB_ICONINFORMATION);
			pDlg->newhistory(_LOST);
			pDlg->SetMenuState(TRUE, 2);
			pDlg->SetMenuState(TRUE, 0);

			SetWait(TRUE);
		}

		return;
	}
	/////////////////   人机模式结束   /////////////////////////



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
		// 如果在(0, 0)～(14, 14)范围内，且该坐标没有落子，
		// 则落子于此，否则发声警告并退出过程
		if (x < 0 || x > 14 || y < 0 || y > 14 || m_data[x][y] != -1)
		{
			MessageBeep(MB_OK);
			return;
		}
		else
		{
			// 如果位置合法，则落子
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
			//初始化并播放落子声音
			init();
			play();
		}
		// 开始等待
		m_bWait = TRUE;
		msg.msgType = MSG_PUTSTEP;
		pDlg->Send(&msg);
		
		if (rule.Win(m_color, msg.x, msg.y) == _WIN)
		{// 胜利
			pDlg->whoTurn = 4;
			pDlg->MessageBox(_T("恭喜，您获得了胜利！"), _T("胜利"), MB_ICONINFORMATION);
			pDlg->newhistory(_WIN);
			pDlg->SetMenuState(TRUE, 2);
			pDlg->SetMenuState(TRUE, 0);

			SetWait(TRUE);
		}
		else if (rule.Win(m_color, msg.x, msg.y) == _LOST)
		{//	出现禁手
			pDlg->whoTurn = 4;
			pDlg->MessageBox(_T("执黑禁手, 您输了！"), _T("失败"), MB_ICONINFORMATION);
			pDlg->newhistory(_LOST);
			pDlg->SetMenuState(TRUE, 2);
			pDlg->SetMenuState(TRUE, 0);

			SetWait(TRUE);
		}
	}

}

//////////////////////////////////////////////////////////////////////////
// 清空棋盘
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
	// 设置等待标志
	m_bWait = bWait;
	c = d = -1;
	a = b = -1;
	num = 0;
	quit = 0;
	CFiveChessDlg a;
	a.Invali();
}

//重载，用于悔棋后重绘棋盘，保留了已有m_data数据
void CBoard::Draw2()
{
	quit = 1;
	CFiveChessDlg a;
	a.Invali();
}

//////////////////////////////////////////////////////////////////////////
// 设置玩家颜色
//////////////////////////////////////////////////////////////////////////
void CBoard::SetColor(int color)
{
	m_color = color;
}

//////////////////////////////////////////////////////////////////////////
// 获取玩家颜色
//////////////////////////////////////////////////////////////////////////
int CBoard::GetColor() const
{
	return m_color;
}

//////////////////////////////////////////////////////////////////////////
// 设置等待标志
//////////////////////////////////////////////////////////////////////////
void CBoard::SetWait(BOOL bWait)
{
	m_bOldWait = m_bWait;
	m_bWait = bWait;
}

//////////////////////////////////////////////////////////////////////////
// 设置棋盘数据，并绘制棋子
//////////////////////////////////////////////////////////////////////////
void CBoard::SetData(int x, int y, int color)
{
	m_data[x][y] = color;
	num++;
	Draw(x, y, color);
}

//////////////////////////////////////////////////////////////////////////
// 在指定棋盘坐标处绘制指定颜色的棋子
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
// 接收来自对方的数据
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
		AfxGetMainWnd()->MessageBox(_T("接收数据时发生错误，请检查您的网络连接。"), _T("错误"), MB_ICONSTOP);
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
		if (IDYES == GetParent()->MessageBox(_T("对方请求和棋，接受这个请求吗？"),
			_T("和棋"), MB_ICONQUESTION | MB_YESNO))
		{
			// 发送允许和棋消息
			MSGSTRUCT msg;
			msg.msgType = MSG_AGREE_DRAW;
			pDlg->m_sock.Send((LPCVOID)&msg, sizeof(MSGSTRUCT));
			SetWait(TRUE);
			// 使“重玩”菜单生效
			pDlg->newhistory(MSG_AGREE_DRAW);
			pDlg->SetMenuState(TRUE, 2);
			pDlg->SetMenuState(TRUE, 0);
			pDlg->whoTurn = 0;
			SetWait(TRUE);
		}
		else
		{
			// 发送拒绝和棋消息
			MSGSTRUCT msg;
			msg.msgType = MSG_REFUSE_DRAW;
			pDlg->m_sock.Send((LPCVOID)&msg, sizeof(MSGSTRUCT));
		}
		break;
	case MSG_AGREE_DRAW:
		pDlg->whoTurn = 0;
		pDlg->MessageBox(_T("看来真是棋逢对手，对方接受了您的和棋请求。"), _T("和棋"), MB_ICONINFORMATION);
		// 和棋后，使“重玩”菜单生效
		pDlg->newhistory(MSG_AGREE_DRAW);
		pDlg->SetMenuState(TRUE, 2);
		pDlg->SetMenuState(TRUE, 0);
		SetWait(TRUE);
		break;
	case MSG_REFUSE_DRAW:
		pDlg->MessageBox(_T("看来对方很有信心取得胜利，所以拒绝了您的和棋请求。"),
			_T("和棋"), MB_ICONINFORMATION);
		RestoreWait();
		pDlg->SetMenuState(FALSE, 2);
		break;
	case MSG_BACK:
		if (IDYES == GetParent()->MessageBox(_T("对方请求悔棋，接受这个请求吗？"),
			_T("悔棋"), MB_ICONQUESTION | MB_YESNO))
		{
			// 发送允许悔棋消息
			MSGSTRUCT msg;
			msg.msgType = MSG_AGREE_BACK;
			pDlg->m_sock.Send((LPCVOID)&msg, sizeof(MSGSTRUCT));
			m_data[a][b] = -1;
			Draw2();
			pDlg->initSetTimer();//悔棋后重置计时器
			SetWait(TRUE);
			// 使“重玩”菜单生效
			//pDlg->SetMenuState(TRUE);
		}
		else
		{
			// 发送拒绝悔棋消息
			MSGSTRUCT msg;
			msg.msgType = MSG_REFUSE_BACK;
			pDlg->m_sock.Send((LPCVOID)&msg, sizeof(MSGSTRUCT));
		}
		break;
	case MSG_AGREE_BACK:
		pDlg->initSetTimer();//悔棋后重置计时器
		pDlg->MessageBox(_T("对方接受了您的悔棋请求。"), _T("悔棋"), MB_ICONINFORMATION);
		//清除上一步棋子数据
		m_data[a][b] = -1;
		Draw2();
		SetWait(FALSE);
		// 悔棋后，使“重玩”菜单生效
		//pDlg->SetMenuState(TRUE);
		break;
	case MSG_REFUSE_BACK:
		pDlg->MessageBox(_T("对方拒绝了您的悔棋请求。"),
			_T("悔棋"), MB_ICONINFORMATION);
		RestoreWait();
		pDlg->SetMenuState(FALSE, 2);
		break;
	case MSG_NEW_GAME:
		if (IDYES == GetParent()->MessageBox(_T("对方请求开始新游戏，接受这个请求吗？"),
			_T("新游戏"), MB_ICONQUESTION | MB_YESNO))
		{
			// 发送允许新游戏消息
			MSGSTRUCT msg;
			msg.msgType = MSG_AGREE_NEW;
			pDlg->m_sock.Send((LPCVOID)&msg, sizeof(MSGSTRUCT));
			//SetWait(TRUE);
			// 使“重玩”菜单失效,“悔棋”失效
			pDlg->SetMenuState(FALSE, 2);
			pDlg->SetMenuState(FALSE, 0);
			Clear(!(pDlg->m_isHost));
			pDlg->whoTurn = 3;
		}
		else
		{
			// 发送拒绝和棋消息
			MSGSTRUCT msg;
			msg.msgType = MSG_REFUSE_NEW;
			pDlg->m_sock.Send((LPCVOID)&msg, sizeof(MSGSTRUCT));
		}
		break;
	case MSG_AGREE_NEW:
		pDlg->MessageBox(_T("对方接受了您的请求。"), _T("新游戏"), MB_ICONINFORMATION);
		// 使“重玩”菜单失效,“悔棋”失效
		pDlg->SetMenuState(FALSE, 2);
		pDlg->SetMenuState(FALSE, 0);
		Clear(!(pDlg->m_isHost));
		pDlg->whoTurn = 3;
		break;
	case MSG_REFUSE_NEW:
		pDlg->MessageBox(_T("对方拒绝了您的请求。"), _T("新游戏"), MB_ICONINFORMATION);
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
// 和棋操作
//////////////////////////////////////////////////////////////////////////
void CBoard::DrawGame()
{
	CFiveChessDlg * pDlg = (CFiveChessDlg*)AfxGetMainWnd();
	// 设置等待标志
	SetWait(TRUE);
	MSGSTRUCT msg;
	msg.msgType = MSG_DRAW;
	pDlg->m_sock.Send((LPCVOID)&msg, sizeof(MSGSTRUCT));
}

//////////////////////////////////////////////////////////////////////////
// 处理对方落子后的工作
//////////////////////////////////////////////////////////////////////////
void CBoard::Over(int x, int y)
{
	CRule rule;
	CFiveChessDlg *pDlg = (CFiveChessDlg *)GetParent();
	// 判断对方是否胜利
	if (rule.Win(1 - m_color, x, y) == _WIN)
	{
		pDlg->whoTurn = 4;
		pDlg->MessageBox(_T("您输了，再接再厉吧！"), _T("失败"), MB_ICONINFORMATION);
		pDlg->newhistory(_LOST);
		// 如果是网络对战，则生效“重玩”
		if (pDlg->m_bIsConnect)
		{
			pDlg->SetMenuState(TRUE, 2);
			pDlg->SetMenuState(TRUE, 0);
			pDlg->whoTurn = 4;
		}
		SetWait(TRUE);
		return;
	}
	//判断对方是否出现禁手
	else if (rule.Win(1 - m_color, x, y) == _LOST)
	{
		pDlg->whoTurn = 4;
		pDlg->MessageBox(_T("恭喜您, 对方出现禁手输了！"), _T("胜利"), MB_ICONINFORMATION);
		pDlg->newhistory(_WIN);
		// 如果是网络对战，则生效“重玩”
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
//加载音频资源
////////////////////////////////////////////////////////////
bool CBoard::ExtractResource(LPCTSTR strDstFile, LPCTSTR strResType, LPCTSTR strResName)
{
	//中间调用函							  
	// 创建文件
	HANDLE hFile = ::CreateFile(strDstFile, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_TEMPORARY, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return false;

	// 查找资源文件中、加载资源到内存、得到资源大小
	HRSRC    hRes = ::FindResource(NULL, strResName, strResType);
	HGLOBAL    hMem = ::LoadResource(NULL, hRes);
	DWORD    dwSize = ::SizeofResource(NULL, hRes);

	// 写入文件
	DWORD dwWrite = 0;      // 返回写入字节
	::WriteFile(hFile, hMem, dwSize, &dwWrite, NULL);
	::CloseHandle(hFile);

	return true;
}

/////////////////////////////////////////////////////////////
//初始化落子音效
////////////////////////////////////////////////////////////
void CBoard::init()
{
	//初始化函数
	// 产生临时文件的文件名
	TCHAR tmpwav[_MAX_PATH];
	::GetTempPath(_MAX_PATH, tmpwav);
	_tcscat_s(tmpwav, _T("testapp_background.wav"));
	// 将wav 资源提取为临时文件
	ExtractResource(tmpwav, _T("WAVE"), MAKEINTRESOURCE(IDR_WAVE_BTNDOWN));
	// 打开音乐
	//TCHAR mcicmd[300];
	_stprintf_s(mcicmd, _T("open \"%s\" alias mymusic"), tmpwav);
}

/////////////////////////////////////////////////////////////
//播放落子音效
////////////////////////////////////////////////////////////
void CBoard::play()
{
	if (BtnDownFlg == TRUE)
	{
		mciSendString(_T("close mymusic"), NULL, 0, NULL);//先关再开，注意顺序！！！
		mciSendString(mcicmd, NULL, 0, NULL);
		mciSendString(_T("play mymusic"), NULL, 0, NULL);
	}
}

//////////////////////////////////////////////////////////////////////////
// 重新设置先前的等待标志
//////////////////////////////////////////////////////////////////////////
void CBoard::RestoreWait()
{
	SetWait(m_bOldWait);
}
