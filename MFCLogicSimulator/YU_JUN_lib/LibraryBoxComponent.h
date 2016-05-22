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

//component type ������
enum COMPONENT_TYPE { COMPONENT_TYPE_INPUT_PIN,COMPONENT_TYPE_CLOCK, COMPONENT_TYPE_ONE_BIT_SWITCH,
	COMPONENT_TYPE_AND_GATE, COMPONENT_TYPE_OR_GATE, COMPONENT_TYPE_NOT_GATE,
	COMPONENT_TYPE_NAND_GATE, COMPONENT_TYPE_NOR_GATE, COMPONENT_TYPE_XOR_GATE,
	COMPONENT_TYPE_WIRE,
	COMPONENT_TYPE_7SEGMENT, COMPONENT_TYPE_OUTPUT_PIN, COMPONENT_TYPE_ONE_BIT_LAMP,
	COMPONENT_TYPE_LIBRARY_BOX,
	COMPONENT_TYPE_NONE
};

#define COMPONENT_ID int 

//����
//�߰��� component�� ����ü 
struct COMPONENT_INFO {
	COMPONENT_INFO() {
		componentID = 0;
		componentType = COMPONENT_TYPE_NONE;
		x = 0;
		y = 0;
		direction = DIRECTION_EAST;
		label = std::string("");
	}
	COMPONENT_ID componentID;
	COMPONENT_TYPE componentType;
	int x, y;
	enum DIRECTION direction;
	std::string label;

};

//������ component�� ����ü
struct COMPONENT_CONENTION_INFO {
	COMPONENT_CONENTION_INFO() {
		componentID = COMPONENT_TYPE_NONE;
		terminalType = TERMINAL_TYPE_NONE;
		terminalNumber = -1;
	}
	COMPONENT_ID componentID;
	TERMINAL_TYPE terminalType;
	int terminalNumber;
};

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
	std::vector<CSimulatorObject*> componentList;

	//���̺귯�� �ڽ��� ��ǲ�ɰ� �ƿ�ǲ ���� �����ϴ� ���� ����Ʈ
	std::vector<COMPONENT_ID> inputPinIDList;
	std::vector<COMPONENT_ID> outputPinIDList;

	//��ǰ���� ���ᳪŸ���� ���� �׷����� ��������Ʈ  
	std::vector<std::vector<COMPONENT_CONENTION_INFO>> connnectionGraph;

	//��ǰ�� � ���ڰ� ��������� �˷��ִ� ������ ����
	std::vector<std::vector<COMPONENT_CONENTION_INFO>> connectedTerminalInfo;
	
	//��ǰ���� ������ Ÿ���� �����ϴ� ����
	std::vector< COMPONENT_TYPE >  componentTypeList;


public:
	CLibraryBox();
	CLibraryBox(CLibraryBox& object);
	~CLibraryBox();
	
	COMPONENT_ID getNewComponetID(COMPONENT_TYPE componentType);
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

};