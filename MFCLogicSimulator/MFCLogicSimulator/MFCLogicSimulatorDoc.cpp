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
	operationMode = OPERATION_MODE_NONE;
	selectedComponentID = 0;
	isRunningMode = false;
	isCurcuitOcillate = false;
}

int CMFCLogicSimulatorDoc::getSelectedItemIndexInToolBox(HTREEITEM hItem)
{
	// mainframe���� fileview�� Ʈ�� ���� ��ȸ
	// http://www.dreamy.pe.kr/zbxe/CodeClip/18117

	CMainFrame* p_MainFrm = (CMainFrame*)AfxGetMainWnd();
	CFileView* p_FileViewInDoc = p_MainFrm->getCFileView();
	CViewTree* p_ToolboxInDoc = p_FileViewInDoc->getCFileViewTree();

	int indexOfItem = 0;
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

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));
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
	if (operationMode != OPERATION_MODE_ADDING_COMPONENT) {
		return false;
	}

	COMPONENT_TYPE selectedType;
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	COutputWnd* pOutput = pFrame->getCOutputWnd();
	CString str;
	selectedType = getComponentTypeByToolBoxItemIndex(currentSelectedItemIndex);

	// �׽�Ʈ ��
	COMPONENT_INFO addComponent(selectedType);
	int ret = 0;

	if (selectedType == COMPONENT_TYPE_LIBRARY_BOX) {
		if (currentSelectedItemIndex == ITEM_DFF) {

		}
		else if (currentSelectedItemIndex == ITEM_JKFF) {

		}
		else if (currentSelectedItemIndex == ITEM_TFF) {

		}
		else if (currentSelectedItemIndex == ITEM_NOR) {
			ret = logicSimulatorEngine.addComponent(addComponent);
		}
		else if (currentSelectedItemIndex == ITEM_NAND) {
			ret = logicSimulatorEngine.addComponent(addComponent);
		}
		//����� ���� ���̺귯�� �ڽ��϶�
		else {

		}
	}
	else {
		ret = logicSimulatorEngine.addComponent(addComponent);
	}

	if (ret == false) {

		str.Format(_T("in mfc logicsimulator doc : add component fail -> not support component\n"),
			addComponent.componentID, selectedType, _x, _y);
		pOutput->addBuildWindowString(str);
		return ret;
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
	engineComponentData[addComponent.componentID].direction = DEFAULT_VALUE_ADDING_COMPONENT_DIRECTION;
	engineComponentData[addComponent.componentID].label = _T("���� �����ϼ���.");


	str.Format(_T("in mfc logicsimulator doc : add component, ID : %d\n, type : %d (x,y) = (%d,%d),"),
		addComponent.componentID, selectedType, _x, _y);
	pOutput->addBuildWindowString(str);
	return true;
}

bool CMFCLogicSimulatorDoc::connectComponent(COMPONENT_CONENTION_INFO & A, COMPONENT_CONENTION_INFO & B)
{
	bool AToBDirection;
	bool BToADirection;
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	COutputWnd* pOutput = pFrame->getCOutputWnd();

	CString str;
	AToBDirection = logicSimulatorEngine.connnectComponent(A, B);
	BToADirection = logicSimulatorEngine.connnectComponent(B, A);
	bool ret = false;
	if (AToBDirection == true) {

		str.Format(_T("in mfc logicsimulator doc : connect component ID : %d to ID: %d\n"),
			B.componentID, A.componentID);
		pOutput->addBuildWindowString(str);
		str.Format(_T("ID :%d type: %d terminal number : %d -> ID : %d type : %d terminal number : %d \n"),
			A.componentID, A.terminalType, A.terminalNumber,
			B.componentID, B.terminalType, B.terminalNumber);
		pOutput->addBuildWindowString(str);
		ret = true;
	}
	else if (BToADirection == true) {
		str.Format(_T("in mfc logicsimulator doc : connect component ID : %d to ID: %d\n"),
			B.componentID, A.componentID);
		pOutput->addBuildWindowString(str);
		str.Format(_T("ID :%d type: %d terminal number : %d -> ID : %d type : %d terminal number : %d \n"),
			B.componentID, B.terminalType, B.terminalNumber,
			A.componentID, A.terminalType, A.terminalNumber);
		pOutput->addBuildWindowString(str);
		ret = true;
	}
	else {
		str.Format(_T("in mfc logicsimulator doc : connect component fail\n"));
		pOutput->addBuildWindowString(str);

	}
	return ret;
}

COMPONENT_TYPE CMFCLogicSimulatorDoc::getComponentTypeByToolBoxItemIndex(int type)
{
	COMPONENT_TYPE ret = COMPONENT_TYPE_LIBRARY_BOX;
	switch (type) {
	case FOLDER_ROOT:
		ret = COMPONENT_TYPE_NONE;
		break;
		//wire
	case  ITEM_WIRE:
		ret = COMPONENT_TYPE_WIRE;
		break;
	case  ITEM_PIN:
		ret = COMPONENT_TYPE_INPUT_PIN;
		break;
	case  ITEM_PROBE:
		ret = COMPONENT_TYPE_OUTPUT_PIN;
		break;

		//gate
	case  ITEM_AND:
		ret = COMPONENT_TYPE_AND_GATE;
		break;
	case  ITEM_OR:
		ret = COMPONENT_TYPE_OR_GATE;
		break;
	case  ITEM_XOR:
		ret = COMPONENT_TYPE_XOR_GATE;
		break;
	case  ITEM_NOT:
		ret = COMPONENT_TYPE_NOT_GATE;
		break;

		//input
	case  ITEM_1BITBUTIN:
		ret = COMPONENT_TYPE_ONE_BIT_SWITCH;
		break;
	case  ITEM_CLOCK:
		ret = COMPONENT_TYPE_CLOCK;
		break;

		//output
	case  ITEM_1BITBUTOUT:
		ret = COMPONENT_TYPE_ONE_BIT_LAMP;
		break;
	case  ITEM_7SEGMENT:
		ret = COMPONENT_TYPE_7SEGMENT;
		break;
	}
	return ret;
}

COMPONENT_TYPE CMFCLogicSimulatorDoc::getCurrentSelectedComponentType()
{
	COMPONENT_TYPE ret = getComponentTypeByToolBoxItemIndex(currentSelectedItemIndex);
	return ret;
}

void CMFCLogicSimulatorDoc::make_NANDGATE(CLibraryBox & box)
{
	COMPONENT_INFO andgate(COMPONENT_TYPE_AND_GATE);
	COMPONENT_INFO notgate(COMPONENT_TYPE_NOT_GATE);
	COMPONENT_INFO wire1(COMPONENT_TYPE_WIRE);
	COMPONENT_INFO wire2(COMPONENT_TYPE_WIRE);
	COMPONENT_INFO wire3(COMPONENT_TYPE_WIRE);
	COMPONENT_INFO wire4(COMPONENT_TYPE_WIRE);
	COMPONENT_INFO inputpin1(COMPONENT_TYPE_INPUT_PIN);
	COMPONENT_INFO inputpin2(COMPONENT_TYPE_INPUT_PIN);
	COMPONENT_INFO outputpin1(COMPONENT_TYPE_OUTPUT_PIN);

	//1
	box.addComponent(outputpin1);
	//2
	box.addComponent(wire2);
	//3
	box.addComponent(andgate);
	//4
	box.addComponent(wire3);
	//5
	box.addComponent(wire1);
	//6
	box.addComponent(notgate);
	//7
	box.addComponent(inputpin1);
	//8
	box.addComponent(inputpin2);
	//9
	box.addComponent(wire4);

	COMPONENT_CONENTION_INFO B, A;
	{
		//A->B
		//input pin 1-> wire1
		A.componentID = inputpin1.componentID;
		A.terminalNumber = 0;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		B.componentID = wire1.componentID;
		B.terminalNumber = 0;
		B.terminalType = TERMINAL_TYPE_INPUT;
		box.connnectComponent(A, B);

		//input pin 2 -> wire2 
		A.componentID = inputpin2.componentID;
		A.terminalNumber = 0;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		B.componentID = wire2.componentID;
		B.terminalNumber = 0;
		B.terminalType = TERMINAL_TYPE_INPUT;
		box.connnectComponent(A, B);

		//wire1 -> andgate in 1
		A.componentID = wire1.componentID;
		A.terminalNumber = 0;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		B.componentID = andgate.componentID;
		B.terminalNumber = 0;
		B.terminalType = TERMINAL_TYPE_INPUT;
		box.connnectComponent(A, B);

		//wire2 -> andgate in 2
		A.componentID = wire2.componentID;
		A.terminalNumber = 0;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		B.componentID = andgate.componentID;
		B.terminalNumber = 1;
		B.terminalType = TERMINAL_TYPE_INPUT;
		box.connnectComponent(A, B);

		//andgate out 1 -> wire 3
		A.componentID = andgate.componentID;
		A.terminalNumber = 0;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		B.componentID = wire3.componentID;
		B.terminalNumber = 0;
		B.terminalType = TERMINAL_TYPE_INPUT;
		box.connnectComponent(A, B);

		//wire 3 -> notgate 
		A.componentID = wire3.componentID;
		A.terminalNumber = 0;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		B.componentID = notgate.componentID;
		B.terminalNumber = 0;
		B.terminalType = TERMINAL_TYPE_INPUT;
		box.connnectComponent(A, B);

		//notgate -> wire 4
		A.componentID = notgate.componentID;
		A.terminalNumber = 0;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		B.componentID = wire4.componentID;
		B.terminalNumber = 0;
		B.terminalType = TERMINAL_TYPE_INPUT;
		box.connnectComponent(A, B);

		//wire 4 -> output pin 
		A.componentID = wire4.componentID;
		A.terminalNumber = 0;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		B.componentID = outputpin1.componentID;
		B.terminalNumber = 0;
		B.terminalType = TERMINAL_TYPE_INPUT;
		box.connnectComponent(A, B);
	}
}

void CMFCLogicSimulatorDoc::make_NORGATE(CLibraryBox & box)
{
	COMPONENT_INFO andgate(COMPONENT_TYPE_OR_GATE);
	COMPONENT_INFO notgate(COMPONENT_TYPE_NOT_GATE);
	COMPONENT_INFO wire1(COMPONENT_TYPE_WIRE);
	COMPONENT_INFO wire2(COMPONENT_TYPE_WIRE);
	COMPONENT_INFO wire3(COMPONENT_TYPE_WIRE);
	COMPONENT_INFO wire4(COMPONENT_TYPE_WIRE);
	COMPONENT_INFO inputpin1(COMPONENT_TYPE_INPUT_PIN);
	COMPONENT_INFO inputpin2(COMPONENT_TYPE_INPUT_PIN);
	COMPONENT_INFO outputpin1(COMPONENT_TYPE_OUTPUT_PIN);

	box.addComponent(inputpin1);
	box.addComponent(inputpin2);
	box.addComponent(wire1);
	box.addComponent(wire2);
	box.addComponent(andgate);
	box.addComponent(wire3);
	box.addComponent(notgate);
	box.addComponent(wire4);
	box.addComponent(outputpin1);

	COMPONENT_CONENTION_INFO B, A;
	{
		//A->B
		//input pin 1-> wire1
		A.componentID = inputpin1.componentID;
		A.terminalNumber = 0;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		B.componentID = wire1.componentID;
		B.terminalNumber = 0;
		B.terminalType = TERMINAL_TYPE_INPUT;
		box.connnectComponent(A, B);

		//input pin 2 -> wire2 
		A.componentID = inputpin2.componentID;
		A.terminalNumber = 0;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		B.componentID = wire2.componentID;
		B.terminalNumber = 0;
		B.terminalType = TERMINAL_TYPE_INPUT;
		box.connnectComponent(A, B);

		//wire1 -> andgate in 1
		A.componentID = wire1.componentID;
		A.terminalNumber = 0;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		B.componentID = andgate.componentID;
		B.terminalNumber = 0;
		B.terminalType = TERMINAL_TYPE_INPUT;
		box.connnectComponent(A, B);

		//wire2 -> andgate in 2
		A.componentID = wire2.componentID;
		A.terminalNumber = 0;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		B.componentID = andgate.componentID;
		B.terminalNumber = 1;
		B.terminalType = TERMINAL_TYPE_INPUT;
		box.connnectComponent(A, B);

		//andgate out 1 -> wire 3
		A.componentID = andgate.componentID;
		A.terminalNumber = 0;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		B.componentID = wire3.componentID;
		B.terminalNumber = 0;
		B.terminalType = TERMINAL_TYPE_INPUT;
		box.connnectComponent(A, B);

		//wire 3 -> notgate 
		A.componentID = wire3.componentID;
		A.terminalNumber = 0;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		B.componentID = notgate.componentID;
		B.terminalNumber = 0;
		B.terminalType = TERMINAL_TYPE_INPUT;
		box.connnectComponent(A, B);

		//notgate -> wire 4
		A.componentID = notgate.componentID;
		A.terminalNumber = 0;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		B.componentID = wire4.componentID;
		B.terminalNumber = 0;
		B.terminalType = TERMINAL_TYPE_INPUT;
		box.connnectComponent(A, B);

		//wire 4 -> output pin 
		A.componentID = wire4.componentID;
		A.terminalNumber = 0;
		A.terminalType = TERMINAL_TYPE_OUTPUT;
		B.componentID = outputpin1.componentID;
		B.terminalNumber = 0;
		B.terminalType = TERMINAL_TYPE_INPUT;
		box.connnectComponent(A, B);
	}
}

void CMFCLogicSimulatorDoc::getStringByCOMPONENT_TYPE(COMPONENT_TYPE compType, CString& CS)
{
	switch (compType) {
	case COMPONENT_TYPE_NONE:
		CS = _T("none");
		break;
	case COMPONENT_TYPE_INPUT_PIN:
		CS = _T("Input pin");
		break;
	case COMPONENT_TYPE_CLOCK:
		CS = _T("Clock");
		break;
	case COMPONENT_TYPE_ONE_BIT_SWITCH:
		CS = _T("One bit switch");
		break;
	case COMPONENT_TYPE_AND_GATE:
		CS = _T("AND");
		break;
	case COMPONENT_TYPE_OR_GATE:
		CS = _T("OR");
		break;
	case COMPONENT_TYPE_NOT_GATE:
		CS = _T("INVERTOR");
		break;
	case COMPONENT_TYPE_XOR_GATE:
		CS = _T("XOR");
		break;
	case COMPONENT_TYPE_WIRE:
		CS = _T("Wire");
		break;
	case COMPONENT_TYPE_7SEGMENT:
		CS = _T("7-Segment");
		break;
	case COMPONENT_TYPE_OUTPUT_PIN:
		CS = _T("Output pin");
		break;
	case COMPONENT_TYPE_ONE_BIT_LAMP:
		CS = _T("One bit lamp");
		break;
	case COMPONENT_TYPE_LIBRARY_BOX:
		CS = _T("Lib box");
		break;
	default:
		CS = _T("no exist type");
	}

}

void CMFCLogicSimulatorDoc::getStringByCOMPONENT_DIRECTION(COMPONENT_DIRECTION direct, CString & CS)
{
	switch (direct)
	{
	case EAST:
		CS = _T("East");
		break;
	case SOUTH:
		CS = _T("South");
		break;
	case WEST:
		CS = _T("West");
		break;
	case NORTH:
		CS = _T("North");
		break;
	default:
		CS = _T("No direction");
		break;
	}
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