#pragma once
#include "afxdialogex.h"


// CObjectDlg 대화 상자

class CObjectDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CObjectDlg)

public:
	CObjectDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CObjectDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_OBJECT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_nSelObject;
	// COLORREF m_colorObject;
	// bool m_bSameRatio;
	// int m_nCurHScale;
	// int m_nCurVScale;
	virtual BOOL OnInitDialog();
	afx_msg void OnRadioRect();
	afx_msg void OnRadioCircle();
};
