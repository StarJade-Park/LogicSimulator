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

// MFCLogicSimulatorDoc.cpp : CMFCLogicSimulatorDoc Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "MFCLogicSimulator.h"
#endif

#include "MFCLogicSimulatorDoc.h"
#include "MainFrm.h"

#include <propkey.h>



#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMFCLogicSimulatorDoc

IMPLEMENT_DYNCREATE(CMFCLogicSimulatorDoc, CDocument)

BEGIN_MESSAGE_MAP(CMFCLogicSimulatorDoc, CDocument)
END_MESSAGE_MAP()


// CMFCLogicSimulatorDoc ����/�Ҹ�


//������ ����鼭 ���̺귯�� ������ �ִ´�
CMFCLogicSimulatorDoc::CMFCLogicSimulatorDoc()
{
	// TODO: ���⿡ ��ȸ�� ���� �ڵ带 �߰��մϴ�.
	engineComponentData.resize(10);
	currentSelectedItem = -1;
}

int CMFCLogicSimulatorDoc::itemSelectedInDoc()
{	
	// mainframe���� fileview�� Ʈ�� ���� ��ȸ
	// http://www.dreamy.pe.kr/zbxe/CodeClip/18117

	CMainFrame* p_MainFrm = (CMainFrame*)AfxGetMainWnd();

	CFileView* p_FileViewInDoc = p_MainFrm->getCFileView();

	CViewTree* p_ToolboxInDoc = p_FileViewInDoc->getCFileViewTree();

	// Ʈ�� ��Ʈ�� ������ �ε���
	// goo.gl/mdFKLz
	int indexOfItem = 0;

	HTREEITEM hItem = p_ToolboxInDoc->GetSelectedItem();
	HTREEITEM hComp = p_ToolboxInDoc->GetChildItem(NULL);

	while (hComp)
	{
		if (hComp == hItem) break;
		hComp = p_ToolboxInDoc->GetNextItem(hComp, TVGN_NEXTVISIBLE);
		++indexOfItem;
	}


	return indexOfItem;
}

CMFCLogicSimulatorDoc::~CMFCLogicSimulatorDoc()
{
}

BOOL CMFCLogicSimulatorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ���⿡ ���ʱ�ȭ �ڵ带 �߰��մϴ�.
	// SDI ������ �� ������ �ٽ� ����մϴ�.

	return TRUE;
}




// CMFCLogicSimulatorDoc serialization

void CMFCLogicSimulatorDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	}
	else
	{
		// TODO: ���⿡ �ε� �ڵ带 �߰��մϴ�.


	}
}

#ifdef SHARED_HANDLERS

// ����� �׸��� �����մϴ�.
void CMFCLogicSimulatorDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// ������ �����͸� �׸����� �� �ڵ带 �����Ͻʽÿ�.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// �˻� ó���⸦ �����մϴ�.
void CMFCLogicSimulatorDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ������ �����Ϳ��� �˻� �������� �����մϴ�.
	// ������ �κ��� ";"�� ���еǾ�� �մϴ�.

	// ��: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CMFCLogicSimulatorDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}


#endif // SHARED_HANDLERS


bool CMFCLogicSimulatorDoc::addComponentToEngine(int _x, int _y)
{
	//��ǰ ���� ��尡 �ƴϸ� ������ ��ȯ��
	if (currentSelectedItem < 1 ) {
		return false;
	}

	//��ǰ���� ��带 �����Ѵ�
	

	currentSelectedItem;
	engineComponentData;
	COMPONENT_TYPE selectedType; 

	//��ǰ Ÿ���� �˾Ƴ���
	switch (currentSelectedItem ) {

		//wire
	case  ITEM_WIRE:
		selectedType = COMPONENT_TYPE_WIRE;
		break;
	case  ITEM_PIN:
		selectedType = COMPONENT_TYPE_INPUT_PIN;
		break;
	case  ITEM_PROBE:
		selectedType = COMPONENT_TYPE_OUTPUT_PIN;
		break;

		//gate
	case  ITEM_AND:
		selectedType = COMPONENT_TYPE_AND_GATE;
		break;
	case  ITEM_NAND:
		selectedType = COMPONENT_TYPE_NAND_GATE;
		break;
	case  ITEM_OR:
		selectedType = COMPONENT_TYPE_OR_GATE;
		break;
	case  ITEM_NOR:
		selectedType = COMPONENT_TYPE_NOR_GATE;
		break;
	case  ITEM_XOR:
		selectedType = COMPONENT_TYPE_XOR_GATE;
		break;
	case  ITEM_NOT:
		selectedType = COMPONENT_TYPE_NOT_GATE;
		break;

		//flipflop
	case  ITEM_DFF:
		selectedType = COMPONENT_TYPE_WIRE;
		break;
	case  ITEM_JKFF:
		selectedType = COMPONENT_TYPE_WIRE;
		break;
	case  ITEM_TFF:
		selectedType = COMPONENT_TYPE_WIRE;
		break;

		//input
	case  ITEM_1BITBUTIN:
		selectedType = COMPONENT_TYPE_ONE_BIT_SWITCH;
		break;
	case  ITEM_CLOCK:
		selectedType = COMPONENT_TYPE_CLOCK;
		break;

		//output
	case  ITEM_1BITBUTOUT:
		selectedType = COMPONENT_TYPE_ONE_BIT_LAMP;
		break;
	case  ITEM_7SEGMENT:
		selectedType = COMPONENT_TYPE_7SEGMENT;
		break;


	case  ITEM_ETC:
		break;

	//����� ���� Ÿ���� ������ �ʰ� ������ ��ȯ�Ѵ�
	default :
		return false;
		break;
	}
	
	// �׽�Ʈ ��
	COMPONENT_INFO addComponent;
	addComponent.componentType = selectedType;
	
	//�������� �ʴ� ����϶�
	if (logicSimulatorEngine.addComponent(addComponent) == false) {
		CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
		COutputWnd* pOutput = pFrame->getCOutputWnd();
		CString str;
		str.Format(_T("in mfc logicsimulator doc : add component fail -> not support component\n"),
			addComponent.componentID, selectedType, _x, _y);
		pOutput->addBuildWindowString(str);
		return false;
	}
	
	//����� ���ڸ��� Ȯ���Ѵ�
	if (addComponent.componentID >= engineComponentData.size()) {
		engineComponentData.resize(engineComponentData.size() + 10);
	}
	//��ť��Ʈ �����Ϳ� ����ִ´�
	engineComponentData[addComponent.componentID].id = addComponent.componentID;
	engineComponentData[addComponent.componentID].type = selectedType;
	engineComponentData[addComponent.componentID].x = _x;
	engineComponentData[addComponent.componentID].y = _y;
	engineComponentData[addComponent.componentID].direction = EAST;
	engineComponentData[addComponent.componentID].label = "";
	
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	COutputWnd* pOutput = pFrame->getCOutputWnd();
	CString str;
	str.Format(_T("in mfc logicsimulator doc : add component, ID : %d\n, type : %d (x,y) = (%d,%d),"), 
		addComponent.componentID, selectedType,_x,_y);
	pOutput->addBuildWindowString(str);
	return true;
	

}

// CMFCLogicSimulatorDoc ����

#ifdef _DEBUG
void CMFCLogicSimulatorDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMFCLogicSimulatorDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMFCLogicSimulatorDoc ���