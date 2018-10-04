#ifndef __BOARD_H__
#define __BOARD_H__

#include "stdafx.h"
#include "Rule.h"

class CBoard :public CWnd, public CRule
{
private:
	CImageList m_iml; // 棋子图像
	int m_color; // 玩家颜色
	int quit = 0;//是否调用悔棋函数
	int num = 0;
	BOOL m_bWait; // 等待标志
	BOOL m_bOldWait;	//原来的等待状态
	TCHAR mcicmd[300];	//用于落子声音
public:
	int a = -1;//最新一步棋子坐标
	int b = -1;
	int c = -1;//先前一步棋子坐标
	int d = -1;

public:
	CBoard();
	virtual ~CBoard();
	void RestoreWait();			//恢复之前的等待状态
	void Clear(BOOL bWait);	//清空棋盘，并设置等待状态
	void SetColor(int color);	//设置棋子颜色
	int  GetColor() const;		//获取当前颜色
	void SetWait(BOOL bWait);	//设置等待状态
	void SetData(int x, int y, int color);//设置棋盘数据
	void DrawGame();			//和棋函数
	void Draw(int x, int y, int color);//绘制棋子
	void Receive();				//接收到消息后处理
	void Over(int x, int y);	//处理落子后工作
	bool ExtractResource(LPCTSTR strDstFile, LPCTSTR strResType, LPCTSTR strResName);
	//用于落子声音初始化
	void init();				//初始化落子声音
	void play();				//播放落子声音
	void Draw2();
	//重载，用于悔棋后重绘棋盘，保留了已有m_data数据
protected:
	afx_msg void OnPaint();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//鼠标左键点击事件处理函数
	DECLARE_MESSAGE_MAP()
};

#endif