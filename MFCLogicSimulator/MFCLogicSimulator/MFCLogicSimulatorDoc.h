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

//��ť��Ʈ���� ����� ��ǰ���� ����ü
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

enum TOOLBOX_ITEM_TYPE {
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

enum OPERATION_MODE {
	OPERATION_MODE_NONE,
	OPERATION_MODE_ADDING_COMPONENT,
	OPERATION_MODE_SELECT_COMPONENT,
	OPERATION_MODE_CONNECTING_COMPONENT
};

class CMFCLogicSimulatorDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CMFCLogicSimulatorDoc();
	DECLARE_DYNCREATE(CMFCLogicSimulatorDoc)

// Ư���Դϴ�.
public:

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
	TOOLBOX_ITEM_TYPE currentSelectedItem;

	//��ǰ�� �߰��Ѵ�
	bool addComponentToEngine(int _x,int _y);

	TOOLBOX_ITEM_TYPE getSelectedItemInToolBox(HTREEITEM hItem);

	//Ʈ���信�� ������ ��ǰ�� �÷��׷�  COMPONENT_TYPE�� �˾Ƴ���
	COMPONENT_TYPE getComponentTypeByToolBoxItem(TOOLBOX_ITEM_TYPE type);

	COMPONENT_TYPE getCurrentSelectedComponentType();

	OPERATION_MODE operationMode;


};
