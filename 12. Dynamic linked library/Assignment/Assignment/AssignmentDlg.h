
// AssignmentDlg.h: 헤더 파일
//

#pragma once
#include "CCalculator.h"


// CAssignmentDlg 대화 상자
class CAssignmentDlg : public CDialogEx
{
// 생성입니다.
public:
	CAssignmentDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ASSIGNMENT_DIALOG };
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
	CCalculator m_calculator;
	int m_nOperand;
	char m_chOperator;
	void MakeNumber(int nNumber);
	afx_msg void OnBnClickedRadioNum1();
	afx_msg void OnBnClickedRadioNum2();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton0();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonSubtract();
	afx_msg void OnBnClickedButtonMultiply();
	afx_msg void OnBnClickedButtonDivide();
	afx_msg void OnBnClickedButtonBack();
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnBnClickedButtonEqual();
};
