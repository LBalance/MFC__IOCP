
// MFC__IOCPView.cpp : CMFC__IOCPView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "MFC__IOCP.h"
#endif

#include "MFC__IOCPDoc.h"
#include "MFC__IOCPView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFC__IOCPView

IMPLEMENT_DYNCREATE(CMFC__IOCPView, CView)

BEGIN_MESSAGE_MAP(CMFC__IOCPView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(2, OnStartServer)
	ON_COMMAND(3, OnStopServer)
	ON_COMMAND(4, OnStartClent)
END_MESSAGE_MAP()

// CMFC__IOCPView ����/����

CMFC__IOCPView::CMFC__IOCPView()
{
	// TODO: �ڴ˴���ӹ������
	m_nNumOfMsg = 0;
	::InitializeCriticalSection(&m_ListLock);
}

CMFC__IOCPView::~CMFC__IOCPView()
{
	::DeleteCriticalSection(&m_ListLock);
}

BOOL CMFC__IOCPView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CMFC__IOCPView ����

void CMFC__IOCPView::OnDraw(CDC* /*pDC*/)
{
	CMFC__IOCPDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}

void CMFC__IOCPView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFC__IOCPView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFC__IOCPView ���

#ifdef _DEBUG
void CMFC__IOCPView::AssertValid() const
{
	CView::AssertValid();
}

void CMFC__IOCPView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFC__IOCPDoc* CMFC__IOCPView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFC__IOCPDoc)));
	return (CMFC__IOCPDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFC__IOCPView ��Ϣ�������


void CMFC__IOCPView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
	//��ʼ���б�ؼ�
	CRect Workrect;
	GetClientRect(&Workrect);
	Workrect.right /= 2;
	m_List.Create(LVS_REPORT, Workrect, this, 1);
	m_List.ModifyStyle(0, LVS_REPORT | LVS_SHOWSELALWAYS);
	m_List.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_List.ShowWindow(SW_SHOW);
	m_List.InsertColumn(0, _T("��־"), LVCFMT_CENTER, Workrect.right);
	//m_List.InsertItem(0, _T("name0"));

	//��ʼ����ť�ؼ�
	m_button1.Create(_T("����������"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		CRect(Workrect.right + 50, 10, Workrect.right + 150, 50), this, 2);
	m_button2.Create(_T("ֹͣ������"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		CRect(Workrect.right + 200, 10, Workrect.right + 300, 50), this, 3);
	m_button3.Create(_T("���Կͻ���"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		CRect(Workrect.right + 50, 200+10, Workrect.right + 150, 200+50), this, 4);
}

void CMFC__IOCPView::ShowMsgOnListCtrl(CString *psz)
{
	//::EnterCriticalSection(&m_ListLock);
	m_nNumOfMsg++;
	//psz->Format(_T("%d--%s--"), m_nNumOfMsg, psz->GetBuffer());
	m_List.InsertItem(0, psz->GetBuffer());
	//::LeaveCriticalSection(&m_ListLock);
	return;
}


DWORD WINAPI start(LPVOID lpParameter);
DWORD WINAPI close(LPVOID lpParameter);
void CMFC__IOCPView::OnStartServer()
{
	m_nNumOfMsg = 0;
	m_List.DeleteAllItems();
	CreateThread(NULL, 0, start, this, 0, 0);
}
void CMFC__IOCPView::OnStopServer()
{
	CreateThread(NULL, 0, close, this, 0, 0);
}
void CMFC__IOCPView::OnStartClent()
{
	STARTUPINFO si = { sizeof(si) };
	PROCESS_INFORMATION pi;
	BOOL bStatus = CreateProcess( _T("F:\\program files\\study resources\\1c++ѧϰ����\\IOCP�������Ϳͻ���-�ı�CSDNС������\\IOCP�������Ϳͻ���-�ı�CSDNС������\\PiggyStressTestClient\\Debug\\PiggyStressTestClient.exe"),
		NULL,NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
}
