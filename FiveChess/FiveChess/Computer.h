#pragma once
class Computer
{
public:
	Computer();
	~Computer();

	//���㲢���ص�����Ԫ�����
	int countScore(int numOfBlack, int numOfWhite, int numOfEmpty);
	//���㲢����m_data[m_data_x][m_data_y]��������
	int Score(int m_data_x, int m_data_y);
	//���ؼ��������λ��
	void computerPoint(int &x, int &y);
	//��������
	int scoreData[15][15] = { 0 };


	//���ֱ�(������⣬δʹ�ø�����)
	const int ScoreTable[11] =
	{
		7,		//��Ԫ��Ϊ��
		35,		//B
		800,	//BB
		15000,	//BBB
		800000,	//BBBB
		15,		//W
		400,	//WW
		1800,	//WWW
		100000,	//WWWW
		0,		//��Ԫ�鲻����
		0		//��Ԫ���������һ��������ɫ������
	};
};

