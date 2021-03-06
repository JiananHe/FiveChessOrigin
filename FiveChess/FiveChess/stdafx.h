#pragma once
#include <afxcontrolbars.h>
#include <afxcontrolbars.h>
// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__8E3D8C5D_95B4_4E18_A7C7_6CD0DF5A63AD__INCLUDED_)
#define AFX_STDAFX_H__8E3D8C5D_95B4_4E18_A7C7_6CD0DF5A63AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxsock.h>		// MFC socket extensions

// 棋盘数据
extern int m_data[15][15];

// 落子声音开关
extern BOOL BtnDownFlg;

// 落子声音开关
extern BOOL BackmusicFlg;

//背景
extern int backint;

//记录上一步坐标，用于悔棋
extern int m_backX, m_backY;

//人机标识
extern BOOL isCompter;

//棋子标识
const int BLACK = 0;
const int WHITE = 1;
const int BLACK2 = 2;
const int WHITE2 = 3;
const int QUIT = 4;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__8E3D8C5D_95B4_4E18_A7C7_6CD0DF5A63AD__INCLUDED_)
