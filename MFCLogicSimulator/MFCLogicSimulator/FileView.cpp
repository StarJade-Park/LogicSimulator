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
#include "mainfrm.h"
#include "FileView.h"
#include "Resource.h"
#include "MFCLogicSimulator.h"
#include "MFCLogicSimulatorDoc.h"
#include "MFCLogicSimulatorView.h"
#include "ChildFrm.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileView

CFileView::CFileView()
{
	LIBRARY_BOX_DATA dummy;
	//coreDataList.resize(1,dummy);
	coreDataList.resize(0);

}

CFileView::~CFileView()
{
}

void CFileView::addLibraryBox(CString LibraryBoxName)
{
	m_wndFileView.InsertItem(LibraryBoxName, 1, 2, hLib);
}

BEGIN_MESSAGE_MAP(CFileView, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	//ON_COMMAND(ID_PROPERTIES, OnProperties)
	ON_COMMAND(ID_OPEN, OnFileOpen)
	ON_COMMAND(ID_OPEN_WITH, OnFileOpenWith)
	ON_COMMAND(ID_DUMMY_COMPILE, OnDummyCompile)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CLEAR, OnEditClear)
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceBar �޽��� ó����

int CFileView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// �並 ����ϴ�.
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS;
	
	if (!m_wndFileView.Create(dwViewStyle, rectDummy, this, 4))
	{
		TRACE0("���� ���ڸ� ������ ���߽��ϴ�.\n");
		return -1;      // ������ ���߽��ϴ�.
	}

	// �� �̹����� �ε��մϴ�.
	/* IDB_FILE_VIEW ���ҽ��� 16�ȼ� ������ ��� ����Ѵ�. */
	m_FileViewImages.Create(IDB_FILE_VIEW, 16, 0, RGB(255, 0, 255));
	m_wndFileView.SetImageList(&m_FileViewImages, TVSIL_NORMAL);

	m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_EXPLORER);
	m_wndToolBar.LoadToolBar(IDR_EXPLORER, 0, 0, TRUE /* ��� */);

	OnChangeVisualStyle();

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));

	m_wndToolBar.SetOwner(this);
	
	// ��� ����� �θ� �������� �ƴ� �� ��Ʈ���� ���� ����õ˴ϴ�.
	m_wndToolBar.SetRouteCommandsViaFrame(FALSE);

	// ���� Ʈ�� �� �����͸� ä��ϴ�.
	FillFileView();
	AdjustLayout();



	return 0;
}

void CFileView::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

void CFileView::FillFileView()
{	// tool box data
	HTREEITEM hRoot = m_wndFileView.InsertItem(_T("Logic Simulator"), 0, 0);
	m_wndFileView.SetItemState(hRoot, TVIS_BOLD, TVIS_BOLD);
	/*
		0 ���� | 1,2 ��Ÿ | 3,4 and | 5,6 nand | 7,8 or |
		9,10 nor | 11,12 xor | 13,14 not | 15,16 FF
	*/

	HTREEITEM hWire = m_wndFileView.InsertItem(_T("Terminal"), 0, 0, hRoot);
	m_wndFileView.InsertItem(_T("Splitter"), 1, 2, hWire);
	m_wndFileView.InsertItem(_T("Pin"), 1, 2, hWire);
	m_wndFileView.InsertItem(_T("Probe"), 1, 2, hWire);

	HTREEITEM hLog = m_wndFileView.InsertItem(_T("Logic Gate"), 0, 0, hRoot);
	m_wndFileView.InsertItem(_T("AND"), 3, 4, hLog);
	m_wndFileView.InsertItem(_T("NAND"), 5, 6, hLog);
	m_wndFileView.InsertItem(_T("OR"), 7, 8, hLog);
	m_wndFileView.InsertItem(_T("NOR"), 9, 10, hLog);
	m_wndFileView.InsertItem(_T("XOR"), 11, 12, hLog);
	m_wndFileView.InsertItem(_T("NOT"), 13, 14, hLog);

	HTREEITEM hFlip = m_wndFileView.InsertItem(_T("Flip-flop"), 0, 0, hRoot);
	m_wndFileView.InsertItem(_T("D-FF"), 15, 16, hFlip);
	m_wndFileView.InsertItem(_T("JK-FF"), 15, 16, hFlip);
	m_wndFileView.InsertItem(_T("T-FF"), 15, 16, hFlip);

	HTREEITEM hInp = m_wndFileView.InsertItem(_T("Input"), 0, 0, hRoot);
	m_wndFileView.InsertItem(_T("1 Bit input switch"), 1, 2, hInp);
	m_wndFileView.InsertItem(_T("Clock"), 1, 2, hInp);

	HTREEITEM hOut = m_wndFileView.InsertItem(_T("Output"), 0, 0, hRoot);
	m_wndFileView.InsertItem(_T("1 Bit out put lamp"), 1, 2, hOut);
	m_wndFileView.InsertItem(_T("7-segment"), 1, 2, hOut);

	hLib = m_wndFileView.InsertItem(_T("Library Box"), 0, 0, hRoot);
	//m_wndFileView.InsertItem(_T("lib box test"), 1, 2, hLib);


	m_wndFileView.Expand(hRoot, TVE_EXPAND);
	m_wndFileView.Expand(hWire, TVE_EXPAND);
	m_wndFileView.Expand(hLog, TVE_EXPAND);
	m_wndFileView.Expand(hFlip, TVE_EXPAND);
	m_wndFileView.Expand(hInp, TVE_EXPAND);
	m_wndFileView.Expand(hOut, TVE_EXPAND);
	m_wndFileView.Expand(hLib, TVE_EXPAND);

}

void CFileView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CTreeCtrl* pWndTree = (CTreeCtrl*) &m_wndFileView;
	ASSERT_VALID(pWndTree);

	if (pWnd != pWndTree)
	{
		CDockablePane::OnContextMenu(pWnd, point);
		return;
	}

	if (point != CPoint(-1, -1))
	{
		// Ŭ���� �׸��� �����մϴ�.
		CPoint ptTree = point;
		pWndTree->ScreenToClient(&ptTree);

		UINT flags = 0;
		HTREEITEM hTreeItem = pWndTree->HitTest(ptTree, &flags);
		if (hTreeItem != NULL)
		{
			pWndTree->SelectItem(hTreeItem);
		}
	}

	pWndTree->SetFocus();
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EXPLORER, point.x, point.y, this, TRUE);
}

void CFileView::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	m_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndFileView.SetWindowPos(NULL, rectClient.left + 1, rectClient.top + cyTlb + 1, rectClient.Width() - 2, rectClient.Height() - cyTlb - 2, SWP_NOACTIVATE | SWP_NOZORDER);
}

//void CFileView::OnProperties()
//{
//	AfxMessageBox(_T("�Ӽ�...."));
//
//}

void CFileView::OnFileOpen()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

void CFileView::OnFileOpenWith()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

void CFileView::OnDummyCompile()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

void CFileView::OnEditCut()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

void CFileView::OnEditCopy()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

void CFileView::OnEditClear()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

void CFileView::OnPaint()
{
	CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

	CRect rectTree;
	m_wndFileView.GetWindowRect(rectTree);
	ScreenToClient(rectTree);

	rectTree.InflateRect(1, 1);
	dc.Draw3dRect(rectTree, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}

void CFileView::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);

	m_wndFileView.SetFocus();
}

void CFileView::OnChangeVisualStyle()
{
	m_wndToolBar.CleanUpLockedImages();
	m_wndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_EXPLORER_24 : IDR_EXPLORER, 0, 0, TRUE /* ��� */);
	m_FileViewImages.DeleteImageList();
	UINT uiBmpId = theApp.m_bHiColorIcons ? IDB_FILE_VIEW_24 : IDB_FILE_VIEW;

	CBitmap bmp;
	if (!bmp.LoadBitmap(uiBmpId))
	{
		TRACE(_T("��Ʈ���� �ε��� �� �����ϴ�. %x\n"), uiBmpId);
		ASSERT(FALSE);
		return;
	}

	BITMAP bmpObj;
	bmp.GetBitmap(&bmpObj);
	UINT nFlags = ILC_MASK;

	nFlags |= (theApp.m_bHiColorIcons) ? ILC_COLOR24 : ILC_COLOR4;

	m_FileViewImages.Create(16, bmpObj.bmHeight, nFlags, 0, 0);
	m_FileViewImages.Add(&bmp, RGB(255, 0, 255));
	m_wndFileView.SetImageList(&m_FileViewImages, TVSIL_NORMAL);
}

CViewTree * CFileView::getCFileViewTree()
{
	return &m_wndFileView;
}

void CFileView::addCoreData(LIBRARY_BOX_DATA & coreData)
{
	coreDataList.push_back(coreData);
}

void CFileView::getCoreData(LIBRARY_BOX_DATA & coreData, int index)
{
	coreData = LIBRARY_BOX_DATA(coreDataList[index]);
}

void CFileView::initCoreData()
{
	TCHAR path[_MAX_PATH];
	GetModuleFileName(NULL, path, sizeof path);
	CString currentExcuteFilePath = path;
	int i = currentExcuteFilePath.ReverseFind('\\');
	currentExcuteFilePath = currentExcuteFilePath.Left(i);
	
	CString coreDataFilePath = currentExcuteFilePath +
		CString(_T("\\MFCLogicSimulatorCoreData\\*.ls"));

	//�˻� Ŭ����
	CFileFind finder;

	//CFileFind�� ����, ���͸��� �����ϸ� TRUE �� ��ȯ��
	BOOL bWorking = finder.FindFile(coreDataFilePath); //

	CString filepath;
	CString fileName;
	CString massageName,massagePath;
	while (bWorking)
	{
		//���� ���� / ���� �� �����ϸ�ٸ� TRUE ��ȯ
		bWorking = finder.FindNextFile();
		//���� �϶�
		if (finder.IsArchived()){
			CString _fileName = finder.GetFileName();
			// �������� �������� ����������� ����
			if (_fileName == _T(".") ||
				_fileName == _T("..") ||
				_fileName == _T("Thumbs.db")) continue;
			filepath = finder.GetFilePath();
			fileName = finder.GetFileName();
			loadCoreData(filepath, fileName);

		}	
	}
	m_wndFileView.Expand(hLib, TVE_EXPAND);
	AfxMessageBox(_T("Complete load Core data"));
	return ;
}

void CFileView::loadCoreData(CString PathName,CString fileName)
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

	bool isSuccessReadFile = false;
	CFile  librayboxFile;

	vector <COMPONENT_DATA> dummy;

	LIBRARY_BOX_DATA coreData;

	if (librayboxFile.Open(PathName, CFile::modeRead)) {
		CArchive ar(&librayboxFile, CArchive::load);
		try {
			if (fileName == "D-FF.ls") {
				pDoc->loadEngineComponentData(ar, &dummy);
				pDoc->loadEngineCoreData(ar, pDoc->D_FF_Data);
				addCoreData(pDoc->D_FF_Data);
			}
			else if (fileName == "JK-FF.ls") {
				pDoc->loadEngineComponentData(ar, &dummy);
				pDoc->loadEngineCoreData(ar, pDoc->JK_FF_Data);
				addCoreData(pDoc->JK_FF_Data);
			}
			else if (fileName == "T-FF.ls") {
				pDoc->loadEngineComponentData(ar, &dummy);
				pDoc->loadEngineCoreData(ar, pDoc->T_FF_Data);
				addCoreData(pDoc->T_FF_Data);
			}
			else {
				pDoc->loadEngineComponentData(ar, &dummy);
				pDoc->loadEngineCoreData(ar, coreData);
				addCoreData(coreData);
				
			}
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

	if (isSuccessReadFile == true) {
		pFileView->addLibraryBox(fileName);
		str.Format(_T("in file view : load success\n"));
		pOutput->addBuildWindowString(str);
	}
	else {
		str.Format(_T("in file view : load success\n"));
		pOutput->addBuildWindowString(str);
	}
}


