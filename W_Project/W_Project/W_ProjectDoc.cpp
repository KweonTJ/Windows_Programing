
// W_ProjectDoc.cpp: CWProjectDoc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "W_Project.h"
#endif

#include "W_ProjectDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CWProjectDoc

IMPLEMENT_DYNCREATE(CWProjectDoc, CDocument)

BEGIN_MESSAGE_MAP(CWProjectDoc, CDocument)
	ON_COMMAND(ID_LINE, &CWProjectDoc::OnLine)
	ON_UPDATE_COMMAND_UI(ID_LINE, &CWProjectDoc::OnUpdateLine)
	ON_COMMAND(ID_RECTANGLE, &CWProjectDoc::OnRectangle)
	ON_UPDATE_COMMAND_UI(ID_RECTANGLE, &CWProjectDoc::OnUpdateRectangle)
	ON_COMMAND(ID_TEXT, &CWProjectDoc::OnText)
	ON_UPDATE_COMMAND_UI(ID_TEXT, &CWProjectDoc::OnUpdateText)
	ON_COMMAND(ID_ELLIPSE, &CWProjectDoc::OnEllipse)
	ON_UPDATE_COMMAND_UI(ID_ELLIPSE, &CWProjectDoc::OnUpdateEllipse)
	ON_COMMAND(ID_DIAMOND, &CWProjectDoc::OnDiamond)
	ON_UPDATE_COMMAND_UI(ID_DIAMOND, &CWProjectDoc::OnUpdateDiamond)
	ON_COMMAND(ID_RIGHT_TRIANGLE, &CWProjectDoc::OnRightTriangle)
	ON_UPDATE_COMMAND_UI(ID_RIGHT_TRIANGLE, &CWProjectDoc::OnUpdateRightTriangle)
	ON_COMMAND(ID_ISO_TRIANGLE, &CWProjectDoc::OnIsoTriangle)
	ON_UPDATE_COMMAND_UI(ID_ISO_TRIANGLE, &CWProjectDoc::OnUpdateIsoTriangle)
END_MESSAGE_MAP()


// CWProjectDoc 생성/소멸

CWProjectDoc::CWProjectDoc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.
	m_Pcolor = RGB(0, 0, 0);	// 선 컬러 
	m_Bcolor = RGB(255, 255, 255);	// 면 컬러
	m_PenWidth = 2.0f;	// 텍스트 두께
}

CWProjectDoc::~CWProjectDoc()
{
}

BOOL CWProjectDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	m_list.RemoveAll();
	m_Pcolor = RGB(0, 0, 0);	
	m_Bcolor = RGB(255, 255, 255);
	m_PenWidth = 2.0f;
	return TRUE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CWProjectDoc serialization

void CWProjectDoc::Serialize(CArchive& ar) // 데이터 파일 저장 및 불러오기
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
		INT n = (INT)m_list.GetCount();
		ar << n;
		for (POSITION pos = m_list.GetHeadPosition(); pos; )	// 리스트의 모든 도형 정보를 저장
		{
			const CMyShape& s = m_list.GetNext(pos);
			ar << (INT)s.type << s.rc << s.pen << s.brush << s.penWidth << s.text << s.textPt;
		}
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
		m_list.RemoveAll();
		INT n = 0; ar >> n;
		for (INT i = 0; i < n; ++i)		// 리스트의 모든 도형 정보를 불러옴
		{
			CMyShape s; INT tt; ar >> tt; s.type = (SHAPE_TYPE)tt;
			ar >> s.rc >> s.pen >> s.brush >> s.penWidth >> s.text >> s.textPt;
			m_list.AddTail(s);
		}
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CWProjectDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CWProjectDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CWProjectDoc::SetSearchContent(const CString& value)
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

// CWProjectDoc 진단

#ifdef _DEBUG
void CWProjectDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CWProjectDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CWProjectDoc 명령

void CWProjectDoc::OnLine()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

void CWProjectDoc::OnUpdateLine(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}

void CWProjectDoc::OnRectangle()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

void CWProjectDoc::OnUpdateRectangle(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}

void CWProjectDoc::OnText()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

void CWProjectDoc::OnUpdateText(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}

void CWProjectDoc::OnEllipse()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

void CWProjectDoc::OnUpdateEllipse(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}

void CWProjectDoc::OnDiamond()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

void CWProjectDoc::OnUpdateDiamond(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}

void CWProjectDoc::OnRightTriangle()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

void CWProjectDoc::OnUpdateRightTriangle(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}

void CWProjectDoc::OnIsoTriangle()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

void CWProjectDoc::OnUpdateIsoTriangle(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}

// 실제 동작의 경우, View에서 동작. 