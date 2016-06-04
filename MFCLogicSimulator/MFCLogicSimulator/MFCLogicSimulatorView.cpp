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

// MFCLogicSimulatorView.cpp : CMFCLogicSimulatorView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "MFCLogicSimulator.h"
#endif

#include "MFCLogicSimulatorDoc.h"
#include "MFCLogicSimulatorView.h"

#include "FileView.h" // tree item �����Ͽ� �߰�
#include "PropertiesWnd.h" // �Ӽ�â �ɼ� ���� �����Ͽ� �߰�

#include "ViewTree.h"
#include "ChildFrm.h"
#include "MainFrm.h"
#include"OutputPin.h"
#include "PropertiesWnd.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMFCLogicSimulatorView

IMPLEMENT_DYNCREATE(CMFCLogicSimulatorView, CScrollView)

BEGIN_MESSAGE_MAP(CMFCLogicSimulatorView, CScrollView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMFCLogicSimulatorView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CMFCLogicSimulatorView ����/�Ҹ�



CMFCLogicSimulatorView::CMFCLogicSimulatorView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	isHighlightComponentMode = false;
	isHighlightTerminalPin = false;
	currentSelectedTerminalPoint.x = 0;
	currentSelectedTerminalPoint.y = 0;
}

CMFCLogicSimulatorView::~CMFCLogicSimulatorView()
{

}

BOOL CMFCLogicSimulatorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CScrollView::PreCreateWindow(cs);
}



void CMFCLogicSimulatorView::OnDraw(CDC* /*pDC*/)
{
	CMFCLogicSimulatorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.


}

void CMFCLogicSimulatorView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

void CMFCLogicSimulatorView::OnInitialUpdate()
{
	GetClientRect(&rlClientRect);
	CSize sizeTotal;
	// ���� ��ü ũ�� ���(����)
	sizeTotal.cx = SIZE_OF_VIEW_X;
	sizeTotal.cy = SIZE_OF_VIEW_Y;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

BOOL CMFCLogicSimulatorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CMFCLogicSimulatorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CMFCLogicSimulatorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}

void CMFCLogicSimulatorView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCLogicSimulatorView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	// popup menu ��Ȱ��ȭ ����
	//theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}

void CMFCLogicSimulatorView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// logic doc ������ ������
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CMFCLogicSimulatorDoc* pDoc = GetDocument();
	SELECTED_TERMINAL_INFO selectedTerminalInfo;
	int nVertScroll = GetScrollPos(SB_VERT);
	int nHorzScroll = GetScrollPos(SB_HORZ);	

	//���� ��ǰ �߰� ����̸�
	switch (pDoc->operationMode) {
	case OPERATION_MODE_ADDING_COMPONENT: {
		//������ ��ǥ�� �����´�

		//������ ��ǰ�� ��ť�� �߰��Ѵ�
		pDoc->addComponentToEngine(point.x + nHorzScroll, point.y + nVertScroll);
		pDoc->operationMode = OPERATION_MODE_NONE;
		//tree view ��ǰ ���ø�带 �����ϴ� �޼����� ������		
		((pFrame->getCFileView())->getCFileViewTree())->SendMessage(UM_UNSELECT_ITEM_IN_TREEVIEW);
		
		Invalidate();
		break;}

		//���� ��ǰ ���� �����
		//��ǰ�� 
	case OPERATION_MODE_SELECT_COMPONENT: {
		int newIndex;
		newIndex = checkMouesPointOnComponent();
		//������ ��ҵ�
		if (newIndex <=0) {
			highlightComponentIndex = 0;
			pDoc->operationMode = OPERATION_MODE_NONE;

		}
		// �ٸ� ��ǰ�� ������
		else if (newIndex != highlightComponentIndex) {
			highlightComponentIndex = newIndex;
		}
		
		//���� ��ǰ�� �����ϸ� ��ǰ ���� ���� �����Ѵ�
		//������ ��ǰ�� ���̶���Ʈ �Ѵ�

		//���� ��ǰ�� ���ڸ� �����ϸ� ���ڸ� ���̶���Ʈ �Ѵ�

		Invalidate();
		break;}
	
	case OPERATION_MODE_CONNECTING_COMPONENT: {
		bool isInTerminalPin = checkMouesPointOnTerminalPin(selectedTerminalInfo);
		//�ٸ����� Ŭ���Ͽ��� �����Ѵ�
		if (isInTerminalPin == true) {
			checkMouesPointOnTerminalPin(selectedTerminalInfo);
			//���ᰡ���ϸ�
			pDoc->connectComponent(selectedTerminalInfo,
				firstSelectedTerminalPin);
		}
		//�����Ѵ�
		pDoc->operationMode = OPERATION_MODE_NONE;
		oldSelectedTerminalPoint.x = 0;
		oldSelectedTerminalPoint.y = 0;
		currentSelectedTerminalPoint.x = 0;
		currentSelectedTerminalPoint.y = 0;
		copyTerminalInfo(dummy_SELECTED_TERMINAL_INFO, firstSelectedTerminalPin);
		copyTerminalInfo(dummy_SELECTED_TERMINAL_INFO, secondSelectedTerminalPin);

		Invalidate();
		break;}

	case OPERATION_MODE_NONE: {
		//���콺�� ȭ���� ��ǰ�� ������

		highlightComponentIndex = checkMouesPointOnComponent();
		if (highlightComponentIndex > 0) {
			pDoc->operationMode = OPERATION_MODE_SELECT_COMPONENT;
			Invalidate();
		}
		
		//���� Ŭ���� ���� ���� ��ȯ�Ѵ�
		bool isInTerminalPin  = checkMouesPointOnTerminalPin(selectedTerminalInfo);
		if (isInTerminalPin == true) {
			pDoc->operationMode = OPERATION_MODE_CONNECTING_COMPONENT;
			copyTerminalInfo(selectedTerminalInfo, firstSelectedTerminalPin);
			oldSelectedTerminalPoint.x = currentSelectedTerminalPoint.x;
			oldSelectedTerminalPoint.y = currentSelectedTerminalPoint.y;
			Invalidate();
		}
		break; }
	default: {


		break;}
	}
	

	CScrollView::OnLButtonDown(nFlags, point);
}

void CMFCLogicSimulatorView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CScrollView::OnLButtonUp(nFlags, point);
}

//�̰��� �ؾ��Ѵ� �����ڷ�
//http://adnoctum.tistory.com/149
void CMFCLogicSimulatorView::OnPaint()
{
	CPaintDC dc(this);

	CMFCLogicSimulatorDoc* pDoc = GetDocument();
	CRect rect;
	GetClientRect(&rect);

	CDC memDC;
	CBitmap newBitmap;
	CBitmap *pOldBitmap;
	SELECTED_TERMINAL_INFO dummyInfo;


	//������۸��� �ϱ� ���� ���ۿ����� �� ��Ʈ���� �����Ѵ�
	memDC.CreateCompatibleDC(&dc);
	newBitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
	pOldBitmap = memDC.SelectObject(&newBitmap);
	memDC.PatBlt(0, 0, rect.Width(), rect.Height(), WHITENESS);


	//�޸𸮿��ٰ� �׸������
	{
		// �� ��ũ�� �� ũ�� ����
		// https://msdn.microsoft.com/ko-kr/library/cc468151(v=vs.71).aspx
		// http://eachan.tistory.com/3
		/* ��ũ�ѹ� ��Ʈ�� */ {
			int nVertScroll = GetScrollPos(SB_VERT);
			int nHorzScroll = GetScrollPos(SB_HORZ);

			CPoint scrollpos = GetScrollPosition();
			memDC.BitBlt(-scrollpos.x, -scrollpos.y, rlClientRect.right, rlClientRect.bottom, &memDC, 0, 0, SRCCOPY);
		}
		/* ��ũ�ѹ� ��Ʈ�� �� */

			//�׸��� ����
		{
			//��ǰ���� �׸���
			drawComponent(memDC);
			//���̾���� �׸�
			drawConnectedWire(memDC);

			//�߰� ����϶��� �Ѵ�
			//��ǰ �߰� ����ϋ� �����̸鼭 �����ִ°�
			if (pDoc->operationMode == OPERATION_MODE_ADDING_COMPONENT) {
				drawAddingComponent(memDC);
			}
			if (pDoc->operationMode == OPERATION_MODE_SELECT_COMPONENT) {
				//ȭ�鿡 �ִ� ���� �Ѻ�ǰ�� �����ϴ°�
				drawHighlightSelectedComponent(memDC);
			}
			
			if (isHighlightTerminalPin == true) {
				drawHighlightComponentTerminalPin(memDC);
			}

			if (ishighlightConnectedWire == true) {
				drawHighlightSelectedconnectedWire(memDC);
			}

			if (pDoc->operationMode == OPERATION_MODE_CONNECTING_COMPONENT) {
				drawConnectingWire(memDC);
			}


			//ȭ�鿡 �޼����� ����ִ°�
			drawMassage(memDC);
		}
	}

	//�׸��� ����

	//���� ������ �ϴ� ��Ʈ���� ȭ������ ����Ѵ�
	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);
	dc.SelectObject(pOldBitmap);
	newBitmap.DeleteObject();
	ReleaseDC(&memDC);
	DeleteDC(memDC);




}

void CMFCLogicSimulatorView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CScrollView::OnMouseMove(nFlags, point);

	//��ǰ �߰� ��� �϶� ������ ��ǰ�� ��ǥ�� �����Ѵ�

	//���콺�� ��ǰ���� �ִ°�� ��ǰ�� �����Ѵ�

	//���콺����ǰ�� ���� ���� ������  ���ڸ� �����Ѵ�
	CMFCLogicSimulatorDoc* pDoc = GetDocument();

	if (pDoc->operationMode == OPERATION_MODE_ADDING_COMPONENT) {
		Invalidate();
	}
	if (pDoc->operationMode == OPERATION_MODE_SELECT_COMPONENT) {

		//���콺�� ���� ���¿��� �����̸� ������ �����Ѵ�
		if ((nFlags & MK_LBUTTON) == MK_LBUTTON){

			CPoint point;
			GetCursorPos(&point);
			ScreenToClient(&point);

			int nVertScroll = GetScrollPos(SB_VERT);
			int nHorzScroll = GetScrollPos(SB_HORZ);
			COMPONENT_DATA* highlightComponent;
			highlightComponent = &pDoc->engineComponentData[highlightComponentIndex];
			highlightComponent->x = point.x+ nHorzScroll;
			highlightComponent->y = point.y+ nVertScroll;
			Invalidate();
		}



	}
	SELECTED_TERMINAL_INFO dummyInfo;

	bool oldval = isHighlightTerminalPin;
	isHighlightTerminalPin = checkMouesPointOnTerminalPin(dummyInfo);
	if (oldval != isHighlightTerminalPin) {
		Invalidate();
	}

	oldval = ishighlightConnectedWire;
	ishighlightConnectedWire=checkMousePointOnConnectedWire();
	if (oldval != ishighlightConnectedWire) {
		Invalidate();
	}

	if (pDoc->operationMode == OPERATION_MODE_CONNECTING_COMPONENT) {
		Invalidate();
	}

}

void CMFCLogicSimulatorView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	CScrollView::OnHScroll(nSBCode, nPos, pScrollBar);
	Invalidate();
}
void CMFCLogicSimulatorView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	CScrollView::OnVScroll(nSBCode, nPos, pScrollBar);
	Invalidate();
}

//�̰��� �ؾ��Ѵ�
//http://adnoctum.tistory.com/149
BOOL CMFCLogicSimulatorView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	return true;
}

// CMFCLogicSimulatorView ����

#ifdef _DEBUG
void CMFCLogicSimulatorView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CMFCLogicSimulatorView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CMFCLogicSimulatorDoc* CMFCLogicSimulatorView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCLogicSimulatorDoc)));
	return (CMFCLogicSimulatorDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCLogicSimulatorView �޽��� ó����




//����ǰ�� �׸����� �����߰��� �ʿ��ϴ�
void CMFCLogicSimulatorView::drawComponent(CDC &DC)
{
	//���������� �� ������
	CDC memDC;
	memDC.CreateCompatibleDC(&DC);
	CMFCLogicSimulatorDoc* pDoc = GetDocument();
	int nVertScroll = GetScrollPos(SB_VERT);
	int nHorzScroll = GetScrollPos(SB_HORZ);
	int x, y;
	COMPONENT_TYPE type;
	COMPONENT_DIRECTION direction;
	CBitmap componentBitmap;
	CBitmap *oldBitmap;
	BITMAP bitmapInfo;
	CComponentObject* currentObject;

	CBitmap terminalPin;
	BITMAP terminalPinInfo;

	for (int i = 0; i < pDoc->engineComponentData.size(); i++) {
		//�������� �ʴ°��� �Ѿ��
		if (pDoc->engineComponentData[i].id <= 0) {
			continue;
		}

		//�׸� ��ǰ�� ��ü�� �����´�
		currentObject = pDoc->logicSimulatorEngine.getComponentObject(i);
		//�׷��� ��ǥ�� �����Ѵ�
		x = pDoc->engineComponentData[i].x - nHorzScroll;
		y = pDoc->engineComponentData[i].y - nVertScroll;
		type = pDoc->engineComponentData[i].type;
		direction = pDoc->engineComponentData[i].direction;
		//���� ���׸�Ʈ�� ���� �����Ѵ�
		

		//Ÿ�Կ� �´� ��ǰ�� ��Ʈ�� ���̵� �������� �ε��Ѵ�
		componentBitmap.LoadBitmapW(getBitmapIDByComponentType(type, direction));
		componentBitmap.GetBitmap(&bitmapInfo);

		// �͹̳� ���� �׸���
		drawComponentTermialPin(DC, x, y, direction, bitmapInfo.bmWidth, bitmapInfo.bmHeight,
			currentObject->numberOfInput(), currentObject->numberOfOutput());

		//��ǰ�� �׸���
		oldBitmap = memDC.SelectObject(&componentBitmap);
		DC.BitBlt(x, y, bitmapInfo.bmWidth, bitmapInfo.bmHeight, &memDC, 0, 0, SRCCOPY);
		memDC.SelectObject(oldBitmap);

		//������ ��Ʈ���� �����Ѵ�
		componentBitmap.DeleteObject();
		
	}
}

void CMFCLogicSimulatorView::drawConnectedWire(CDC & DC)
{
	CDC memDC;
	memDC.CreateCompatibleDC(&DC);
	CMFCLogicSimulatorDoc* pDoc = GetDocument();
	int nVertScroll = GetScrollPos(SB_VERT);
	int nHorzScroll = GetScrollPos(SB_HORZ);
	int x, y;
	ADJ_LIST* Grahp;
	Grahp = pDoc->logicSimulatorEngine.getConnectionGrahp();
	COMPONENT_DATA* pCurrentComponent;

	CPen pen;
	pen.CreatePen(PS_DOT, 5, RGB(0, 0, 0));
	CPen* oldPen = DC.SelectObject(&pen);

	CBrush brush;
	brush.CreateSolidBrush(RGB(0, 0, 0));
	CBrush* oldBrush = DC.SelectObject(&brush);
	int curID;
	int nextID;
	CPoint A, B;
	for (int i = 0; i < pDoc->engineComponentData.size(); i++) {
		if (pDoc->engineComponentData[i].id <= 0) { continue; }
		pCurrentComponent = &pDoc->engineComponentData[i];
		curID = pCurrentComponent->id;
		
		for (int j = 0; j<(*Grahp)[i].size(); j++) {
			nextID = (*Grahp)[i][j].componentID;
			if (nextID <= 0) { continue; }
			
			//output ������ ��ǥ�� �����´�
			getOutputTerminalPoint(curID,A, j);

			//input ������ ��ǥ�� �����´�
			getInputTerminalPoint(nextID, B, (*Grahp)[i][j].terminalNumber);

			//��ǥ�� �����Ѵ�
			A.x -= nHorzScroll;
			A.y -= nVertScroll;
			B.x -= nHorzScroll;
			B.y -= nVertScroll;
			//������ ���� �׸���			
			DC.MoveTo(A);
			DC.LineTo(B);
		}
	}
	DC.SelectObject(oldBrush);
	DC.SelectObject(oldPen);
}

void CMFCLogicSimulatorView::drawAddingComponent(CDC & DC)
{
	//���������� �� ������
	CDC memDC;
	memDC.CreateCompatibleDC(&DC);
	CMFCLogicSimulatorDoc* pDoc = GetDocument();
	int nVertScroll = GetScrollPos(SB_VERT);
	int nHorzScroll = GetScrollPos(SB_HORZ);
	int x, y;
	COMPONENT_TYPE type;
	CBitmap componentBitmap;
	CBitmap *oldBitmap;
	BITMAP bitmapInfo;
	CComponentObject* currentObject;

	//���콺����ǥ�� �����´�
	CPoint point;
	GetCursorPos(&point);
	ScreenToClient(&point);
	//�׷��� ��ǥ�� �����Ѵ�

	x = point.x;
	y = point.y;


	type = pDoc->getCurrentSelectedComponentType();
	if (type == COMPONENT_TYPE_NONE)
		return;

	//Ÿ�Կ� �´� ��ǰ�� ��Ʈ�� ���̵� �������� �ε��Ѵ�
	componentBitmap.LoadBitmapW(getBitmapIDByComponentType(type,EAST));
	componentBitmap.GetBitmap(&bitmapInfo);

	//��ǰ�� �׸���
	oldBitmap = memDC.SelectObject(&componentBitmap);
	DC.BitBlt(x, y, bitmapInfo.bmWidth, bitmapInfo.bmHeight, &memDC, 0, 0, SRCCOPY);
	memDC.SelectObject(oldBitmap);

	//������ ��Ʈ���� �����Ѵ�
	componentBitmap.DeleteObject();

}

void CMFCLogicSimulatorView::drawHighlightSelectedComponent(CDC & DC)
{
	//���������� �� ������
	CDC memDC;
	memDC.CreateCompatibleDC(&DC);
	CMFCLogicSimulatorDoc* pDoc = GetDocument();
	int nVertScroll = GetScrollPos(SB_VERT);
	int nHorzScroll = GetScrollPos(SB_HORZ);
	int x, y;
	CBitmap bitmap;
	BITMAP bitmapInfo;

	COMPONENT_DATA* currentComponent;
	currentComponent = &pDoc->engineComponentData[highlightComponentIndex];
	x = currentComponent->x - nHorzScroll;
	y = currentComponent->y - nVertScroll;
	currentComponent->type;

	if (currentComponent->type == COMPONENT_TYPE_LIBRARY_BOX) {

	}
	else if (currentComponent->type == COMPONENT_TYPE_7SEGMENT) {

	}
	else {
		drawHighlightComponentBody(DC, x, y, 75, 75);
	}


}

void CMFCLogicSimulatorView::drawHighlightSelectedconnectedWire(CDC & DC)
{
	CPen pen;
	pen.CreatePen(PS_SOLID, 3, RGB(255, 0, 0));   //������ �һ���
	CPen* oldPen = DC.SelectObject(&pen); 

	DC.Polyline(selectedConnectedWirePoints,4);
	DC.MoveTo(selectedConnectedWirePoints[3]);
	DC.LineTo(selectedConnectedWirePoints[0]);
	DC.SelectObject(oldPen);
}

void CMFCLogicSimulatorView::drawMassage(CDC & DC)
{
	//���������� �� ������
	CDC memDC;
	memDC.CreateCompatibleDC(&DC);
	CMFCLogicSimulatorDoc* pDoc = GetDocument();
	int nVertScroll = GetScrollPos(SB_VERT);
	int nHorzScroll = GetScrollPos(SB_HORZ);
	int x, y;
}

void CMFCLogicSimulatorView::drawHighlightComponentBody(CDC& DC, int x, int y, int bitmapWidth, int bitmapHeight)
{
	CPen pen;
	pen.CreatePen(PS_SOLID, 3, RGB(255, 0, 0));    // ������ �� ����
	CPen* oldPen = DC.SelectObject(&pen);

	DC.MoveTo(x - HIGHLIGHT_EDGE_GAP, y - HIGHLIGHT_EDGE_GAP);
	DC.LineTo(x + HIGHLIGHT_EDGE_GAP + bitmapWidth, y - HIGHLIGHT_EDGE_GAP);
	DC.LineTo(x + HIGHLIGHT_EDGE_GAP + bitmapWidth, y + HIGHLIGHT_EDGE_GAP + bitmapHeight);
	DC.LineTo(x - HIGHLIGHT_EDGE_GAP, y + HIGHLIGHT_EDGE_GAP + bitmapHeight);
	DC.LineTo(x - HIGHLIGHT_EDGE_GAP, y - HIGHLIGHT_EDGE_GAP);
	DC.SelectObject(oldPen);
}

void CMFCLogicSimulatorView::drawHighlightComponentTerminalPin(CDC & DC)
{
	int nVertScroll = GetScrollPos(SB_VERT);
	int nHorzScroll = GetScrollPos(SB_HORZ);
	int x = currentSelectedTerminalPoint.x - nHorzScroll;
	int y = currentSelectedTerminalPoint.y - nVertScroll;

	CPen pen;
	CPen* oldPen;
	//��ǲ���� �׸���
	pen.CreatePen(PS_SOLID, 2, RGB(153, 0, 0255));    // �� ����
	oldPen = DC.SelectObject(&pen);
	DC.Ellipse(x - HIGHLIGHIT_TERMINAL_PIN_HALF_SIZE, y - HIGHLIGHIT_TERMINAL_PIN_HALF_SIZE,
		x + HIGHLIGHIT_TERMINAL_PIN_HALF_SIZE, y + HIGHLIGHIT_TERMINAL_PIN_HALF_SIZE);
	DC.SelectObject(oldPen);
	pen.DeleteObject();
}

void CMFCLogicSimulatorView::drawComponentTermialPin(CDC & DC, int x, int y, COMPONENT_DIRECTION direction, 
	int componentWidth, int componentHeight, int numberOfInputTerminal, int numberOfOutputTerminal)
{
	CPen pen;
	CPen* oldPen;

	int inputTerminalGap, outputTerminalGap;
	int a, b;
	switch (direction) {
	case EAST: {
		inputTerminalGap = componentHeight / (numberOfInputTerminal + 1);
		outputTerminalGap = componentHeight / (numberOfOutputTerminal + 1);

		//��ǲ���� �׸���
		pen.CreatePen(PS_SOLID, 2, RGB(255, 0, 0));    // ������ �� ����
		oldPen = DC.SelectObject(&pen);
		for (int curI = 1; curI < numberOfInputTerminal + 1; curI++) {
			a = x - 10;
			b = y + inputTerminalGap * curI;
			DC.MoveTo(a, b);
			DC.LineTo(a + 30, b);
			DC.Ellipse(a - TERMINAL_PIN_HALF_SIZE, b - TERMINAL_PIN_HALF_SIZE,
				a + TERMINAL_PIN_HALF_SIZE, b + TERMINAL_PIN_HALF_SIZE);
		}
		DC.SelectObject(oldPen);
		pen.DeleteObject();

		pen.CreatePen(PS_SOLID, 2, RGB(0, 0, 255));    // ������ �� ����
		oldPen = DC.SelectObject(&pen);
		//��ǰ�� �ƿ�ǲ ���� �׸���
		for (int curI = 1; curI < numberOfOutputTerminal + 1; curI++) {
			a = x + componentWidth + 10;
			b = y + outputTerminalGap * curI;
			DC.MoveTo(a, b);
			DC.LineTo(a - 30, b);
			DC.Ellipse(a - TERMINAL_PIN_HALF_SIZE, b - TERMINAL_PIN_HALF_SIZE,
				a + TERMINAL_PIN_HALF_SIZE, b + TERMINAL_PIN_HALF_SIZE);
		}
		DC.SelectObject(oldPen);
		pen.DeleteObject();
		break;
	}
	case SOUTH: {
		inputTerminalGap = componentWidth / (numberOfInputTerminal + 1);
		outputTerminalGap = componentWidth / (numberOfOutputTerminal + 1);

		//��ǲ���� �׸���
		pen.CreatePen(PS_SOLID, 2, RGB(255, 0, 0));    // ������ �� ����
		oldPen = DC.SelectObject(&pen);
		for (int curI = 1; curI < numberOfInputTerminal + 1; curI++) {
			a = x + inputTerminalGap * curI;
			b = y + -10;
			DC.MoveTo(a, b);
			DC.LineTo(a , b+30);
			DC.Ellipse(a - TERMINAL_PIN_HALF_SIZE, b - TERMINAL_PIN_HALF_SIZE,
				a + TERMINAL_PIN_HALF_SIZE, b + TERMINAL_PIN_HALF_SIZE);
		}
		DC.SelectObject(oldPen);
		pen.DeleteObject();

		pen.CreatePen(PS_SOLID, 2, RGB(0, 0, 255));    // ������ �� ����
		oldPen = DC.SelectObject(&pen);
		//��ǰ�� �ƿ�ǲ ���� �׸���
		for (int curI = 1; curI < numberOfOutputTerminal + 1; curI++) {
			a = x + outputTerminalGap * curI;
			b = y + componentHeight+10;
			DC.MoveTo(a, b);
			DC.LineTo(a , b-30);
			DC.Ellipse(a - TERMINAL_PIN_HALF_SIZE, b - TERMINAL_PIN_HALF_SIZE,
				a + TERMINAL_PIN_HALF_SIZE, b + TERMINAL_PIN_HALF_SIZE);
		}
		DC.SelectObject(oldPen);
		pen.DeleteObject();
		break;
	}
	case WEST: {
		inputTerminalGap = componentHeight / (numberOfInputTerminal + 1);
		outputTerminalGap = componentHeight / (numberOfOutputTerminal + 1);

		//��ǲ���� �׸���
		pen.CreatePen(PS_SOLID, 2, RGB(255, 0, 0));    // ������ �� ����
		oldPen = DC.SelectObject(&pen);
		for (int curI = 1; curI < numberOfInputTerminal + 1; curI++) {
			a = x + componentWidth + 10;
			b = y + inputTerminalGap * curI;
			DC.MoveTo(a, b);
			DC.LineTo(a - 30, b);
			DC.Ellipse(a - TERMINAL_PIN_HALF_SIZE, b - TERMINAL_PIN_HALF_SIZE,
				a + TERMINAL_PIN_HALF_SIZE, b + TERMINAL_PIN_HALF_SIZE);
		}
		DC.SelectObject(oldPen);
		pen.DeleteObject();

		pen.CreatePen(PS_SOLID, 2, RGB(0, 0, 255));    // ������ �� ����
		oldPen = DC.SelectObject(&pen);
		//��ǰ�� �ƿ�ǲ ���� �׸���
		for (int curI = 1; curI < numberOfOutputTerminal + 1; curI++) {
			a = x - 10;
			b = y + outputTerminalGap * curI;
			DC.MoveTo(a, b);
			DC.LineTo(a + 30, b);
			DC.Ellipse(a - TERMINAL_PIN_HALF_SIZE, b - TERMINAL_PIN_HALF_SIZE,
				a + TERMINAL_PIN_HALF_SIZE, b + TERMINAL_PIN_HALF_SIZE);
		}
		DC.SelectObject(oldPen);
		pen.DeleteObject();


		break;
	}
	case NORTH: {
		inputTerminalGap = componentWidth / (numberOfInputTerminal + 1);
		outputTerminalGap = componentWidth / (numberOfOutputTerminal + 1);

		//��ǲ���� �׸���
		pen.CreatePen(PS_SOLID, 2, RGB(255, 0, 0));    // ������ �� ����
		oldPen = DC.SelectObject(&pen);
		for (int curI = 1; curI < numberOfInputTerminal + 1; curI++) {
			a = x + inputTerminalGap * curI;
			b = y + componentHeight + 10;
			DC.MoveTo(a, b);
			DC.LineTo(a, b - 30);
			DC.Ellipse(a - TERMINAL_PIN_HALF_SIZE, b - TERMINAL_PIN_HALF_SIZE,
				a + TERMINAL_PIN_HALF_SIZE, b + TERMINAL_PIN_HALF_SIZE);
		}
		DC.SelectObject(oldPen);
		pen.DeleteObject();

		pen.CreatePen(PS_SOLID, 2, RGB(0, 0, 255));    // ������ �� ����
		oldPen = DC.SelectObject(&pen);
		//��ǰ�� �ƿ�ǲ ���� �׸���
		for (int curI = 1; curI < numberOfOutputTerminal + 1; curI++) {
			a = x + outputTerminalGap * curI;
			b = y - 10;
			DC.MoveTo(a, b);
			DC.LineTo(a, b + 30);
			DC.Ellipse(a - TERMINAL_PIN_HALF_SIZE, b - TERMINAL_PIN_HALF_SIZE,
				a + TERMINAL_PIN_HALF_SIZE, b + TERMINAL_PIN_HALF_SIZE);
		}
		DC.SelectObject(oldPen);
		pen.DeleteObject();
		break;
	}
	default:
		break;
	}
}

void CMFCLogicSimulatorView::drawComponentBody(CDC & DC, int x, int y, COMPONENT_DIRECTION direction,
	int componentWidth, int componentHeight)
{
	switch (direction) {
	case EAST:
		break;
	case SOUTH:
		break;
	case WEST:
		break;
	case NORTH:
		break;
	default:
		break;
	}

}

void CMFCLogicSimulatorView::drawConnectingWire(CDC & DC)
{
	int nVertScroll = GetScrollPos(SB_VERT);
	int nHorzScroll = GetScrollPos(SB_HORZ);
	CPoint point;
	GetCursorPos(&point);
	ScreenToClient(&point);
	point.x ;
	point.y ;

	CPen pen;
	pen.CreatePen(PS_DOT, 5, RGB(0, 0, 0));    
	CPen* oldPen = DC.SelectObject(&pen);

	CBrush brush;
	brush.CreateSolidBrush(RGB(0, 0, 0));
	CBrush* oldBrush = DC.SelectObject(&brush);

	int x = oldSelectedTerminalPoint.x - nHorzScroll;
	int y = oldSelectedTerminalPoint.y - nVertScroll;
	//�����׸���
	DC.Ellipse(x- CONNECTING_WIRE_ELLIPSE_HALF_SIZE, 
		y - CONNECTING_WIRE_ELLIPSE_HALF_SIZE,
		x + CONNECTING_WIRE_ELLIPSE_HALF_SIZE,
		y + CONNECTING_WIRE_ELLIPSE_HALF_SIZE);	

	DC.SelectObject(oldBrush);
	DC.MoveTo(x,y);
	DC.LineTo(point.x, point.y);
	DC.SelectObject(oldPen);
}




int CMFCLogicSimulatorView::getBitmapIDByComponentType(COMPONENT_TYPE _type, COMPONENT_DIRECTION direction)
{
	////�������� ����ϴ� ��ǰ Ÿ�� ������
	//enum COMPONENT_TYPE {
	//	COMPONENT_TYPE_NONE,
	//	COMPONENT_TYPE_INPUT_PIN, COMPONENT_TYPE_CLOCK, COMPONENT_TYPE_ONE_BIT_SWITCH,
	//	COMPONENT_TYPE_AND_GATE, COMPONENT_TYPE_OR_GATE, COMPONENT_TYPE_NOT_GATE, COMPONENT_TYPE_XOR_GATE,
	//	COMPONENT_TYPE_WIRE,
	//	COMPONENT_TYPE_7SEGMENT, COMPONENT_TYPE_OUTPUT_PIN, COMPONENT_TYPE_ONE_BIT_LAMP,
	//	COMPONENT_TYPE_LIBRARY_BOX
	//};
//���ҽ����� ���Ǵ� ��Ʈ�� ���̵�
	switch (_type) {

	case COMPONENT_TYPE_ONE_BIT_SWITCH:
		return IDB_SWITCH_OFF_E;
		break;

	case COMPONENT_TYPE_ONE_BIT_LAMP:
		return IDB_LAMP_OFF_E;
		break;
	case COMPONENT_TYPE_CLOCK:
		return IDB_CLOCK_E;
		break ;
		 
	//case COMPONENT_TYPE_7SEGMENT:
	//	return IDB_ONE_BIT_SWITCH_OFF;
	//	break;




	case COMPONENT_TYPE_AND_GATE:
		return IDB_GATE_AND_E+ direction;
		break;
	case COMPONENT_TYPE_OR_GATE :
		return IDB_GATE_OR_E + direction;
		break;
	case COMPONENT_TYPE_NOT_GATE:
		return IDB_INVERTOR_E + direction;
		break;
	case COMPONENT_TYPE_XOR_GATE:
		return IDB_GATE_XOR_E + direction;
		break;

	case COMPONENT_TYPE_INPUT_PIN:
		return IDB_PIN_ON_E;
		break;
	case COMPONENT_TYPE_OUTPUT_PIN:
		return IDB_PROBE_OFF_E ;
		break;

	case COMPONENT_TYPE_WIRE:
		return IDB_COPPER_WIRE;
		break;
		

	case COMPONENT_TYPE_LIBRARY_BOX:
		return IDB_LIBBOX_E + direction;
		break;


	//
	//
	//	case COMPONENT_TYPE_LIBRARY_BOX:
	//		return IDB_FF_DFF;
	//		break;
	//	case COMPONENT_TYPE_LIBRARY_BOX:
	//		return IDB_FF_JKFF;
	//		break;
	//	case COMPONENT_TYPE_LIBRARY_BOX:
	//		return IDB_FF_TFF;
	//		break;



		//#define IDB_FF_DFF                      327
		//#define IDB_FF_JKFF                     328
		//#define IDB_FF_TFF                      329
		//
		//#define IDB_GATE_NAND                   332
		//#define IDB_GATE_NOR                    333
	default:
		return -1;
	}
	return 0;
}

void CMFCLogicSimulatorView::getConnnectedWirePoints(CPoint* points, CPoint A, CPoint B)
{
	int dx, dy;
	int x = A.x;
	int y = A.y;
	int w = B.x - A.x;
	int h = B.y - A.y;

	double angle;
	double theta = w ? atan(double(h) / double(w)) : sin(h)* PI / 2.0;

	if (theta < 0) {
		angle = (theta + PI / 2.0);
	}
	angle = (theta + PI / 2.0);
	dx = int(HIGHLIGHT_CONNECTED_WIRE_LINE_WIDTH* cos(angle));
	dy = int(HIGHLIGHT_CONNECTED_WIRE_LINE_WIDTH* sin(angle));

	points[0] = CPoint(x + dx, y + dy);
	points[1] = CPoint(x - dx, y - dy);
	points[2] = CPoint(x - dx + w, y - dy +h);
	points[3] = CPoint(x + dx + w, y + dy + h);
}

int CMFCLogicSimulatorView::getComponentHeight(COMPONENT_TYPE type)
{
	//���׸�Ʈ�϶�
	if (type == COMPONENT_TYPE_7SEGMENT) {
		return 120;
	}
	else if (type == COMPONENT_TYPE_LIBRARY_BOX) {
		return 120;
	}
	else {
		return 75;
	}
}

int CMFCLogicSimulatorView::getComponentWidth(COMPONENT_TYPE type)
{
	//���׸�Ʈ�϶�
	if (type == COMPONENT_TYPE_7SEGMENT) {
		return 75;
	}
	else if (type == COMPONENT_TYPE_LIBRARY_BOX) {
		return 75;
	}
	else {
		return 75;
	}
}

void CMFCLogicSimulatorView::getInputTerminalPoint(int id, CPoint &point, int index)
{
	CMFCLogicSimulatorDoc* pDoc = GetDocument();
	CComponentObject* currentObject;
	int inputTerminalGap;
	int nVertScroll = GetScrollPos(SB_VERT);
	int nHorzScroll = GetScrollPos(SB_HORZ);
	point.x += nHorzScroll;
	point.y += nVertScroll;

	currentObject = pDoc->logicSimulatorEngine.getComponentObject(id);
	int numberOfInputTerminal = currentObject->numberOfInput();
	COMPONENT_DATA *data = &pDoc->engineComponentData[id];
	int width = getComponentWidth(data->type);
	int Height = getComponentHeight(data->type);

	switch (data->direction) {
	case EAST: {
		inputTerminalGap = Height / (numberOfInputTerminal + 1);
		point.x = data->x - 10;
		point.y = data->y + inputTerminalGap * (index + 1);
		break; 
	}
	case SOUTH: {
		inputTerminalGap = width / (numberOfInputTerminal + 1);
		point.x = data->x + inputTerminalGap * (index+1);
		point.y = data->y + -10;
		break;
	}
	case WEST: {
		inputTerminalGap = Height / (numberOfInputTerminal + 1);
		point.x = data->x + Height + 10;
		point.y = data->y + inputTerminalGap * (index+1);
		break;
	}
	case NORTH: {
		inputTerminalGap = width / (numberOfInputTerminal + 1);
		point.x = data->x + inputTerminalGap * (index+1);
		point.y = data->y + width + 10;
		break;
	}
	default: break;	
	}
}

void CMFCLogicSimulatorView::getOutputTerminalPoint(int id, CPoint & point, int index)
{
	CMFCLogicSimulatorDoc* pDoc = GetDocument();
	CComponentObject* currentObject;
	int outputTerminalGap;
	int nVertScroll = GetScrollPos(SB_VERT);
	int nHorzScroll = GetScrollPos(SB_HORZ);
	point.x += nHorzScroll;
	point.y += nVertScroll;

	currentObject = pDoc->logicSimulatorEngine.getComponentObject(id);
	int numberOfOutputTerminal = currentObject->numberOfOutput();
	COMPONENT_DATA *data = &pDoc->engineComponentData[id];
	int width = getComponentWidth(data->type);
	int Height = getComponentHeight(data->type);

	switch (data->direction) {
	case EAST: {
		outputTerminalGap = Height / (numberOfOutputTerminal + 1);
		point.x  = data->x + width + 10;
		point.y = data->y + outputTerminalGap * (index+1);
		break;
	}
	case SOUTH: {
		outputTerminalGap = width / (numberOfOutputTerminal + 1);
		point.x = data->x + outputTerminalGap *  (index + 1);
		point.y = data->y + Height + 10;
		break;
	}
	case WEST: {
		outputTerminalGap = Height / (numberOfOutputTerminal + 1);
		point.x = data->x - 10;
		point.y = data->y + outputTerminalGap *  (index + 1);
		break;
	}
	case NORTH: {
		outputTerminalGap = width / (numberOfOutputTerminal + 1);
		point.x = data->x + outputTerminalGap *  (index + 1);
		point.y = data->y - 10;
		break;
	}
	default: break;
	}
}




int CMFCLogicSimulatorView::checkMouesPointOnComponent()
{
	CMFCLogicSimulatorDoc* pDoc = GetDocument();
	int mouseX, mouseY;
	CPoint point;
	GetCursorPos(&point);
	ScreenToClient(&point);
	int nVertScroll = GetScrollPos(SB_VERT);
	int nHorzScroll = GetScrollPos(SB_HORZ);
	//�׷��� ��ǥ�� �����Ѵ�
	mouseX = point.x + nHorzScroll;
	mouseY = point.y + nVertScroll;

	int endX, endY;
	int startX, startY;
	COMPONENT_DATA* currentComponent;
	for (int i = 0; i < pDoc->engineComponentData.size(); i++) {
		currentComponent = &pDoc->engineComponentData[i];
		//�������� �ʴ°��� �Ѿ��
		if (currentComponent->id <= 0) { continue; }

		startX = currentComponent->x;
		startY = currentComponent->y;
		if (currentComponent->type == COMPONENT_TYPE_LIBRARY_BOX) {
			endX = currentComponent->x + 75;
			endY = currentComponent->y + 120;
		}
		else if (currentComponent->type == COMPONENT_TYPE_7SEGMENT) {
			endX = currentComponent->x + 75;
			endY = currentComponent->y + 120;
		}
		else {
			endX = currentComponent->x + 75;
			endY = currentComponent->y + 75;
		}

		//���콺�� �ش� ��ǰ�����ִ��� �˻��Ѵ�
		if (startX <= mouseX && mouseX <= endX &&
			startY <= mouseY && mouseY <= endY) {
			return i;
		}
	}

	return 0;
}

bool CMFCLogicSimulatorView::checkMouesPointOnTerminalPin(SELECTED_TERMINAL_INFO& selectedTerminalInfo)
{
	CMFCLogicSimulatorDoc* pDoc = GetDocument();
	CComponentObject* currentObject;
	int inputTerminalGap;
	int outputTerminalGap;
	CBitmap componentBitmap;
	CBitmap* oldBitmap;
	BITMAP bitmapInfo;
	COMPONENT_DATA* currentData;
	BOOL isInTerminalPin = false;
	CRgn terminalPinRgn;
	CPoint mousePoint;
	GetCursorPos(&mousePoint);
	ScreenToClient(&mousePoint);
	int nVertScroll = GetScrollPos(SB_VERT);
	int nHorzScroll = GetScrollPos(SB_HORZ);
	mousePoint.x += nHorzScroll;
	mousePoint.y += nVertScroll;
	CPoint TerminalPoint;

	int a, b;
	for (int ID = 0; ID < pDoc->engineComponentData.size(); ID++) {
		currentData = &pDoc->engineComponentData[ID];
		//�������� �ʴ°��� �Ѿ��
		if (currentData->id <= 0) {continue;}

		currentObject = pDoc->logicSimulatorEngine.getComponentObject(ID);
		int numberOfInputTerminal = currentObject->numberOfInput();
		int numberOfOuputTerminal = currentObject->numberOfOutput();

		//��ǲ�� �˻��Ѵ�
		for (int  i= 0; i < numberOfInputTerminal ; i++) {
			getInputTerminalPoint(ID, TerminalPoint,i);
			a = TerminalPoint.x;
			b = TerminalPoint.y;
			terminalPinRgn.CreateEllipticRgn(
				a - TERMINAL_PIN_HALF_SIZE, b - TERMINAL_PIN_HALF_SIZE,
				a + TERMINAL_PIN_HALF_SIZE, b + TERMINAL_PIN_HALF_SIZE);
			if (terminalPinRgn.PtInRegion(mousePoint)) {
				isInTerminalPin = true;
				SELECTED_TERMINAL_INFO curInfo(ID, TERMINAL_TYPE_INPUT, i);
				copyTerminalInfo(curInfo, selectedTerminalInfo);
				currentSelectedTerminalPoint.x = a;
				currentSelectedTerminalPoint.y = b;
			};
			terminalPinRgn.DeleteObject();
		}
		//�ƿ�ǲ�� �˻��Ѵ�
		for (int i = 0; i < numberOfOuputTerminal; i++) {
			getOutputTerminalPoint(ID, TerminalPoint, i);
			a = TerminalPoint.x;
			b = TerminalPoint.y;
			terminalPinRgn.CreateEllipticRgn(
				a - TERMINAL_PIN_HALF_SIZE, b - TERMINAL_PIN_HALF_SIZE,
				a + TERMINAL_PIN_HALF_SIZE, b + TERMINAL_PIN_HALF_SIZE);
			if (terminalPinRgn.PtInRegion(mousePoint)) {
				isInTerminalPin = true;
				SELECTED_TERMINAL_INFO curInfo(ID, TERMINAL_TYPE_OUTPUT, i);
				copyTerminalInfo(curInfo, selectedTerminalInfo);
				currentSelectedTerminalPoint.x = a;
				currentSelectedTerminalPoint.y = b;
			};
			terminalPinRgn.DeleteObject();
		}	
	}
	if (isInTerminalPin == false){
		currentSelectedTerminalPoint.x = 0;
		currentSelectedTerminalPoint.y = 0;
	}
	return isInTerminalPin;
}

bool CMFCLogicSimulatorView::checkMousePointOnConnectedWire()
{
	CMFCLogicSimulatorDoc* pDoc = GetDocument();
	CComponentObject* currentObject;

	COMPONENT_DATA* pCurrentData;
	CRgn connectedWireRgn;
	CPoint mousePoint;
	CPoint points[4];
	GetCursorPos(&mousePoint);
	ScreenToClient(&mousePoint);
	int nVertScroll = GetScrollPos(SB_VERT);
	int nHorzScroll = GetScrollPos(SB_HORZ);
	mousePoint.x += nHorzScroll;
	mousePoint.y += nVertScroll;
	ADJ_LIST* pGraph  = pDoc->logicSimulatorEngine.getConnectionGrahp();;
	int curID,nextID;
	CPoint A, B;
	bool ret = false;
	for (int i = 0; i < pDoc->engineComponentData.size(); i++) {
		if (pDoc->engineComponentData[i].id <= 0) { continue; }
		pCurrentData = &pDoc->engineComponentData[i];
		curID = pCurrentData->id;
		
		for (int j = 0; j<(*pGraph)[i].size(); j++) {
			nextID = (*pGraph)[i][j].componentID;
			if (nextID <= 0) { continue; }

			//output ������ ��ǥ�� �����´�
			getOutputTerminalPoint(curID, A, j);
			//input ������ ��ǥ�� �����´�
			getInputTerminalPoint(nextID, B, (*pGraph)[i][j].terminalNumber);

			//��ǥ�� �����Ѵ�
			A.x -= nHorzScroll;
			A.y -= nVertScroll;
			B.x -= nHorzScroll;
			B.y -= nVertScroll;

			getConnnectedWirePoints(points, A, B);
			connectedWireRgn.CreatePolygonRgn(points,4,WINDING);

			//�����ȿ� �ִ��� �˻��Ѵ�
			if (connectedWireRgn.PtInRegion(mousePoint)) {
				copyPoints(points, selectedConnectedWirePoints,4);
				ret = true;
				break;
			}
			connectedWireRgn.DeleteObject();

		}
		if (ret == true) { break; }
	}

	return ret;
}




void CMFCLogicSimulatorView::copyTerminalInfo(SELECTED_TERMINAL_INFO & source, SELECTED_TERMINAL_INFO & destination)
{
	destination.componentID = source.componentID;
	destination.terminalType = source.terminalType;
	destination.terminalNumber = source.terminalNumber;
}

void CMFCLogicSimulatorView::copyPoints(CPoint * source, CPoint * destination,int size)
{
	for (int i = 0; i < size; i++) {
		destination[i].x = source[i].x;
		destination[i].y = source[i].y;
 	}
}

