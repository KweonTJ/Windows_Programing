
// Example1Dlg.h: 헤더 파일
//

#pragma once
#include "CNCardListBox.h"

typedef struct NameCard
{
	CString strCompany;
	CString strTitle;
	CString strName;
	CString strContact;
} NameCard;

// CExample1Dlg 대화 상자
class CExample1Dlg : public CDialogEx
{
// 생성입니다.
public:
	CExample1Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EXAMPLE1_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	NameCard m_pNameCards[20];
	int m_nCount;
	int m_nSelectedCard;
	void AddNameCard(CString strName);
	void SelectNameCard(int nIndex);
	void DeleteNameCard(int nIndex);
	CNCardListBox m_listNamdCard;
	CMFCPropertyGridCtrl m_pgCardInfo;
	CMFCFontComboBox m_fcbText;
	CMFCColorButton m_cbtnText;
	void InitializePropGrid(NameCard card);
	void DrawNameCard(NameCard card);

	afx_msg LRESULT OnPropertyChanged(WPARAM wParam, LPARAM lParam);
	afx_msg void OnClickedMfccolorbuttonText();
	afx_msg void OnSelchangeMfcfontcomboText();
};
