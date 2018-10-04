#ifndef __CONNECT_DATA_H__
#define __CONNECT_DATA_H__

// 落子消息
#define MSG_PUTSTEP     0x01
// 和棋请求消息
#define MSG_DRAW        0x02
// 同意和棋消息
#define MSG_AGREE_DRAW	0x03
// 拒绝和棋消息
#define MSG_REFUSE_DRAW	0x04
// 其他消息
#define MSG_EXTERN		0x05
//悔棋请求消息
#define MSG_BACK		0x06
//同意悔棋消息
#define MSG_AGREE_BACK	0x07
//拒绝悔棋消息
#define MSG_REFUSE_BACK	0x08
//新游戏请求
#define MSG_NEW_GAME	0x09
//同意开始新游戏
#define MSG_AGREE_NEW	0x0A
//拒绝开始新游戏
#define MSG_REFUSE_NEW	0x0B
//查看历史请求
#define MSG_SEE_HISTORY 0x0C
//同意查看历史
#define MSG_AREE_SEE   0X0E

typedef struct _tagMsgStruct {
	USHORT len;
	// 消息ID
	BYTE msgType;
	// 落子信息
	int x;
	int y;
	int color;
	//历史成绩
	int win;
	int lost;
	int draw;
	// 其他消息内容
	BYTE byMsg[128] = { 0 };

} MSGSTRUCT;

#endif