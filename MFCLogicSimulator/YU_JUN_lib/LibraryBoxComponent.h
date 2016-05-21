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
	vector<CComponentObject> logicGateList;
	vector<InputPinComponent> inputList;
	vector< vector<int> > componetGrape;
	vector<COutputPin> outputList;
	vector<CWireComponent> wireList;
	int totalComponentNumber;
	

public:
	CLibraryBox();
	CLibraryBox(CLibraryBox& object);
	~CLibraryBox();
	
	void setinputValue(bool _inputValue, int componentnumber);
	void getOutputValue(int ComponentNumber);
	
	void addInputPin();
	void addOuputPin();	
	void addWire();
	void addANDGate();
	void addORGate();
	void addNORGate();
	void addNANDGate();
	void addNOTGate();
	void addXORGate();

	void deleteInputPin();
	void deleteOutputPin();
	void deleteOutputPin()












};