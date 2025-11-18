#pragma once


// CNCardListBox

class CNCardListBox : public CVSListBox
{
	DECLARE_DYNAMIC(CNCardListBox)

public:
	CNCardListBox();
	virtual ~CNCardListBox();

protected:
	DECLARE_MESSAGE_MAP()
public:
	void OnAfterAddItem(int nIndex);
	void OnSelectionChanged();
	BOOL OnBeforeRemoveItem(int nIndex);
};


