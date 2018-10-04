#ifndef __CONNECT_DATA_H__
#define __CONNECT_DATA_H__

// ������Ϣ
#define MSG_PUTSTEP     0x01
// ����������Ϣ
#define MSG_DRAW        0x02
// ͬ�������Ϣ
#define MSG_AGREE_DRAW	0x03
// �ܾ�������Ϣ
#define MSG_REFUSE_DRAW	0x04
// ������Ϣ
#define MSG_EXTERN		0x05
//����������Ϣ
#define MSG_BACK		0x06
//ͬ�������Ϣ
#define MSG_AGREE_BACK	0x07
//�ܾ�������Ϣ
#define MSG_REFUSE_BACK	0x08
//����Ϸ����
#define MSG_NEW_GAME	0x09
//ͬ�⿪ʼ����Ϸ
#define MSG_AGREE_NEW	0x0A
//�ܾ���ʼ����Ϸ
#define MSG_REFUSE_NEW	0x0B
//�鿴��ʷ����
#define MSG_SEE_HISTORY 0x0C
//ͬ��鿴��ʷ
#define MSG_AREE_SEE   0X0E

typedef struct _tagMsgStruct {
	USHORT len;
	// ��ϢID
	BYTE msgType;
	// ������Ϣ
	int x;
	int y;
	int color;
	//��ʷ�ɼ�
	int win;
	int lost;
	int draw;
	// ������Ϣ����
	BYTE byMsg[128] = { 0 };

} MSGSTRUCT;

#endif