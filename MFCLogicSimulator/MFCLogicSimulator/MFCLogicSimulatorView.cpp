// 이 MFC 샘플 소스 코드는 MFC Microsoft Office Fluent 사용자 인터페이스("Fluent UI")를 
// 사용하는 방법을 보여 주며, MFC C++ 라이브러리 소프트웨어에 포함된 
// Microsoft Foundation Classes Reference 및 관련 전자 문서에 대해 
// 추가적으로 제공되는 내용입니다.  
// Fluent UI를 복사, 사용 또는 배포하는 데 대한 사용 약관은 별도로 제공됩니다.  
// Fluent UI 라이선싱 프로그램에 대한 자세한 내용은 
// http://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// MFCLogicSimulatorView.cpp : CMFCLogicSimulatorView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFCLogicSimulator.h"
#endif

#include "MFCLogicSimulatorDoc.h"
#include "MFCLogicSimulatorView.h"

#include "FileView.h" // tree item 관련하여 추가
#include "PropertiesWnd.h" // 속성창 옵션 수정 관련하여 추가

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
	// 표준 인쇄 명령입니다.
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

// CMFCLogicSimulatorView 생성/소멸



CMFCLogicSimulatorView::CMFCLogicSimulatorView()
{
	// TODO: 여기에 생성 코드를 추가합니다.


}

CMFCLogicSimulatorView::~CMFCLogicSimulatorView()
{
}

BOOL CMFCLogicSimulatorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CScrollView::PreCreateWindow(cs);
}

// CMFCLogicSimulatorView 그리기

void CMFCLogicSimulatorView::OnDraw(CDC* /*pDC*/)
{
	CMFCLogicSimulatorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.


}


// CMFCLogicSimulatorView 인쇄


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
	// 뷰의 전체 크기 계산(정의)
	sizeTotal.cx = 1600;
	sizeTotal.cy = 1200;

	SetScrollSizes(MM_TEXT, sizeTotal);
}

BOOL CMFCLogicSimulatorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMFCLogicSimulatorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMFCLogicSimulatorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CMFCLogicSimulatorView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCLogicSimulatorView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	// popup menu 비활성화 상태
	//theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCLogicSimulatorView 진단

#ifdef _DEBUG
void CMFCLogicSimulatorView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CMFCLogicSimulatorView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CMFCLogicSimulatorDoc* CMFCLogicSimulatorView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCLogicSimulatorDoc)));
	return (CMFCLogicSimulatorDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCLogicSimulatorView 메시지 처리기


void CMFCLogicSimulatorView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// logic doc 포인터 가져옴
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CMFCLogicSimulatorDoc* pDoc = GetDocument();

	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CDC* pDC = GetDC();
	CString str;

	int itemIndex = GetDocument()->itemSelectedInDoc();
	str.Format(_T("%d"), itemIndex);

	// 스크롤바 컨트롤시 지워지는 문제있음
	switch (itemIndex) { // 사용자 설정 따로 빼둘 것
	case FOLDER_ROOT: // root
		pDC->TextOutW(point.x, point.y, str);
		break;
	default:
		//AfxMessageBox(_T("item ??"));
		pDC->TextOutW(point.x, point.y, str);
		break;
	}


	//지금 부품 선택 모드이면
	if (pDoc->currentSelectedItem > 0) {
		//보정할 좌표를 가져온다
		int nVertScroll = GetScrollPos(SB_VERT);
		int nHorzScroll = GetScrollPos(SB_HORZ);
		//선택한 부품을 도큐에 추가한다
		pDoc->addComponentToEngine(point.x + nHorzScroll, point.y + nVertScroll);

		//tree view 부품 선택모드를 해제하는 메세지를 날린다		
		((pFrame->getCFileView())->getCFileViewTree())->SendMessage(UM_UNSELECT_ITEM);

	}
	//지금 부품 선택 아니면
	else {
		//만약 부품을 선택하면 부품 선택 모드로 변경한다
		//선택한 부품을 하이라이트 한다

		//만약 부품의 단자를 선택하면 단자를 하이라이트 한다




	}






	ReleaseDC(pDC); //사용이 끝나고 디바이스 컨텍스트를 운영체제에게 반납한다.


	Invalidate();




	CScrollView::OnLButtonDown(nFlags, point);
}


void CMFCLogicSimulatorView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CScrollView::OnLButtonUp(nFlags, point);
}

//이것을 해야한다 참고자료
//http://adnoctum.tistory.com/149
void CMFCLogicSimulatorView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CScrollView::OnPaint()을(를) 호출하지 마십시오.

	CMFCLogicSimulatorDoc* pDoc = GetDocument();
	CRect rect;
	GetClientRect(&rect);

	CDC memDC;
	CBitmap newBitmap;
	CBitmap *pOldBitmap;

	//더블버퍼링을 하기 위해 버퍼역할을 할 비트맵을 지정한다
	memDC.CreateCompatibleDC(&dc);
	newBitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
	pOldBitmap = memDC.SelectObject(&newBitmap);
	memDC.PatBlt(0, 0, rect.Width(), rect.Height(), WHITENESS);


	//메모리에다가 그리기시작
	{
		// 뷰 스크롤 및 크기 조정
		// https://msdn.microsoft.com/ko-kr/library/cc468151(v=vs.71).aspx
		// http://eachan.tistory.com/3
		/* 스크롤바 컨트롤 */ {
			int nVertScroll = GetScrollPos(SB_VERT);
			int nHorzScroll = GetScrollPos(SB_HORZ);

			CPoint scrollpos = GetScrollPosition();
			memDC.BitBlt(-scrollpos.x, -scrollpos.y, rlClientRect.right, rlClientRect.bottom,&memDC, 0, 0, SRCCOPY);
		}
		/* 스크롤바 컨트롤 끝 */

		{
			//그리기 시작

			//부품들을 그린다
			drawComponent(memDC);

			//터미널 단자를 그림
			drawComponentTerminal(memDC);

			//와이어들을 그림
			drawComponentWire(memDC);

			//추가 모드일때만 한다
			//부품 추가 모드일떄 움직이면서 보여주는거
			drawAddingComponent(memDC);

			//화면에 있는 선택 한부품을 강조하는거
			drawHighlightSelectedComponent(memDC);

			//화면에 메세지를 띄어주는것
			drawMassage(memDC);
		}
	}

	//그리기 종료

	//버퍼 역할을 하는 비트맵을 화면으로 출력한다
	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);
	dc.SelectObject(pOldBitmap);
	newBitmap.DeleteObject();
	ReleaseDC(&memDC);
	DeleteDC(memDC);




}

void CMFCLogicSimulatorView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CScrollView::OnMouseMove(nFlags, point);

	//부품 추가 모드 일때 선택한 부품의 좌표를 갱신한다

	//마우스가 부품위에 있는경우 부품을 강조한다

	//마우스가부품의 단자 위에 있으면  단자를 강조한다

}



void CMFCLogicSimulatorView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CScrollView::OnHScroll(nSBCode, nPos, pScrollBar);
	Invalidate();
}


void CMFCLogicSimulatorView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CScrollView::OnVScroll(nSBCode, nPos, pScrollBar);
	Invalidate();
}





void CMFCLogicSimulatorView::drawComponent(CDC &DC)
{
	//공통적으로 들어갈 변수들
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

	

	//부품 추가 모드일때
	//추가하는 부품을 그려준다
	for (int i = 0; i < pDoc->engineComponentData.size(); i++) {
		//존재하지 않는것은 넘어간다
		if (pDoc->engineComponentData[i].id <= 0) {
			continue;
		}
		//그려줄 좌표를 보정한다
		x = pDoc->engineComponentData[i].x - nHorzScroll;
		y = pDoc->engineComponentData[i].y - nVertScroll;
		type = pDoc->engineComponentData[i].type;

		componentBitmap.LoadBitmapW(IDB_IN_OFF);
		componentBitmap.GetBitmap(&bitmapInfo);

		//타입에 맞는 부품을 그린다
		oldBitmap = memDC.SelectObject(&componentBitmap);
		DC.BitBlt(x, y, bitmapInfo.bmWidth, bitmapInfo.bmHeight, &memDC, 0, 0, SRCCOPY);
		memDC.SelectObject(oldBitmap);

		componentBitmap.DeleteObject();
		count++;
	}
}

void CMFCLogicSimulatorView::drawComponentTerminal(CDC & DC)
{
	//공통적으로 들어갈 변수들
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
	//공통적으로 들어갈 변수들
	CDC memDC;
	memDC.CreateCompatibleDC(&DC);
	CMFCLogicSimulatorDoc* pDoc = GetDocument();
	int nVertScroll = GetScrollPos(SB_VERT);
	int nHorzScroll = GetScrollPos(SB_HORZ);
	int x, y;
}

void CMFCLogicSimulatorView::drawHighlightSelectedComponent(CDC & DC)
{
	//공통적으로 들어갈 변수들
	CDC memDC;
	memDC.CreateCompatibleDC(&DC);
	CMFCLogicSimulatorDoc* pDoc = GetDocument();
	int nVertScroll = GetScrollPos(SB_VERT);
	int nHorzScroll = GetScrollPos(SB_HORZ);
	int x, y;
}

void CMFCLogicSimulatorView::drawMassage(CDC & DC)
{
	//공통적으로 들어갈 변수들
	CDC memDC;
	memDC.CreateCompatibleDC(&DC);
	CMFCLogicSimulatorDoc* pDoc = GetDocument();
	int nVertScroll = GetScrollPos(SB_VERT);
	int nHorzScroll = GetScrollPos(SB_HORZ);
	int x, y;
}

int CMFCLogicSimulatorView::getBitmapIDByComponentType(COMPONENT_TYPE _type)
{
	//enum COMPONENT_TYPE {
	//	COMPONENT_TYPE_NONE,
	//	COMPONENT_TYPE_INPUT_PIN, COMPONENT_TYPE_CLOCK, COMPONENT_TYPE_ONE_BIT_SWITCH,
	//	COMPONENT_TYPE_AND_GATE, COMPONENT_TYPE_OR_GATE, COMPONENT_TYPE_NOT_GATE,
	//	COMPONENT_TYPE_NAND_GATE, COMPONENT_TYPE_NOR_GATE, COMPONENT_TYPE_XOR_GATE,
	//	COMPONENT_TYPE_WIRE,
	//	COMPONENT_TYPE_7SEGMENT, COMPONENT_TYPE_OUTPUT_PIN, COMPONENT_TYPE_ONE_BIT_LAMP,
	//	COMPONENT_TYPE_LIBRARY_BOX
	//};

	//switch (_type) {
	//case COMPONENT_TYPE_NONE:
	//	break;
	//case COMPONENT_TYPE_INPUT_PIN:

	//case COMPONENT_TYPE_CLOCK:

	//casen COMPONENT_TYPE_ONE_BIT_SWITCH:

	//case COMPONENT_TYPE_AND_GATE:

	//case COMPONENT_TYPE_OR_GATE:

	//case COMPONENT_TYPE_NOT_GATE:

	//case COMPONENT_TYPE_NAND_GATE:

	//case COMPONENT_TYPE_NOR_GATE:

	//case COMPONENT_TYPE_XOR_GATE:

	//case COMPONENT_TYPE_WIRE:

	//case COMPONENT_TYPE_7SEGMENT:

	//case COMPONENT_TYPE_OUTPUT_PIN:

	//case COMPONENT_TYPE_ONE_BIT_LAMP:

	//case COMPONENT_TYPE_LIBRARY_BOX:


	//}

	return 0;
}

//이것을 해야한다
//http://adnoctum.tistory.com/149
BOOL CMFCLogicSimulatorView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	return true;
}
