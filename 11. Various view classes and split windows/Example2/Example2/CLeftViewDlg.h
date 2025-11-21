#pragma once



// CLeftViewDlg 폼 보기

class CLeftViewDlg : public CFormView
{
	DECLARE_DYNCREATE(CLeftViewDlg)

protected:
	CLeftViewDlg();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CLeftViewDlg();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FORMVIEW };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_strNodeText;
	CString m_strSelectedNode;
	afx_msg void OnClickedButtonInsert();
	afx_msg void OnClickedButtonModify();
	afx_msg void OnClickedButtonDelete();
};


