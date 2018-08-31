////////////////////////////////////////////////
// iocpserver.cpp文件
#include "stdafx.h"

// CIOCPServer类的测试程序

#include "iocp.h"
#include <stdio.h>
#include <windows.h>
#include "../MFC__IOCPView.h"
BOOL MByteToWChar(LPCSTR lpcszStr, LPWSTR lpwszStr, DWORD dwSize)
{
	// Get the required size of the buffer that receives the Unicode
	// string.
	DWORD dwMinSize;
	dwMinSize = MultiByteToWideChar(CP_ACP, 0, lpcszStr, -1, NULL, 0);

	if (dwSize < dwMinSize)
	{
		return FALSE;
	}
	// Convert headers from ASCII to Unicode.
	MultiByteToWideChar(CP_ACP, 0, lpcszStr, -1, lpwszStr, dwMinSize);
	return TRUE;
}

class CMyServer : public CIOCPServer
{
public:
	CMyServer(void *p)
	{
		m_pView = (CMFC__IOCPView *)p;
	}
	void OnConnectionEstablished(CIOCPContext *pContext, CIOCPBuffer *pBuffer)
	{
		//printf(" 接收到一个新的连接（%d）： %s \n", 
		//			GetCurrentConnection(), ::inet_ntoa(pContext->addrRemote.sin_addr));
		char *pchar = ::inet_ntoa(pContext->addrRemote.sin_addr);
		TCHAR lpwszStr[100] ;
		DWORD dwMinSize = MultiByteToWideChar(CP_ACP, 0, pchar, -1, NULL, 0);
		MultiByteToWideChar(CP_ACP, 0, pchar, -1, lpwszStr, dwMinSize);

		CString sz;
		sz.Format(_T(" 接收到一个新的连接（%d）： %s \n"), GetCurrentConnection(), lpwszStr);
		PTCHAR psz = sz.GetBuffer();
		m_pView->ShowMsgOnListCtrl(&sz);

		SendText(pContext, pBuffer->buff, pBuffer->nLen);
	}

	void OnConnectionClosing(CIOCPContext *pContext, CIOCPBuffer *pBuffer)
	{
		//printf(" 一个连接关闭！ \n" );
		CString sz;
		sz.Format(_T("一个连接关闭！ \n"));
		m_pView->ShowMsgOnListCtrl(&sz);
	}

	void OnConnectionError(CIOCPContext *pContext, CIOCPBuffer *pBuffer, int nError)
	{
		//printf(" 一个连接发生错误： %d \n ", nError);
		CString sz;
		sz.Format(_T("一个连接发生错误： %d \n"), nError);
		m_pView->ShowMsgOnListCtrl(&sz);
	}

	void OnReadCompleted(CIOCPContext *pContext, CIOCPBuffer *pBuffer)
	{
		//SendText(pContext, pBuffer->buff, pBuffer->nLen);//回显
		TCHAR lpwszStr[200];
		DWORD dwMinSize = MultiByteToWideChar(CP_ACP, 0, pBuffer->buff, -1, NULL, 0);
		MultiByteToWideChar(CP_ACP, 0, pBuffer->buff, -1, lpwszStr, dwMinSize);
		CString sz;
		sz.Format(_T("收到客户端数据12345 ：%s \n"), lpwszStr);
		TCHAR *pt = sz.GetBuffer();
		m_pView->ShowMsgOnListCtrl(&sz);
	}
	
	void OnWriteCompleted(CIOCPContext *pContext, CIOCPBuffer *pBuffer)
	{
		//printf(" 数据发送成功！\n ");
		CString sz;
		sz.Format(_T("数据发送成功！\n"));
		m_pView->ShowMsgOnListCtrl(&sz);
	}
};
CMyServer *pServer;
 DWORD WINAPI start(LPVOID lpParameter)
{
	//int a = 99;
	//CString sz;
	//sz.Format(_T("ssss%d\n"), a);
	//((CMFC__IOCPView *)lpParameter)->ShowMsgOnListCtrl(&sz);
	//return 0;
	pServer = new CMyServer(lpParameter);

	// 开启服务
	if(pServer->Start())
	{
		//((CMFC__IOCPView *)lpParameter)->m_List.InsertItem(0, _T("服务器开启成功... \n"));
		CString sz;
		sz.Format(_T("服务器开启成功... \n"));
		((CMFC__IOCPView *)lpParameter)->ShowMsgOnListCtrl(&sz);
	}
	else
	{
		//((CMFC__IOCPView *)lpParameter)->m_List.InsertItem(0, _T("服务器开启失败！\n"));
		CString sz;
		sz.Format(_T("服务器开启失败！\n"));
		((CMFC__IOCPView *)lpParameter)->ShowMsgOnListCtrl(&sz);
		return 0;
	}

	//// 创建事件对象，让ServerShutdown程序能够关闭自己
	//HANDLE hEvent = ::CreateEvent(NULL, FALSE, FALSE, _T("ShutdownEvent"));
	//::WaitForSingleObject(hEvent, INFINITE);
	//::CloseHandle(hEvent);

	//// 关闭服务
	//pServer->Shutdown();
	//delete pServer;

	//((CMFC__IOCPView *)lpParameter)->m_List.InsertItem(0, _T("服务器关闭 \n"));
	return 0;
}

 DWORD WINAPI close(LPVOID lpParameter)
 {
	 //pServer->Shutdown();
	 delete pServer;

	 //((CMFC__IOCPView *)lpParameter)->m_List.InsertItem(0, _T("服务器关闭 \n"));
	 CString sz;
	 sz.Format(_T("服务器关闭 \n"));
	 ((CMFC__IOCPView *)lpParameter)->ShowMsgOnListCtrl(&sz);
	 return 0;
 }
