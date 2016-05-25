#include "LibraryBoxComponent.h"

CLibraryBox::CLibraryBox()
{
	//������Ʈ�� ��������
	componentVector.resize(VECTOR_INIT_SIZE,NULL);

	inputPinIDVector.resize(VECTOR_INIT_SIZE);
	outputPinIDVector.resize(VECTOR_INIT_SIZE);

	//������Ʈ Ÿ���� �����ϴ� ����
	componentTypeVector.resize(VECTOR_INIT_SIZE, COMPONENT_TYPE_NONE);
	//������Ʈ ���̵��� �����ϴ� 
	componentIDVector.resize(VECTOR_INIT_SIZE,false);

	//�����ϴ� ���� �׷���	
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
		inputGraph[newComponentID].resize(INPUT_PIN_INPUT_SIZE, empty);
		outputGraph[newComponentID].resize(INPUT_PIN_OUTPUT_SIZE, empty);
		break;

		//logic gate component
	case COMPONENT_TYPE_AND_GATE:
		componentVector[newComponentID] = new CANDGateComponent();
		inputGraph[newComponentID].resize(ANDGATE_INPUT_SIZE, empty);
		outputGraph[newComponentID].resize(ANDGATE_OUTPUT_SIZE, empty);
		break;
	case COMPONENT_TYPE_OR_GATE:
		componentVector[newComponentID] = new CORGateComponent();
		inputGraph[newComponentID].resize(ORGATE_INPUT_SIZE, empty);
		outputGraph[newComponentID].resize(ORGATE_OUTPUT_SIZE, empty);
		break;
	case COMPONENT_TYPE_NOT_GATE:
		componentVector[newComponentID] = new CNOTGateComponent();
		inputGraph[newComponentID].resize(NOTGATE_INPUT_SIZE, empty);
		outputGraph[newComponentID].resize(NOTGATE_OUTPUT_SIZE, empty);
		break;
	case COMPONENT_TYPE_XOR_GATE:
		componentVector[newComponentID] = new CXORGateComponent();
		inputGraph[newComponentID].resize(XORGATE_INPUT_SIZE, empty);
		outputGraph[newComponentID].resize(XORGATE_OUTPUT_SIZE, empty);
		break;

		//wire component
	case COMPONENT_TYPE_WIRE:
		componentVector[newComponentID] = new CWireComponent();
		///����...
		inputGraph[newComponentID].resize(1, empty);
		outputGraph[newComponentID].resize(10, empty);
		break;

		//output component

	case COMPONENT_TYPE_OUTPUT_PIN:
		outputPinIDVector.push_back(newComponentID);
		componentVector[newComponentID] = new COutputPinComponent();
		inputGraph[newComponentID].resize(OUTPUT_PIN_INPUT_SIZE, empty);
		outputGraph[newComponentID].resize(OUTPUT_PIN_OUTPUT_SIZE, empty);
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

	//������Ʈ ���̵� ����
	deleteComponentID(_componentID);
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
	if ((componentTypeVector[A.componentID] != COMPONENT_TYPE_WIRE ||
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
	if (outputGraph[A.componentID][A.terminalNumber].componentID == -1 ||
		outputGraph[B.componentID][B.terminalNumber].componentID == -1) {
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




ishavecycle = false

def dfs(curV,inputvalue,terminalNumber):
global ishavecycle
//����� ���� �����Ѵ�
component[curV].setvalue(inputvalue,terminalNumber)

//���� ��尡 ���̴�
if component[curV] = WIRE:
int val = component[curV].getvalue()
for next in outG[curV]:
dfs(nextV,val,nextTerminal)
if isHaveCycle == True:
return

//���� ��尡 ��ǰ�϶�
else:
outputValue = component[curV].getvalue()
//���¸� �˻��Ѵ�
if ouputValue in map[curV]:
//����Ŭ�� ã�Ƴ�
ishavecycle = True
retern
for next in outG[curV]:
val = component[curV].getval(currnetTerminal)
dfs(nextV,val,currnetTerminal)
if ishaveCycle == True:
return


return




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


