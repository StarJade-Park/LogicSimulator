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
	EAST,SOUTH,WEST,NORTH
};

//��ť��Ʈ���� ����� ��ǰ���� ����ü
struct COMPONENT_DATA {
	COMPONENT_DATA() {
		x = 0;
		y = 0;
		id = -1;
		type = COMPONENT_TYPE_NONE;
		direction = EAST;	
		label = _T("�󺧸� �������ּ���.");
		hz = 10;
		clockEdge = true;
	}
	//���� ���� �� �� ���� ��ǥ
	int x,y;
	int hz;
	BOOL clockEdge;
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
	ITEM_LIBRARYBOX
};

enum OPERATION_MODE {
	OPERATION_MODE_NONE,
	OPERATION_MODE_ADDING_COMPONENT,
	OPERATION_MODE_SELECT_COMPONENT,
	OPERATION_MODE_CONNECTING_COMPONENT,
	OPERATION_MODE_VAlUE_CHANGE
};


#define DEFAULT_VALUE_ADDING_COMPONENT_DIRECTION EAST
class CMFCLogicSimulatorDoc : public CDocument
{
	protected: // serialization������ ��������ϴ�.
	CMFCLogicSimulatorDoc();
	DECLARE_DYNCREATE(CMFCLogicSimulatorDoc)

// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual ~CMFCLogicSimulatorDoc();


public : 
	//������ ������ ����
	CLibraryBox logicSimulatorEngine;
	//���� �����͵�
	LIBRARY_BOX_DATA engineCoreData;
	//�信�� ���Ǿ��� ������
	vector <COMPONENT_DATA> engineComponentData;

	//Ʈ���信�� ������ ��ǰ����
	int currentSelectedItemIndex;
	bool isRunningMode;
	int selectedComponentID;
	bool isCurcuitOcillate;


	//��ǰ�� �߰��Ѵ�
	bool addComponentToEngine(int _x,int _y);

	//��ǰ�� ���� �����Ѵ�
	bool connectComponent(COMPONENT_CONENTION_INFO& A, COMPONENT_CONENTION_INFO& B);
	
	int getSelectedItemIndexInToolBox(HTREEITEM hItem);

	//Ʈ���信�� ������ ��ǰ�� �÷��׷�  COMPONENT_TYPE�� �˾Ƴ���
	COMPONENT_TYPE getComponentTypeByToolBoxItemIndex(int type);

	COMPONENT_TYPE getCurrentSelectedComponentType();

	OPERATION_MODE operationMode;

	void make_NORGATE(CLibraryBox& box);
    void make_NANDGATE(CLibraryBox& box);

	void getStringByCOMPONENT_DIRECTION(COMPONENT_DIRECTION direct, CString & CS);
	void getStringByCOMPONENT_TYPE(COMPONENT_TYPE compType, CString & CS);
	
	

	void storeEngineComponentData(CArchive& ar);
	void loadEngineComponentData(CArchive& ar);

	void storeEngineDumpData(CArchive& ar, LIBRARY_BOX_DATA& data);
	void loadEngineDumpData(CArchive& ar, LIBRARY_BOX_DATA& data);


#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
	// �˻� ó���⿡ ���� �˻� �������� �����ϴ� ����� �Լ�
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


	// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()


};
