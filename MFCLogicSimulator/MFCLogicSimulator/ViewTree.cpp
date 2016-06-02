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
	ON_MESSAGE(UM_UNSELECT_ITEM_IN_TREEVIEW, &CViewTree::OnUnselectItem)
	ON_WM_CONTEXTMENU()

	ON_WM_LBUTTONDOWN()

//	ON_NOTIFY_REFLECT(TVN_SELCHANGED, &CViewTree::OnTvnSelchanged)

	ON_NOTIFY_REFLECT(TVN_SELCHANGING, &CViewTree::OnTvnSelchanging)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, &CViewTree::OnTvnSelchanged)
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
	
	CFileView* pFileView = p_MainFrm->getCFileView();
	CViewTree* pToolbox = pFileView->getCFileViewTree();
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CChildFrame *pChild = (CChildFrame *)pFrame->GetActiveFrame();
	CMFCLogicSimulatorDoc *pDoc = (CMFCLogicSimulatorDoc *)pChild->GetActiveDocument();
	COutputWnd* pOutput = pFrame->getCOutputWnd();

	
	// Ʈ�� ��Ʈ�� ������ �ε���
	// goo.gl/mdFKLz
	int indexOfItem = 0;


	HTREEITEM hItem = pToolbox->GetChildItem(NULL);
	RECT rect;

	while (hItem)
	{
		this->GetItemRect(hItem, &rect, 0);

		//������ ���� ���� �ȿ� ��� ������
		if (rect.left <= point.x && point.x <= rect.right
			&&rect.top <= point.y && point.y <= rect.bottom) {
			//������ �� �����ϸ� �ƹ��ϵ� ���Ͼ��

			//�ƹ��͵� �ƴѻ����϶�
			if (pDoc->operationMode == OPERATION_MODE_NONE) {
				if (isSelectedItemFolder(pDoc->getSelectedItemInToolBox(hItem)) == false) {
					setItemStateON(hItem);
				}
			}
			//�߰� ����ϋ�
			else if (pDoc->operationMode == OPERATION_MODE_ADDING_COMPONENT) {
				if (pDoc->currentSelectedItem == pDoc->getSelectedItemInToolBox(hItem)) {
					//�߰��ϴ� ��ǰ�� ���� �ϰ� 
					SendMessage(UM_UNSELECT_ITEM_IN_TREEVIEW, 100, 100);
				}
				else {
					//�ٽ� �����Ѵ�
					SendMessage(UM_UNSELECT_ITEM_IN_TREEVIEW, 100, 100);
					if (isSelectedItemFolder(pDoc->getSelectedItemInToolBox(hItem)) == false) {
						setItemStateON(hItem);
					}
				}
			}
			//���� ����ϋ�
			else if (pDoc->operationMode == OPERATION_MODE_CONNECTING_COMPONENT) {
				//���� ��带 ����Ѵ�
				setItemStateON(hItem);
			}
			//��ǰ ���ø���϶�
			else if (pDoc->operationMode == OPERATION_MODE_SELECT_COMPONENT) {
				setItemStateON(hItem);

			}
			break;
		}

		hItem = pToolbox->GetNextItem(hItem, TVGN_NEXTVISIBLE);
	}
	(pChild->GetActiveView())->Invalidate();
	CTreeCtrl::OnLButtonDown(nFlags, point);
}


//���� ���� �޼����� ó���Ѵ�
afx_msg LRESULT CViewTree::OnUnselectItem(WPARAM wParam, LPARAM lParam)
{
	CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd();
	CFileView* pFileView = pMainFrm->getCFileView();
	CViewTree* pToolbox = pFileView->getCFileViewTree();
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CChildFrame *pChild = (CChildFrame *)pFrame->GetActiveFrame();
	CMFCLogicSimulatorDoc *pDoc = (CMFCLogicSimulatorDoc *)pChild->GetActiveDocument();
	COutputWnd* pOutput = pFrame->getCOutputWnd();
	HTREEITEM treeItem = pToolbox->GetChildItem(NULL);

	while (treeItem)
	{
		this->SetItemState(treeItem, ~TVIS_SELECTED, TVIS_SELECTED);
		treeItem = pToolbox->GetNextItem(treeItem, TVGN_NEXTVISIBLE);
	}
	pDoc->operationMode = OPERATION_MODE_NONE;
	pDoc->currentSelectedItem = FOLDER_ROOT;
	CString str;
	str.Format(_T("in tree view : unselect item\n"));
	pOutput->addBuildWindowString(str);
	return 0;
}

//�缱�� �޼����� ó���Ѵ�

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




void CViewTree::OnTvnSelchanging(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//
	//https://msdn.microsoft.com/ko-kr/library/a9a9f1t7.aspx
	//*pResult �̰Ÿ� 1�� �����ؾ��Ѵ�
	*pResult = 1;
}

void CViewTree::OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	*pResult = 1;
}

void CViewTree::setItemStateON(HTREEITEM hItem)
{
	CMainFrame* p_MainFrm = (CMainFrame*)AfxGetMainWnd();
	CFileView* p_FileView = p_MainFrm->getCFileView();
	CViewTree* p_Toolbox = p_FileView->getCFileViewTree();
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CChildFrame *pChild = (CChildFrame *)pFrame->GetActiveFrame();
	CMFCLogicSimulatorDoc *pDoc = (CMFCLogicSimulatorDoc *)pChild->GetActiveDocument();
	COutputWnd* pOutput = pFrame->getCOutputWnd();

	SetItemState(hItem, TVIS_SELECTED, TVIS_SELECTED);
	pDoc->operationMode = OPERATION_MODE_ADDING_COMPONENT;
	pDoc->currentSelectedItem = pDoc->getSelectedItemInToolBox(hItem);

	CString str;
	str.Format(_T("in tree view : item selected\n"));
	pOutput->addBuildWindowString(str);
}

