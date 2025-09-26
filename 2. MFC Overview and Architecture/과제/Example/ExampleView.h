
// ExampleView.h: CExampleView 클래스의 인터페이스
//

#pragma once


class CExampleView : public CView
{
protected: // serialization에서만 만들어집니다.
	CExampleView() noexcept;
	DECLARE_DYNCREATE(CExampleView)

// 특성입니다.
public:
	CExampleDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 구현입니다.
public:
	virtual ~CExampleView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	bool m_bDrag;
	CString m_strWindowSize;
	CString m_strOutput;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	CPoint m_ptMouseMove;
	CString m_strMouseMove;
};

#ifndef _DEBUG  // ExampleView.cpp의 디버그 버전
inline CExampleDoc* CExampleView::GetDocument() const
   { return reinterpret_cast<CExampleDoc*>(m_pDocument); }
#endif

