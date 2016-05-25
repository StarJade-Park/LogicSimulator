#include "LibraryBoxComponent.h"

CLibraryBox::CLibraryBox()
{
	//������Ʈ�� ��������
	componentVector.resize(VECTOR_INIT_SIZE);

	inputPinIDVector.resize(VECTOR_INIT_SIZE);
	outputPinIDVector.resize(VECTOR_INIT_SIZE);

	//������Ʈ Ÿ���� �����ϴ� ����
	componentTypeVector.resize(VECTOR_INIT_SIZE, COMPONENT_TYPE_NONE);
	//������Ʈ ���̵��� �����ϴ� 
	componentIDVector.resize(VECTOR_INIT_SIZE,false);

	//�����ϴ� ������ �׷���
	inputGraph.resize(VECTOR_INIT_SIZE);
	outputGraph.resize(VECTOR_INIT_SIZE);
}

CLibraryBox::CLibraryBox(CLibraryBox & object)
	:CComponentObject(object)
{

}

CLibraryBox::~CLibraryBox()
{
	//���� �Ҵ�Ǵ� �κ��� ��� ������
	for (int i = 0; i < componentVector.size(); i++) {
		if (componentIDVector[i] == true ) {
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
	CComponentObject* componentObject = ((CComponentObject*)componentVector[inputPinID]);
	CInputPinComponent* inputPinObject = ((CInputPinComponent*)componentObject);
}

bool CLibraryBox::getSingleOutputPinValue(int _outPutPinNumber)
{
	COMPONENT_ID outputPinID;
	outputPinID = inputPinIDVector[_outPutPinNumber];
	CComponentObject* componentObject = ((CComponentObject*)componentVector[outputPinID]);
	CInputPinComponent* outputPinObject = ((CInputPinComponent*)componentObject);
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
		inputGraph.resize(inputGraph.size() + 10);
		outputGraph.resize(outputGraph.size() + 10);
	}

	switch (newComponentType)
	{
		// input component
	case COMPONENT_TYPE_INPUT_PIN:
		inputPinIDVector.push_back(newComponentID);
		componentVector[newComponentID] = new CInputPinComponent();
		inputGraph[newComponentID].resize(0);
		outputGraph[newComponentID].resize(INPUT_PIN_OUTPUT_VALUE_SIZE+1);
		break;
	case COMPONENT_TYPE_CLOCK:
		componentVector[newComponentID] = new CClockComponent();
		inputGraph[newComponentID].resize(0);
		outputGraph[newComponentID].resize(CLOCK_COMPONENT_OUTPUT_VALUE_SIZE+1);
		break;
	case COMPONENT_TYPE_ONE_BIT_SWITCH:
		componentVector[newComponentID] = new COneBitSwitchComponent();		
		inputGraph[newComponentID].resize(0);
		outputGraph[newComponentID].resize(ONE_BIT_LAMP_INPUT_VALUE_SIZE);
		break;

		//logic gate component
	case COMPONENT_TYPE_AND_GATE:
		componentVector[newComponentID] = new CANDGateComponent();
		inputGraph[newComponentID].resize(AND_GATE_INPUT_VALUE_SIZE);
		outputGraph[newComponentID].resize(AND_GATE_OUTPUT_VALUE_SIZE);
		break;
	case COMPONENT_TYPE_OR_GATE:
		componentVector[newComponentID] = new CORGateComponent();
		inputGraph[newComponentID].resize(OR_GATE_INPUT_VALUE_SIZE);
		outputGraph[newComponentID].resize(OR_GATE_OUTPUT_VALUE_SIZE);
		break;
	case COMPONENT_TYPE_NOT_GATE:
		componentVector[newComponentID] = new CNOTGateComponent();
		inputGraph[newComponentID].resize(NOT_GATE_INPUT_VALUE_SIZE);
		outputGraph[newComponentID].resize(NOT_GATE_OUTPUT_VALUE_SIZE);
		break;
	case COMPONENT_TYPE_XOR_GATE:
		componentVector[newComponentID] = new CXORGateComponent();
		inputGraph[newComponentID].resize(XOR_GATE_INPUT_VALUE_SIZE);
		outputGraph[newComponentID].resize(XOR_GATE_OUTPUT_VALUE_SIZE);
		break;

		//wire component
	case COMPONENT_TYPE_WIRE:
		componentVector[newComponentID] = new CWireComponent();
		///����...
		inputGraph[newComponentID].resize(5);
		outputGraph[newComponentID].resize(5);
		break;

		//output component
	case COMPONENT_TYPE_7SEGMENT:
		componentVector[newComponentID] = new C7SegmentComponent();
		inputGraph[newComponentID].resize(SEVEN_SEGMENT_INPUT_VALUE_SIZE);
		outputGraph[newComponentID].resize(0);
		break;
	case COMPONENT_TYPE_OUTPUT_PIN:
		outputPinIDVector.push_back(newComponentID);
		componentVector[newComponentID] = new COutputPinComponent();
		inputGraph[newComponentID].resize(OUTPUT_PIN_INPUT_VALUE_SIZE);
		outputGraph[newComponentID].resize(0);
		break;
	case COMPONENT_TYPE_ONE_BIT_LAMP:
		componentVector[newComponentID] = new COneBitLampComponent();
		inputGraph[newComponentID].resize(ONE_BIT_LAMP_INPUT_VALUE_SIZE);
		outputGraph[newComponentID].resize(0);
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



	//���� ����
	return true;
}


//�籸�� 
bool CLibraryBox::deleteComponent(COMPONENT_ID _componentID)
{
	//�������� ���� ��ǰ�� �����Ϸ��� �ϸ� false ��ȯ
	if (componentTypeVector[_componentID] == COMPONENT_TYPE_NONE) {
		return false;
	}

	//����� ��ǰ�� ã�Ƽ� ����Ⱥ�ǰ���� ������� ��ǰ�� ������ ���� ����ϴ� ���ڸ� ������
	
	//����� ���� ��ǰ�� �׷����� �͹̳� ������ ������
	

	//�������� ��ǰ�� �׷����� �͹̳� ������ ������


	//������Ʈ ���̵� ����

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
/*���� ���� �޸�
�����ϴ¹�� bfs ������ �Ѵ�

//���� �˻���... ���� ó������:
���̾� �浹�� ���̾� ������ ó��.. wire ����
->���̾ ��ǲ���ڿ� ����� �ƿ�ǲ ��ǰ�� 2�� ���� �˻���
���� ��ǲ�� ť�� ������ �浹�Ǵ� ���̾�� üũ�ؼ�
������� �ʰ� ��
�浹�ϴ� ���̾���� ������ �����ϴ� ���͸� ��������
���̾� ��ü�� ���¿� �浹���¸� �߰��Ѵ�

�������� ��¹��:
������ ����?...
���鼭 ����Ŭ�� �˻��ع�����
.......
���� ��� Ʈ���� ���� ����Ŭ�� �߻��ϸ� ���� �ع���?
..
->dfs�� ������?
��θ� dequeue�� ���� �ϰ� ������
..

�������� ���ǵ� ���̾ �ϳ��� ����Ѵ�
���̾ �߱����ؾ��Ѵ�

�����ϴ� �Լ��ȿ��� ����
�ʱ�ȭ
1 �浹�Ǵ� ���̾ �˻��Ѵ�
2 �����˻縦 �Ѵ� �����ϸ� ���� �߻�
3 ���� �����ϴ� �Լ�������




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


