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

#pragma once
#include "ViewTree.h"
#include "LibraryBoxComponent.h"
class CFileViewToolBar : public CMFCToolBar
{
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*) GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }
};
// CDockablePane ����
// https://msdn.microsoft.com/ko-kr/library/bb984433.aspx
class CFileView : public CDockablePane
{
// �����Դϴ�.
public:
	CFileView();
	//HTREEITEM selectedItem;
	//HTREEITEM nextItem;
	void AdjustLayout();
	void OnChangeVisualStyle();
	//HTREEITEM getItemSelected() const;
	//HTREEITEM getChildItem(HTREEITEM hItem) const;
	//HTREEITEM getNextItem(HTREEITEM n_Item, UINT n_Flag) const;
	CViewTree* getCFileViewTree();
	void addCoreData(LIBRARY_BOX_DATA& coreData);
	void getCoreData(LIBRARY_BOX_DATA& coreData, int index);
// Ư���Դϴ�.
protected:
	CViewTree m_wndFileView;
	CImageList m_FileViewImages;
	CFileViewToolBar m_wndToolBar;
	HTREEITEM hLib;
	vector <LIBRARY_BOX_DATA> coreDataList;

	void FillFileView();



public:
	virtual ~CFileView();
	void addLibraryBox(CString LibraryBoxName);
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnFileOpen();
	afx_msg void OnFileOpenWith();
	afx_msg void OnDummyCompile();
	afx_msg void OnEditCut();
	afx_msg void OnEditCopy();
	afx_msg void OnEditClear();
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);

	DECLARE_MESSAGE_MAP()
};

