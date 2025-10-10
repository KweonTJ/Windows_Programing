
// Example1Doc.cpp: CExample1Doc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Example1.h"
#endif

#include "Example1Doc.h"
#include "MainFrm.h"
#include "Example1View.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CExample1Doc

IMPLEMENT_DYNCREATE(CExample1Doc, CDocument)

BEGIN_MESSAGE_MAP(CExample1Doc, CDocument)
END_MESSAGE_MAP()


// CExample1Doc 생성/소멸

CExample1Doc::CExample1Doc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CExample1Doc::~CExample1Doc()
{
}

BOOL CExample1Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.
	POSITION pos = GetFirstViewPosition();
	CExample1View* pView = (CExample1View*)GetNextView(pos);

	pView->m_strDept.Empty();
	pView->m_strName.Empty();
	pView->m_strSex.Empty();
	pView->m_strHobby.Empty();

	return TRUE;
}




// CExample1Doc serialization

void CExample1Doc::Serialize(CArchive& ar)
{
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CExample1View* pView = (CExample1View*)pFrame->GetActiveView();
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
		ar << pView->m_strDept;
		ar << pView->m_strName;
		ar << pView->m_strSex;
		ar << pView->m_strHobby;
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
		ar >> pView->m_strDept;
		ar >> pView->m_strName;
		ar >> pView->m_strSex;
		ar >> pView->m_strHobby;
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CExample1Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CExample1Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CExample1Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CExample1Doc 진단

#ifdef _DEBUG
void CExample1Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CExample1Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CExample1Doc 명령
