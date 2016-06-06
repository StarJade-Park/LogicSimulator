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
#define DEFAULT_VALUE_ADDING_COMPONENT_DIRECTION EAST 

enum LIBRARYBOX_TYPE {
	LIBRARYBOX_TYPE_NONE,
	LIBRARYBOX_TYPE_NAND,
	LIBRARYBOX_TYPE_NOR,
	LIBRARYBOX_TYPE_TFF, 
	LIBRARYBOX_TYPE_JKFF,
	LIBRARYBOX_TYPE_DFF,
	LIBRARYBOX_TYPE_USER_DEFINE
};

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
		label = "";
		hz = 10;
		clockEdge = true;
		libraryBoxType = LIBRARYBOX_TYPE_NONE;
	}
	//���� ���� �� �� ���� ��ǥ
	int x,y;
	int hz;
	BOOL clockEdge;
	COMPONENT_ID id;
	COMPONENT_TYPE type;
	COMPONENT_DIRECTION direction;
	CString label;
	LIBRARYBOX_TYPE libraryBoxType;
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
	OPERATION_MODE_VAlUE_CHANGE,
	OPERATION_MODE_SELECTeE_WIRE
};



class CMFCLogicSimulatorDoc : public CDocument
{
	protected: // serialization������ ��������ϴ�.
	CMFCLogicSimulatorDoc();
	DECLARE_DYNCREATE(CMFCLogicSimulatorDoc)

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

	LIBRARY_BOX_DATA nandGateData;
	LIBRARY_BOX_DATA norGateData;

	//Ʈ���信�� ������ ��ǰ����
	int currentSelectedItemIndex;
	bool isRunningMode;
	int selectedComponentID;
	bool isCurcuitOcillate;
	COMPONENT_CONENTION_INFO selectedconnectionInfoA;
	COMPONENT_CONENTION_INFO selectedconnectionInfoB;
	OPERATION_MODE operationMode;

	//��ǰ�� �߰��Ѵ�
	bool addComponentToEngine(int _x,int _y);	
	void deleteComponentToEngine();

	//��ǰ�� ���� �����Ѵ�
	bool connectComponent(COMPONENT_CONENTION_INFO& A, COMPONENT_CONENTION_INFO& B);
	//��ǰ�� ���� ���������Ѵ�
	void disconectComponent();

	int getSelectedItemIndexInToolBox(HTREEITEM hItem);
	//Ʈ���信�� ������ ��ǰ�� �÷��׷�  COMPONENT_TYPE�� �˾Ƴ���
	COMPONENT_TYPE getComponentTypeByToolBoxItemIndex(int type);
	COMPONENT_TYPE getCurrentSelectedComponentType();
	LIBRARYBOX_TYPE getCurrentSelectedComponentlibraryBoxType();
	void getStringByCOMPONENT_DIRECTION(COMPONENT_DIRECTION direct, CString & CS);
	void getStringByCOMPONENT_TYPE(COMPONENT_TYPE compType, CString & CS);
	
	void make_NORGATE(CLibraryBox& box);
    void make_NANDGATE(CLibraryBox& box);		

	void storeEngineComponentData(CArchive& ar, vector <COMPONENT_DATA>* engineComponentData);
	void loadEngineComponentData(CArchive& ar, vector <COMPONENT_DATA>* engineComponentData);
	void storeEngineCoreData(CArchive& ar, LIBRARY_BOX_DATA& data);
	void loadEngineCoreData(CArchive& ar, LIBRARY_BOX_DATA& data);

	bool checkConnectionWireToWire(COMPONENT_CONENTION_INFO& A, COMPONENT_CONENTION_INFO& B);

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
