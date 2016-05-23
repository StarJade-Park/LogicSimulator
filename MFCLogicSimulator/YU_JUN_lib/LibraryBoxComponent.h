#pragma once
//���� Ŭ���� �߰�
#include "ComponentObject.h"

//�� ����Ʈ ��� ����߰�
#include "ANDGateComponet.h"
#include "ORGateComponent.h"
#include "NANDGateComponent.h"
#include "NORGateComponent.h"
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


//������ ����ϴ°�
#include <stdio.h>



enum TERMINAL_TYPE { TERMINAL_TYPE_NONE, TERMINAL_TYPE_INPUT, TERMINAL_TYPE_OUTPUT };


//component type ������
enum COMPONENT_TYPE {
	COMPONENT_TYPE_NONE,	
	COMPONENT_TYPE_INPUT_PIN,COMPONENT_TYPE_CLOCK, COMPONENT_TYPE_ONE_BIT_SWITCH,
	COMPONENT_TYPE_AND_GATE, COMPONENT_TYPE_OR_GATE, COMPONENT_TYPE_NOT_GATE,
	COMPONENT_TYPE_NAND_GATE, COMPONENT_TYPE_NOR_GATE, COMPONENT_TYPE_XOR_GATE,
	COMPONENT_TYPE_WIRE,
	COMPONENT_TYPE_7SEGMENT, COMPONENT_TYPE_OUTPUT_PIN, COMPONENT_TYPE_ONE_BIT_LAMP,
	COMPONENT_TYPE_LIBRARY_BOX
};

#define COMPONENT_ID int 

#define VECTOR_INIT_SIZE 10

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

//������ component�� ����ü
struct COMPONENT_CONENTION_INFO {
	COMPONENT_CONENTION_INFO() {
		componentID = 0;
		terminalType = TERMINAL_TYPE_NONE;
		terminalNumber = -1;
	}
	COMPONENT_CONENTION_INFO(COMPONENT_ID _componentId, TERMINAL_TYPE _terminalType, int _terminalNumber) {
		componentID = 0;
		terminalType = TERMINAL_TYPE_NONE;
		terminalNumber = -1;
	}
	COMPONENT_ID componentID;
	TERMINAL_TYPE terminalType;
	int terminalNumber;
};

//����
//���̺� �ε� �� ����ü
struct LIBRARY_BOX_DATA {
	LIBRARY_BOX_DATA() {

	}
	COMPONENT_ID componentID;
	COMPONENT_TYPE componentType;


	//CSimulatorObject ����
	std::string componentName;
	int numberOfInputTerminal;
	int numberOfOutputTerminal;

	//CComponentObject ����
	int x, y;
	enum DIRECTION direction;
	std::string label;


};


class CLibraryBox :public CComponentObject {
private:
	//��ǰ���� ���� ���� ��ü��
	std::vector<CSimulatorObject*> componentVector;

	//���̺귯�� �ڽ��� ��ǲ�ɰ� �ƿ�ǲ ���� �����ϴ� ���� ����Ʈ
	std::vector<COMPONENT_ID> inputPinIDVector;
	std::vector<COMPONENT_ID> outputPinIDVector;

	//��ǰ���� ���ᳪŸ���� ������ �׷����� ��������Ʈ 
	std::vector<std::vector<COMPONENT_CONENTION_INFO>> connnectionGraph;

	//��ǰ�� � ���ڰ� ��������� �˷��ִ� ������ ����
	std::vector<std::vector<COMPONENT_CONENTION_INFO>> connectedTerminalInfo;
	
	//��ǰ���� ������ Ÿ���� �����ϴ� ����
	std::vector< COMPONENT_TYPE >  componentTypeVector;

	//��ǰ���� ���̵� �����ϴ� ����
	std::vector < bool > componentIDVector;


public:
	CLibraryBox();
	CLibraryBox(CLibraryBox& object);
	~CLibraryBox();
	

	//��ǰ�� ���̵� �������
	COMPONENT_ID makeNewComponetID(COMPONENT_TYPE componentType);
	//��ǰ�� ���̵� ������
	void deleteComponentID(COMPONENT_ID deleteId);
	
	//���̺귯�� �ڽ��� �ε���
	void loadLibrarybox(std::vector<LIBRARY_BOX_DATA>& LibraryBoxData);
	//���̺귯�� �ڽ��� ���̺���
	void saveLibrarybox(std::vector<LIBRARY_BOX_DATA>& _componentList);

	//��ǲ �� �ϳ������� getter,setter
	void setSingleInputPinValue(bool _inputValue, int _inputPinNumber);
	bool getSingleInputPinValue(int _inputPinNumber);
	//�ƿ�ǲ �� �ϳ������� getter
	bool getSingleOutputPinValue(int _outputPinNumber);
	
	//��ǰ �߰� ���н� false ��ȯ
	bool addComponent(COMPONENT_INFO& componentInfo);	
	//��ǰ����
	bool deleteComponent(COMPONENT_ID componentID);
	
	//����������� ��ǰ�� ���̾ ������
	bool connectComponentAndWire(COMPONENT_CONENTION_INFO& ComponentInfo, COMPONENT_CONENTION_INFO& wireInfo);
	//���̾�� ����� ��ǰ�� �и���
	bool disconnectComponentAndWire(COMPONENT_CONENTION_INFO& ComponentInfo, COMPONENT_CONENTION_INFO& wireInfo);
	//wireA �� juntion�� ����� �ű� ���ٰ� wireB�� ������
	bool connectWireAndWire(COMPONENT_CONENTION_INFO& wireA, COMPONENT_CONENTION_INFO& wireB);
	//wireA �� juntion�� �����ϰ� wireB�� �и���
	bool disconnectWireAndWire(COMPONENT_CONENTION_INFO& wireA, COMPONENT_CONENTION_INFO& wireB);

	//���̺귯�� �ڽ� ����ȸ�� ���� 
	bool updateCircuit();
	
	//�����ֱ⿩�� ���� ���� ������ִ� ���α׷�
	void printstatus();

};