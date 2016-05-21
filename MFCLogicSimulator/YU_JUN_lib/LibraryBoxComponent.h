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


class CLibraryBox : CComponentObject {

private:
	//��ǰ���� ���� ���� ��ü��
	vector<CComponentObject> logicGateList;
	vector<InputPinComponent> inputList;	
	vector<COutputPin> outputList;
	vector<CWireComponent> wireList;

	//��ǰ���� �׷�����ǥ���� 2�� vector
	vector< vector<int> > componetGrape;
	
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
	ID_COMPONENT getNewComponentID();
	ID_COMPONENT getNumberOfComponentID();

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












};