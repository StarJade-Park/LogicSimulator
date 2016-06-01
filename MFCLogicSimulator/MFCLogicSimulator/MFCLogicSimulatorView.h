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

#pragma once
#include "ViewTree.h"
#include "FileView.h" // tree item �����Ͽ� �߰�
#include "PropertiesWnd.h" // �Ӽ�â �ɼ� ���� �����Ͽ� �߰�
#include "MFCLogicSimulatorDoc.h"

// ��ũ�� ����
// http://moguwai.tistory.com/entry/CView-CScrollView%EB%A1%9C-%EC%A0%84%ED%99%98


class CMFCLogicSimulatorView : public CScrollView
{
protected: // serialization������ ��������ϴ�.
	CMFCLogicSimulatorView();
	DECLARE_DYNCREATE(CMFCLogicSimulatorView)

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

// �۾��Դϴ�.
public:
	CRect rlClientRect;
	CFileView* p_toolbox; // tool box ������
						  
// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate();
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CMFCLogicSimulatorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

protected:

	//��� �׸��� �Լ���
	//��� ������Ʈ �� �׸�
	void drawComponent(CDC &MemDC);

	//�͹̳� ���ڸ� �׸�
	void drawComponentTerminal(CDC &MemDC);

	//���̾���� �׸�
	void drawComponentWire(CDC &MemDC);
	
	//��ǰ �߰� ����ϋ� �����̸鼭 �����ִ°�
	void drawAddingComponent(CDC &MemDC);

	//ȭ�鿡 �ִ� ���� �Ѻ�ǰ�� �����ϴ°�
	void drawHighlightSelectedComponent(CDC &MemDC);

	//ȭ�鿡 �ִ� ���� �Ѻ�ǰ�� �����ϴ°�
	void drawMassage( CDC &MemDC);

public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

#ifndef _DEBUG  // MFCLogicSimulatorView.cpp�� ����� ����
inline CMFCLogicSimulatorDoc* CMFCLogicSimulatorView::GetDocument() const
   { return reinterpret_cast<CMFCLogicSimulatorDoc*>(m_pDocument); }
#endif

