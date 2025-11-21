// CNCardListBox.cpp: 구현 파일
//

#include "pch.h"
#include "Example1.h"
#include "CNCardListBox.h"
#include "Example1Dlg.h"


// CNCardListBox

IMPLEMENT_DYNAMIC(CNCardListBox, CVSListBox)

CNCardListBox::CNCardListBox()
{

}

CNCardListBox::~CNCardListBox()
{
}


BEGIN_MESSAGE_MAP(CNCardListBox, CVSListBox)
END_MESSAGE_MAP()



// CNCardListBox 메시지 처리기



void CNCardListBox::OnAfterAddItem(int nIndex)
{
    // TODO: 여기에 구현 코드 추가.
    CExample1Dlg* pParent = (CExample1Dlg*)GetParent();
    pParent->AddNameCard(GetItemText(nIndex));
}

void CNCardListBox::OnSelectionChanged()
{
    // TODO: 여기에 구현 코드 추가.
    int nItem;
    if ((nItem = GetSelItem()) < 0)
        return;

    CExample1Dlg* pParent = (CExample1Dlg*)GetParent();
    pParent->SelectNameCard(nItem);
}

BOOL CNCardListBox::OnBeforeRemoveItem(int nIndex)
{
    // TODO: 여기에 구현 코드 추가.
    CExample1Dlg* pParent = (CExample1Dlg*)GetParent();
    pParent->DeleteNameCard(GetSelItem());
    if (pParent->m_nCount == 0)
    {
        pParent->m_pNameCards[0].strCompany.Empty();
        pParent->m_pNameCards[0].strContact.Empty();
        pParent->m_pNameCards[0].strName.Empty();
        pParent->m_pNameCards[0].strTitle.Empty();
        pParent->InitializePropGrid(NameCard());
        pParent->DrawNameCard(NameCard());
    }
    return 0;
}
