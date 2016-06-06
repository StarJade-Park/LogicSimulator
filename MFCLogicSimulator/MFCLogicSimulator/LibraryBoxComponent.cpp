#include "stdafx.h"
#include "LibraryBoxComponent.h"

CLibraryBox::CLibraryBox()
{
	//������Ʈ�� ��������
	componentVector.resize(VECTOR_INIT_SIZE, NULL);
	//������Ʈ Ÿ���� �����ϴ� ����
	componentTypeVector.resize(VECTOR_INIT_SIZE, COMPONENT_TYPE_NONE);
	//������Ʈ ���̵��� �����ϴ� 
	componentIDVector.resize(VECTOR_INIT_SIZE, false);

	amIInsideBox = false;
	//�����ϴ� ���� �׷���	
	inputGraph.resize(VECTOR_INIT_SIZE);
	outputGraph.resize(VECTOR_INIT_SIZE);
	//��ǰ�� ��ü ����
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
	for (int i = 0; i < componentIDVector.size(); i++) {
		if (componentIDVector[i] == true) {
			delete componentVector[i];
		}
	}
}

//���ο� ������Ʈ ���̵� ��������
COMPONENT_ID CLibraryBox::makeNewComponetID(COMPONENT_TYPE componentType)
{
	int ret = 0;
	for (int i = 1; i < componentIDVector.size(); i++) {
		if (componentIDVector[i] == false) {
			componentIDVector[i] = true;
			componentTypeVector[i] = componentType;
			ret = i;
			break;
		}
	}
	if (ret == 0) {
		ret = componentIDVector.size();
		componentIDVector.push_back(true);
		componentTypeVector.resize(componentIDVector.size());
		componentTypeVector[ret] = componentType;		
	}
	return ret;
}

//������Ʈ ���̵� ������
void CLibraryBox::deleteComponentID(COMPONENT_ID deleteId)
{
	componentTypeVector[deleteId] = COMPONENT_TYPE_NONE;
	componentIDVector[deleteId] = false;
}


bool CLibraryBox::loadLibraryBoxData(LIBRARY_BOX_DATA & libraryBoxData)
{	


	//�׷��� ������ �ε���
	inputGraph.resize(libraryBoxData.inputGraph.size());
	for (int i = 0; i < libraryBoxData.inputGraph.size(); i++) {
		inputGraph[i].resize(libraryBoxData.inputGraph[i].size());
		for (int j = 0; j < libraryBoxData.inputGraph[i].size(); j++) {
			inputGraph[i][j].componentID  = libraryBoxData.inputGraph[i][j].componentID;
			inputGraph[i][j].terminalNumber = libraryBoxData.inputGraph[i][j].terminalNumber;
			inputGraph[i][j].terminalType = libraryBoxData.inputGraph[i][j].terminalType;
		}
	}
	outputGraph.resize(libraryBoxData.outputGraph.size());
	for (int i = 0; i < libraryBoxData.outputGraph.size(); i++) {
		outputGraph[i].resize(libraryBoxData.outputGraph[i].size());
		for (int j = 0; j < libraryBoxData.outputGraph[i].size(); j++) {
			outputGraph[i][j].componentID = libraryBoxData.outputGraph[i][j].componentID;
			outputGraph[i][j].terminalNumber = libraryBoxData.outputGraph[i][j].terminalNumber;
			outputGraph[i][j].terminalType = libraryBoxData.outputGraph[i][j].terminalType;
		}
	}

	int curLibboxInfo = 0;
	//��ǰ���� ID�� ��ǰ�� Ÿ������ ���̺귯�� �ڽ��� �߰��Ѵ�.
	//���� ���� �ʴ� ID�� ������ ���Ƴ��´�
	COMPONENT_INFO loadInfo;
	componentIDVector.resize(libraryBoxData.componentIDVector.size());
	componentTypeVector.resize(libraryBoxData.componentIDVector.size());
	for (int i = 0; i < libraryBoxData.componentIDVector.size(); i++) {
		if (libraryBoxData.componentIDVector[i] == false) {
			componentIDVector[i] = true;
		}
		else {
			loadInfo.componentID = 0;
			loadInfo.componentType = libraryBoxData.componentTypeVector[i];
			//���̺귯�� �ڽ��ϰ�� ���� �߰���
			if (loadInfo.componentType == COMPONENT_TYPE_LIBRARY_BOX) {
				addComponent(loadInfo, libraryBoxData.internalLibraryBoxData[curLibboxInfo]);
				curLibboxInfo += 1;
				((CLibraryBox*)componentVector[i])->amIInsideBox = true;
			}
			else {
				addComponent(loadInfo);
			}
		}
	}
	//���Ƴ��� ID�� ������
	for (int i = 0; i < libraryBoxData.componentIDVector.size(); i++) {
		if (libraryBoxData.componentIDVector[i] == false) {
			componentIDVector[i] = false;
		}
	}

	isOscillation = false;
	isLibraryBoxOutputValueChanged = false;

	//���̺귯�� �ڽ��� ��ǲ�ɰ� �ƿ�ǲ �� clock���� �����ϴ� ���� ����Ʈ
	inputPinIDVector.resize(libraryBoxData.inputPinIDVector.size(),0);
	for (int i = 0; i < libraryBoxData.inputPinIDVector.size(); i++) {
		inputPinIDVector[i] = libraryBoxData.inputPinIDVector[i];
	}
	outputPinIDVector.resize(libraryBoxData.outputPinIDVector.size(), 0);
	for (int i = 0; i < libraryBoxData.outputPinIDVector.size(); i++) {
		outputPinIDVector[i] = libraryBoxData.outputPinIDVector[i];
	}
	inputClockVector.resize(libraryBoxData.inputClockVector.size(), 0);
	for (int i = 0; i < libraryBoxData.inputClockVector.size(); i++) {
		inputClockVector[i] = libraryBoxData.inputClockVector[i];
	}
	return true;
}

//���̺귯�� �ڽ��� ������
bool CLibraryBox::saveLibraryBoxData(LIBRARY_BOX_DATA& libraryBoxData)
{


	//���̺귯�� �ڽ��� ��ǲ�ɰ� �ƿ�ǲ ,clock���� ����
	libraryBoxData.inputPinIDVector.resize(inputPinIDVector.size());
	for (int i = 0; i < inputPinIDVector.size(); i++) {
		libraryBoxData.inputPinIDVector[i] = inputPinIDVector[i];
	}
	libraryBoxData.outputPinIDVector.resize(outputPinIDVector.size());
	for (int i = 0; i < outputPinIDVector.size(); i++) {
		libraryBoxData.outputPinIDVector[i] = outputPinIDVector[i];
	}
	libraryBoxData.inputClockVector.resize(inputClockVector.size());
	for (int i = 0; i < inputClockVector.size(); i++) {
		libraryBoxData.inputClockVector[i] = inputClockVector[i];
	}

	//��ǰ���� �׷����� ������
	libraryBoxData.inputGraph.resize(inputGraph.size());
	for (int i = 0; i < inputGraph.size(); i++) {
		libraryBoxData.inputGraph[i].resize(inputGraph[i].size());
		for (int j = 0; j < inputGraph[i].size(); j++) {
			libraryBoxData.inputGraph[i][j].componentID = inputGraph[i][j].componentID;
			libraryBoxData.inputGraph[i][j].terminalNumber = inputGraph[i][j].terminalNumber;
			libraryBoxData.inputGraph[i][j].terminalType = inputGraph[i][j].terminalType;
		}
	}
	libraryBoxData.outputGraph.resize(outputGraph.size());
	for (int i = 0; i < outputGraph.size(); i++) {
		libraryBoxData.outputGraph[i].resize(outputGraph[i].size());
		for (int j = 0; j < outputGraph[i].size(); j++) {
			libraryBoxData.outputGraph[i][j].componentID = outputGraph[i][j].componentID;
			libraryBoxData.outputGraph[i][j].terminalNumber = outputGraph[i][j].terminalNumber;
			libraryBoxData.outputGraph[i][j].terminalType = outputGraph[i][j].terminalType;
		}
	}

	//��ǰ���� ������ Ÿ���� ����
	libraryBoxData.componentTypeVector.resize(componentTypeVector.size());
	for (int i = 0; i < componentTypeVector.size(); i++) {
		libraryBoxData.componentTypeVector[i] = componentTypeVector[i];
	}

	//��ǰ���� ���̵� ����
	libraryBoxData.componentIDVector.resize(componentIDVector.size());
	for (int i = 0; i < componentIDVector.size(); i++) {
		libraryBoxData.componentIDVector[i] = componentIDVector[i];
	}

	//���� ���̺귯�� �ڽ� �� ������ ������
	for (int i = 0; i < componentIDVector.size(); i++) {
		if (componentIDVector[i] == true && componentTypeVector[i] == COMPONENT_TYPE_LIBRARY_BOX) {
			LIBRARY_BOX_DATA libData;
			//���� ���̺귯�� �ڽ� ������ libdata�� ������
			((CLibraryBox*)componentVector[i])->saveLibraryBoxData(libData);
			//������ ������ �� �������
			libraryBoxData.internalLibraryBoxData.push_back(libData);
		}
	}
	return true;
}

bool CLibraryBox::getComponentOutputValue(COMPONENT_ID ID, int index)
{
	return componentVector[ID]->getOutputValue(index);
}

bool CLibraryBox::checkOscillation()
{
	return isOscillation;
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
	case COMPONENT_TYPE_ONE_BIT_SWITCH:
		componentVector[newComponentID] = new COneBitSwitchComponent();
		break;
	case COMPONENT_TYPE_CLOCK:
		inputClockVector.push_back(newComponentID);
		componentVector[newComponentID] = new CClockComponent();
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
		break;

		//output component
	case COMPONENT_TYPE_OUTPUT_PIN:
		outputPinIDVector.push_back(newComponentID);
		componentVector[newComponentID] = new COutputPinComponent();
		break;
	case COMPONENT_TYPE_ONE_BIT_LAMP:
		componentVector[newComponentID] = new COneBitLampComponent();
		break;
	case COMPONENT_TYPE_7SEGMENT:
		componentVector[newComponentID] = new C7SegmentComponent();
		break;

		//�����ϴ� ������ ������ �ƴ� 
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

bool CLibraryBox::addComponent(COMPONENT_INFO & componentInfo, LIBRARY_BOX_DATA & libBoxdata)
{
	//���̺귯�� �ڽ� �� �ƴҰ��
	if (componentInfo.componentType != COMPONENT_TYPE_LIBRARY_BOX) {
		return false;
	}

	COMPONENT_TYPE newComponentType;
	COMPONENT_ID newComponentID;
	COMPONENT_CONENTION_INFO empty;

	//���̵� �Ҵ�����
	newComponentType = componentInfo.componentType;
	newComponentID = makeNewComponetID(newComponentType);
	componentInfo.componentID = newComponentID;

	//��ǰ���� �����Ұ����� �÷���
	if (componentVector.size() <= newComponentID) {
		componentVector.resize(componentVector.size() + 3);
	}

	//���̺귯�� ��ǰ�� �Ҵ��ϰ� ������ �ε���
	componentVector[newComponentID] = new CLibraryBox();
	((CLibraryBox*)componentVector[newComponentID])->loadLibraryBoxData(libBoxdata);


	if (inputGraph.size() <= newComponentID) {
		inputGraph.resize(inputGraph.size() + 3);
	}
	inputGraph[newComponentID].resize(componentVector[newComponentID]->numberOfInput(), empty);
	
	if (outputGraph.size() <= newComponentID) {
		outputGraph.resize(outputGraph.size() + 3);
	}
	outputGraph[newComponentID].resize(componentVector[newComponentID]->numberOfOutput(), empty);
	
	if (componentTypeVector.size() <= newComponentID) {
		componentTypeVector.resize(componentTypeVector.size() + 3);
	}
	componentTypeVector[newComponentID] = newComponentType;

	//��ǰ�� ������
	numberOfComponent += 1;

	//�ڱⰡ �ȿ� �ִ°��� �����ϱ�
	((CLibraryBox*)componentVector[newComponentID])->amIInsideBox = true;

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
		if (info->componentID <= 0) { continue; }
		outputGraph[info->componentID][info->terminalNumber].componentID = -1;
		outputGraph[info->componentID][info->terminalNumber].terminalNumber = -1;
		outputGraph[info->componentID][info->terminalNumber].terminalType = TERMINAL_TYPE_NONE;
	}
	//�����ǰ�� �ƿ�ǲ���ڿ� ����� ��Ǳ�� ������ ������
	for (int i = 0; i < outputGraph[_componentID].size(); i++) {
		info = &outputGraph[_componentID][i];
		if (info->componentID <= 0) { continue; }
		inputGraph[info->componentID][info->terminalNumber].componentID = -1;
		inputGraph[info->componentID][info->terminalNumber].terminalNumber = -1;
		inputGraph[info->componentID][info->terminalNumber].terminalType = TERMINAL_TYPE_NONE;
	}

	//�������� ��ǰ�� �׷����� �͹̳� ������ ������
	COMPONENT_CONENTION_INFO deleteinfo;
	inputGraph[_componentID].clear();
	outputGraph[_componentID].clear();

	//input pin �Ǵ� output pin ,clock �̸� ������ �ɺ��Ϳ��� �����Ѵ�
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
			if (outputPinIDVector[i] == _componentID) {
				outputPinIDVector.erase(outputPinIDVector.begin() + i);
				break;
			}
		}
	}
	if (componentTypeVector[_componentID] == COMPONENT_TYPE_CLOCK) {
		for (int i = 0; i < inputClockVector.size(); i++) {
			if (inputClockVector[i] == _componentID) {
				inputClockVector.erase(inputClockVector.begin() + i);
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


bool CLibraryBox::connnectComponent(COMPONENT_CONENTION_INFO& componentA, COMPONENT_CONENTION_INFO& componentB)
{
	
	//�ùٸ��� ���� ����
	if (isPossibleConnection(componentA, componentB) == false) {
		return false;
	 }

	COMPONENT_CONENTION_INFO A;
	COMPONENT_CONENTION_INFO B;
	if (componentA.terminalType == TERMINAL_TYPE_INPUT &&
		componentB.terminalType == TERMINAL_TYPE_OUTPUT) {
		A.componentID = componentB.componentID;
		A.terminalNumber = componentB.terminalNumber;
		A.terminalType = componentB.terminalType;
		B.componentID = componentA.componentID;
		B.terminalNumber = componentA.terminalNumber;
		B.terminalType = componentA.terminalType;;
	}
	else {
		B.componentID = componentB.componentID;
		B.terminalNumber = componentB.terminalNumber;
		B.terminalType = componentB.terminalType;
		A.componentID = componentA.componentID;
		A.terminalNumber = componentA.terminalNumber;
		A.terminalType = componentA.terminalType;;
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

bool CLibraryBox::disconnectComponent(COMPONENT_CONENTION_INFO& componentA, COMPONENT_CONENTION_INFO& componentB)
{
	COMPONENT_CONENTION_INFO A;
	COMPONENT_CONENTION_INFO B;

	////A->B �ΰ��°�
	//output -> input
	if (componentA.terminalType == TERMINAL_TYPE_INPUT &&
		componentB.terminalType == TERMINAL_TYPE_OUTPUT) {
		A.componentID = componentB.componentID;
		A.terminalNumber = componentB.terminalNumber;
		A.terminalType = componentB.terminalType;
		B.componentID = componentA.componentID;
		B.terminalNumber = componentA.terminalNumber;
		B.terminalType = componentA.terminalType;;
	}
	else {
		B.componentID = componentB.componentID;
		B.terminalNumber = componentB.terminalNumber;
		B.terminalType = componentB.terminalType;
		A.componentID = componentA.componentID;
		A.terminalNumber = componentA.terminalNumber;
		A.terminalType = componentA.terminalType;;
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

	////����Ʈ�� ����Ʈ�� �и��Ϸ� �ҋ� �Ǵ�
	////�ٰ� ���� �и��Ϸ� �Ҷ�
	//if ((componentTypeVector[A.componentID] != COMPONENT_TYPE_WIRE ||
	//	componentTypeVector[B.componentID] != COMPONENT_TYPE_WIRE) ||
	//	(componentTypeVector[A.componentID] == COMPONENT_TYPE_WIRE &&
	//		componentTypeVector[B.componentID] == COMPONENT_TYPE_WIRE)) {
	//	return false;
	//}

	//���� ���� �ʴ� ���ڿ� �и��Ϸ��Ҷ�
	if (A.terminalNumber >= outputGraph[A.componentID].size() ||
		B.terminalNumber >= inputGraph[B.componentID].size()) {
		return false;
	}

	//�̹� ������ ���ڿ� �� �и��Ϸ� �ҋ�
	if (outputGraph[A.componentID][A.terminalNumber].componentID == -1 ||
		inputGraph[B.componentID][B.terminalNumber].componentID == -1) {
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
	int nextID;
 	queue< pair< int, int > > Q;
	vector<int> checktime;
	checktime.resize(componentIDVector.size(), 0);
	vector<int> countCheck;
	countCheck.resize(componentIDVector.size(), 0);
	int time = 0;
	CComponentObject* curComponent;
	COMPONENT_CONENTION_INFO preConectionInfo;	

	//��ǰ���� ť���ٰ� �������	
	for (int i = 1; i < componentIDVector.size(); i++) {
		//�������� �ʴ� ��ǰ�϶� �Ѿ��
		if (componentIDVector[i] == false) { continue; }
		int curID = i;
	
		bool isCanPushToQueue = false;
		//���� ���� �Ѻ�ǰ��  output ���� �̾����� �ϳ��� ������ �Ѿ��
		for (int j = 0; j < componentVector[curID]->numberOfOutput(); j++) {
			if (outputGraph[curID][j].componentID != -1) {
				isCanPushToQueue = true;
				break;
			}
		}

		//ť���ٰ� �������
		if (isCanPushToQueue == true) { 
			Q.push(make_pair(time, curID));
			checktime[curID] = time;
			countCheck[curID] += 1;
			time += 1;	
		}

	}	

	int curtime, curID, preID, preTerminalNumber;
	while (!Q.empty()) {		
		curtime = Q.front().first;
		curID = Q.front().second;
		Q.pop();

		//�ֱ��� ������ �ƴҋ� �׳� �ѱ�
		if (checktime[curID] > curtime) { continue; }

		//������ �߻��Ͽ���.
		if (countCheck[curID] >= LOOP_LIMIT) {
			isOscillation = true;
			return true;
		}
		//�ð��� �帥��
		time += 1;
		if (amIInsideBox == false) {
			//printf("cur ID :%d cur type : %d time : %d \n", curID, componentTypeVector[curID], curtime);
		}

		//���� ��ǰ ��ü
		curComponent = componentVector[curID];

		//���� ��ǰ�� ���� ������
		bool val = false;
		bool isUpdated = false;
		//�����ص� �޶����� ������ �Ѿ
		for (int i = 0; i < curComponent->numberOfInput(); i++) {
			//���� ��ǰ���� ���� ���� ����
			preID = inputGraph[curID][i].componentID;

			//�����ǰ�� ���� ���ڿ� ����Ȱ� ������
			if (preID == -1) {
				val = false;
			}
			//����Ȱ��������� �ű⼭ ���� ������
			else {
				preTerminalNumber = inputGraph[curID][i].terminalNumber;
				val = componentVector[preID]->getOutputValue(preTerminalNumber);
			}			

			//���� ��ǰ���� ���� �ٲ���� �˻���
			if (curComponent->setInputValue(i, val)) {
				isUpdated = true;
			}
		}
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

				//���� ��ǰ�� ������
				if (nextID == -1) {
					continue;
				}

				if (amIInsideBox == false) {
					//printf("##cur ID :%d nextID : %d\n", curID, nextID);
				}
				Q.push(make_pair(time, nextID));
				checktime[nextID] = time;
				countCheck[nextID] += 1;
				time += 1;
			}
		}
	}

	return isLibraryBoxOutputValueChanged;
}

int CLibraryBox::numberOfInput()
{
	return (int)inputPinIDVector.size();
}

int CLibraryBox::numberOfOutput()
{
	return (int)outputPinIDVector.size();
}

bool CLibraryBox::setInputValue(int index, bool _value)
{
	bool val = componentVector[inputPinIDVector[index]]->setInputValue(0,_value);
	if (amIInsideBox == true) {
		update();
	}
	return val;
}

bool CLibraryBox::getInputValue(int index)
{
	return componentVector[inputPinIDVector[index]]->getInputValue(0);
}

bool CLibraryBox::getOutputValue(int index)
{
	return componentVector[outputPinIDVector[index]]->getOutputValue(0);
}

bool CLibraryBox::update()
{
	updateCircuit();
	return isOscillation;
}

void CLibraryBox::reset()
{
	for (int i = 0; i < componentIDVector.size(); i++) {
		if (componentIDVector[i] == false) { continue; }
		componentVector[i]->reset();
	}
	isOscillation = false;
}

bool CLibraryBox::setClockValue(int index, bool _value)
{
	componentVector[inputClockVector[index]]->setInputValue(0,_value);
	if (amIInsideBox == true) {
		update();
	}
	return false;
}

bool CLibraryBox::getClockValue(int index)
{
	return componentVector[inputClockVector[index]]->getOutputValue(0);
}

int CLibraryBox::numberOfClock()
{
	return (int)inputClockVector.size();
}

CComponentObject * CLibraryBox::getComponentObject(int index)
{
	return componentVector[index];
}

bool CLibraryBox::isPossibleConnection(COMPONENT_CONENTION_INFO & componentA, COMPONENT_CONENTION_INFO & componentB)
{
	COMPONENT_CONENTION_INFO A;
	COMPONENT_CONENTION_INFO B;

	copyCOMPONENT_CONENTION_INFO(componentA, A);
	copyCOMPONENT_CONENTION_INFO(componentB, B);

	////A->B �ΰ��°�
	//output -> input
	if (A.terminalType == TERMINAL_TYPE_INPUT &&
		B.terminalType == TERMINAL_TYPE_OUTPUT) {
		swapCOMPONENT_CONENTION_INFO(A, B);
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
	//if ((componentTypeVector[A.componentID] != COMPONENT_TYPE_WIRE &&
	//	componentTypeVector[B.componentID] != COMPONENT_TYPE_WIRE) ||
	//	(componentTypeVector[A.componentID] == COMPONENT_TYPE_WIRE &&
	//		componentTypeVector[B.componentID] == COMPONENT_TYPE_WIRE)) {
	//	return false;
	//}

	if ((componentTypeVector[A.componentID] != COMPONENT_TYPE_WIRE &&
		componentTypeVector[B.componentID] != COMPONENT_TYPE_WIRE) ) {
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

	return true;
}

void CLibraryBox::swapCOMPONENT_CONENTION_INFO(COMPONENT_CONENTION_INFO & A, COMPONENT_CONENTION_INFO & B)
{
	COMPONENT_CONENTION_INFO temp;
	copyCOMPONENT_CONENTION_INFO(A, temp);
	copyCOMPONENT_CONENTION_INFO(B, A);
	copyCOMPONENT_CONENTION_INFO(temp, B);
}

void CLibraryBox::copyCOMPONENT_CONENTION_INFO(COMPONENT_CONENTION_INFO & source, COMPONENT_CONENTION_INFO & destination)
{
	destination.componentID = source.componentID;
	destination.terminalType = source.terminalType;
	destination.terminalNumber = source.terminalNumber;
}

ADJ_LIST* CLibraryBox::getOutputGrahp()
{
	// TODO: ���⿡ ��ȯ ������ �����մϴ�.
	return &outputGraph;
}

ADJ_LIST * CLibraryBox::getInputGrahp()
{
	return &inputGraph;
}

void CLibraryBox::deleteObject()
{
	for (int i = 0; i < componentIDVector.size(); i++) {
		if (componentIDVector[i] == true) {
			deleteComponent(i);
		}
	}
}

void CLibraryBox::setOffOscillation()
{
	isOscillation = false;
}
