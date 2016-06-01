// �� MFC ���� �ҽ� �ڵ�� MFC Microsoft Office Fluent ����� �������̽�("Fluent UI")�� 
// ����ϴ� ����� ���� �ָ�, MFC C++ ���̺귯�� ����Ʈ��� ���Ե� 
// Microsoft Foundation Classes Reference �� ���� ���� ������ ���� 
// �߰������� �����Ǵ� �����Դϴ�.  
// Fluent UI�� ����, ��� �Ǵ� �����ϴ� �� ���� ��� ����� ������ �����˴ϴ�.  
// Fluent UI ���̼��� ���α׷��� ���� �ڼ��� ������ 
// http://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

#include "stdafx.h"
#include "ViewTree.h"
#include "MFCLogicSimulatorDoc.h"
#include "MainFrm.h"
#include "MFCLogicSimulatorView.h"
#include "MFCLogicSimulator.h"
#include "ChildFrm.h"
#include "FileView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewTree

CViewTree::CViewTree()
{

}

CViewTree::~CViewTree()
{
}

BEGIN_MESSAGE_MAP(CViewTree, CTreeCtrl)
	//	ON_WM_LBUTTONDOWN()
	ON_WM_CREATE()

	ON_WM_CONTEXTMENU()
	//	ON_WM_LBUTTONUP()
//	ON_WM_LBUTTONDBLCLK()
ON_WM_LBUTTONDOWN()
//	ON_NOTIFY_REFLECT(TVN_ITEMCHANGED, &CViewTree::OnTvnItemChanged)
//	ON_NOTIFY_REFLECT(TVN_ITEMCHANGING, &CViewTree::OnTvnItemChanging)
//	ON_NOTIFY_REFLECT(TVN_ITEMCHANGED, &CViewTree::OnTvnItemChanged)
ON_NOTIFY_REFLECT(TVN_SELCHANGED, &CViewTree::OnTvnSelchanged)
//	ON_NOTIFY_REFLECT(TVN_SELCHANGING, &CViewTree::OnTvnSelchanging)
ON_MESSAGE(UM_UNSELECT_ITEM, &CViewTree::OnUnselectItem)
ON_MESSAGE(UM_RESELECT_ITEM, &CViewTree::OnReselectItem)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewTree �޽��� ó����


int CViewTree::OnCreate(LPCREATESTRUCT lpCreateStruct)
{


	if (CTreeCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.
	CTreeCtrl m_treeCtr;



	return 0;
}



void CViewTree::OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}


//�����ߴ��Ŷ� �����Ÿ� �����Ѵ�
void CViewTree::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CMainFrame* p_MainFrm = (CMainFrame*)AfxGetMainWnd();
	//
	CFileView* p_FileView = p_MainFrm->getCFileView();
	CViewTree* p_Toolbox = p_FileView->getCFileViewTree();
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CChildFrame *pChild = (CChildFrame *)pFrame->GetActiveFrame();
	CMFCLogicSimulatorDoc *pDoc = (CMFCLogicSimulatorDoc *)pChild->GetActiveDocument();
	COutputWnd* pOutput = pFrame->getCOutputWnd();

	// Ʈ�� ��Ʈ�� ������ �ε���
	// goo.gl/mdFKLz


	HTREEITEM hItem = p_Toolbox->GetSelectedItem();
	int itemIndex = pDoc->itemSelectedInDoc();
	RECT rect;
	this->GetItemRect(hItem, &rect, 0);

	//������ ���� ���� �ȿ� ��� ������
	if (rect.left <= point.x && point.x <= rect.right
		&&rect.top <= point.y && point.y <= rect.bottom) {
		//������ �� �����ϸ� �ƹ��ϵ� ���Ͼ��

		//������ ���� �Ѱ��� �ٽ� ���� �Ϸ� �Ҷ�
		if (pDoc->currentSelectedItem == -1) {
			SendMessage(UM_RESELECT_ITEM, 100, 100);
		}
		//���� ���õȰ��� �����Ϸ� �Ҷ�
		else if (itemIndex == pDoc->currentSelectedItem) {

			SendMessage(UM_UNSELECT_ITEM, 100, 100);
		}
	}
	CTreeCtrl::OnLButtonDown(nFlags, point);
}


//���õ� ���� ����Ǹ� ��ť��Ʈ�� ���� �����Ѵ�
void CViewTree::OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	*pResult = 0;

	// TODO: Add your specialized code here and/or call the base class
	CMainFrame* p_MainFrm = (CMainFrame*)AfxGetMainWnd();
	CFileView* p_FileView = p_MainFrm->getCFileView();
	CViewTree* p_Toolbox = p_FileView->getCFileViewTree();
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CChildFrame *pChild = (CChildFrame *)pFrame->GetActiveFrame();
	CMFCLogicSimulatorDoc *pDoc = (CMFCLogicSimulatorDoc *)pChild->GetActiveDocument();
	COutputWnd* pOutput = pFrame->getCOutputWnd();

	if (pDoc == NULL)return;
	// Ʈ�� ��Ʈ�� ������ �ε���
	// goo.gl/mdFKLz

	HTREEITEM hItem = p_Toolbox->GetSelectedItem();
	int itemIndex = pDoc->itemSelectedInDoc();

	CString str;


	//������ ó�� ���� �ϸ� �ƹ��͵� ���Ѵ�
	if (isSelectedItemFolder(itemIndex)) {
		pDoc->currentSelectedItem = -1;
		str.Format(_T("in tree view : select item is folder\n"));
		pOutput->addBuildWindowString(str);
	}
	else {
		pDoc->currentSelectedItem = itemIndex;
		str.Format(_T("in tree view : item %d selected\n"), itemIndex);
		pOutput->addBuildWindowString(str);

	}
}

void CViewTree::unseletectItem()
{


}




//���� ���� �޼����� ó���Ѵ�
afx_msg LRESULT CViewTree::OnUnselectItem(WPARAM wParam, LPARAM lParam)
{

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CMainFrame* p_MainFrm = (CMainFrame*)AfxGetMainWnd();
	//
	CFileView* p_FileView = p_MainFrm->getCFileView();
	CViewTree* p_Toolbox = p_FileView->getCFileViewTree();
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CChildFrame *pChild = (CChildFrame *)pFrame->GetActiveFrame();
	CMFCLogicSimulatorDoc *pDoc = (CMFCLogicSimulatorDoc *)pChild->GetActiveDocument();
	COutputWnd* pOutput = pFrame->getCOutputWnd();

	// Ʈ�� ��Ʈ�� ������ �ε���
	// goo.gl/mdFKLz


	HTREEITEM hItem = p_Toolbox->GetSelectedItem();
	int itemIndex = pDoc->itemSelectedInDoc();

	pDoc->currentSelectedItem = -1;
	this->SetItemState(hItem, ~TVIS_SELECTED, TVIS_SELECTED);

	CString str;
	if (isSelectedItemFolder(pDoc->currentSelectedItem)) {
		pDoc->currentSelectedItem = -1;
		str.Format(_T("in tree view : select item is folder\n"));
		pOutput->addBuildWindowString(str);
		return 0;
	}

	str.Format(_T("in tree view : item %d unselected\n"), itemIndex);
	pOutput->addBuildWindowString(str);

	return 0;
}

//�缱�� �޼����� ó���Ѵ�
afx_msg LRESULT CViewTree::OnReselectItem(WPARAM wParam, LPARAM lParam)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CMainFrame* p_MainFrm = (CMainFrame*)AfxGetMainWnd();
	//
	CFileView* p_FileView = p_MainFrm->getCFileView();
	CViewTree* p_Toolbox = p_FileView->getCFileViewTree();
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CChildFrame *pChild = (CChildFrame *)pFrame->GetActiveFrame();
	CMFCLogicSimulatorDoc *pDoc = (CMFCLogicSimulatorDoc *)pChild->GetActiveDocument();
	COutputWnd* pOutput = pFrame->getCOutputWnd();

	// Ʈ�� ��Ʈ�� ������ �ε���
	// goo.gl/mdFKLz


	HTREEITEM hItem = p_Toolbox->GetSelectedItem();
	int itemIndex = pDoc->itemSelectedInDoc();

	pDoc->currentSelectedItem = itemIndex;
	this->SetItemState(hItem, TVIS_SELECTED, TVIS_SELECTED);

	CString str;

	if (isSelectedItemFolder(pDoc->currentSelectedItem)) {
		pDoc->currentSelectedItem = -1;
		str.Format(_T("in tree view : select item is folder\n"));
		pOutput->addBuildWindowString(str);
		return 0;
	}
	
	str.Format(_T("in tree view : item %d reselected\n"), itemIndex);
	pOutput->addBuildWindowString(str);

	return 0;
}

//������ �������� �������� Ȯ���Ѵ�
bool CViewTree::isSelectedItemFolder(int selecteItem)
{
	if (selecteItem == FOLDER_ROOT || selecteItem == FOLDER_FF || selecteItem == FOLDER_GATE
		|| selecteItem == FOLDER_INPUT || selecteItem == FOLDER_OUTPUT || selecteItem == FOLDER_WIRE
		) {
		return true;
	}



	return false;
}
