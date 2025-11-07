#pragma once
#include "afxdialogex.h"


// CRatioDlg 대화 상자

class CRatioDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRatioDlg)

public:
	CRatioDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CRatioDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_RATIO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl m_sliderHorizontal;
	CSliderCtrl m_sliderVertical;
	int m_nHorizontal;
	int m_nVertical;
	int m_nCurHScale;
	int m_nCurVScale;
	virtual BOOL OnInitDialog();
	bool m_bSameRatio;
	
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnClickedCheckSameRatio();
};
