#pragma once
#include "afxdialogex.h"


// CCardDlg 대화 상자

class CCardDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCardDlg)

public:
	CCardDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CCardDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CARD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_strDept;
	CString m_strName;
	bool m_bHobby[3];
	bool m_bSex;
	virtual BOOL OnInitDialog();
	afx_msg void OnRadioFemale();
	afx_msg void OnRadioMale();
	afx_msg void OnClickedCheckFishing();
	afx_msg void OnClickedCheckReading();
	afx_msg void OnClickedCheckSports();
};
