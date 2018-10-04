#ifndef __CONNECT_H__
#define __CONNECT_H__

#include <afxsock.h>

class CConnect : public CAsyncSocket
{
public:
	CConnect();				//���캯��
	virtual ~CConnect();	//��������
							// Implementation
	virtual void OnAccept(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
};

#endif