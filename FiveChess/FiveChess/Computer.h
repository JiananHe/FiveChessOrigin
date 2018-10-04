#pragma once
class Computer
{
public:
	Computer();
	~Computer();

	//计算并返回单个五元组分数
	int countScore(int numOfBlack, int numOfWhite, int numOfEmpty);
	//计算并返回m_data[m_data_x][m_data_y]的总评分
	int Score(int m_data_x, int m_data_y);
	//返回计算机落子位置
	void computerPoint(int &x, int &y);
	//分数储存
	int scoreData[15][15] = { 0 };


	//评分表(辅助理解，未使用该数组)
	const int ScoreTable[11] =
	{
		7,		//五元组为空
		35,		//B
		800,	//BB
		15000,	//BBB
		800000,	//BBBB
		15,		//W
		400,	//WW
		1800,	//WWW
		100000,	//WWWW
		0,		//五元组不存在
		0		//五元组包含至少一颗其他颜色的棋子
	};
};

