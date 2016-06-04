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

// MFCLogicSimulatorView.h : CMFCLogicSimulatorView Ŭ������ �������̽�
//

//gdi+ ����
///http://redstory2010.tistory.com/157



#pragma once
#include "ViewTree.h"
#include "FileView.h" // tree item �����Ͽ� �߰�
#include "PropertiesWnd.h" // �Ӽ�â �ɼ� ���� �����Ͽ� �߰�
#include "MFCLogicSimulatorDoc.h"
#include <math.h>
// ��ũ�� ����
// http://moguwai.tistory.com/entry/CView-CScrollView%EB%A1%9C-%EC%A0%84%ED%99%98

#define HIGHLIGHT_EDGE_GAP 5
#define	SELECTED_TERMINAL_INFO COMPONENT_CONENTION_INFO
#define CONNECTING_WIRE_ELLIPSE_HALF_SIZE 3
#define TERMINAL_PIN_HALF_SIZE 10
#define HIGHLIGHIT_TERMINAL_PIN_HALF_SIZE  15
#define SIZE_OF_COMPONENT_BITMAP 20
#define SIZE_OF_VIEW_X 4000
#define SIZE_OF_VIEW_Y 2000
#define PI 	3.14159265358979323846
#define HIGHLIGHT_CONNECTED_WIRE_LINE_WIDTH 10

class CMFCLogicSimulatorView : public CScrollView
{
protected: // serialization������ ��������ϴ�.
	CMFCLogicSimulatorView();
	DECLARE_DYNCREATE(CMFCLogicSimulatorView)
	DECLARE_MESSAGE_MAP()
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnFilePrintPreview();
	virtual void OnInitialUpdate();
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	// �����Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual ~CMFCLogicSimulatorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Ư���Դϴ�.
public:
	CMFCLogicSimulatorDoc* GetDocument() const;

	enum MouseButtonFlag {
		NBUTTON = NULL,							// ���콺 ��ư�� ������ ���� ����
		LBUTTON = MK_LBUTTON,					// ��Ŭ�� ����
		RBUTTON = MK_RBUTTON,					// ��Ŭ�� ����
		MBUTTON = MK_MBUTTON					// ��� Ŭ�� ����
	};
	MouseButtonFlag m_MouseButtonFlag;			// ���콺 ��ư�� Ŭ���Ǿ��ִ� ���� �÷���
	
	enum ModeFlag {
		NONE = NULL,	// ��� ��ư�� ������ ���� ����
		//EDIT = ID_INSERT_LINE		// ���� ��� ��ư
	};
	ModeFlag m_ModeFlag;

	CRect rlClientRect;
	CFileView* p_toolbox; // tool box ������
		
	CBitmap componentBitmap[SIZE_OF_COMPONENT_BITMAP];
	bool isHighlightComponentMode;
	int highlightComponentIndex;
	bool isHighlightTerminalPin;
	bool ishighlightConnectedWire;

	SELECTED_TERMINAL_INFO firstSelectedTerminalPin;
	SELECTED_TERMINAL_INFO secondSelectedTerminalPin;
	SELECTED_TERMINAL_INFO dummy_SELECTED_TERMINAL_INFO;
	CPoint currentSelectedTerminalPoint;
	CPoint oldSelectedTerminalPoint;
	CPoint selectedConnectedWirePoints[4];


// ������ �޽��� �� �Լ�
protected:
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

protected:
	//��� �׸��� �Լ���
	//��� ������Ʈ �� �׸�
	void drawComponent(CDC &DC);
	//���̾���� �׸�
	void drawConnectedWire(CDC &DC);	
	//��ǰ �߰� ����ϋ� �����̸鼭 �����ִ°�
	void drawAddingComponent(CDC &DC);
	//ȭ�鿡 �ִ� ���� �Ѻ�ǰ�� �����ϴ°�
	void drawMassage( CDC &DC);
	//��ǰ�� ���ڸ� �׸���
	void drawComponentTermialPin(CDC& DC, int x, int y, COMPONENT_DIRECTION direction, 
		int componentWidth, int componentHeight, int numberOfInputTerminal, int numberOfOutputTerminal);
	//��ǰ�� ��ü�� �׸���
	void drawComponentBody(CDC& DC, int x, int y, COMPONENT_DIRECTION direction, 
		int componentWidth, int componentHeight);
	//�����ϴ����϶��� ���� �׸���
	void drawConnectingWire(CDC& DC);
	//��ǰ ��ü�� �����ϴ� �κ��� �׸���
	void drawHighlightComponentBody(CDC& DC, int x, int y, int bitmapWidth, int bitmapHeight);
	//��ǰ��  ���ڸ� �����ϴ� �κ��� �׸���
	void drawHighlightComponentTerminalPin(CDC& DC);
	//ȭ�鿡 �ִ� ���� �Ѻ�ǰ�� �����ϴ°�
	void drawHighlightSelectedComponent(CDC &DC);
	//����ȼ��� �����ϴ� �κ��� �׸���
	void drawHighlightSelectedconnectedWire(CDC &DC);

	//Ÿ������ ��ǰ�� ���̸� ���Ѵ�
	int getComponentHeight(COMPONENT_TYPE type);
	int getComponentWidth(COMPONENT_TYPE type);
	//���� ��ǰ�� ��ǲ �͹̳� ����ǥ�� ��ȯ�Ѵ� 
	void getInputTerminalPoint(int id, CPoint &point,int index);
	//���� ��ǰ�� ��ǲ �͹̳� ���� ��ȯ�Ѵ� 
	void getOutputTerminalPoint(int id, CPoint &point,int index);
	//��ǰ�� Ÿ�Կ� �ش��ϴ� ��ǰ�� ��Ʈ�� ���̵� �����´�
	int getBitmapIDByComponentType(COMPONENT_TYPE _type, COMPONENT_DIRECTION direction);

	void getConnnectedWirePoints(CPoint* points,CPoint A ,CPoint B);


	//���� ���콺�� ��ǰ���� �ִ��� �˻��Ѵ�
	int checkMouesPointOnComponent();
	bool checkMouesPointOnTerminalPin(SELECTED_TERMINAL_INFO& selectedTerminalInfo);
	bool checkMousePointOnConnectedWire();

	void copyTerminalInfo(SELECTED_TERMINAL_INFO& source, SELECTED_TERMINAL_INFO& destination);
	void copyPoints(CPoint* source, CPoint* destination,int size);
	

};

#ifndef _DEBUG  // MFCLogicSimulatorView.cpp�� ����� ����
inline CMFCLogicSimulatorDoc* CMFCLogicSimulatorView::GetDocument() const
   { return reinterpret_cast<CMFCLogicSimulatorDoc*>(m_pDocument); }
#endif

