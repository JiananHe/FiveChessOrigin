#include "stdafx.h"
#include "Computer.h"
#include "FiveChessDlg.h"


Computer::Computer()
{
}


Computer::~Computer()
{
}


//返回单个五元组分数
int Computer::countScore(int numOfBlack, int numOfWhite, int numOfEmpty)
{
	if ((numOfBlack + numOfWhite + numOfEmpty) < 5)
		return 0;
	if (numOfBlack == 0)
	{
		switch (numOfWhite)
		{
		case 1://W
			return 15;
		case 2://WW
			return 400;
		case 3://WWW
			return 1800;
		case 4://WWWW
			return 200000;
		default:
			return 0;
		}
	}
	else if (numOfWhite == 0)
	{
		switch (numOfBlack)
		{
		case 1://B
			return 35;
		case 2://BB
			return 800;
		case 3://BBB
			return 15000;
		case 4://BBBB
			return 1000000;
		default:
			return 0;
		}
	}
	return 0;
}


//返回m_data[m_data_x][m_data_y]的总评分
int Computer::Score(int m_data_x, int m_data_y)
{
	int x = 0, y = 0;
	int numOfBlack = 0;		//五元组中黑棋数量
	int numOfWhite = 0;		//五元组中白棋数量
	int numOfEmpty = 0;		//五元组中空棋数量

							//统计“|”方向
	for (y = (m_data_y >= 4) ? m_data_y - 4 : 0; y <= m_data_y; y++)
	{
		for (int i = 0; i < 5 && y + i < 15; i++)
		{
			if (m_data[m_data_x][y + i] == WHITE)
				numOfWhite++;
			else if (m_data[m_data_x][y + i] == BLACK)
				numOfBlack++;
			else if (m_data[m_data_x][y + i] == -1)
				numOfEmpty++;
		}
		scoreData[m_data_x][m_data_y] += countScore(numOfBlack, numOfWhite, numOfEmpty);
		numOfBlack = 0;
		numOfWhite = 0;
		numOfEmpty = 0;
	}


	//统计“——”方向
	for (x = (m_data_x >= 4) ? m_data_x - 4 : 0; x <= m_data_x; x++)
	{
		for (int i = 0; i < 5 && (x + i) < 15; i++)
		{
			if (m_data[x + i][m_data_y] == WHITE)
				numOfWhite++;
			else if (m_data[x + i][m_data_y] == BLACK)
				numOfBlack++;
			else if (m_data[x + i][m_data_y] == -1)
				numOfEmpty++;
		}
		scoreData[m_data_x][m_data_y] += countScore(numOfBlack, numOfWhite, numOfEmpty);
		numOfBlack = 0;
		numOfWhite = 0;
		numOfEmpty = 0;
	}

	//统计“\"方向
	if (m_data_x <= m_data_y)
	{
		x = (m_data_x >= 4) ? m_data_x - 4 : 0;
		y = m_data_y - (m_data_x - x);
	}
	else
	{
		y = (m_data_y >= 4) ? m_data_y - 4 : 0;
		x = m_data_x - (m_data_y - y);
	}
	for (; x <= m_data_x && y <= m_data_y; x++, y++)
	{
		for (int i = 0; i < 5 && (x + i) < 15 && (y + i) < 15; i++)
		{
			if (m_data[x + i][y + i] == WHITE)
				numOfWhite++;
			else if (m_data[x + i][y + i] == BLACK)
				numOfBlack++;
			else if (m_data[x + i][y + i] == -1)
				numOfEmpty++;
		}
		scoreData[m_data_x][m_data_y] += countScore(numOfBlack, numOfWhite, numOfEmpty);
		numOfBlack = 0;
		numOfWhite = 0;
		numOfEmpty = 0;
	}


	//统计“/”方向
	if (m_data_x <= (14 - m_data_y))
	{
		x = (m_data_x >= 4) ? m_data_x - 4 : 0;
		y = m_data_y - (x - m_data_x);
	}
	else
	{
		y = (m_data_y <= 10) ? m_data_y + 4 : 14;
		x = m_data_x - (y - m_data_y);
	}
	for (; x <= m_data_x && y >= m_data_y; x++, y--)
	{
		for (int i = 0; i < 5 && (x + i) < 15 && (y - i) >= 0; i++)
		{
			if (m_data[x + i][y - i] == WHITE)
				numOfWhite++;
			else if (m_data[x + i][y - i] == BLACK)
				numOfBlack++;
			else if (m_data[x + i][y - i] == -1)
				numOfEmpty++;
		}
		scoreData[m_data_x][m_data_y] += countScore(numOfBlack, numOfWhite, numOfEmpty);
		numOfBlack = 0;
		numOfWhite = 0;
		numOfEmpty = 0;
	}

	return scoreData[m_data_x][m_data_y];
}


//返回电脑落子坐标
void Computer::computerPoint(int &x, int &y)
{
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if (m_data[i][j] != -1)
				continue;
			scoreData[i][j] = Score(i, j);
		}
	}

	int maxScore = 0;
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if (maxScore < scoreData[i][j] && m_data[i][j] == -1)
			{
				maxScore = scoreData[i][j];
				x = i;
				y = j;
			}
		}
	}
}


