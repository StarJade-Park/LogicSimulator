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


void CMFCLogicSimulatorView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
					   // �׸��� �޽����� ���ؼ��� CScrollView::OnPaint()��(��) ȣ������ ���ʽÿ�.
	
	CDC MemDC;
	CDC *pDC = GetDC();
	CMFCLogicSimulatorDoc* pDoc = GetDocument();

	CBitmap buffer;
	CRect bufferRect;
	GetClientRect(&bufferRect);

	MemDC.CreateCompatibleDC(pDC);
	buffer.CreateCompatibleBitmap(pDC, bufferRect.Width(), bufferRect.Height());
	MemDC.SelectObject(&buffer);

	//�������� �ʱ�ȭ
	MemDC.PatBlt(0, 0, bufferRect.Width(), bufferRect.Height(), WHITENESS);



	// �� ��ũ�� �� ũ�� ����
	// https://msdn.microsoft.com/ko-kr/library/cc468151(v=vs.71).aspx
	// http://eachan.tistory.com/3
	/* ��ũ�ѹ� ��Ʈ�� */

	int nVertScroll = GetScrollPos(SB_VERT);
	int nHorzScroll = GetScrollPos(SB_HORZ);

	CPoint scrollpos = GetScrollPosition();
	dc.BitBlt(-scrollpos.x, -scrollpos.y, rlClientRect.right, rlClientRect.bottom,
		&MemDC, 0, 0, SRCCOPY);
	/* ��ũ�ѹ� ��Ʈ�� �� */




	// ���� ���۸� �ذ� ����
	// goo.gl/CucRl6

	


	//�׸��� ����

	//��ǰ���� �׸���
	drawComponent(dc, MemDC, pDC);

	//�͹̳� ���ڸ� �׸�
	drawComponentTerminal(dc, MemDC, pDC);

	//���̾���� �׸�
	drawComponentWire(dc, MemDC, pDC);

	//�߰� ����϶��� �Ѵ�
	//��ǰ �߰� ����ϋ� �����̸鼭 �����ִ°�
	 drawAddingComponent(dc, MemDC, pDC);

	//ȭ�鿡 �ִ� ���� �Ѻ�ǰ�� �����ϴ°�
	 drawHighlightSelectedComponent(dc, MemDC, pDC);

	//ȭ�鿡 �޼����� ����ִ°�
	 drawMassage(dc, MemDC, pDC);



	 //�׸��ⳡ

	 MemDC.SelectObject(&pDC);
	 pDC->BitBlt(0, 0, bufferRect.Width(), bufferRect.Height(), &MemDC, 0, 0, SRCCOPY);
	
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

void CMFCLogicSimulatorView::drawComponent(CPaintDC &dc, CDC &MemDC,CDC *pDC)
{

	CMFCLogicSimulatorDoc* pDoc = GetDocument();
	int nVertScroll = GetScrollPos(SB_VERT);
	int nHorzScroll = GetScrollPos(SB_HORZ);

	CPoint scrollpos = GetScrollPosition();
	MemDC.BitBlt(-scrollpos.x, -scrollpos.y, rlClientRect.right, rlClientRect.bottom,
		&MemDC, 0, 0, SRCCOPY);
	/* ��ũ�ѹ� ��Ʈ�� �� */

	// ���� ���۸� �ذ� ����
	// goo.gl/CucRl6

	//��ǰ �߰� ����϶�
	//�߰��ϴ� ��ǰ�� �׷��ش�
	for (int i = 0; i < pDoc->engineComponentData.size(); i++) {
		//�������� �ʴ°��� �Ѿ��
		if (pDoc->engineComponentData[i].id <= 0) {
			continue;
		}
		//�ش� ��ǰ�� �׷��ش�
		//������ ���� �̴�
		CString str;
		str.Format(_T("componentID: %d (x,y) = (%d,%d) type : %d"), pDoc->engineComponentData[i].id
			, pDoc->engineComponentData[i].x, pDoc->engineComponentData[i].y, pDoc->engineComponentData[i].type);
		MemDC.TextOutW(pDoc->engineComponentData[i].x - nHorzScroll,
			pDoc->engineComponentData[i].y - nVertScroll, str);


	}
}

void CMFCLogicSimulatorView::drawComponentTerminal(CPaintDC & dc, CDC & MemDC, CDC * pDC)
{
}

void CMFCLogicSimulatorView::drawComponentWire(CPaintDC & dc, CDC & MemDC, CDC * pDC)
{
}

void CMFCLogicSimulatorView::drawAddingComponent(CPaintDC & dc, CDC & MemDC, CDC * pDC)
{
}

void CMFCLogicSimulatorView::drawHighlightSelectedComponent(CPaintDC & dc, CDC & MemDC, CDC * pDC)
{
}

void CMFCLogicSimulatorView::drawMassage(CPaintDC & dc, CDC & MemDC, CDC * pDC)
{
}
