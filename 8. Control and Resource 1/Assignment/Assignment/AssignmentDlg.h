
// AssignmentDlg.h: 헤더 파일
//

#pragma once
typedef struct Student {
	CString strDept;
	CString strName;
	CString strID;
	CString strYear;
} Student;;

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
	CTreeCtrl m_treeDept;
	CListCtrl m_listStudent;
	CString m_strName;
	CString m_strID;
	CString m_strYear;
	HTREEITEM m_hRoot;
	HTREEITEM m_hComputer;
	HTREEITEM m_hInfomation;
	HTREEITEM m_hSelectedNode;
	Student m_StudentInfo[50];
	int m_nCount = 0;
	int m_nSelectedItem = -1;
	afx_msg void OnSelchangedTreeDept(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemchangedListStudent(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickedButtonInsert();
	afx_msg void OnClickedButtonDelete();
	void InsertListItem(int index);
};
