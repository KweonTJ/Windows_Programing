
// Example1View.h: CExample1View 클래스의 인터페이스
//

#pragma once


class CExample1View : public CView
{
protected: // serialization에서만 만들어집니다.
	CExample1View() noexcept;
	DECLARE_DYNCREATE(CExample1View)

// 특성입니다.
public:
	CExample1Doc* GetDocument() const;

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
	virtual ~CExample1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	CString m_strDept;	// 학과 저장
	CString m_strName;	// 이름 저장
	CString m_strSex;	// 성별 저장
	CString m_strHobby; // 취미 저장
};

#ifndef _DEBUG  // Example1View.cpp의 디버그 버전
inline CExample1Doc* CExample1View::GetDocument() const
   { return reinterpret_cast<CExample1Doc*>(m_pDocument); }
#endif

