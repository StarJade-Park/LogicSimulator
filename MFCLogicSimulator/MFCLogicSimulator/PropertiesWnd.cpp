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

#include "PropertiesWnd.h"
#include "Resource.h"
#include "MainFrm.h"
#include "MFCLogicSimulator.h"

#include "ViewTree.h"
#include "MFCLogicSimulatorDoc.h"
#include "MFCLogicSimulatorView.h"
#include "ChildFrm.h"
#include "FileView.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar

CPropertiesWnd::CPropertiesWnd()
{
	m_nComboHeight = 0;
}

CPropertiesWnd::~CPropertiesWnd()
{
}

BEGIN_MESSAGE_MAP(CPropertiesWnd, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_EXPAND_ALL, OnExpandAllProperties)
	ON_UPDATE_COMMAND_UI(ID_EXPAND_ALL, OnUpdateExpandAllProperties)
	ON_COMMAND(ID_SORTPROPERTIES, OnSortProperties)
	ON_UPDATE_COMMAND_UI(ID_SORTPROPERTIES, OnUpdateSortProperties)
	ON_COMMAND(ID_PROPERTIES1, OnProperties1)
	ON_UPDATE_COMMAND_UI(ID_PROPERTIES1, OnUpdateProperties1)
	ON_COMMAND(ID_PROPERTIES2, OnProperties2)
	ON_UPDATE_COMMAND_UI(ID_PROPERTIES2, OnUpdateProperties2)
	ON_WM_SETFOCUS()
	ON_WM_SETTINGCHANGE()
	ON_REGISTERED_MESSAGE(AFX_WM_PROPERTY_CHANGED, OnPropertyChangeMSG) // ������Ƽ ����˻�����
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar �޽��� ó����

void CPropertiesWnd::AdjustLayout()
{
	if (GetSafeHwnd () == NULL || (AfxGetMainWnd() != NULL && AfxGetMainWnd()->IsIconic()))
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	//m_wndObjectCombo.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), m_nComboHeight, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top + m_nComboHeight, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndPropList.SetWindowPos(NULL, rectClient.left, rectClient.top + m_nComboHeight + cyTlb, rectClient.Width(), rectClient.Height() -(m_nComboHeight+cyTlb), SWP_NOACTIVATE | SWP_NOZORDER);
}

CPropertiesToolBar * CPropertiesWnd::getProperties()
{
	return &m_wndToolBar;
}

int CPropertiesWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	if (!m_wndPropList.Create(WS_VISIBLE | WS_CHILD, rectDummy, this, 2))
	{
		TRACE0("�Ӽ� ǥ�� ������ ���߽��ϴ�. \n");
		return -1;      // ������ ���߽��ϴ�.
	}

	InitPropList();

	m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_PROPERTIES);
	m_wndToolBar.LoadToolBar(IDR_PROPERTIES, 0, 0, TRUE /* ��� */);
	m_wndToolBar.CleanUpLockedImages();
	m_wndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_PROPERTIES_HC : IDR_PROPERTIES, 0, 0, TRUE /* ��� */);

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));
	m_wndToolBar.SetOwner(this);

	// ��� ����� �θ� �������� �ƴ� �� ��Ʈ���� ���� ����õ˴ϴ�.
	m_wndToolBar.SetRouteCommandsViaFrame(FALSE);

	AdjustLayout();
	return 0;
}

void CPropertiesWnd::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

void CPropertiesWnd::OnExpandAllProperties()
{
	m_wndPropList.ExpandAll();
	// �Ӽ�â 1���� ��ư �ڵ鷯
}

void CPropertiesWnd::OnUpdateExpandAllProperties(CCmdUI* /* pCmdUI */)
{
}

void CPropertiesWnd::OnSortProperties()
{
	m_wndPropList.SetAlphabeticMode(!m_wndPropList.IsAlphabeticMode());
	// �Ӽ�â 2���� ��ư �ڵ鷯
}

void CPropertiesWnd::OnUpdateSortProperties(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_wndPropList.IsAlphabeticMode());
}

void CPropertiesWnd::OnProperties1()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	// �Ӽ�â 3��° ��ư �ڵ鷯
}

void CPropertiesWnd::OnUpdateProperties1(CCmdUI* /*pCmdUI*/)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}

void CPropertiesWnd::OnProperties2()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	// �Ӽ�â 4��° ��ư �ڵ鷯
}

void CPropertiesWnd::OnUpdateProperties2(CCmdUI* /*pCmdUI*/)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}

void CPropertiesWnd::InitPropList()
{
	SetPropListFont();
	/* �Ӽ�â ���� �ɼ� */
	m_wndPropList.EnableHeaderCtrl(FALSE);
	m_wndPropList.EnableDescriptionArea();
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties();

	/******************** �з�: ����Ʈ ���� ���� ************************/
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("��ǰ ����"));
	/* Ŭ�� ���� ����(���, �ϰ�) */
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Ŭ�� ���� ����"), (_variant_t) true,
		_T("true = ���, false = �ϰ�")));

	/* ������ ��ǰ id */
	CMFCPropertyGridProperty* pPropID = new CMFCPropertyGridProperty(_T("��ǰ id"),
		_T("")/* ������ ����Ʈ �̸��� �����ϰ��� �� */, _T("����׿� ��ǰ id ���â"));
	pPropID->AllowEdit(FALSE);

	/* ����Ʈ ���� ���� */
	CMFCPropertyGridProperty* pPropComp = new CMFCPropertyGridProperty(_T("��ǰ ����"),
		_T("")/* ������ ����Ʈ �̸��� �����ϰ��� �� */, _T("Logic gate �� �ϳ��� �����մϴ�."));
	pPropComp->AllowEdit(FALSE);

	pGroup1->AddSubItem(pPropID);
	pGroup1->AddSubItem(pPropComp);

	/* ����Ʈ ���� ���� */
	CMFCPropertyGridProperty* pPropDirc = new CMFCPropertyGridProperty(_T("����Ʈ ����"),
		_T("��")/* ������ ����Ʈ �̸��� �����ϰ��� �� */, _T("��ǰ ������ �����մϴ�."));
	pPropDirc->AddOption(_T("��"));
	pPropDirc->AddOption(_T("��"));
	pPropDirc->AddOption(_T("��"));
	pPropDirc->AddOption(_T("��"));
	pPropDirc->AllowEdit(FALSE);

	pGroup1->AddSubItem(pPropDirc);
	/* ��ǰ �� ���� */
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("��"),
		(_variant_t)_T("���� �����ϼ���."), _T("����Ʈ�� ���� �����մϴ�.")));
	m_wndPropList.AddProperty(pGroup1);

	/* ����Ʈ ũ�� ���� */
	CMFCPropertyGridProperty* pSize = new CMFCPropertyGridProperty(_T("��ǰ ��ġ"), 0, TRUE);
	pSize->AllowEdit(FALSE);

	CMFCPropertyGridProperty* pPropXY = new CMFCPropertyGridProperty(_T("x��ǥ"), (_variant_t) 0l, _T("��ǰ x��ǥ"));
	pSize->AddSubItem(pPropXY);
	pPropXY->AllowEdit(FALSE);

	pPropXY = new CMFCPropertyGridProperty( _T("y��ǥ"), (_variant_t) 0l, _T("��ǰ y��ǥ"));
	pSize->AddSubItem(pPropXY);
	pPropXY->AllowEdit(FALSE);

	m_wndPropList.AddProperty(pSize);
	/******************** �з�: ����Ʈ ���� �� ************************/
}

void CPropertiesWnd::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);
	m_wndPropList.SetFocus();
}

void CPropertiesWnd::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{
	CDockablePane::OnSettingChange(uFlags, lpszSection);
	SetPropListFont();
}
/* properties ������ ȣ�� */
LRESULT CPropertiesWnd::OnPropertyChangeMSG(WPARAM wParam, LPARAM lParam)
{
	CMFCPropertyGridProperty * pProperty = (CMFCPropertyGridProperty *)lParam;

	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	//CFileView* pFileView = pFrame->getCFileView();
	//CViewTree* pToolbox = pFileView->getCFileViewTree();
	CChildFrame *pChild = (CChildFrame *)pFrame->GetActiveFrame();
	CMFCLogicSimulatorDoc *pDoc = (CMFCLogicSimulatorDoc *)pChild->GetActiveDocument();
	COutputWnd* pOutput = pFrame->getCOutputWnd();

	pDoc->operationMode = OPERATION_MODE_SELECT_COMPONENT;
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CString str;
	str.Format(_T("in properties wnd menu : changed properties value\n"));
	pOutput->addBuildWindowString(str);

	// Note: the return value is not used.
	return(0);
}

void CPropertiesWnd::SetPropListFont()
{
	::DeleteObject(m_fntPropList.Detach());

	LOGFONT lf;
	afxGlobalData.fontRegular.GetLogFont(&lf);

	NONCLIENTMETRICS info;
	info.cbSize = sizeof(info);

	afxGlobalData.GetNonClientMetrics(info);

	lf.lfHeight = info.lfMenuFont.lfHeight;
	lf.lfWeight = info.lfMenuFont.lfWeight;
	lf.lfItalic = info.lfMenuFont.lfItalic;

	m_fntPropList.CreateFontIndirect(&lf);

	m_wndPropList.SetFont(&m_fntPropList);
	//m_wndObjectCombo.SetFont(&m_fntPropList);
}