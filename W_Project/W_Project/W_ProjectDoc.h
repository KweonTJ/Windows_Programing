
// W_ProjectDoc.h: CWProjectDoc 클래스의 인터페이스
//


#pragma once
#include <afxtempl.h>

enum SHAPE_TYPE { ST_LINE = 1, ST_RECTANGLE, ST_ELLIPSE, ST_DIAMOND, ST_RT_TRIANGLE, ST_ISO_TRIANGLE, ST_TEXT };

// 도형 레코드 클래스
class CMyShape
{
public:
	SHAPE_TYPE type = ST_LINE;
	CRect rc{};		//	선의 경우, start, end를 rc 에 담고 사용
	COLORREF pen = RGB(0, 0, 0);	// 선 색상
	COLORREF brush = RGB(255, 255, 255);	// 면 색상
	float penWidth = 2.0f;		// 선 굵기

	CString text;
	CPoint textPt{ };	

	static CMyShape MakeRectLike(SHAPE_TYPE t, CPoint a, CPoint b, COLORREF pen, COLORREF brush, float w) 
	{
		CMyShape s; s.type = t; s.pen = pen; s.brush = brush; s.penWidth = w;
		s.rc.SetRect(min(a.x, b.x), min(a.y, b.y), max(a.x, b.x), max(a.y, b.y));
		return s;
	}
	// 사각형 기반 도형 생성
	static CMyShape MakeLine(CPoint a, CPoint b, COLORREF pen, float w) 
	{
		CMyShape s; s.type = ST_LINE; s.pen = pen; s.brush = RGB(255, 255, 255); s.penWidth = w;
		s.rc.SetRect(a, b);
		return s;
	}
	// 선 객체 생성
	static CMyShape MakeText(CString t, CPoint pt, COLORREF pen)
	{
		CMyShape s; s.type = ST_TEXT; s.text = t; s.textPt = pt; s.pen = pen;
		return s;
	}
	// 텍스트 객체 생성
};


class CWProjectDoc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CWProjectDoc() noexcept;
	DECLARE_DYNCREATE(CWProjectDoc)

	// 특성입니다.
public:
	CList<CMyShape, CMyShape&>m_list;
	COLORREF m_Pcolor, m_Bcolor;
	float m_PenWidth;
	// 작업입니다.
public:

	// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

	// 구현입니다.
public:
	virtual ~CWProjectDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void OnLine();
	afx_msg void OnUpdateLine(CCmdUI* pCmdUI);
	afx_msg void OnRectangle();
	afx_msg void OnUpdateRectangle(CCmdUI* pCmdUI);
	afx_msg void OnText();
	afx_msg void OnUpdateText(CCmdUI* pCmdUI);
	afx_msg void OnEllipse();
	afx_msg void OnUpdateEllipse(CCmdUI* pCmdUI);
	afx_msg void OnDiamond();
	afx_msg void OnUpdateDiamond(CCmdUI* pCmdUI);
	afx_msg void OnRightTriangle();
	afx_msg void OnUpdateRightTriangle(CCmdUI* pCmdUI);
	afx_msg void OnIsoTriangle();
	afx_msg void OnUpdateIsoTriangle(CCmdUI* pCmdUI);
};
