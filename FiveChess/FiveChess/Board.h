#ifndef __BOARD_H__
#define __BOARD_H__

#include "stdafx.h"
#include "Rule.h"

class CBoard :public CWnd, public CRule
{
private:
	CImageList m_iml; // ����ͼ��
	int m_color; // �����ɫ
	int quit = 0;//�Ƿ���û��庯��
	int num = 0;
	BOOL m_bWait; // �ȴ���־
	BOOL m_bOldWait;	//ԭ���ĵȴ�״̬
	TCHAR mcicmd[300];	//������������
public:
	int a = -1;//����һ����������
	int b = -1;
	int c = -1;//��ǰһ����������
	int d = -1;

public:
	CBoard();
	virtual ~CBoard();
	void RestoreWait();			//�ָ�֮ǰ�ĵȴ�״̬
	void Clear(BOOL bWait);	//������̣������õȴ�״̬
	void SetColor(int color);	//����������ɫ
	int  GetColor() const;		//��ȡ��ǰ��ɫ
	void SetWait(BOOL bWait);	//���õȴ�״̬
	void SetData(int x, int y, int color);//������������
	void DrawGame();			//���庯��
	void Draw(int x, int y, int color);//��������
	void Receive();				//���յ���Ϣ����
	void Over(int x, int y);	//�������Ӻ���
	bool ExtractResource(LPCTSTR strDstFile, LPCTSTR strResType, LPCTSTR strResName);
	//��������������ʼ��
	void init();				//��ʼ����������
	void play();				//������������
	void Draw2();
	//���أ����ڻ�����ػ����̣�����������m_data����
protected:
	afx_msg void OnPaint();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//����������¼�������
	DECLARE_MESSAGE_MAP()
};

#endif