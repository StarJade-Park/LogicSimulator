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


class CLibraryBox :public CComponentObject {
private:
	//��ǰ���� ���� ���� ��ü��
	std::vector<CComponentObject> logicGateList;
	std::vector<InputPinComponent> inputList;
	std::vector<COutputPin> outputList;
	std::vector<CWireComponent> wireList;

	//��ǰ���� �׷�����ǥ���� 2�� vector
	std::vector< std::vector<int> > componetGrape;
	
	//��� ��ǰ�� ��
	int totalComponentNumber;

	// ��ǰ���� id�� ������ִ� ����
	// ���ݱ��� ������ ��ǰ�� ���� ����


public:
	CLibraryBox();
	CLibraryBox(CLibraryBox& object);
	~CLibraryBox();
	
	void setinputValue(bool _inputValue, int componentnumber);
	void getOutputValue(int ComponentNumber);
	
	//���ο� component Id ���� ����


	//��ǰ �߰�	
	ID_COMPONENT addInputPin();
	ID_COMPONENT addOutputPin();
	ID_COMPONENT addWire();
	ID_COMPONENT addANDGate();
	ID_COMPONENT addORGate();
	ID_COMPONENT addNORGate();
	ID_COMPONENT addNANDGate();
	ID_COMPONENT addNOTGate();
	ID_COMPONENT addXORGate();
	
	//��ǰ����
	void deleteInputPin(ID_COMPONENT inputPinID);
	void deleteOutputPin(ID_COMPONENT outputPinID);
	void deleteComponent(ID_COMPONENT componentID);
	
	//����������� ��ǰ�� ������
	bool connectComponentAToB(ID_COMPONENT AComponentID, TERMINAL_TYPE AComponentType, int AComponentTerminalNumber,
		ID_COMPONENT BComponentID, TERMINAL_TYPE BComponentType, int BComponentTerminalNumber);
	
	//����� ��ǰ�� �и���
	bool disConnectComponentAToB(ID_COMPONENT AComponentID, TERMINAL_TYPE AComponentType, int AComponentTerminalNumber,
		ID_COMPONENT BComponentID, TERMINAL_TYPE BComponentType, int BComponentTerminalNumber);











};