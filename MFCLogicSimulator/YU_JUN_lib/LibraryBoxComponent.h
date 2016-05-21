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
//input pin ��� �߰�
#include "InputPinComponent.h"
//output pin ��� �߰�
#include "OutputPin.h"
#include <vector>

//component type ������
enum COMPONENT_TYPE { COMPONENT_TYPE_INPUT_PIN,COMPONENT_TYPE_CLOCK, COMPONENT_TYPE_ONE_BIT_SWITCH,
	COMPONENT_TYPE_AND_GATE, COMPONENT_TYPE_OR_GATE, COMPONENT_TYPE_NOT_GATE,
	COMPONENT_TYPE_NAND_GATE, COMPONENT_TYPE_NOR_GATE, COMPONENT_TYPE_XOR_GATE,
	COMPONENT_TYPE_WIRE,
	COMPONENT_TYPE_7SEGMENT, COMPONENT_TYPE_OUTPUT_PIN, COMPONENT_TYPE_ONE_BIT_LAMP,
	COMPONENT_TYPE_LIBRARY_BOX
};

//�߰��� component�� ����ü
struct COMPONENT_INFO {
	COMPONENT_TYPE componentType;
	int x, y;
	enum DIRECTION direction;
	ID_COMPONENT componentID;
};

//������ component�� ����ü
struct CONNECTING_COMPONENT_INFO {
	ID_COMPONENT componentID;
	TERMINAL_TYPE terminalType;
	int terminalNumber;
};

struct LIBRARY_BOX_DATA {

};


class CLibraryBox :public CComponentObject {
private:
	//��ǰ���� ���� ���� ��ü��
	std::vector<CComponentObject> logicGateList;
	std::vector<InputPinComponent> inputList;
	std::vector<COutputPin> outputList;
	std::vector<CWireComponent> wireList;

	//��ǰ���� �׷�����ǥ���� 2�� vector
	std::vector< std::vector<int> > componetGraph;

public:
	CLibraryBox();
	CLibraryBox(CLibraryBox& object);
	~CLibraryBox();
	
	//���̺귯�� �ڽ��� �ε���
	void loadLibrarybox(LIBRARY_BOX_DATA componentList);
	//���̺귯�� �ڽ��� ���̺���
	LIBRARY_BOX_DATA saveLibrarybox();

	//��ǲ �� �ϳ������� getter,setter
	void setSingleInputPinValue(bool _inputValue, int _inputPinNumber);
	bool getSingleInputPinValue(int _inputPinNumber);

	//�ƿ�ǲ �� �ϳ������� getter
	void getSingleOutputPinValue(int _inputPinNumber);
	

	//��ǰ �߰� ���н� false ��ȯ
	bool addComponent(COMPONENT_INFO& componentInfo);
	
	//��ǰ����
	void deleteInputPin(ID_COMPONENT inputPinID);
	void deleteOutputPin(ID_COMPONENT outputPinID);
	void deleteComponent(ID_COMPONENT componentID);
	
	//����������� ��ǰ�� ������
	bool connectComponentAToB(ID_COMPONENT AComponentID, TERMINAL_TYPE AComponentType, int AComponentTerminalNumber,
		ID_COMPONENT BComponentID, TERMINAL_TYPE BComponentType, int BComponentTerminalNumber);
	bool connectComponentAToB(CONNECTING_COMPONENT_INFO& AConponentInfo, CONNECTING_COMPONENT_INFO& BConponentInfo);
	
	//����� ��ǰ�� �и���
	bool disconnectComponentAToB(ID_COMPONENT AComponentID, TERMINAL_TYPE AComponentType, int AComponentTerminalNumber,
		ID_COMPONENT BComponentID, TERMINAL_TYPE BComponentType, int BComponentTerminalNumber);
	bool disconnectComponentAToB(CONNECTING_COMPONENT_INFO& AConponentInfo, CONNECTING_COMPONENT_INFO& BConponentInfo);

	//���̺귯�� �ڽ� ����ȸ�� ���� 
	bool updateCircuit();

};