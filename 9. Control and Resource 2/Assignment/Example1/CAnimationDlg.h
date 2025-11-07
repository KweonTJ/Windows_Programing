#pragma once
#include "afxdialogex.h"


// CAnimationDlg 대화 상자

class CAnimationDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAnimationDlg)

public:
	CAnimationDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CAnimationDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ANIMATION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CProgressCtrl m_prgsAnimation;
	CSliderCtrl m_sliderAnimation;
	int m_nAniHScale;
	int m_nAniVScale;
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnClickedButtonAnimation();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
