////////////////////////////////////////////////
// iocpserver.cpp�ļ�
#include "stdafx.h"

// CIOCPServer��Ĳ��Գ���

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
		//printf(" ���յ�һ���µ����ӣ�%d���� %s \n", 
		//			GetCurrentConnection(), ::inet_ntoa(pContext->addrRemote.sin_addr));
		char *pchar = ::inet_ntoa(pContext->addrRemote.sin_addr);
		TCHAR lpwszStr[100] ;
		DWORD dwMinSize = MultiByteToWideChar(CP_ACP, 0, pchar, -1, NULL, 0);
		MultiByteToWideChar(CP_ACP, 0, pchar, -1, lpwszStr, dwMinSize);

		CString sz;
		sz.Format(_T(" ���յ�һ���µ����ӣ�%d���� %s \n"), GetCurrentConnection(), lpwszStr);
		PTCHAR psz = sz.GetBuffer();
		m_pView->ShowMsgOnListCtrl(&sz);

		SendText(pContext, pBuffer->buff, pBuffer->nLen);
	}

	void OnConnectionClosing(CIOCPContext *pContext, CIOCPBuffer *pBuffer)
	{
		//printf(" һ�����ӹرգ� \n" );
		CString sz;
		sz.Format(_T("һ�����ӹرգ� \n"));
		m_pView->ShowMsgOnListCtrl(&sz);
	}

	void OnConnectionError(CIOCPContext *pContext, CIOCPBuffer *pBuffer, int nError)
	{
		//printf(" һ�����ӷ������� %d \n ", nError);
		CString sz;
		sz.Format(_T("һ�����ӷ������� %d \n"), nError);
		m_pView->ShowMsgOnListCtrl(&sz);
	}

	void OnReadCompleted(CIOCPContext *pContext, CIOCPBuffer *pBuffer)
	{
		//SendText(pContext, pBuffer->buff, pBuffer->nLen);//����
		TCHAR lpwszStr[200];
		DWORD dwMinSize = MultiByteToWideChar(CP_ACP, 0, pBuffer->buff, -1, NULL, 0);
		MultiByteToWideChar(CP_ACP, 0, pBuffer->buff, -1, lpwszStr, dwMinSize);
		CString sz;
		sz.Format(_T("�յ��ͻ�������12345 ��%s \n"), lpwszStr);
		TCHAR *pt = sz.GetBuffer();
		m_pView->ShowMsgOnListCtrl(&sz);
	}
	
	void OnWriteCompleted(CIOCPContext *pContext, CIOCPBuffer *pBuffer)
	{
		//printf(" ���ݷ��ͳɹ���\n ");
		CString sz;
		sz.Format(_T("���ݷ��ͳɹ���\n"));
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

	// ��������
	if(pServer->Start())
	{
		//((CMFC__IOCPView *)lpParameter)->m_List.InsertItem(0, _T("�����������ɹ�... \n"));
		CString sz;
		sz.Format(_T("�����������ɹ�... \n"));
		((CMFC__IOCPView *)lpParameter)->ShowMsgOnListCtrl(&sz);
	}
	else
	{
		//((CMFC__IOCPView *)lpParameter)->m_List.InsertItem(0, _T("����������ʧ�ܣ�\n"));
		CString sz;
		sz.Format(_T("����������ʧ�ܣ�\n"));
		((CMFC__IOCPView *)lpParameter)->ShowMsgOnListCtrl(&sz);
		return 0;
	}

	//// �����¼�������ServerShutdown�����ܹ��ر��Լ�
	//HANDLE hEvent = ::CreateEvent(NULL, FALSE, FALSE, _T("ShutdownEvent"));
	//::WaitForSingleObject(hEvent, INFINITE);
	//::CloseHandle(hEvent);

	//// �رշ���
	//pServer->Shutdown();
	//delete pServer;

	//((CMFC__IOCPView *)lpParameter)->m_List.InsertItem(0, _T("�������ر� \n"));
	return 0;
}

 DWORD WINAPI close(LPVOID lpParameter)
 {
	 //pServer->Shutdown();
	 delete pServer;

	 //((CMFC__IOCPView *)lpParameter)->m_List.InsertItem(0, _T("�������ر� \n"));
	 CString sz;
	 sz.Format(_T("�������ر� \n"));
	 ((CMFC__IOCPView *)lpParameter)->ShowMsgOnListCtrl(&sz);
	 return 0;
 }
