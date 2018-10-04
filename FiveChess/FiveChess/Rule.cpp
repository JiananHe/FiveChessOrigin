#include "stdafx.h"
#include "Rule.h"

#define NONE -1

//////////////////////////////////////////////////////////////////////////
// 禁手判断接口函数
//////////////////////////////////////////////////////////////////////////
bool CRule::Ban(int x, int y, int color)
{
	int adjsame[8] = { 0 };//记录与（x,y）相邻连续黑色棋子
	int adjempty[8] = { 0 };//记录与（x,y）相邻连续空白
	int jumpsame[8] = { 0 };//记录adiempty后连续黑色棋子
	int jumpempty[8] = { 0 };//记录jumpsame后的空白
	int jumpjumpsame[8] = { 0 };//记录jumpempty后连续黑子
	int _y;
	int _x;
	//统计左边
	for (_x = x - 1; _x >= 0 && m_data[_x][y] == BLACK; adjsame[0]++, _x--);
	for (; _x >= 0 && m_data[_x][y] == -1; adjempty[0]++, _x--);
	for (; _x >= 0 && m_data[_x][y] == BLACK; jumpsame[0]++, _x--);
	for (; _x >= 0 && m_data[_x][y] == -1; jumpempty[0]++, _x--);
	for (; _x >= 0 && m_data[_x][y] == BLACK; jumpjumpsame[0]++, _x--);
	//统计右边
	for (_x = x + 1; _x < 15 && m_data[_x][y] == BLACK; adjsame[4]++, _x++);
	for (; _x < 15 && m_data[_x][y] == -1; adjempty[4]++, _x++);
	for (; _x < 15 && m_data[_x][y] == BLACK; jumpsame[4]++, _x++);
	for (; _x < 15 && m_data[_x][y] == -1; jumpempty[4]++, _x++);
	for (; _x < 15 && m_data[_x][y] == BLACK; jumpjumpsame[4]++, _x++);
	//统计上方
	for (_y = y - 1; _y >= 0 && m_data[x][_y] == BLACK; adjsame[1]++, _y--);
	for (; _y >= 0 && m_data[x][_y] == -1; adjempty[1]++, _y--);
	for (; _y >= 0 && m_data[x][_y] == BLACK; jumpsame[1]++, _y--);
	for (; _y >= 0 && m_data[x][_y] == -1; jumpempty[1]++, _y--);
	for (; _y >= 0 && m_data[x][_y] == BLACK; jumpjumpsame[1]++, _y--);
	//统计下方
	for (_y = y + 1; _y < 15 && m_data[x][_y] == BLACK; adjsame[5]++, _y++);
	for (; _y < 15 && m_data[x][_y] == -1; adjempty[5]++, _y++);
	for (; _y < 15 && m_data[x][_y] == BLACK; jumpsame[5]++, _y++);
	for (; _y < 15 && m_data[x][_y] == -1; jumpempty[5]++, _y++);
	for (; _y < 15 && m_data[x][_y] == BLACK; jumpjumpsame[5]++, _y++);
	//统计右上
	for (_x = x + 1, _y = y - 1; _x < 15 && _y >= 0 && m_data[_x][_y] == BLACK; adjsame[2]++, _x++, _y--);
	for (; _x < 15 && _y >= 0 && m_data[_x][_y] == -1; adjempty[2]++, _x++, _y--);
	for (; _x < 15 && _y >= 0 && m_data[_x][_y] == BLACK; jumpsame[2]++, _x++, _y--);
	for (; _x < 15 && _y >= 0 && m_data[_x][_y] == -1; jumpempty[2]++, _x++, _y--);
	for (; _x < 15 && _y >= 0 && m_data[_x][_y] == BLACK; jumpjumpsame[2]++, _x++, _y--);
	//统计左下
	for (_x = x - 1, _y = y + 1; _x >= 0 && _y < 15 && m_data[_x][_y] == BLACK; adjsame[6]++, _x--, _y++);
	for (; _x >= 0 && _y < 15 && m_data[_x][_y] == -1; adjempty[6]++, _x--, _y++);
	for (; _x >= 0 && _y < 15 && m_data[_x][_y] == BLACK; jumpsame[6]++, _x--, _y++);
	for (; _x >= 0 && _y < 15 && m_data[_x][_y] == -1; jumpempty[6]++, _x--, _y++);
	for (; _x >= 0 && _y < 15 && m_data[_x][_y] == BLACK; jumpjumpsame[6]++, _x--, _y++);
	//统计左上
	for (_x = x - 1, _y = y - 1; _x >= 0 && _y >= 0 && m_data[_x][_y] == BLACK; adjsame[3]++, _x--, _y--);
	for (; _x >= 0 && _y >= 0 && m_data[_x][_y] == -1; adjempty[3]++, _x--, _y--);
	for (; _x >= 0 && _y >= 0 && m_data[_x][_y] == BLACK; jumpsame[3]++, _x--, _y--);
	for (; _x >= 0 && _y >= 0 && m_data[_x][_y] == -1; jumpempty[3]++, _x--, _y--);
	for (; _x >= 0 && _y >= 0 && m_data[_x][_y] == BLACK; jumpjumpsame[3]++, _x--, _y--);
	//统计右下
	for (_x = x + 1, _y = y + 1; _x < 15 && _y < 15 && m_data[_x][_y] == BLACK; adjsame[7]++, _x++, _y++);
	for (; _x < 15 && _y < 15 && m_data[_x][_y] == -1; adjempty[7]++, _x++, _y++);
	for (; _x < 15 && _y < 15 && m_data[_x][_y] == BLACK; jumpsame[7]++, _x++, _y++);
	for (; _x < 15 && _y < 15 && m_data[_x][_y] == -1; jumpempty[7]++, _x++, _y++);
	for (; _x < 15 && _y < 15 && m_data[_x][_y] == BLACK; jumpjumpsame[7]++, _x++, _y++);
	//统计结束

	//检查是否超过连五
	for (int i2 = 0; i2 < 4; i2++)
	{
		if (adjsame[i2] + adjsame[i2 + 4] >= 5)
			return true;
	}

	//类型统计
	int three = 0;
	int four = 0;

	for (int i = 0; i < 4; i++)
	{
		//?0000?
		if (adjsame[i] + adjsame[i + 4] == 3)
		{
			if (adjempty[i] > 1 || adjempty[i + 4] > 1)
			{
				four++;
			}
		}

		//?000?
		if (adjsame[i] + adjsame[i + 4] == 2)
		{//？0+000+？||?000+0?
			if (adjempty[i] == 1 && jumpsame[i] == 1)
			{
				four++;
			}
			if (adjempty[i + 4] == 1 && jumpsame[i + 4] == 1)
			{
				four++;
			}
			//?++000+?||?+000++?
			if (((adjempty[i] > 2 || (adjempty[2] == 2 && jumpsame[i] == 0)) && (adjempty[i + 4] > 1 || (adjempty[i + 4] == 1 && jumpsame[i + 4] == 0)))
				|| ((adjempty[i + 4] > 2 || (adjempty[i + 4] == 2 && jumpsame[i + 4] == 0)) && (adjempty[i] > 1 || (adjempty[i] == 1 && jumpsame[i] == 0))))
			{
				three++;
			}
		}
		//?00?
		if (adjsame[i] + adjsame[i + 4] == 1)
		{//?00+00?
			if (adjempty[i] == 1 && jumpsame[i] == 2)
			{
				four++;
			}
			if (adjempty[i + 4] == 1 && jumpsame[i + 4] == 2)
			{
				four++;
			}
			//?+00+0+?||?+0+00+?
			if (adjempty[i] == 1 && jumpsame[i] == 1 && (jumpempty[i] >1 || (jumpempty[i] == 1 && jumpjumpsame[i] == 0))
				&& (adjempty[i + 4]>1 || (adjempty[i + 4] == 1 && jumpsame[i + 4] == 0)))
			{
				three++;
			}
			if (adjempty[i + 4] == 1 && jumpsame[i + 4] == 1 && (jumpempty[i + 4] >1 || (jumpempty[i + 4] == 1 && jumpjumpsame[i + 4] == 0))
				&& (adjempty[i]>1 || (adjempty[i] == 1 && jumpsame[i] == 0)))
			{
				three++;
			}
		}
		//?0?
		if (adjsame[i] + adjsame[i + 4] == 0)
		{
			//?000+0?
			if (adjempty[i] == 0 && jumpsame[i] == 3)
			{
				four++;
			}
			if (adjempty[i + 4] == 0 && jumpsame[i + 4] == 3)
			{
				four++;
			}
			//?+0+00+?||?+00+0+?
			if (adjempty[i] == 1 && jumpsame[i] == 2 && (jumpempty[i] > 1 || (jumpempty[i] == 1 && jumpjumpsame[i] == 0))
				&& (adjempty[i + 4] > 1 || (adjempty[i + 4] == 1 && jumpsame[i + 4] == 0)))
			{
				three++;
			}
			if (adjempty[i + 4] == 1 && jumpsame[i + 4] == 2 && (jumpempty[i + 4] > 1 || (jumpempty[i + 4] == 1 && jumpjumpsame[i + 4] == 0))
				&& (adjempty[i] > 1 || (adjempty[i] == 1 && jumpsame[i] == 0)))
			{
				three++;
			}
		}
	}
	if (four >= 2)
	{
		return TRUE;
	}
	if (three >= 2)
	{
		return TRUE;
	}
	return FALSE;
}
//////////////////////////////////////////////////////////////////////////
// 连五判断
// 返回 0 为胜利 1为禁手 2为无状态
//////////////////////////////////////////////////////////////////////////
int CRule::Win(int color, int xpos, int ypos)
{
	int x, y;
	if (color == BLACK)
	{
		if (Ban(xpos, ypos, color))
		{
			return _LOST;
		}
	}
	// 判断横向
	for (y = 0; y < 15; y++)
	{
		for (x = 0; x < 11; x++)
		{
			if (color == m_data[x][y] && color == m_data[x + 1][y] &&
				color == m_data[x + 2][y] && color == m_data[x + 3][y] &&
				color == m_data[x + 4][y])
			{
				return _WIN;
			}
		}
	}
	// 判断纵向
	for (y = 0; y < 11; y++)
	{
		for (x = 0; x < 15; x++)
		{
			if (color == m_data[x][y] && color == m_data[x][y + 1] &&
				color == m_data[x][y + 2] && color == m_data[x][y + 3] &&
				color == m_data[x][y + 4])
			{
				return _WIN;
			}
		}
	}
	// 判断“\”方向
	for (y = 0; y < 11; y++)
	{
		for (x = 0; x < 11; x++)
		{
			if (color == m_data[x][y] && color == m_data[x + 1][y + 1] &&
				color == m_data[x + 2][y + 2] && color == m_data[x + 3][y + 3] &&
				color == m_data[x + 4][y + 4])
			{
				return _WIN;
			}
		}
	}
	// 判断“/”方向
	for (y = 0; y < 11; y++)
	{
		for (x = 4; x < 15; x++)
		{
			if (color == m_data[x][y] && color == m_data[x - 1][y + 1] &&
				color == m_data[x - 2][y + 2] && color == m_data[x - 3][y + 3] &&
				color == m_data[x - 4][y + 4])
			{
				return _WIN;
			}
		}
	}


	return _OTHER;
}

