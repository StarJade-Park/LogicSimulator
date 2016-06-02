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

// CMFCLogicSimulatorView �׸���

void CMFCLogicSimulatorView::OnDraw(CDC* /*pDC*/)
{
	CMFCLogicSimulatorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.


}


// CMFCLogicSimulatorView �μ�


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
	sizeTotal.cx = 1600;
	sizeTotal.cy = 1200;

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


void CMFCLogicSimulatorView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// logic doc ������ ������
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CMFCLogicSimulatorDoc* pDoc = GetDocument();

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CDC* pDC = GetDC();
	CString str;

	int itemIndex = GetDocument()->itemSelectedInDoc();
	str.Format(_T("%d"), itemIndex);

	// ��ũ�ѹ� ��Ʈ�ѽ� �������� ��������
	switch (itemIndex) { // ����� ���� ���� ���� ��
	case FOLDER_ROOT: // root
		pDC->TextOutW(point.x, point.y, str);
		break;
	default:
		//AfxMessageBox(_T("item ??"));
		pDC->TextOutW(point.x, point.y, str);
		break;
	}


	//���� ��ǰ ���� ����̸�
	if (pDoc->currentSelectedItem > 0) {
		//������ ��ǥ�� �����´�
		int nVertScroll = GetScrollPos(SB_VERT);
		int nHorzScroll = GetScrollPos(SB_HORZ);
		//������ ��ǰ�� ��ť�� �߰��Ѵ�
		pDoc->addComponentToEngine(point.x + nHorzScroll, point.y + nVertScroll);

		//tree view ��ǰ ���ø�带 �����ϴ� �޼����� ������		
		((pFrame->getCFileView())->getCFileViewTree())->SendMessage(UM_UNSELECT_ITEM);

	}
	//���� ��ǰ ���� �ƴϸ�
	else {
		//���� ��ǰ�� �����ϸ� ��ǰ ���� ���� �����Ѵ�
		//������ ��ǰ�� ���̶���Ʈ �Ѵ�

		//���� ��ǰ�� ���ڸ� �����ϸ� ���ڸ� ���̶���Ʈ �Ѵ�




	}






	ReleaseDC(pDC); //����� ������ ����̽� ���ؽ�Ʈ�� �ü������ �ݳ��Ѵ�.


	Invalidate();




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
	CPaintDC dc(this); // device context for painting
					   // TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
					   // �׸��� �޽����� ���ؼ��� CScrollView::OnPaint()��(��) ȣ������ ���ʽÿ�.

	CMFCLogicSimulatorDoc* pDoc = GetDocument();
	CRect rect;
	GetClientRect(&rect);

	CDC memDC;
	CBitmap newBitmap;
	CBitmap *pOldBitmap;

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
			memDC.BitBlt(-scrollpos.x, -scrollpos.y, rlClientRect.right, rlClientRect.bottom,&memDC, 0, 0, SRCCOPY);
		}
		/* ��ũ�ѹ� ��Ʈ�� �� */

		{
			//�׸��� ����

			//��ǰ���� �׸���
			drawComponent(memDC);

			//�͹̳� ���ڸ� �׸�
			drawComponentTerminal(memDC);

			//���̾���� �׸�
			drawComponentWire(memDC);

			//�߰� ����϶��� �Ѵ�
			//��ǰ �߰� ����ϋ� �����̸鼭 �����ִ°�
			drawAddingComponent(memDC);

			//ȭ�鿡 �ִ� ���� �Ѻ�ǰ�� �����ϴ°�
			drawHighlightSelectedComponent(memDC);

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

}



void CMFCLogicSimulatorView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CScrollView::OnHScroll(nSBCode, nPos, pScrollBar);
	Invalidate();
}


void CMFCLogicSimulatorView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CScrollView::OnVScroll(nSBCode, nPos, pScrollBar);
	Invalidate();
}





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

	CBitmap componentBitmap;
	CBitmap *oldBitmap;
	BITMAP bitmapInfo;

	

	//��ǰ �߰� ����϶�
	//�߰��ϴ� ��ǰ�� �׷��ش�
	for (int i = 0; i < pDoc->engineComponentData.size(); i++) {
		//�������� �ʴ°��� �Ѿ��
		if (pDoc->engineComponentData[i].id <= 0) {
			continue;
		}
		//�׷��� ��ǥ�� �����Ѵ�
		x = pDoc->engineComponentData[i].x - nHorzScroll;
		y = pDoc->engineComponentData[i].y - nVertScroll;
		type = pDoc->engineComponentData[i].type;

		//Ÿ�Կ� �´� ��ǰ�� ��Ʈ�� ���̵� �������� �ε��Ѵ�
		//getBitmapIDByComponentType(type)//����Ѵ�
		componentBitmap.LoadBitmapW(IDB_LIBRARY_BOX);
		componentBitmap.GetBitmap(&bitmapInfo);

		//��ǰ�� �׸���
		oldBitmap = memDC.SelectObject(&componentBitmap);
		DC.BitBlt(x, y, bitmapInfo.bmWidth, bitmapInfo.bmHeight, &memDC, 0, 0, SRCCOPY);
		memDC.SelectObject(oldBitmap);

		//������ ��Ʈ���� �����Ѵ�
		componentBitmap.DeleteObject();
	}
}

void CMFCLogicSimulatorView::drawComponentTerminal(CDC & DC)
{
	//���������� �� ������
	CDC memDC;
	memDC.CreateCompatibleDC(&DC);
	CMFCLogicSimulatorDoc* pDoc = GetDocument();
	int nVertScroll = GetScrollPos(SB_VERT);
	int nHorzScroll = GetScrollPos(SB_HORZ);
	int x, y;
}

void CMFCLogicSimulatorView::drawComponentWire(CDC & DC)
{
	CDC memDC;
	memDC.CreateCompatibleDC(&DC);
	CMFCLogicSimulatorDoc* pDoc = GetDocument();
	int nVertScroll = GetScrollPos(SB_VERT);
	int nHorzScroll = GetScrollPos(SB_HORZ);
	int x, y;
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

int CMFCLogicSimulatorView::getBitmapIDByComponentType(COMPONENT_TYPE _type)
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
		return IDB_ONE_BIT_SWITCH_OFF;
		break;

	//case COMPONENT_TYPE_ONE_BIT_LAMP:
	//	return IDB_ONE_BIT_SWITCH_OFF;
	//	break;
	//case COMPONENT_TYPE_7SEGMENT:
	//	return IDB_ONE_BIT_SWITCH_OFF;
	//	break;




	case COMPONENT_TYPE_AND_GATE:
		return IDB_GATE_AND;
		break;
	case COMPONENT_TYPE_OR_GATE:
		return IDB_GATE_OR;
		break;
	case COMPONENT_TYPE_NOT_GATE:
		return IDB_GATE_INVERTOR;
		break;
	case COMPONENT_TYPE_XOR_GATE:
		return IDB_GATE_XOR;
		break;

	case COMPONENT_TYPE_INPUT_PIN:
		return IDB_INPUT_PIN_OFF;
		break;
	case COMPONENT_TYPE_OUTPUT_PIN:
		return IDB_PROBE_OFF;
		break;

	case COMPONENT_TYPE_WIRE:
		return IDB_WIRE;
		break;



	case COMPONENT_TYPE_LIBRARY_BOX:
		return IDB_LIBRARY_BOX;
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
	default :
		return -1;
	}
	return 0;
}

//�̰��� �ؾ��Ѵ�
//http://adnoctum.tistory.com/149
BOOL CMFCLogicSimulatorView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	return true;
}
