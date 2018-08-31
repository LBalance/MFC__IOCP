
// MFC__IOCPView.h : CMFC__IOCPView ��Ľӿ�
//

#pragma once

class CMFC__IOCPDoc;
class CMFC__IOCPView : public CView
{
protected: // �������л�����
	CMFC__IOCPView();
	DECLARE_DYNCREATE(CMFC__IOCPView)
//��Ա
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
	//�������Կͻ���
	afx_msg void OnStartClent();	
// ����
public:
	CMFC__IOCPDoc* GetDocument() const;

// ����
public:
	virtual void ShowMsgOnListCtrl(CString *psz);
// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// ʵ��
public:
	virtual ~CMFC__IOCPView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
};

#ifndef _DEBUG  // MFC__IOCPView.cpp �еĵ��԰汾
inline CMFC__IOCPDoc* CMFC__IOCPView::GetDocument() const
   { return reinterpret_cast<CMFC__IOCPDoc*>(m_pDocument); }
#endif

