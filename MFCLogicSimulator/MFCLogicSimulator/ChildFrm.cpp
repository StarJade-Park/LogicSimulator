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
#include "ViewTree.h"
#include "MFCLogicSimulatorDoc.h"
#include "MainFrm.h"
#include "MFCLogicSimulatorView.h"
#include "FileView.h"
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
	ON_COMMAND(ID_BUTTONACT, &CChildFrame::OnButtonExcutingMode)
	ON_UPDATE_COMMAND_UI(ID_BUTTONACT, &CChildFrame::OnUpdateButtonExcutingMode)
	ON_COMMAND(ID_BUTTONEDIT, &CChildFrame::OnButtonEditMode)
	ON_UPDATE_COMMAND_UI(ID_BUTTONEDIT, &CChildFrame::OnUpdateButtonEditMode)
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
	ON_COMMAND(ID_COMP_DELETE, &CChildFrame::OnComponentDelete)
	ON_UPDATE_COMMAND_UI(ID_COMP_DELETE, &CChildFrame::OnUpdateComponentDelete)
	ON_COMMAND(ID_UNCONECT, &CChildFrame::OnUnconnect)
	ON_UPDATE_COMMAND_UI(ID_UNCONECT, &CChildFrame::OnUpdateUnconnect)
END_MESSAGE_MAP()

// CChildFrame ����/�Ҹ�

CChildFrame::CChildFrame()
{
	selectedComponentID = 0;
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
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CFileView* pFileView = pFrame->getCFileView();
	CViewTree* pToolbox = pFileView->getCFileViewTree();
	CChildFrame *pChild = (CChildFrame *)pFrame->GetActiveFrame();
	CMFCLogicSimulatorDoc *pDoc = (CMFCLogicSimulatorDoc *)pChild->GetActiveDocument();
	COutputWnd* pOutput = pFrame->getCOutputWnd();

	pDoc->isRunningMode = false;
	pDoc->isCurcuitOcillate = false;
	CMFCLogicSimulatorView* pView = (CMFCLogicSimulatorView*)pChild->GetActiveView();
	pView->stopUpdating();
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CString str;
	str.Format(_T("in rebbon menu : stop updating curcuit \n"));
	pOutput->addBuildWindowString(str);

}
void CChildFrame::OnUpdateButtonstop(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	pCmdUI->Enable(TRUE);
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CChildFrame *pChild = (CChildFrame *)pFrame->GetActiveFrame();
	CMFCLogicSimulatorDoc *pDoc = (CMFCLogicSimulatorDoc *)pChild->GetActiveDocument();


	if (pDoc->isCurcuitOcillate == true) {
		pCmdUI->SetCheck(1);

	}
	if (pDoc->isRunningMode == false) {
		pCmdUI->SetCheck(1);
	}
	else {
		pCmdUI->SetCheck(0);
	}
}


/* ��� button ó���� */
void CChildFrame::OnButtoncontinue()
{
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CFileView* pFileView = pFrame->getCFileView();
	CViewTree* pToolbox = pFileView->getCFileViewTree();
	CChildFrame *pChild = (CChildFrame *)pFrame->GetActiveFrame();
	CMFCLogicSimulatorDoc *pDoc = (CMFCLogicSimulatorDoc *)pChild->GetActiveDocument();
	COutputWnd* pOutput = pFrame->getCOutputWnd();
	CMFCLogicSimulatorView* pView = (CMFCLogicSimulatorView*)pChild->GetActiveView();
	
	pView->startUpdating();
	pDoc->isRunningMode = true;
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CString str;
	str.Format(_T("in rebbon menu : updating curcuit \n"));
	pOutput->addBuildWindowString(str);
}
void CChildFrame::OnUpdateButtoncontinue(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	pCmdUI->Enable(TRUE);

	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CChildFrame *pChild = (CChildFrame *)pFrame->GetActiveFrame();
	CMFCLogicSimulatorDoc *pDoc = (CMFCLogicSimulatorDoc *)pChild->GetActiveDocument();
	
	if (pDoc->isCurcuitOcillate == true) {
		pCmdUI->SetCheck(0);
		pDoc->isRunningMode = false;
	}
	if (pDoc->isRunningMode == true) {
		pCmdUI->SetCheck(1);
	}
	else {
		pCmdUI->SetCheck(0);
	}

}


/* ������ botton ó���� */
void CChildFrame::OnButtonExcutingMode()
{
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CFileView* pFileView = pFrame->getCFileView();
	CViewTree* pToolbox = pFileView->getCFileViewTree();
	CChildFrame *pChild = (CChildFrame *)pFrame->GetActiveFrame();
	CMFCLogicSimulatorDoc *pDoc = (CMFCLogicSimulatorDoc *)pChild->GetActiveDocument();
	COutputWnd* pOutput = pFrame->getCOutputWnd();

	pDoc->operationMode = OPERATION_MODE_VAlUE_CHANGE;
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CString str;
	str.Format(_T("in rebbon menu : mode change -> changing componnent value\n"));
	pOutput->addBuildWindowString(str);

}
void CChildFrame::OnUpdateButtonExcutingMode(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	pCmdUI->Enable(TRUE);


	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CChildFrame *pChild = (CChildFrame *)pFrame->GetActiveFrame();
	CMFCLogicSimulatorDoc *pDoc = (CMFCLogicSimulatorDoc *)pChild->GetActiveDocument();

	if (pDoc->operationMode == OPERATION_MODE_VAlUE_CHANGE) {
		pCmdUI->SetCheck(1);
	}
	else {
		pCmdUI->SetCheck(0);
	}
}


/* ������� botton ó���� */
void CChildFrame::OnButtonEditMode()
{
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CFileView* pFileView = pFrame->getCFileView();
	CViewTree* pToolbox = pFileView->getCFileViewTree();
	CChildFrame *pChild = (CChildFrame *)pFrame->GetActiveFrame();
	CMFCLogicSimulatorDoc *pDoc = (CMFCLogicSimulatorDoc *)pChild->GetActiveDocument();
	COutputWnd* pOutput = pFrame->getCOutputWnd();

	pDoc->operationMode = OPERATION_MODE_NONE;
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CString str;
	str.Format(_T("in rebbon menu : mode change -> edit mode\n"));
	pOutput->addBuildWindowString(str);
}
void CChildFrame::OnUpdateButtonEditMode(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	pCmdUI->Enable(TRUE);

	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CChildFrame *pChild = (CChildFrame *)pFrame->GetActiveFrame();
	CMFCLogicSimulatorDoc *pDoc = (CMFCLogicSimulatorDoc *)pChild->GetActiveDocument();

	if (pDoc->operationMode != OPERATION_MODE_VAlUE_CHANGE) {
		pCmdUI->SetCheck(1);
	}
	else {
		pCmdUI->SetCheck(0);
	}

}
/*************** Ribbon button ó���� *****************/




/*************** Ribbon Ŭ������ ó���� *****************/
// https://msdn.microsoft.com/ko-kr/library/80db3kax.aspx
void CChildFrame::OnEditCopy()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CChildFrame *pChild = (CChildFrame *)pFrame->GetActiveFrame();
	CMFCLogicSimulatorDoc *pDoc = (CMFCLogicSimulatorDoc *)pChild->GetActiveDocument();
	selectedComponentID = pDoc->selectedComponentID;
	


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
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CChildFrame *pChild = (CChildFrame *)pFrame->GetActiveFrame();
	CMFCLogicSimulatorDoc *pDoc = (CMFCLogicSimulatorDoc *)pChild->GetActiveDocument();
	if (selectedComponentID <= 0) {
		return;
	}
		
	if (pDoc->engineComponentData[selectedComponentID].id > 0) {
		int x = pDoc->engineComponentData[selectedComponentID].x;
		int y = pDoc->engineComponentData[selectedComponentID].y;
	}



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
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CChildFrame *pChild = (CChildFrame *)pFrame->GetActiveFrame();
	CMFCLogicSimulatorDoc *pDoc = (CMFCLogicSimulatorDoc *)pChild->GetActiveDocument();
	COutputWnd* pOutput = pFrame->getCOutputWnd();
	CMFCLogicSimulatorView* pView = (CMFCLogicSimulatorView*)pChild->GetActiveView();
	CFileView *pFileView = (CFileView*)pFrame->getCFileView();
	CViewTree* pToolbox = pFileView->getCFileViewTree();

	CString str;
	CFileDialog load_dlg(true);
	CString PathName;
	CString fileName;
	str.Format(_T("in rebbon menu : try load library box\n"), pDoc->selectedComponentID);
	pOutput->addBuildWindowString(str);

	if (load_dlg.DoModal() == IDOK) {
		PathName = load_dlg.GetPathName();
		fileName = load_dlg.GetFileName();
		//AfxMessageBox(PathName);
	}

	bool isSuccessReadFile = false;
	CFile  librayboxFile;

	vector <COMPONENT_DATA> dummy; 

	LIBRARY_BOX_DATA coreData;
	
	if (librayboxFile.Open(PathName, CFile::modeRead)) {
		CArchive ar(&librayboxFile, CArchive::load);
		try {
			pDoc->loadEngineComponentData(ar, &dummy);
			pDoc->loadEngineCoreData(ar,coreData);
			pFileView->addCoreData(coreData);
			isSuccessReadFile = true;
			str.Format(_T("in rebbon menu : load library core data  to toolBox\n"), pDoc->selectedComponentID);
			pOutput->addBuildWindowString(str);
		}
		catch (CFileException *fe) {
			// ���ܰ� �߻��ϸ� �޼����ڽ��� ���Ͽ� ����ڿ��� �˸���.
			fe->ReportError();
		}
		catch (CArchiveException *ae) {
			// ���ܰ� �߻��ϸ� �޼����ڽ��� ���Ͽ� ����ڿ��� �˸���.
			ae->ReportError();
		}
		// CArchive �� �ݴ´�.
		ar.Close();
		// ������ �ݴ´�.
		librayboxFile.Close();
	}


	
	str.Format(_T("in rebbon menu : try delete component ->ID : %d \n"), pDoc->selectedComponentID);
	pOutput->addBuildWindowString(str);


	if (isSuccessReadFile == true) {
		pFileView->addLibraryBox(fileName);
		str.Format(_T("in rebbon menu : try add libbox to toolBox\n"), pDoc->selectedComponentID);
		pOutput->addBuildWindowString(str);
	}
	else {
		str.Format(_T("in rebbon menu : fail load library box -> readfile fail\n"), pDoc->selectedComponentID);
		pOutput->addBuildWindowString(str);
	}

	
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
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	//CChildFrame *pChild = (CChildFrame *)pFrame->GetActiveFrame();
	//CMFCLogicSimulatorDoc *pDoc = (CMFCLogicSimulatorDoc *)pChild->GetActiveDocument();
	COutputWnd* pOutput = pFrame->getCOutputWnd();
	//CMFCLogicSimulatorView* pView = (CMFCLogicSimulatorView*)pChild->GetActiveView();
	//CFileView *pFileView = (CFileView*)pFrame->getCFileView();
	//CViewTree* pToolbox = pFileView->getCFileViewTree();
	pOutput->resetBuildWindowString();
	AfxMessageBox(_T("Log clear"));
}
void CChildFrame::OnUpdateCleanLog(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}

void CChildFrame::OnComponentDelete()
{
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CChildFrame *pChild = (CChildFrame *)pFrame->GetActiveFrame();
	CMFCLogicSimulatorDoc *pDoc = (CMFCLogicSimulatorDoc *)pChild->GetActiveDocument();
	COutputWnd* pOutput = pFrame->getCOutputWnd();
	CMFCLogicSimulatorView* pView = (CMFCLogicSimulatorView*)pChild->GetActiveView();
	CString str;
	
	if (pDoc->operationMode == OPERATION_MODE_SELECT_COMPONENT) {
		str.Format(_T("in rebbon menu : try delete component ->ID : %d \n"), pDoc->selectedComponentID);
		pOutput->addBuildWindowString(str);
		pDoc->deleteComponentToEngine(pDoc->selectedComponentID);
		pView->Invalidate();
	}
	else {
		str.Format(_T("in rebbon menu : fail to delete component -> component not selected\n"));
		pOutput->addBuildWindowString(str);
	}

}
void CChildFrame::OnUpdateComponentDelete(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}

void CChildFrame::OnUnconnect()
{
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CChildFrame *pChild = (CChildFrame *)pFrame->GetActiveFrame();
	CMFCLogicSimulatorDoc *pDoc = (CMFCLogicSimulatorDoc *)pChild->GetActiveDocument();
	COutputWnd* pOutput = pFrame->getCOutputWnd();
	CMFCLogicSimulatorView* pView = (CMFCLogicSimulatorView*)pChild->GetActiveView();
	CString str;


	str.Format(_T("in rebbon menu : try disconnect\n"));
	pOutput->addBuildWindowString(str);
	pDoc->disconectComponent();
	pView->Invalidate();


}
void CChildFrame::OnUpdateUnconnect(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}
/*************** Ribbon output wnd control END*****************/


