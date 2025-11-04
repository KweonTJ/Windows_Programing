
// Example1Dlg.h: 헤더 파일
//

#pragma once


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
	CListCtrl m_listStudent;
	CString m_strDept;
	CString m_strID;
	CString m_strName;
	CString m_strSelectedItem;
	afx_msg void OnClickedButtonInsert();
	int m_nSelectedItem;
	afx_msg void OnItemchangedListStudent(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickedButtonModify();
	afx_msg void OnClickedButtonDelete();
	afx_msg void OnClickedButtonReset();
	afx_msg void OnSelchangeComboStyle();
};
