
// MFC__IOCPView.cpp : CMFC__IOCPView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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

// CMFC__IOCPView 构造/析构

CMFC__IOCPView::CMFC__IOCPView()
{
	// TODO: 在此处添加构造代码
	m_nNumOfMsg = 0;
	::InitializeCriticalSection(&m_ListLock);
}

CMFC__IOCPView::~CMFC__IOCPView()
{
	::DeleteCriticalSection(&m_ListLock);
}

BOOL CMFC__IOCPView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMFC__IOCPView 绘制

void CMFC__IOCPView::OnDraw(CDC* /*pDC*/)
{
	CMFC__IOCPDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
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


// CMFC__IOCPView 诊断

#ifdef _DEBUG
void CMFC__IOCPView::AssertValid() const
{
	CView::AssertValid();
}

void CMFC__IOCPView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFC__IOCPDoc* CMFC__IOCPView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFC__IOCPDoc)));
	return (CMFC__IOCPDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFC__IOCPView 消息处理程序


void CMFC__IOCPView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
	//初始化列表控件
	CRect Workrect;
	GetClientRect(&Workrect);
	Workrect.right /= 2;
	m_List.Create(LVS_REPORT, Workrect, this, 1);
	m_List.ModifyStyle(0, LVS_REPORT | LVS_SHOWSELALWAYS);
	m_List.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_List.ShowWindow(SW_SHOW);
	m_List.InsertColumn(0, _T("日志"), LVCFMT_CENTER, Workrect.right);
	//m_List.InsertItem(0, _T("name0"));

	//初始化按钮控件
	m_button1.Create(_T("启动服务器"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		CRect(Workrect.right + 50, 10, Workrect.right + 150, 50), this, 2);
	m_button2.Create(_T("停止服务器"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		CRect(Workrect.right + 200, 10, Workrect.right + 300, 50), this, 3);
	m_button3.Create(_T("测试客户端"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
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
	BOOL bStatus = CreateProcess( _T("F:\\program files\\study resources\\1c++学习资料\\IOCP服务器和客户端-改编CSDN小猪例子\\IOCP服务器和客户端-改编CSDN小猪例子\\PiggyStressTestClient\\Debug\\PiggyStressTestClient.exe"),
		NULL,NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
}
