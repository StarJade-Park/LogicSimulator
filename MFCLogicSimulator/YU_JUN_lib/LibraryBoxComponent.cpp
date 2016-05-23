#include "LibraryBoxComponent.h"

CLibraryBox::CLibraryBox()
{
	componentVector.resize(VECTOR_INIT_SIZE);

	inputPinIDVector.resize(VECTOR_INIT_SIZE);
	outputPinIDVector.resize(VECTOR_INIT_SIZE);

	componentTypeVector.resize(VECTOR_INIT_SIZE, COMPONENT_TYPE_NONE);
	componentIDVector.resize(VECTOR_INIT_SIZE);
	connnectionGraph.resize(VECTOR_INIT_SIZE);
	connectedTerminalInfo.resize(VECTOR_INIT_SIZE);

}

CLibraryBox::CLibraryBox(CLibraryBox & object)
	:CComponentObject(object)
{

}

CLibraryBox::~CLibraryBox()
{
	//���� �Ҵ�Ǵ� �κ��� ��� ������
	for (int i = 0; i < componentVector.size(); i++) {
		if (componentTypeVector[i] == COMPONENT_TYPE_NONE) {
			delete componentVector[i];
		}
	}
}

//���ο� ������Ʈ ���̵� ��������
COMPONENT_ID CLibraryBox::makeNewComponetID(COMPONENT_TYPE componentType)
{
	for (int i = 1; i < componentTypeVector.size(); i++) {
		if (componentIDVector[i] == false) {
			componentIDVector[i] = false;
			componentTypeVector[i] = componentType;
			return i;
		}
	}
	componentIDVector.push_back(true);
	componentTypeVector.push_back(componentType);
	return componentTypeVector.size()-1;
}

//������Ʈ ���̵� ������
void CLibraryBox::deleteComponentID(COMPONENT_ID deleteId)
{
	componentTypeVector[deleteId] = COMPONENT_TYPE_NONE;
	componentIDVector[deleteId] = false;
}

void CLibraryBox::setSingleInputPinValue(bool _inputValue, int _inputPinNumber)
{
	COMPONENT_ID inputPinID;
	inputPinID = inputPinIDVector[_inputPinNumber];
	CComponentObject* componentObject = ((CComponentObject*)componentVector[inputPinID]);
	CInputPinComponent* inputPinObject = ((CInputPinComponent*)componentObject);
	inputPinObject->setValue(_inputValue);
}

bool CLibraryBox::getSingleInputPinValue(int _inputPinNumber)
{
	COMPONENT_ID inputPinID;
	inputPinID = inputPinIDVector[_inputPinNumber];
	CComponentObject* componentObject = ((CComponentObject*)componentVector[inputPinID]);
	CInputPinComponent* inputPinObject = ((CInputPinComponent*)componentObject);
	return inputPinObject->getValue();

}

bool CLibraryBox::getSingleOutputPinValue(int _outPutPinNumber)
{
	COMPONENT_ID outputPinID;
	outputPinID = inputPinIDVector[_outPutPinNumber];
	CComponentObject* componentObject = ((CComponentObject*)componentVector[outputPinID]);
	CInputPinComponent* outputPinObject = ((CInputPinComponent*)componentObject);
	return outputPinObject->getValue();
}

bool CLibraryBox::addComponent(COMPONENT_INFO & componentInfo)
{
	COMPONENT_TYPE newComponentType;
	COMPONENT_ID newComponentID;
	
	//���̵� �Ҵ�����
	newComponentType = componentInfo.componentType;
	newComponentID = makeNewComponetID(newComponentType);
	componentInfo.componentID = newComponentID;

	//��ǰ���� �����Ұ����� �׷����� �뷮�� �� �߰� �ؾ� �Ұ�� Ȯ����
	if (componentVector.size() <= newComponentID) {
		componentVector.resize(componentVector.size() + 10);
		connnectionGraph.resize(connnectionGraph.size() + 10);
	}

	switch (newComponentType)
	{
		// input component
	case COMPONENT_TYPE_INPUT_PIN:
		inputPinIDVector.push_back(newComponentID);
		componentVector[newComponentID] = new CInputPinComponent();


		break;
	case COMPONENT_TYPE_CLOCK:
		componentVector[newComponentID] = new CClockComponent();
		break;
	case COMPONENT_TYPE_ONE_BIT_SWITCH:
		componentVector[newComponentID] = new COneBitSwitchComponent();

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
	case COMPONENT_TYPE_NAND_GATE:
		componentVector[newComponentID] = new CNANDGateComponent();

		break;
	case COMPONENT_TYPE_NOR_GATE:
		componentVector[newComponentID] = new CNORGateComponent();

		break;
	case COMPONENT_TYPE_XOR_GATE:
		componentVector[newComponentID] = new CXORGateComponent();

		break;

		//wire component
	case COMPONENT_TYPE_WIRE:
		componentVector[newComponentID] = new CWireComponent();
		break;

		//output component
	case COMPONENT_TYPE_7SEGMENT:
		componentVector[newComponentID] = new C7SegmentComponent();

		break;
	case COMPONENT_TYPE_OUTPUT_PIN:
		componentVector[newComponentID] = new COutputPinComponent();

		break;
	case COMPONENT_TYPE_ONE_BIT_LAMP:
		componentVector[newComponentID] = new COneBitLampComponent();

		break;

		//�����Ҽ�����
	default:
		deleteComponentID(newComponentID);
		return false;
		break;
	}

	//���� ����
	return true;
}

bool CLibraryBox::deleteComponent(COMPONENT_ID _componentID)
{
	//�������� ���� ��ǰ�� �����Ϸ��� �ϸ� false ��ȯ
	if (componentTypeVector[_componentID] == COMPONENT_TYPE_NONE) {
		return false;
	}

	//����� ��ǰ�� ã�Ƽ� ����Ⱥ�ǰ���� ������� ��ǰ�� ������ ���� ����ϴ� ���ڸ� ������
	COMPONENT_ID nextID;
	COMPONENT_CONENTION_INFO* nextConnectionInfo;
	COMPONENT_CONENTION_INFO* deleteConnetionInfo;

	//����� ���� ��ǰ�� �׷����� �͹̳� ������ ������
	for (int i = 0; i < connnectionGraph[_componentID].size(); i++) {
		nextConnectionInfo = &connnectionGraph[_componentID][i];
		//if (componentID[nextConnectionInfo->componentID] == COMPONENT_TYPE_WIRE &&);
		nextID = nextConnectionInfo->componentID;

		//����� �ݴ����� ��ǰ���� �͹̳������� ������
		for (int j = 0; j < connectedTerminalInfo[nextID].size(); j++) {
			deleteConnetionInfo = &connectedTerminalInfo[nextID][j];
			if (deleteConnetionInfo->componentID == nextConnectionInfo->componentID) {
				connectedTerminalInfo[nextID].erase(connectedTerminalInfo[nextID].begin() + j);
				break;
			}
		}
		//����� �ݴ����� ��ǰ���� �׷��������� ����
		for (int j = 0; j < connnectionGraph[nextID].size(); j++) {
			deleteConnetionInfo = &connnectionGraph[nextID][j];
			if (deleteConnetionInfo->componentID == _componentID) {
				connnectionGraph[nextID].erase(connnectionGraph[nextID].begin() + j);
				break;
			}
		}
	}

	//�������� ��ǰ�� �׷����� �͹̳� ������ ������
	connnectionGraph[_componentID].clear();
	connectedTerminalInfo[_componentID].clear();

	//������Ʈ ���̵� ����
	deleteComponentID(_componentID);
	delete componentVector[_componentID];

	return true;
}

bool CLibraryBox::connectComponentAndWire(COMPONENT_CONENTION_INFO & ComponentInfo, COMPONENT_CONENTION_INFO & wireInfo)
{
	// �������� �ʴ� ��ǰ�̶� �����Ϸ��ҋ� ������ϰ���
	if (componentTypeVector[ComponentInfo.componentID] == COMPONENT_TYPE_NONE ||
		componentTypeVector[wireInfo.componentID] == COMPONENT_TYPE_NONE) {
		return false;
	}

	COMPONENT_CONENTION_INFO* connectionInfo;
	// �����Ϸ��� ��ǰ�� ���ڰ� �̹̻�������� �˻�
	for (int i = 0; i < connectedTerminalInfo[ComponentInfo.componentID].size(); i++) {
		connectionInfo = &connectedTerminalInfo[ComponentInfo.componentID][i];
		if (connectionInfo->componentID == ComponentInfo.componentID &&
			connectionInfo->terminalNumber == ComponentInfo.terminalNumber&&
			connectionInfo->terminalType == ComponentInfo.terminalType) {
			return false;
		}
	}
	// �����Ϸ��� ���� ���ڰ� �̹� ��������� �˻�
	for (int i = 0; i < connectedTerminalInfo[wireInfo.componentID].size(); i++) {
		connectionInfo = &connectedTerminalInfo[wireInfo.componentID][i];
		if (connectionInfo->componentID == wireInfo.componentID &&
			connectionInfo->terminalNumber == wireInfo.terminalNumber&&
			connectionInfo->terminalType == wireInfo.terminalType) {
			return false;
		}
	}

	//�瓇������ ������
	connnectionGraph[ComponentInfo.componentID].push_back(wireInfo);
	connectedTerminalInfo[ComponentInfo.componentID].push_back(ComponentInfo);
	connnectionGraph[wireInfo.componentID].push_back(ComponentInfo);
	connectedTerminalInfo[wireInfo.componentID].push_back(wireInfo);
	return true;
}

bool CLibraryBox::disconnectComponentAndWire(COMPONENT_CONENTION_INFO & ComponentInfo, COMPONENT_CONENTION_INFO & wireInfo)
{
	// �������� �ʴ� ��ǰ�̶� �и��Ϸ��ҋ� ������ϰ���
	if (componentTypeVector[ComponentInfo.componentID] == COMPONENT_TYPE_NONE ||
		componentTypeVector[wireInfo.componentID] == COMPONENT_TYPE_NONE) {
		return false;
	}

	COMPONENT_CONENTION_INFO* currrentComponent;
	//��ǰ���� ���̾�������� ����Ȱ��� ����
	for (int i = 0; i < connnectionGraph[ComponentInfo.componentID].size(); i++) {
		currrentComponent = &connnectionGraph[ComponentInfo.componentID][i];
		if (currrentComponent->componentID == wireInfo.componentID &&
			currrentComponent->terminalNumber == wireInfo.terminalNumber &&
			currrentComponent->terminalType == wireInfo.terminalType) {
			connnectionGraph[ComponentInfo.componentID].erase(connnectionGraph[ComponentInfo.componentID].begin() + i);
			break;
		}
	}

	COMPONENT_CONENTION_INFO* currrentWire;
	//���̾�� ��ǰ �������� ����Ȱ��� ����
	for (int i = 0; i < connnectionGraph[wireInfo.componentID].size(); i++) {
		currrentWire = &connnectionGraph[wireInfo.componentID][i];
		if (currrentWire->componentID == ComponentInfo.componentID &&
			currrentWire->terminalNumber == ComponentInfo.terminalNumber &&
			currrentWire->terminalType == ComponentInfo.terminalType) {
			connnectionGraph[wireInfo.componentID].erase(connnectionGraph[wireInfo.componentID].begin() + i);
			break;
		}
	}

	COMPONENT_CONENTION_INFO* connectionInfo;
	//����ߴ� ��ǰ�� ������ ����� ������
	for (int i = 0; i < connectedTerminalInfo[ComponentInfo.componentID].size(); i++) {
		connectionInfo = &connectedTerminalInfo[ComponentInfo.componentID][i];
		if (connectionInfo->componentID == ComponentInfo.componentID &&
			connectionInfo->terminalNumber == ComponentInfo.terminalNumber &&
			connectionInfo->terminalType == ComponentInfo.terminalType) {
			connectedTerminalInfo[ComponentInfo.componentID].erase(connectedTerminalInfo[ComponentInfo.componentID].begin() + i);
			break;
		}
	}

	//����ߴ� ���̾��� ���ڸ� ������
	for (int i = 0; i < connectedTerminalInfo[wireInfo.componentID].size(); i++) {
		connectionInfo = &connectedTerminalInfo[wireInfo.componentID][i];
		if (connectionInfo->componentID == wireInfo.componentID &&
			connectionInfo->terminalNumber == wireInfo.terminalNumber &&
			connectionInfo->terminalType == wireInfo.terminalType) {
			connectedTerminalInfo[wireInfo.componentID].erase(connectedTerminalInfo[wireInfo.componentID].begin() + i);
			break;
		}
	}

	return true;
}

bool CLibraryBox::connectWireAndWire(COMPONENT_CONENTION_INFO & wireA, COMPONENT_CONENTION_INFO & wireB)
{
	//���� �ϳ��� ���������ʴ� ��ǰ�ϋ�
	if (componentTypeVector[wireA.componentID] == COMPONENT_TYPE_NONE ||
		componentTypeVector[wireB.componentID] == COMPONENT_TYPE_NONE) {
		return false;
	}
	COMPONENT_CONENTION_INFO* wire;
	//�̹� �����߾����� Ȯ����
	for (int i = 0; i < connnectionGraph[wireA.componentID].size(); i++) {
		wire = &connnectionGraph[wireA.componentID][i];
		if (wire->componentID == wireB.componentID &&
			wire->terminalNumber == wireB.terminalNumber &&
			wire->terminalType == wireB.terminalType) {
			return false;
		}
	}
	for (int i = 0; i < connnectionGraph[wireB.componentID].size(); i++) {
		wire = &connnectionGraph[wireB.componentID][i];
		if (wire->componentID == wireA.componentID &&
			wire->terminalNumber == wireA.terminalNumber &&
			wire->terminalType == wireA.terminalType) {
			return false;
		}
	}

	//������
	connnectionGraph[wireA.componentID].push_back(wireB);
	connnectionGraph[wireB.componentID].push_back(wireA);
	connectedTerminalInfo[wireA.componentID].push_back(wireA);
	connectedTerminalInfo[wireB.componentID].push_back(wireB);

	return true;
}

bool CLibraryBox::disconnectWireAndWire(COMPONENT_CONENTION_INFO & wireA, COMPONENT_CONENTION_INFO & wireB)
{
	//�������� ���̾ �и��Ϸ����� �˻���
	if (componentTypeVector[wireA.componentID] == COMPONENT_TYPE_NONE ||
		componentTypeVector[wireB.componentID] == COMPONENT_TYPE_NONE) {
		return false;
	}

	//���� �׷������� ���� ���̾ �и���
	COMPONENT_CONENTION_INFO* currentWire;
	for (int i = 0; i < connnectionGraph[wireA.componentID].size(); i++) {
		currentWire = &connnectionGraph[wireA.componentID][i];
		if (currentWire->componentID == wireB.componentID &&
			currentWire->terminalNumber == wireB.terminalNumber &&
			currentWire->terminalType == wireB.terminalType) {
			connnectionGraph[wireA.componentID].erase(connnectionGraph[wireA.componentID].begin() + i);
break;
		}
	}
	for (int i = 0; i < connnectionGraph[wireB.componentID].size(); i++) {
		currentWire = &connnectionGraph[wireB.componentID][i];
		if (currentWire->componentID == wireA.componentID &&
			currentWire->terminalNumber == wireA.terminalNumber &&
			currentWire->terminalType == wireA.terminalType) {
			connnectionGraph[wireB.componentID].erase(connnectionGraph[wireB.componentID].begin() + i);
			break;
		}
	}

	COMPONENT_CONENTION_INFO* terminalInfo;
	//���� ����ϴ� ���ڸ� ������
	for (int i = 0; i < connnectionGraph[wireA.componentID].size(); i++) {
		terminalInfo = &connnectionGraph[wireA.componentID][i];
		if (terminalInfo->componentID == wireA.componentID &&
			terminalInfo->terminalNumber == wireA.terminalNumber &&
			terminalInfo->terminalType == wireA.terminalType) {
			connnectionGraph[wireA.componentID].erase(connnectionGraph[wireA.componentID].begin() + i);
			break;
		}
	}
	for (int i = 0; i < connnectionGraph[wireB.componentID].size(); i++) {
		terminalInfo = &connnectionGraph[wireB.componentID][i];
		if (terminalInfo->componentID == wireB.componentID &&
			terminalInfo->terminalNumber == wireB.terminalNumber &&
			terminalInfo->terminalType == wireB.terminalType) {
			connnectionGraph[wireB.componentID].erase(connnectionGraph[wireB.componentID].begin() + i);
			break;
		}
	}

	return true;
}



/*
�޸�
�׷��� ��ü�� �ʿ��� �޾ƿͼ� �����ֱ���
vector �� ������ ������ ã�Ƽ� ���� �������� �׳� �ٸ������� �ϱ�


*/
bool CLibraryBox::updateCircuit()
{

	//���̾���� �瓇���̴�
	//��ǰ�� ���̾�� �ܹ������ΰ�
	//���̾��� output Ÿ���̴��ڿ��� ��ǰ�� input Ÿ�� ���ڷ� �����ϸ� ������ ���̾�� ��ǰ���� 
	//��ǰ�� output Ÿ���� ���ڿ��� ���̾��� input Ÿ���� ���ڷ� �����ϸ� ������ ��ǰ���� ���̷� 

	//���� ���� ȸ�� �̸� ���߱׸��Ѵ�...

	//bfs ������� �Ѵ�
	std::queue<COMPONENT_ID> queue;
	std::vector< std::vector<bool> > componentValueVector;

	//���� �����س���
	//�ʿ��� ������ ��ŭ �Ҵ��س���
	componentValueVector.resize(componentTypeVector.size());


	for (int i = 0; i < componentTypeVector.size(); i++) {




	}

	//�������� ��ǲ���� component id �� ť���ٰ� �ִ´�
	for (int i = 0; i < inputPinIDVector.size(); i++) {
		queue.push(inputPinIDVector[i]);
	}


	//ť�� ���鼭 ��ǰ���� ���������� �����Ѵ�
	while (queue.empty()) {




	}
	//Ž���� �ҋ� �ƿ�ǲ �������� ���� �� ����
	//�Ǵ� ��ǲ���� ���µ� ������ �ƿ�ǲ�� �޶�����  �޶����� �ƿ�ǲ������
	//ť�� �߰��Ѵ�
	//���̾�� ��ǲ �ƿ�ǲ�� ����̾���

	//��ŧ���̼� ���ؼ� ��� �ؾ���?


	return false;
}

void CLibraryBox::printstatus()
{
	printf("\n");
	printf("################################\n");
	printf("simultor status \n");
	printf("################################\n");

	//���� ����ִ� ������Ʈ���� �� ���°��� ����Ѵ�;

	for (int i = 0; i < componentTypeVector.size(); i++) {
		//���°Ŵ� ������
		if (componentTypeVector[i] == COMPONENT_TYPE_NONE){
			continue;
		}
		printf("componentID : %d component type: %d\n", i, componentTypeVector[i]);
		printf("component information:\n");
		//���϶�
		COMPONENT_CONENTION_INFO* info;
		printf("using terminal infoation:\n");
		for (int j = 0; j<connectedTerminalInfo[i].size(); j++) {
			info = &connectedTerminalInfo[i][j];
			printf("terminal type : %d  terminal number : %d\n", 
				info->terminalType, info->terminalNumber);
		}
		printf("connnected info\n");
		for (int j = 0; j<connnectionGraph[i].size(); j++) {
			info = &connnectionGraph[i][j];
			printf("connnected to component ID : %d, terminal type : %d	terminal number : %d\n",
				info->componentID, info->terminalType, info->terminalNumber);
		}
		printf("\n");
	}




	printf("################################\n");
	printf("end\n");
	printf("################################\n");
	printf("\n\n");
}


