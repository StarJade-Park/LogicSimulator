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

// ChildFrm.h : CChildFrame Ŭ������ �������̽�
//

#pragma once

class CChildFrame : public CMDIChildWndEx
{
	DECLARE_DYNCREATE(CChildFrame)
public:
	CChildFrame();

// Ư���Դϴ�.
public:
	/* check box, button �̺�Ʈ ó�� ���� �߰� ��� */
// �۾��Դϴ�.
public:

// �������Դϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// �����Դϴ�.
public:
	virtual ~CChildFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// ������ �޽��� �� �Լ�
protected:
	afx_msg void OnFilePrint();
	afx_msg void OnFilePrintPreview();
	afx_msg void OnUpdateFilePrintPreview(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnUpdateCheckoutput(CCmdUI *pCmdUI);
	afx_msg void OnCheckoutput();
	afx_msg void OnCheckproperties();
	afx_msg void OnUpdateCheckproperties(CCmdUI *pCmdUI);
	afx_msg void OnChecktoolbox();
	afx_msg void OnUpdateChecktoolbox(CCmdUI *pCmdUI);
	afx_msg void OnButtonstop();
	afx_msg void OnUpdateButtonstop(CCmdUI *pCmdUI);
	afx_msg void OnButtoncontinue();
	afx_msg void OnUpdateButtoncontinue(CCmdUI *pCmdUI);
	afx_msg void OnButtonact();
	afx_msg void OnUpdateButtonact(CCmdUI *pCmdUI);
	afx_msg void OnButtonedit();
	afx_msg void OnUpdateButtonedit(CCmdUI *pCmdUI);
	afx_msg void OnEditCopy();
	afx_msg void OnUpdateEditCopy(CCmdUI *pCmdUI);
	afx_msg void OnEditPaste();
	afx_msg void OnUpdateEditPaste(CCmdUI *pCmdUI);
	afx_msg void OnEditUndo();
	afx_msg void OnUpdateEditUndo(CCmdUI *pCmdUI);
	afx_msg void OnEditCut();
	afx_msg void OnUpdateEditCut(CCmdUI *pCmdUI);
	afx_msg void OnEditSelectAll();
	afx_msg void OnUpdateEditSelectAll(CCmdUI *pCmdUI);
	afx_msg void OnEditRedo();
	afx_msg void OnUpdateEditRedo(CCmdUI *pCmdUI);
	afx_msg void OnSaveLibrarybox();
	afx_msg void OnUpdateSaveLibrarybox(CCmdUI *pCmdUI);
	afx_msg void OnLoadLibrarybox();
	afx_msg void OnUpdateLoadLibrarybox(CCmdUI *pCmdUI);
	afx_msg void OnCleanLog();
	afx_msg void OnUpdateCleanLog(CCmdUI *pCmdUI);
};
