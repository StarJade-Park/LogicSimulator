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

// MFCLogicSimulatorDoc.h : CMFCLogicSimulatorDoc Ŭ������ �������̽�
//


#pragma once
#include "MainFrm.h"
#include "LibraryBoxComponent.h"
class CMainFrame;
using std::vector;
using std::pair;
using std::make_pair;

enum COMPONENT_DIRECTION {
	EAST,WEST,NORTH,SOUTH
};

//��ť��Ʈ���� ����� ����ü
struct COMPONENT_DATA {
	COMPONENT_DATA() {
		x = 0;
		y = 0;
		id = -1;
		type = COMPONENT_TYPE_NONE;
		direction = EAST;	
		label = "";
	}
	//���� ���� �� �� ���� ��ǥ
	int x,y;
	COMPONENT_ID id;
	COMPONENT_TYPE type;
	COMPONENT_DIRECTION direction;
	CString label;
	
};

enum ToolBoxItemFlag {
	FOLDER_ROOT,
	FOLDER_WIRE,
	ITEM_WIRE, ITEM_PIN, ITEM_PROBE,
	FOLDER_GATE,
	ITEM_AND, ITEM_NAND, ITEM_OR,
	ITEM_NOR, ITEM_XOR, ITEM_NOT,
	FOLDER_FF,
	ITEM_DFF, ITEM_JKFF, ITEM_TFF,
	FOLDER_INPUT,
	ITEM_1BITBUTIN, ITEM_CLOCK,
	FOLDER_OUTPUT,
	ITEM_1BITBUTOUT, ITEM_7SEGMENT,
	ITEM_ETC
};

/* ��Ʈ�� ���ҽ� ��� ��ǥ */
#define _ZERO_POINT_X 0 // ��Ʈ�� ���� x
#define _ZERO_POINT_Y 0 // ��Ʈ�� ���� y
#define _REF_POINT_X 75 // ���콺 Ŭ���� ��� ����(x)
#define _REF_POINT_Y 32 // ���콺 Ŭ���� ��� ����(y)

#define _IN_POINT_X 0 // input a, b(x)
#define _IN_POINT_AY 25 // input a(y)
#define _IN_POINT_BY 51 // input b(y)
#define _IN_POINT_OX 75 // output (x)
#define _IN_POINT_OY 32 // output (y)


class CMFCLogicSimulatorDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CMFCLogicSimulatorDoc();
	DECLARE_DYNCREATE(CMFCLogicSimulatorDoc)

// Ư���Դϴ�.
public:
	int itemSelectedInDoc();
// �۾��Դϴ�.
public:
	CMainFrame m_MainFrmInDoc;
	CFileView m_FileViewInDoc;
	CViewTree m_FileViewTreeInDoc;
// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// �����Դϴ�.
public:
	virtual ~CMFCLogicSimulatorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// �˻� ó���⿡ ���� �˻� �������� �����ϴ� ����� �Լ�
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS


public : 
	//������ ������ ����
	CLibraryBox logicSimulatorEngine;
	//���� �����͵�
	LIBRARY_BOX_DATA engineDumpData;


	//�信�� ���Ǿ��� ������
	vector <COMPONENT_DATA> engineComponentData;

	//Ʈ���信�� ������ ��ǰ����
	int currentSelectedItem;

	//��ǰ�� �߰��Ѵ�
	bool addComponentToEngine(int _x,int _y);
};
