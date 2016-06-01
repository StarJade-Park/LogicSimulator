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

/////////////////////////////////////////////////////////////////////////////
// CViewTree â�Դϴ�.

class CViewTree : public CTreeCtrl
{
// �����Դϴ�.
public:
	CViewTree();

// �������Դϴ�.
protected:


// �����Դϴ�.
public:
	virtual ~CViewTree();


public:

//	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	afx_msg void OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult);


	void unseletectItem();

	LRESULT OnUnselectItem(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnReselectItem(WPARAM wParam, LPARAM lParam);

protected:
protected:
	DECLARE_MESSAGE_MAP()

	bool isSelectedItemFolder(int selecteItem);
	afx_msg LRESULT OnUmUnselectItem(WPARAM wParam, LPARAM lParam);
};
