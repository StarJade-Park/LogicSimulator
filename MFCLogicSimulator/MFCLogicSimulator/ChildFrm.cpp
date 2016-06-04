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

// ChildFrm.cpp : CChildFrame Ŭ������ ����
//

#include "stdafx.h"
#include "MFCLogicSimulator.h"

#include "ChildFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWndEx)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWndEx)
	ON_COMMAND(ID_FILE_PRINT, &CChildFrame::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CChildFrame::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CChildFrame::OnFilePrintPreview)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_PREVIEW, &CChildFrame::OnUpdateFilePrintPreview)
	ON_UPDATE_COMMAND_UI(ID_CHECKOUTPUT, &CChildFrame::OnUpdateCheckoutput)
	ON_COMMAND(ID_CHECKOUTPUT, &CChildFrame::OnCheckoutput)
	ON_COMMAND(ID_CHECKPROPERTIES, &CChildFrame::OnCheckproperties)
	ON_UPDATE_COMMAND_UI(ID_CHECKPROPERTIES, &CChildFrame::OnUpdateCheckproperties)
	ON_COMMAND(ID_CHECKTOOLBOX, &CChildFrame::OnChecktoolbox)
	ON_UPDATE_COMMAND_UI(ID_CHECKTOOLBOX, &CChildFrame::OnUpdateChecktoolbox)
	ON_COMMAND(ID_BUTTONSTOP, &CChildFrame::OnButtonstop)
	ON_UPDATE_COMMAND_UI(ID_BUTTONSTOP, &CChildFrame::OnUpdateButtonstop)
	ON_COMMAND(ID_BUTTONCONTINUE, &CChildFrame::OnButtoncontinue)
	ON_UPDATE_COMMAND_UI(ID_BUTTONCONTINUE, &CChildFrame::OnUpdateButtoncontinue)
	ON_COMMAND(ID_BUTTONACT, &CChildFrame::OnButtonact)
	ON_UPDATE_COMMAND_UI(ID_BUTTONACT, &CChildFrame::OnUpdateButtonact)
	ON_COMMAND(ID_BUTTONEDIT, &CChildFrame::OnButtonedit)
	ON_UPDATE_COMMAND_UI(ID_BUTTONEDIT, &CChildFrame::OnUpdateButtonedit)
	ON_COMMAND(ID_EDIT_COPY, &CChildFrame::OnEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, &CChildFrame::OnUpdateEditCopy)
	ON_COMMAND(ID_EDIT_PASTE, &CChildFrame::OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, &CChildFrame::OnUpdateEditPaste)
	ON_COMMAND(ID_EDIT_UNDO, &CChildFrame::OnEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, &CChildFrame::OnUpdateEditUndo)
	ON_COMMAND(ID_EDIT_CUT, &CChildFrame::OnEditCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, &CChildFrame::OnUpdateEditCut)
	ON_COMMAND(ID_EDIT_SELECT_ALL, &CChildFrame::OnEditSelectAll)
	ON_UPDATE_COMMAND_UI(ID_EDIT_SELECT_ALL, &CChildFrame::OnUpdateEditSelectAll)
	ON_COMMAND(ID_EDIT_REDO, &CChildFrame::OnEditRedo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_REDO, &CChildFrame::OnUpdateEditRedo)
	ON_COMMAND(ID_SAVE_LIBRARYBOX, &CChildFrame::OnSaveLibrarybox)
	ON_UPDATE_COMMAND_UI(ID_SAVE_LIBRARYBOX, &CChildFrame::OnUpdateSaveLibrarybox)
	ON_COMMAND(ID_LOAD_LIBRARYBOX, &CChildFrame::OnLoadLibrarybox)
	ON_UPDATE_COMMAND_UI(ID_LOAD_LIBRARYBOX, &CChildFrame::OnUpdateLoadLibrarybox)
	ON_COMMAND(ID_CLEAN_LOG, &CChildFrame::OnCleanLog)
	ON_UPDATE_COMMAND_UI(ID_CLEAN_LOG, &CChildFrame::OnUpdateCleanLog)
	ON_COMMAND(ID_COMP_DELETE, &CChildFrame::OnCompDelete)
	ON_UPDATE_COMMAND_UI(ID_COMP_DELETE, &CChildFrame::OnUpdateCompDelete)
	ON_COMMAND(ID_UNCONECT, &CChildFrame::OnUnconect)
	ON_UPDATE_COMMAND_UI(ID_UNCONECT, &CChildFrame::OnUpdateUnconect)
END_MESSAGE_MAP()

// CChildFrame ����/�Ҹ�

CChildFrame::CChildFrame()
{
	// TODO: ���⿡ ��� �ʱ�ȭ �ڵ带 �߰��մϴ�.
}

CChildFrame::~CChildFrame()
{
}


BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡�� Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.
	if( !CMDIChildWndEx::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}

// CChildFrame ����

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWndEx::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWndEx::Dump(dc);
}
#endif //_DEBUG

// CChildFrame �޽��� ó����

void CChildFrame::OnFilePrint()
{
	if (m_dockManager.IsPrintPreviewValid())
	{
		PostMessage(WM_COMMAND, AFX_ID_PREVIEW_PRINT);
	}
}

void CChildFrame::OnFilePrintPreview()
{
	if (m_dockManager.IsPrintPreviewValid())
	{
		PostMessage(WM_COMMAND, AFX_ID_PREVIEW_CLOSE);  // �μ� �̸� ���� ��带 �ݽ��ϴ�.
	}
}

void CChildFrame::OnUpdateFilePrintPreview(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_dockManager.IsPrintPreviewValid());
}


/*************** Ribbon check box ó���� ***************/
/* out put wnd on/off ó���� */
void CChildFrame::OnCheckoutput()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}
void CChildFrame::OnUpdateCheckoutput(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	pCmdUI->Enable(TRUE);
	//pCmdUI->SetCheck(BST_CHECKED);
}


/* properties wnd on/off ó���� */
void CChildFrame::OnCheckproperties()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}
void CChildFrame::OnUpdateCheckproperties(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	pCmdUI->Enable(TRUE);
	//pCmdUI->SetCheck(BST_CHECKED);
}


/* tool box wnd on/off ó���� */
void CChildFrame::OnChecktoolbox()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}
void CChildFrame::OnUpdateChecktoolbox(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	pCmdUI->Enable(TRUE);
	//pCmdUI->SetCheck(BST_CHECKED);
}
/*************** Ribbon check box ó���� *****************/





/*************** Ribbon button ó���� *****************/
/* ���� button ó���� */
void CChildFrame::OnButtonstop()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	AfxMessageBox(_T("stop"));
}
void CChildFrame::OnUpdateButtonstop(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	pCmdUI->Enable(TRUE);

}


/* ��� button ó���� */
void CChildFrame::OnButtoncontinue()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	AfxMessageBox(_T("continue"));
}
void CChildFrame::OnUpdateButtoncontinue(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	pCmdUI->Enable(TRUE);
}


/* ������ botton ó���� */
void CChildFrame::OnButtonact()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	AfxMessageBox(_T("mode: active"));
}
void CChildFrame::OnUpdateButtonact(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	pCmdUI->Enable(TRUE);
}


/* ������� botton ó���� */
void CChildFrame::OnButtonedit()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	AfxMessageBox(_T("mode: edit"));
}
void CChildFrame::OnUpdateButtonedit(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	pCmdUI->Enable(TRUE);
}
/*************** Ribbon button ó���� *****************/




/*************** Ribbon Ŭ������ ó���� *****************/
// https://msdn.microsoft.com/ko-kr/library/80db3kax.aspx
void CChildFrame::OnEditCopy()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	AfxMessageBox(_T("copy"));
	if (!OpenClipboard())
	{
		AfxMessageBox(_T("Cannot open the Clipboard"));
		return;
	}
	// Remove the current Clipboard contents
	if (!EmptyClipboard())
	{
		AfxMessageBox(_T("Cannot empty the Clipboard"));
		return;
	}
	// Get the currently selected data


	CloseClipboard();

}
void CChildFrame::OnUpdateEditCopy(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}


void CChildFrame::OnEditPaste()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	AfxMessageBox(_T("paste"));
}
void CChildFrame::OnUpdateEditPaste(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}


void CChildFrame::OnEditCut()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	AfxMessageBox(_T("cut"));
}
void CChildFrame::OnUpdateEditCut(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}


void CChildFrame::OnEditSelectAll()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	AfxMessageBox(_T("select all"));
}
void CChildFrame::OnUpdateEditSelectAll(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}
/*************** Ribbon Ŭ������ ó���� *****************/





/*************** Ribbon redo, undo ó���� *****************/
void CChildFrame::OnEditUndo()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	AfxMessageBox(_T("undo"));
}
void CChildFrame::OnUpdateEditUndo(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}


void CChildFrame::OnEditRedo()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	AfxMessageBox(_T("redo"));
}
void CChildFrame::OnUpdateEditRedo(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}
/*************** Ribbon redo, undo ó���� *****************/



/*************** Ribbon library box control *****************/
void CChildFrame::OnSaveLibrarybox()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	AfxMessageBox(_T("save lib box"));
}
void CChildFrame::OnUpdateSaveLibrarybox(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}


void CChildFrame::OnLoadLibrarybox()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	AfxMessageBox(_T("load lib box"));
}
void CChildFrame::OnUpdateLoadLibrarybox(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}
/*************** Ribbon library box control END *****************/



/*************** Ribbon output wnd control *****************/
void CChildFrame::OnCleanLog()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	AfxMessageBox(_T("clean log"));
}
void CChildFrame::OnUpdateCleanLog(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}
/*************** Ribbon output wnd control END*****************/


void CChildFrame::OnCompDelete()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}


void CChildFrame::OnUpdateCompDelete(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}


void CChildFrame::OnUnconect()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}


void CChildFrame::OnUpdateUnconect(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}
