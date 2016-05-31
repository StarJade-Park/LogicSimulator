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

		if (pDoc->currentSelectedItem == -1) {
			CString str;
			str.Format(_T("in tree view : item %d selected\n"), itemIndex);
			pOutput->addBuildWindowString(str);
			pDoc->currentSelectedItem = itemIndex;
			this->SetItemState(hItem, TVIS_SELECTED, TVIS_SELECTED);
		}
		else if (itemIndex == pDoc->currentSelectedItem) {
			CString str;
			str.Format(_T("in tree view : item %d unselected\n"), itemIndex);
			pOutput->addBuildWindowString(str);
			pDoc->currentSelectedItem = -1;
			this->SetItemState(hItem, ~TVIS_SELECTED, TVIS_SELECTED);
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

	int state;
	state = this->GetItemState(hItem, TVIS_SELECTED);

	CString str;
	str.Format(_T("in tree view : item %d selected\n"), itemIndex);
	pOutput->addBuildWindowString(str);
	if (itemIndex == 0) {
		pDoc->currentSelectedItem = -1;
	}
	else {
		pDoc->currentSelectedItem = itemIndex;
	}
}



