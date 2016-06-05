#pragma once
//���� Ŭ���� �߰�
#include "ComponentObject.h"
//�� ����Ʈ ��� ����߰�
#include "ANDGateComponet.h"
#include "ORGateComponent.h"
#include "NOTGateComponent.h"
#include "XORGateComponent.h"
//���̾� ��� �߰�
#include "WireComponet.h" 
//input component ��� �߰�
#include "InputPinComponent.h"
#include "ClockComponent.h"
#include "OneBitSwitch.h"
//output pin ��� �߰�
#include "OutputPin.h"
#include "7SegmentComponent.h"
#include "OneBitLampComponent.h"


#include <vector>
#include <queue>
using std::vector;
using std::queue;
using std::pair;
using std::make_pair;

//������ ����ϴ°�
#include <stdio.h>

//��ǰ�� �͹̳� Ÿ��
enum TERMINAL_TYPE {
	TERMINAL_TYPE_NONE, TERMINAL_TYPE_INPUT,
	TERMINAL_TYPE_OUTPUT, TERMINAL_TYPE_WIRE
};

//component Ÿ��
enum COMPONENT_TYPE {
	COMPONENT_TYPE_NONE,
	COMPONENT_TYPE_INPUT_PIN, COMPONENT_TYPE_CLOCK, COMPONENT_TYPE_ONE_BIT_SWITCH,
	COMPONENT_TYPE_AND_GATE, COMPONENT_TYPE_OR_GATE, COMPONENT_TYPE_NOT_GATE, COMPONENT_TYPE_XOR_GATE,
	COMPONENT_TYPE_WIRE,
	COMPONENT_TYPE_7SEGMENT, COMPONENT_TYPE_OUTPUT_PIN, COMPONENT_TYPE_ONE_BIT_LAMP,
	COMPONENT_TYPE_LIBRARY_BOX
};

//��ǰ���� ���̵�
#define COMPONENT_ID int 
//vector �� �⺻ ������
#define VECTOR_INIT_SIZE 10
//���� ī��Ʈ�� ���� �ִ� ����
#define LOOP_LIMIT 200

//������ component�� ����ü
struct COMPONENT_CONENTION_INFO {
	COMPONENT_CONENTION_INFO() {
		componentID = -1;
		terminalType = TERMINAL_TYPE_NONE;
		terminalNumber = -1;
	}
	COMPONENT_CONENTION_INFO(COMPONENT_ID _componentId, TERMINAL_TYPE _terminalType, int _terminalNumber) {
		componentID = _componentId;
		terminalType = _terminalType;
		terminalNumber = _terminalNumber;
	}
	COMPONENT_ID componentID;
	TERMINAL_TYPE terminalType;
	int terminalNumber;
};

//�߰��� component�� ����ü 
struct COMPONENT_INFO {
	COMPONENT_INFO() {
		componentID = 0;
		componentType = COMPONENT_TYPE_NONE;
	}
	COMPONENT_INFO(COMPONENT_TYPE type) {
		componentID = 0;
		componentType = type;
	}
	COMPONENT_ID componentID;
	COMPONENT_TYPE componentType;
};

//���̺귯�� �ڽ��� �ε�,���̺��� ����ü
struct LIBRARY_BOX_DATA {
	int numberOfComponent;
	//��ǰ���� ���� ���� ��ü��
	vector< CComponentObject* > componentVector;

	//���̺귯�� �ڽ��� ��ǲ�ɰ� �ƿ�ǲ ���� �����ϴ� ���� ����Ʈ
	vector< COMPONENT_ID > inputPinIDVector;
	vector< COMPONENT_ID > outputPinIDVector;

	vector < COMPONENT_ID > inputClockVector;

	//��ǰ���� ���ᳪŸ���� ������ �׷����� ��������Ʈ 
	vector< vector < COMPONENT_CONENTION_INFO > > inputGraph;
	vector< vector < COMPONENT_CONENTION_INFO > > outputGraph;

	//��ǰ���� ������ Ÿ���� �����ϴ� ����
	vector< COMPONENT_TYPE >  componentTypeVector;

	//��ǰ���� ���̵� �����ϴ� ����
	vector < bool > componentIDVector;


	bool isOscillation;
	bool isLibraryBoxOutputValueChanged;

	//��ø�� ���̺귯�� �ڽ�
	vector < LIBRARY_BOX_DATA > internalLibraryBoxData;

};

class CLibraryBox :public CComponentObject {
#define LOOP_LIMIT 200
#define ADJ_LIST vector< vector < COMPONENT_CONENTION_INFO > >
private:
	int numberOfComponent;
	//��ǰ���� ���� ���� ��ü��
	vector< CComponentObject* > componentVector;

	//���̺귯�� �ڽ��� ��ǲ�ɰ� �ƿ�ǲ ���� �����ϴ� ���� ����Ʈ
	vector< COMPONENT_ID > inputPinIDVector;
	vector< COMPONENT_ID > outputPinIDVector;
	vector < COMPONENT_ID > inputClockVector;

	//��ǰ���� ���ᳪŸ���� ������ �׷����� ��������Ʈ 
	ADJ_LIST inputGraph;
	ADJ_LIST outputGraph;
	
	//��ǰ���� ������ Ÿ���� �����ϴ� ����
	vector< COMPONENT_TYPE >  componentTypeVector;

	//��ǰ���� ���̵� �����ϴ� ����
	vector < bool > componentIDVector;
	//���� ���� ȸ�ΰ� �����ϴ��� Ȯ���ϴ� �÷���
	bool isOscillation;

	//���� ȸ�ΰ� ��°��� �ٲ������ Ȯ���ϴ� �÷���
	bool isLibraryBoxOutputValueChanged;

	//ȸ�θ� �����Ѵ�
	bool updateCircuit();

public:
	CLibraryBox();
	CLibraryBox(CLibraryBox& object);
	~CLibraryBox();
	bool amIInsideBox;

	//��ǰ�� ���̵� �������
	COMPONENT_ID makeNewComponetID(COMPONENT_TYPE componentType);
	//��ǰ�� ���̵� ������
	void deleteComponentID(COMPONENT_ID deleteId);
	
	//���̺귯�� �ڽ��� �ε���
	bool loadLibraryBoxData(LIBRARY_BOX_DATA& libraryBoxData);
	//���̺귯�� �ڽ��� ���̺���
	bool saveLibraryBoxData(LIBRARY_BOX_DATA& libraryBoxData);
	
	//��ǰ�ϳ��� �ƿ�ǲ getter
	bool getComponentOutputValue(COMPONENT_ID ID, int index);
	
	//���� ȸ�ΰ� �����ϴ��� Ȯ����
	bool checkOscillation();
	
	//��ǰ �߰� ���н� false ��ȯ
	bool addComponent(COMPONENT_INFO& componentInfo);	
	//���̺귯�� �ڽ��� �߰��ϴ� �Լ� �����ε���
	bool addComponent(COMPONENT_INFO& componentInfo, LIBRARY_BOX_DATA& libBoxdata);
	//��ǰ����
	bool deleteComponent(COMPONENT_ID componentID);
	
	//��ǰ ���� 
	bool connnectComponent(COMPONENT_CONENTION_INFO& componentA, COMPONENT_CONENTION_INFO& componentB);
	//��ǰ �и�
	bool disconnectComponent(COMPONENT_CONENTION_INFO& componentA, COMPONENT_CONENTION_INFO& componentB);

	virtual int numberOfInput();
	virtual int numberOfOutput();
	virtual bool setInputValue(int index, bool _value);
	virtual bool getInputValue(int index) ;
	virtual bool getOutputValue(int index) ;
	virtual bool update();

	//��� ��ǰ�� �ʱⰪ���� ����
	virtual void reset();

	bool setClockValue(int index, bool  _value);
	bool getClockValue(int index);
	int numberOfClock();

	CComponentObject* getComponentObject(int index);

	bool isPossibleConnection(COMPONENT_CONENTION_INFO& componentA, COMPONENT_CONENTION_INFO& componentB);

	void swapCOMPONENT_CONENTION_INFO(COMPONENT_CONENTION_INFO& A, COMPONENT_CONENTION_INFO& B);
	void copyCOMPONENT_CONENTION_INFO(COMPONENT_CONENTION_INFO& source, COMPONENT_CONENTION_INFO& destination);
	ADJ_LIST* getOutputGrahp();
	ADJ_LIST* getInputGrahp();

	//��� ������ �����Ѵ�
	void deleteObject();
};