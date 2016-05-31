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
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewTree �޽��� ó����

BOOL CViewTree::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	/* ���콺 �÷��� �� */
	BOOL bRes = CTreeCtrl::OnNotify(wParam, lParam, pResult);

	NMHDR* pNMHDR = (NMHDR*)lParam;
	ASSERT(pNMHDR != NULL);

	if (pNMHDR && pNMHDR->code == TTN_SHOW && GetToolTips() != NULL)
	{
		GetToolTips()->SetWindowPos(&wndTop, -1, -1, -1, -1, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOSIZE);
	}
	return bRes;
}

//Ʈ�� �信�� �����ϸ� ���� ������ ��ť��Ʈ�� �Ѱ��ش�
//void CViewTree::OnLButtonDown(UINT nFlags, CPoint point)
//{
//	CTreeCtrl::OnLButtonDown(nFlags, point);
//}


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




void CViewTree::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CMainFrame* p_MainFrm = (CMainFrame*)AfxGetMainWnd();
	//
	CFileView* p_FileView = p_MainFrm->getCFileView();

	CViewTree* p_Toolbox = p_FileView->getCFileViewTree();

	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CChildFrame *pChild = (CChildFrame *)pFrame->GetActiveFrame();
	CMFCLogicSimulatorDoc *pDoc = (CMFCLogicSimulatorDoc *)pChild->GetActiveDocument();

	// Ʈ�� ��Ʈ�� ������ �ε���
	// goo.gl/mdFKLz


	HTREEITEM hItem = p_Toolbox->GetSelectedItem();
	HTREEITEM hComp = p_Toolbox->GetChildItem(NULL);

	int itemIndex = pDoc->itemSelectedInDoc();
	//�������� �ְ� üũ�ڽ��� �̺�Ʈ�� �߻��ϸ�
	if (itemIndex != FOLDER_ROOT&&itemIndex == pDoc->currentSelectedComponent) {
		//������ �����ϸ� üũ�� �����Ѵ�	
		int state, selecterimage;
		//this->GetItemImage(hItem, image, selecterimage);
		state = this->GetItemState(hItem, TVIS_SELECTED);
		this->SetItemState(hItem, TVIS_SELECTED, TVIS_SELECTED);
		
		//->SetItemImage(hItem, image, selecterimage);
		pDoc->currentSelectedComponent = 0;
	}


	CTreeCtrl::OnLButtonDblClk(nFlags, point);
}


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

	// Ʈ�� ��Ʈ�� ������ �ε���
	// goo.gl/mdFKLz

	HTREEITEM hItem = p_Toolbox->GetSelectedItem();


	int itemIndex = pDoc->itemSelectedInDoc();

	
	int state;
	state = this->GetItemState(hItem, TVIS_SELECTED);
	if (state == TVIS_SELECTED) {
		this->SetItemState(hItem, ~TVIS_SELECTED, TVIS_SELECTED);
	}
	else {
		this->SetItemState(hItem, TVIS_SELECTED, TVIS_SELECTED);
	}

	CTreeCtrl::OnLButtonDown(nFlags, point);
}
