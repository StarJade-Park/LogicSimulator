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