
// MFCLogicSimulatorView.h : CMFCLogicSimulatorView Ŭ������ �������̽�
//

#pragma once


class CMFCLogicSimulatorView : public CView
{
protected: // serialization������ ��������ϴ�.
	CMFCLogicSimulatorView();
	DECLARE_DYNCREATE(CMFCLogicSimulatorView)

// Ư���Դϴ�.
public:
	CMFCLogicSimulatorDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

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
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // MFCLogicSimulatorView.cpp�� ����� ����
inline CMFCLogicSimulatorDoc* CMFCLogicSimulatorView::GetDocument() const
   { return reinterpret_cast<CMFCLogicSimulatorDoc*>(m_pDocument); }
#endif

