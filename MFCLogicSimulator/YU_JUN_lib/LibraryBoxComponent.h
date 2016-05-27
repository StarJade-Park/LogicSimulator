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


enum TERMINAL_TYPE {
	TERMINAL_TYPE_NONE, TERMINAL_TYPE_INPUT,
	TERMINAL_TYPE_OUTPUT, TERMINAL_TYPE_WIRE
};


//component Ÿ��
enum COMPONENT_TYPE {
	COMPONENT_TYPE_NONE,
	COMPONENT_TYPE_INPUT_PIN, COMPONENT_TYPE_CLOCK, COMPONENT_TYPE_ONE_BIT_SWITCH,
	COMPONENT_TYPE_AND_GATE, COMPONENT_TYPE_OR_GATE, COMPONENT_TYPE_NOT_GATE,
	COMPONENT_TYPE_NAND_GATE, COMPONENT_TYPE_NOR_GATE, COMPONENT_TYPE_XOR_GATE,
	COMPONENT_TYPE_WIRE,
	COMPONENT_TYPE_7SEGMENT, COMPONENT_TYPE_OUTPUT_PIN, COMPONENT_TYPE_ONE_BIT_LAMP,
	COMPONENT_TYPE_LIBRARY_BOX
};

#define COMPONENT_ID int 




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
#define INPUT_PIN_INPUT_SIZE 0
#define INPUT_PIN_OUTPUT_SIZE 1
#define ANDGATE_INPUT_SIZE 2
#define ANDGATE_OUTPUT_SIZE 1
#define ORGATE_INPUT_SIZE 2
#define ORGATE_OUTPUT_SIZE 1
#define NOTGATE_INPUT_SIZE 1
#define NOTGATE_OUTPUT_SIZE 1
#define XORGATE_INPUT_SIZE 2
#define XORGATE_OUTPUT_SIZE 1
#define OUTPUT_PIN_INPUT_SIZE 1
#define OUTPUT_PIN_OUTPUT_SIZE 0 

private:
	int numberOfComponent;
	//��ǰ���� ���� ���� ��ü��
	vector< CComponentObject* > componentVector;

	//���̺귯�� �ڽ��� ��ǲ�ɰ� �ƿ�ǲ ���� �����ϴ� ���� ����Ʈ
	vector< COMPONENT_ID > inputPinIDVector;
	vector< COMPONENT_ID > outputPinIDVector;

	//��ǰ���� ���ᳪŸ���� ������ �׷����� ��������Ʈ 
	vector< vector < COMPONENT_CONENTION_INFO > > inputGraph;
	vector< vector < COMPONENT_CONENTION_INFO > > outputGraph;
	
	//��ǰ���� ������ Ÿ���� �����ϴ� ����
	vector< COMPONENT_TYPE >  componentTypeVector;

	//��ǰ���� ���̵� �����ϴ� ����
	vector < bool > componentIDVector;
	bool isOscillation;
	bool isLibraryBoxOutputValueChanged;
public:
	CLibraryBox();
	CLibraryBox(CLibraryBox& object);
	~CLibraryBox();
	

	//��ǰ�� ���̵� �������
	COMPONENT_ID makeNewComponetID(COMPONENT_TYPE componentType);
	//��ǰ�� ���̵� ������
	void deleteComponentID(COMPONENT_ID deleteId);
	
	//���̺귯�� �ڽ��� �ε���
	void loadLibrarybox(vector<LIBRARY_BOX_DATA>& LibraryBoxData);
	//���̺귯�� �ڽ��� ���̺���
	void saveLibrarybox(vector<LIBRARY_BOX_DATA>& _componentList);

	//��ǲ �� �ϳ������� getter,setter
	void setSingleInputPinValue(bool _inputValue, int _inputPinNumber);
	bool getSingleInputPinValue(int _inputPinNumber);
	//�ƿ�ǲ �� �ϳ������� getter
	bool getSingleOutputPinValue(int _outputPinNumber);
	
	//��ǰ �߰� ���н� false ��ȯ
	bool addComponent(COMPONENT_INFO& componentInfo);	
	//��ǰ����
	bool deleteComponent(COMPONENT_ID componentID);
	
	bool connnectComponent(COMPONENT_CONENTION_INFO* componentA, COMPONENT_CONENTION_INFO* componentB);

	bool disconnectComponent(COMPONENT_CONENTION_INFO* componentA, COMPONENT_CONENTION_INFO* componentB);

	//���̺귯�� �ڽ� ����ȸ�� ���� 
	bool updateCircuit();
	
	//�����ֱ⿩�� ���� ���� ������ִ� ���α׷�
	void printstatus();

	virtual int numberOfInput();
	virtual int numberOfOutput();
	virtual bool setInputValue(int index, bool _value);
	virtual bool getInputValue(int index) ;
	virtual bool getOutputValue(int index) ;
	virtual bool update();
};