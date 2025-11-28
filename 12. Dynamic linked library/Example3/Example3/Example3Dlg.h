
// Example3Dlg.h: 헤더 파일
//

#pragma once
#include "CCalculatorBMI.h"

// CExample3Dlg 대화 상자
class CExample3Dlg : public CDialogEx
{
// 생성입니다.
public:
	CExample3Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EXAMPLE3_DIALOG };
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
	CString m_strHeight;
	CString m_strResult;
	CString m_strWeight;
	CCalculatorBMI m_calcBMI;
	char m_chGender;
	afx_msg void OnRadioMale();
	afx_msg void OnRadio2Female();
	afx_msg void OnClickedButtonCalculate();
	afx_msg void OnClickedButtonReset();
};
