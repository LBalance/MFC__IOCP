
// MFC__IOCPView.h : CMFC__IOCPView 类的接口
//

#pragma once

class CMFC__IOCPDoc;
class CMFC__IOCPView : public CView
{
protected: // 仅从序列化创建
	CMFC__IOCPView();
	DECLARE_DYNCREATE(CMFC__IOCPView)
//成员
public:
	CListCtrl m_List;
	unsigned long m_nNumOfMsg;
	CRITICAL_SECTION m_ListLock;
	CButton m_button1;
	CButton m_button2;
	CButton m_button3;
protected:
	afx_msg void OnStartServer();
	afx_msg void OnStopServer();
	//启动测试客户端
	afx_msg void OnStartClent();	
// 特性
public:
	CMFC__IOCPDoc* GetDocument() const;

// 操作
public:
	virtual void ShowMsgOnListCtrl(CString *psz);
// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~CMFC__IOCPView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
};

#ifndef _DEBUG  // MFC__IOCPView.cpp 中的调试版本
inline CMFC__IOCPDoc* CMFC__IOCPView::GetDocument() const
   { return reinterpret_cast<CMFC__IOCPDoc*>(m_pDocument); }
#endif

