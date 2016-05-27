#include "LibraryBoxComponent.h"

CLibraryBox::CLibraryBox()
{
	//������Ʈ�� ��������
	componentVector.resize(VECTOR_INIT_SIZE, NULL);



	//������Ʈ Ÿ���� �����ϴ� ����
	componentTypeVector.resize(VECTOR_INIT_SIZE, COMPONENT_TYPE_NONE);
	//������Ʈ ���̵��� �����ϴ� 
	componentIDVector.resize(VECTOR_INIT_SIZE, false);

	//�����ϴ� ���� �׷���	
	inputGraph.resize(VECTOR_INIT_SIZE);
	outputGraph.resize(VECTOR_INIT_SIZE);
	numberOfComponent = 0;
	isOscillation = false;
	isLibraryBoxOutputValueChanged = false;

}

CLibraryBox::CLibraryBox(CLibraryBox & object)
	:CComponentObject(object)
{

}

CLibraryBox::~CLibraryBox()
{
	//���� �Ҵ�Ǵ� �κ��� ��� ������
	for (int i = 0; i < componentVector.size(); i++) {
		if (componentIDVector[i] == true) {
			delete componentVector[i];
		}
	}
}

//���ο� ������Ʈ ���̵� ��������
COMPONENT_ID CLibraryBox::makeNewComponetID(COMPONENT_TYPE componentType)
{
	for (int i = 1; i < componentTypeVector.size(); i++) {
		if (componentIDVector[i] == false) {
			componentIDVector[i] = true;
			componentTypeVector[i] = componentType;
			return i;
		}
	}
	componentIDVector.push_back(true);
	componentTypeVector.push_back(componentType);
	return (int)(componentTypeVector.size() - 1);
}

//������Ʈ ���̵� ������
void CLibraryBox::deleteComponentID(COMPONENT_ID deleteId)
{
	componentTypeVector[deleteId] = COMPONENT_TYPE_NONE;
	componentIDVector[deleteId] = false;
}


//���̺귯�� �ڽ��� input output pin������ getter setter
void CLibraryBox::setSingleInputPinValue(bool _inputValue, int _inputPinNumber)
{
	COMPONENT_ID inputPinID;
	inputPinID = inputPinIDVector[_inputPinNumber];
	CComponentObject* componentObject = ((CComponentObject*)componentVector[inputPinID]);
	CInputPinComponent* inputPinObject = ((CInputPinComponent*)componentObject);
}

bool CLibraryBox::getSingleInputPinValue(int _inputPinNumber)
{
	COMPONENT_ID inputPinID;
	inputPinID = inputPinIDVector[_inputPinNumber];
	return componentVector[inputPinID]->getInputValue(0);
	return false;
}

bool CLibraryBox::getSingleOutputPinValue(int _outPutPinNumber)
{
	COMPONENT_ID outputPinID;
	outputPinID = outputPinIDVector[_outPutPinNumber];
 	return componentVector[outputPinID]->getOutputValue(0);
}



// ��ǰ �߰�
bool CLibraryBox::addComponent(COMPONENT_INFO & componentInfo)
{
	COMPONENT_TYPE newComponentType;
	COMPONENT_ID newComponentID;

	COMPONENT_CONENTION_INFO empty;

	//���̵� �Ҵ�����
	newComponentType = componentInfo.componentType;
	newComponentID = makeNewComponetID(newComponentType);
	componentInfo.componentID = newComponentID;

	//��ǰ���� �����Ұ����� �׷����� �뷮�� �� �߰� �ؾ� �Ұ�� Ȯ����
	if (componentVector.size() <= newComponentID) {
		componentVector.resize(componentVector.size() + 3);
	}
	if (inputGraph.size() <= newComponentID) {
		inputGraph.resize(inputGraph.size() + 3);
	}
	if (outputGraph.size() <= newComponentID) {
		outputGraph.resize(outputGraph.size() + 3);
	}
	if (componentTypeVector.size() <= newComponentID) {
		componentTypeVector.resize(componentTypeVector.size() + 3);
	}

	switch (newComponentType)
	{
		// input component
	case COMPONENT_TYPE_INPUT_PIN:
		inputPinIDVector.push_back(newComponentID);
		componentVector[newComponentID] = new CInputPinComponent();
		break;

		//logic gate component
	case COMPONENT_TYPE_AND_GATE:
		componentVector[newComponentID] = new CANDGateComponent();
		break;

	case COMPONENT_TYPE_OR_GATE:
		componentVector[newComponentID] = new CORGateComponent();
		break;
	case COMPONENT_TYPE_NOT_GATE:
		componentVector[newComponentID] = new CNOTGateComponent();
		break;
	case COMPONENT_TYPE_XOR_GATE:
		componentVector[newComponentID] = new CXORGateComponent();
		break;

		//wire component
	case COMPONENT_TYPE_WIRE:
		componentVector[newComponentID] = new CWireComponent();
		///����...
		break;

		//output component

	case COMPONENT_TYPE_OUTPUT_PIN:
		outputPinIDVector.push_back(newComponentID);
		componentVector[newComponentID] = new COutputPinComponent();
		break;

		//���̺귯�� �ڽ� ���߿���
	case COMPONENT_TYPE_LIBRARY_BOX:
		break;
		//�����Ҽ�����
	default:
		deleteComponentID(newComponentID);
		return false;
		break;
	}

	inputGraph[newComponentID].resize(componentVector[newComponentID]->numberOfInput(), empty);
	outputGraph[newComponentID].resize(componentVector[newComponentID]->numberOfOutput(), empty);
	componentTypeVector[newComponentID] = newComponentType;
	numberOfComponent += 1;

	//���� ����
	return true;
}

//��ǰ �����϶�
bool CLibraryBox::deleteComponent(COMPONENT_ID _componentID)
{
	//�������� ���� ��ǰ�� �����Ϸ��� �ϸ� false ��ȯ
	if (componentTypeVector[_componentID] == COMPONENT_TYPE_NONE) {
		return false;
	}

	COMPONENT_CONENTION_INFO* info;
	//����� ��ǰ�� ã�Ƽ� ����Ⱥ�ǰ���� ������� ��ǰ�� ������ ���� ����ϴ� ���ڸ� ������
	//���� ��ǰ�� ��ǲ ���ڿ� ����� ��ǰ�� ������ ������
	for (int i = 0; i < inputGraph[_componentID].size(); i++) {
		info = &inputGraph[_componentID][i];
		outputGraph[info->componentID][info->terminalNumber].componentID = -1;
		outputGraph[info->componentID][info->terminalNumber].terminalNumber = -1;
		outputGraph[info->componentID][info->terminalNumber].terminalType = TERMINAL_TYPE_NONE;
	}
	//�����ǰ�� �ƿ�ǲ���ڿ� ����� ��Ǳ�� ������ ������
	for (int i = 0; i < outputGraph[_componentID].size(); i++) {
		info = &outputGraph[_componentID][i];
		inputGraph[info->componentID][info->terminalNumber].componentID = -1;
		inputGraph[info->componentID][info->terminalNumber].terminalNumber = -1;
		inputGraph[info->componentID][info->terminalNumber].terminalType = TERMINAL_TYPE_NONE;
	}

	//�������� ��ǰ�� �׷����� �͹̳� ������ ������
	COMPONENT_CONENTION_INFO deleteinfo;
	inputGraph[_componentID].resize(inputGraph[_componentID].size(), deleteinfo);
	outputGraph[_componentID].resize(outputGraph[_componentID].size(), deleteinfo);

	//input pin �Ǵ� output pin �̸� ������ �ɺ��Ϳ��� �����Ѵ�
	if (componentTypeVector[_componentID] == COMPONENT_TYPE_INPUT_PIN) {
		for (int i = 0; i < inputPinIDVector.size(); i++) {
			if (inputPinIDVector[i] == _componentID) {
				inputPinIDVector.erase(inputPinIDVector.begin() + i);
				break;
			}
		}
	}
	if (componentTypeVector[_componentID] == COMPONENT_TYPE_OUTPUT_PIN) {
		for (int i = 0; i < outputPinIDVector.size(); i++) {
			if (inputPinIDVector[i] == _componentID) {
				outputPinIDVector.erase(outputPinIDVector.begin() + i);
				break;
			}
		}
	}

	componentTypeVector[_componentID] = COMPONENT_TYPE_NONE;
	//������Ʈ ���̵� ����
	deleteComponentID(_componentID);
	delete componentVector[_componentID];
	numberOfComponent -= 1;
	return true;
}

bool CLibraryBox::connnectComponent(COMPONENT_CONENTION_INFO* componentA, COMPONENT_CONENTION_INFO* componentB)
{
	COMPONENT_CONENTION_INFO A;
	COMPONENT_CONENTION_INFO B;

	////A->B �ΰ��°�
	//output -> input
	if (componentA->terminalType == TERMINAL_TYPE_INPUT &&
		componentB->terminalType == TERMINAL_TYPE_OUTPUT) {
		A.componentID = componentB->componentID;
		A.terminalNumber = componentB->terminalNumber;
		A.terminalType = componentB->terminalType;
		B.componentID = componentA->componentID;
		B.terminalNumber = componentA->terminalNumber;
		B.terminalType = componentA->terminalType;;
	}
	else {
		B.componentID = componentB->componentID;
		B.terminalNumber = componentB->terminalNumber;
		B.terminalType = componentB->terminalType;
		A.componentID = componentA->componentID;
		A.terminalNumber = componentA->terminalNumber;
		A.terminalType = componentA->terminalType;;
	}

	//���� ������ ���ڸ� �����Ϸ���
	if (A.terminalType == B.terminalType) {
		return false;
	}

	//�������� �ʴ� ��ǰ�� �����Ϸ� �ҋ�
	if (A.componentID >= componentIDVector.size() ||
		componentIDVector[A.componentID] == false ||
		B.componentID >= componentIDVector.size() ||
		componentIDVector[B.componentID] == false) {
		return false;
	}

	//����Ʈ�� ����Ʈ�� �����Ϸ� �ҋ� �Ǵ�
	//�ٰ� ���� �����Ϸ� �Ҷ�
	if ((componentTypeVector[A.componentID] != COMPONENT_TYPE_WIRE &&
		componentTypeVector[B.componentID] != COMPONENT_TYPE_WIRE) ||
		(componentTypeVector[A.componentID] == COMPONENT_TYPE_WIRE &&
			componentTypeVector[B.componentID] == COMPONENT_TYPE_WIRE)) {
		return false;
	}

	//���� ���� �ʴ� ���ڿ� �����Ϸ��Ҷ�
	if (A.terminalNumber >= outputGraph[A.componentID].size() ||
		B.terminalNumber >= inputGraph[B.componentID].size()) {
		return false;
	}

	//�̹� ������ ���ڿ� �� �����Ϸ� �ҋ�
	if (outputGraph[A.componentID][A.terminalNumber].componentID != -1 ||
		inputGraph[B.componentID][B.terminalNumber].componentID != -1) {
		return false;
	}


	////A->B �ΰ��°�
	//output -> input
	//���� �׷��� ������ �������
	inputGraph[B.componentID][B.terminalNumber].componentID = A.componentID;
	inputGraph[B.componentID][B.terminalNumber].terminalNumber = A.terminalNumber;
	inputGraph[B.componentID][B.terminalNumber].terminalType = A.terminalType;

	outputGraph[A.componentID][A.terminalNumber].componentID = B.componentID;
	outputGraph[A.componentID][A.terminalNumber].terminalNumber = B.terminalNumber;
	outputGraph[A.componentID][A.terminalNumber].terminalType = B.terminalType;


	return true;
}

bool CLibraryBox::disconnectComponent(COMPONENT_CONENTION_INFO * componentA, COMPONENT_CONENTION_INFO * componentB)
{
	COMPONENT_CONENTION_INFO A;
	COMPONENT_CONENTION_INFO B;

	////A->B �ΰ��°�
	//output -> input
	if (componentA->terminalType == TERMINAL_TYPE_INPUT &&
		componentB->terminalType == TERMINAL_TYPE_OUTPUT) {
		A.componentID = componentB->componentID;
		A.terminalNumber = componentB->terminalNumber;
		A.terminalType = componentB->terminalType;
		B.componentID = componentA->componentID;
		B.terminalNumber = componentA->terminalNumber;
		B.terminalType = componentA->terminalType;;
	}
	else {
		B.componentID = componentB->componentID;
		B.terminalNumber = componentB->terminalNumber;
		B.terminalType = componentB->terminalType;
		A.componentID = componentA->componentID;
		A.terminalNumber = componentA->terminalNumber;
		A.terminalType = componentA->terminalType;;
	}

	//���� ������ ���ڸ� �и��Ϸ���
	if (A.terminalType == B.terminalType) {
		return false;
	}

	//�������� �ʴ� ��ǰ�� �и��Ϸ� �ҋ�
	if (A.componentID >= componentIDVector.size() ||
		componentIDVector[A.componentID] == false ||
		B.componentID >= componentIDVector.size() ||
		componentIDVector[B.componentID] == false) {
		return false;
	}

	//����Ʈ�� ����Ʈ�� �и��Ϸ� �ҋ� �Ǵ�
	//�ٰ� ���� �и��Ϸ� �Ҷ�
	if ((componentTypeVector[A.componentID] != COMPONENT_TYPE_WIRE ||
		componentTypeVector[B.componentID] != COMPONENT_TYPE_WIRE) ||
		(componentTypeVector[A.componentID] == COMPONENT_TYPE_WIRE &&
			componentTypeVector[B.componentID] == COMPONENT_TYPE_WIRE)) {
		return false;
	}

	//���� ���� �ʴ� ���ڿ� �и��Ϸ��Ҷ�
	if (A.terminalNumber >= outputGraph[A.componentID].size() ||
		B.terminalNumber >= inputGraph[B.componentID].size()) {
		return false;
	}

	//�̹� ������ ���ڿ� �� �и��Ϸ� �ҋ�
	if (outputGraph[A.componentID][A.terminalNumber].componentID == -1 ||
		outputGraph[B.componentID][B.terminalNumber].componentID == -1) {
		return false;
	}
	//A      -> B
	//output -> input
	inputGraph[B.componentID][B.terminalNumber].componentID = -1;
	inputGraph[B.componentID][B.terminalNumber].terminalNumber = -1;
	inputGraph[B.componentID][B.terminalNumber].terminalType = TERMINAL_TYPE_NONE;

	outputGraph[A.componentID][A.terminalNumber].componentID = -1;
	outputGraph[A.componentID][A.terminalNumber].terminalNumber = -1;
	outputGraph[A.componentID][A.terminalNumber].terminalType = TERMINAL_TYPE_NONE;
	return true;
}




bool CLibraryBox::updateCircuit()
{
	if (isOscillation == true) {
		return false;
	}

 	queue< pair< int, int > > Q;

	vector<int> checktime;
	vector<int> countCheck;
	checktime.resize(componentIDVector.size(), 0);
	countCheck.resize(componentIDVector.size(), 0);
	int time = 0;
	int countLimit = 1000;
	CComponentObject* curComponent;
	CComponentObject* preComponent;
	COMPONENT_CONENTION_INFO preConectionInfo;

	//�������� �� ��ǰ�� ť���ٰ� �������
	int nextID;
	for (int i = 0; i < inputPinIDVector.size(); i++) {
		nextID = outputGraph[inputPinIDVector[i]][0].componentID;
		if (nextID == -1) {
			continue;
		}
		Q.push(make_pair(time, nextID));
		
		
		checktime[inputPinIDVector[i]] = time;
		countCheck[inputPinIDVector[i]] += 1;

		time += 1;
	}

	int curtime, curID, preID, preTerminalNumber;
	while (!Q.empty()) {
		
		curtime = Q.front().first;
		curID = Q.front().second;
		Q.pop();
		//�ֱ��� ������ �ƴҋ� �׳� �ѱ�
		if (checktime[curID] > curtime) { continue; }

		//������ �߻��Ͽ���.
		if (countCheck[curID] >= countLimit) {
			isOscillation = true;
			return true;

		}
		//�ð��� �帥��
		time += 1;
		

		//���� ��ǰ�� ���� ������
		curComponent = componentVector[curID];
		bool val = false;
		bool isUpdated = false;
		//�����ص� �޶����� ������ �Ѿ
		for (int i = 0; i < curComponent->numberOfInput(); i++) {
			//���� ��ǰ���� ���� ���� ����
			preID = inputGraph[curID][i].componentID;
			preTerminalNumber = inputGraph[curID][i].terminalNumber;
			val = componentVector[preID]->getOutputValue(preTerminalNumber);

			//���� ��ǰ���� ���� �ٲ���� �˻���
			if (curComponent->setInputValue(i, val)) {
				isUpdated = true;
			}
		}



		//�ٸ����� ������ �ٸ� ��ǰ���� ������
		//output ���� �ٲ�� ������� ������ ��ǰ�� ť�� �������
		
		if (isUpdated == true) {
			// �ƿ�ǲ ���� ���� �޶��� 
			if (componentTypeVector[curID] == COMPONENT_TYPE_OUTPUT_PIN) {
				isLibraryBoxOutputValueChanged = true;
				continue;
			}
			//���� ��ǰ���� �Ѿ
			for (int i = 0; i < curComponent->numberOfOutput(); i++) {
				nextID = outputGraph[curID][i].componentID;				
				if (nextID == -1) {
					continue;
				}
				
				Q.push(make_pair(time, nextID));
				checktime[inputPinIDVector[i]] = time;
				countCheck[inputPinIDVector[i]] += 1;

				time += 1;
			}
		}
	}

	return isLibraryBoxOutputValueChanged;
}

int CLibraryBox::numberOfInput()
{
	return inputPinIDVector.size();
}

int CLibraryBox::numberOfOutput()
{
	return (int)outputPinIDVector.size();
}

bool CLibraryBox::setInputValue(int index, bool _value)
{
	componentVector[inputPinIDVector[index]]->setInputValue(0,_value);
	return false;
}

bool CLibraryBox::getInputValue(int index)
{
	return false;
}

bool CLibraryBox::getOutputValue(int index)
{
	return false;
}

bool CLibraryBox::update()
{
	return false;
}

//
//void CLibraryBox::printstatus()
//{
//	printf("\n");
//	printf("################################\n");
//	printf("simultor status \n");
//	printf("################################\n");
//
//	//���� ����ִ� ������Ʈ���� �� ���°��� ����Ѵ�;
//
//	for (int i = 0; i < componentTypeVector.size(); i++) {
//		//���°Ŵ� ������
//		if (componentTypeVector[i] == COMPONENT_TYPE_NONE){
//			continue;
//		}
//		printf("componentID : %d component type: %d\n", i, componentTypeVector[i]);
//		printf("component information:\n");
//		//���϶�
//		COMPONENT_CONENTION_INFO* info;
//		printf("using terminal infoation:\n");
//		for (int j = 0; j<connectedTerminalInfo[i].size(); j++) {
//			info = &connectedTerminalInfo[i][j];
//			printf("terminal type : %d  terminal number : %d\n", 
//				info->terminalType, info->terminalNumber);
//		}
//		printf("connnected info\n");
//		for (int j = 0; j<connnectionGraph[i].size(); j++) {
//			info = &connnectionGraph[i][j];
//			printf("connnected to component ID : %d, terminal type : %d	terminal number : %d\n",
//				info->componentID, info->terminalType, info->terminalNumber);
//		}
//		printf("\n");
//	}
//
//
//
//
//	printf("################################\n");
//	printf("end\n");
//	printf("################################\n");
//	printf("\n\n");
//}


