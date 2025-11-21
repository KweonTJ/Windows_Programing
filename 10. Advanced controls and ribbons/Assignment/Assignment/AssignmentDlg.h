
// AssignmentDlg.h: 헤더 파일
//

#pragma once


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
	CListCtrl m_listMembers;
	CMFCPropertyGridCtrl m_proMember;
	CString m_strName;
	CString m_strContact;
	bool m_bSex;
	int m_nSelectedMember;
	void UpdatePropGrid(CString strName, bool bSex, CString strContact);
	afx_msg void OnClickedButtonAdd();
	afx_msg void OnClickedButtonDelete();
	afx_msg void OnRadioMale();
	afx_msg void OnRadioFemale();
	afx_msg void OnItemchangedListMembers(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg LRESULT OnPropertyChanged(WPARAM wParam, LPARAM lParam);
};
