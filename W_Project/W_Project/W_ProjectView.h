
// W_ProjectView.h: CWProjectView 클래스의 인터페이스
//
enum DRAW_MODE {MODE_LINE = 1, MODE_ELLIPSE, MODE_RECTANGLE,
	MODE_DIAMOND, MODE_ISO_TRIANGLE, MODE_RIGHT_TRIANGLE, MODE_TEXT};
#pragma once
#include "W_ProjectDoc.h"
#include <gdiplus.h>
using namespace Gdiplus;


class CWProjectView : public CView
{
protected: // serialization에서만 만들어집니다.
	CWProjectView() noexcept;
	DECLARE_DYNCREATE(CWProjectView)

// 특성입니다.
public:
	CWProjectDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CWProjectView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLine();
	afx_msg void OnEllipse();
	afx_msg void OnRectangle();
	afx_msg void OnDiamond();
	afx_msg void OnRightTriangle();
	afx_msg void OnIsoTriangle();
	afx_msg void OnText();
	CPoint m_ptPrev;
	CPoint m_ptStart;
	CPoint m_textPt{ 0,0 };
	CString m_textBuffer;
	int m_nDrawMode;
	COLORREF m_colorPen;
	COLORREF m_colorBrush;
	float m_penWidth = 2.0f; // 기본 펜 두께
	bool m_bLButtonDown;
	bool m_bRButtonDown = false;
	bool m_bTyping = false;
	afx_msg void OnColor1();
	afx_msg void OnColor2();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // W_ProjectView.cpp의 디버그 버전
inline CWProjectDoc* CWProjectView::GetDocument() const
   { return reinterpret_cast<CWProjectDoc*>(m_pDocument); }
#endif

