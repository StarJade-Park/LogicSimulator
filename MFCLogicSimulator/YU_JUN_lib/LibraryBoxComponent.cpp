#include "LibraryBoxComponent.h"

CLibraryBox::CLibraryBox()
{
	setComponentName(std::string("library box"));
	componentList.resize(10);
	inputPinIDList.resize(10);
	outputPinIDList.resize(10);
	componentIDList.resize(10, COMPONENT_TYPE_NONE);
	connnectionInfo.resize(10);

}

CLibraryBox::CLibraryBox(CLibraryBox & object)
	:CComponentObject(object)
{
	setComponentName(std::string("library box"));
	
}

CLibraryBox::~CLibraryBox()
{
}

COMPONENT_ID CLibraryBox::getNewComponetID(COMPONENT_TYPE componentType)
{
	int availableID = -1;
	for (int i = 1; i < componentIDList.size(); i++){
		if (componentIDList[i] == COMPONENT_TYPE_NONE) {
			componentIDList[i] = componentType;
			return i;
		}
	}
	availableID = componentIDList.size();
	componentIDList.push_back(componentType);
	return availableID;
}

void CLibraryBox::deleteComponentID(COMPONENT_ID deleteId)
{
	componentIDList[deleteId] = COMPONENT_TYPE_NONE;
}

void CLibraryBox::loadLibrarybox(std::vector<LIBRARY_BOX_DATA>& LibraryBoxData)
{
	for (int i = 0; i < LibraryBoxData.size(); i++) {
		LibraryBoxData[i];
	}
}

void CLibraryBox::setSingleInputPinValue(bool _inputValue, int _inputPinNumber)
{
	COMPONENT_ID inputPinID;
	inputPinID = inputPinIDList[_inputPinNumber];
	CComponentObject* componentObject = ((CComponentObject*)componentList[inputPinID]);
	CInputPinComponent* inputPinObject = ((CInputPinComponent*)componentObject);
	inputPinObject->setValue(_inputValue);
}

bool CLibraryBox::getSingleInputPinValue(int _inputPinNumber)
{
	COMPONENT_ID inputPinID;
	inputPinID = inputPinIDList[_inputPinNumber];
	CComponentObject* componentObject = ((CComponentObject*)componentList[inputPinID]);
	CInputPinComponent* inputPinObject = ((CInputPinComponent*)componentObject);
	return inputPinObject->getValue();
	
}

bool CLibraryBox::getSingleOutputPinValue(int _outPutPinNumber)
{
	COMPONENT_ID outputPinID;
	outputPinID = inputPinIDList[_outPutPinNumber];
	CComponentObject* componentObject = ((CComponentObject*)componentList[outputPinID]);
	CInputPinComponent* outputPinObject = ((CInputPinComponent*)componentObject);
	return outputPinObject->getValue();
}

bool CLibraryBox::addComponent(COMPONENT_INFO & componentInfo)
{
	COMPONENT_TYPE newComponentType ;
	int newX, newY;
	enum DIRECTION newDirection;
	COMPONENT_ID newComponentID;

	newComponentType = componentInfo.componentType;
	newX = componentInfo.x;
	newY = componentInfo.y; 
	newDirection = componentInfo.direction;
	newComponentID = getNewComponetID(newComponentType);

	// �� �߰� �ؾ� �Ұ�� Ȯ����
	if (componentList.size() <= newComponentID) {
		componentList.resize(componentList.size() + 10);
		connnectionInfo.resize(connnectionInfo.size() + 10);
	}

	switch (newComponentType)
	{
	// input component
	case COMPONENT_TYPE_INPUT_PIN:
		inputPinIDList.push_back(newComponentID);
		componentList[newComponentID] = new CInputPinComponent();
		((CComponentObject*)componentList[newComponentID])->setDirection(newDirection);
		((CComponentObject*)componentList[newComponentID])->setX(newX);
		((CComponentObject*)componentList[newComponentID])->setY(newY);

		break;			
	case COMPONENT_TYPE_CLOCK:
		componentList[newComponentID] = new CClockComponent();
		((CComponentObject*)componentList[newComponentID])->setDirection(newDirection);
		((CComponentObject*)componentList[newComponentID])->setX(newX);
		((CComponentObject*)componentList[newComponentID])->setY(newY);
		break;
	case COMPONENT_TYPE_ONE_BIT_SWITCH:
		componentList[newComponentID] = new COneBitSwitchComponent();
		((CComponentObject*)componentList[newComponentID])->setDirection(newDirection);
		((CComponentObject*)componentList[newComponentID])->setX(newX);
		((CComponentObject*)componentList[newComponentID])->setY(newY);
		break;

	//logic gate component
	case COMPONENT_TYPE_AND_GATE:
		componentList[newComponentID] = new CANDGateComponent();		
		((CComponentObject*)componentList[newComponentID])->setDirection(newDirection);
		((CComponentObject*)componentList[newComponentID])->setX(newX);
		((CComponentObject*)componentList[newComponentID])->setY(newY);
		break;
	case COMPONENT_TYPE_OR_GATE:
		componentList[newComponentID] = new CORGateComponent();
		((CComponentObject*)componentList[newComponentID])->setDirection(newDirection);
		((CComponentObject*)componentList[newComponentID])->setX(newX);
		((CComponentObject*)componentList[newComponentID])->setY(newY);
		break;
	case COMPONENT_TYPE_NOT_GATE:
		componentList[newComponentID] = new CNOTGateComponent();
		((CComponentObject*)componentList[newComponentID])->setDirection(newDirection);
		((CComponentObject*)componentList[newComponentID])->setX(newX);
		((CComponentObject*)componentList[newComponentID])->setY(newY);
		break;
	case COMPONENT_TYPE_NAND_GATE:
		componentList[newComponentID] = new CNANDGateComponent();
		((CComponentObject*)componentList[newComponentID])->setDirection(newDirection);
		((CComponentObject*)componentList[newComponentID])->setX(newX);
		((CComponentObject*)componentList[newComponentID])->setY(newY);
		break;
	case COMPONENT_TYPE_NOR_GATE:
		componentList[newComponentID] = new CNORGateComponent();
		((CComponentObject*)componentList[newComponentID])->setDirection(newDirection);
		((CComponentObject*)componentList[newComponentID])->setX(newX);
		((CComponentObject*)componentList[newComponentID])->setY(newY);
		break;
	case COMPONENT_TYPE_XOR_GATE:
		componentList[newComponentID] = new CXORGateComponent();
		((CComponentObject*)componentList[newComponentID])->setDirection(newDirection);
		((CComponentObject*)componentList[newComponentID])->setX(newX);
		((CComponentObject*)componentList[newComponentID])->setY(newY);
		break;

	//wire component
	case COMPONENT_TYPE_WIRE:
		componentList[newComponentID] = new CWireComponent();
		break;

	//output component
	case COMPONENT_TYPE_7SEGMENT:
		componentList[newComponentID] = new C7SegmentComponent();
		((CComponentObject*)componentList[newComponentID])->setDirection(newDirection);
		((CComponentObject*)componentList[newComponentID])->setX(newX);
		((CComponentObject*)componentList[newComponentID])->setY(newY);
		break;
	case COMPONENT_TYPE_OUTPUT_PIN:
		componentList[newComponentID] = new COutputPinComponent();
		((CComponentObject*)componentList[newComponentID])->setDirection(newDirection);
		((CComponentObject*)componentList[newComponentID])->setX(newX);
		((CComponentObject*)componentList[newComponentID])->setY(newY);
		break; 
	case COMPONENT_TYPE_ONE_BIT_LAMP:
		componentList[newComponentID] = new COneBitLampComponent();
		((CComponentObject*)componentList[newComponentID])->setDirection(newDirection);
		((CComponentObject*)componentList[newComponentID])->setX(newX);
		((CComponentObject*)componentList[newComponentID])->setY(newY);
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

bool CLibraryBox::deleteComponent(COMPONENT_ID componentID)
{

	
	
	//����� ���̾ ������ ����

	//componentList���� ����

	//������Ʈ ���̵� ����
	deleteComponentID(componentID);

	
	return false;
}

bool CLibraryBox::connectComponentAndWire(COMPONENT_CONENTION_INFO & ComponentInfo, COMPONENT_CONENTION_INFO & wireInfo)
{
	// �������� �ʴ� ��ǰ�̶� �����Ϸ��ҋ� ������ϰ���
	if (componentIDList[ComponentInfo.componentID] == COMPONENT_TYPE_NONE ||
		componentIDList[wireInfo.componentID] == COMPONENT_TYPE_NONE) {
		return false;
	}

	//�瓇������ ������
	connnectionInfo[ComponentInfo.componentID].push_back(ComponentInfo);
	connnectionInfo[wireInfo.componentID].push_back(wireInfo);
	return true;
}

bool CLibraryBox::disconnectComponentAndWire(COMPONENT_CONENTION_INFO & ComponentInfo, COMPONENT_CONENTION_INFO & wireInfo)
{
	// �������� �ʴ� ��ǰ�̶� �и��Ϸ��ҋ� ������ϰ���
	if (componentIDList[ComponentInfo.componentID] == COMPONENT_TYPE_NONE ||
		componentIDList[wireInfo.componentID] == COMPONENT_TYPE_NONE) {
		return false;
	}

	COMPONENT_CONENTION_INFO* currrentComponent;
	for (int i = 0; i < connnectionInfo[ComponentInfo.componentID].size(); i++) {
		currrentComponent = &connnectionInfo[ComponentInfo.componentID][i];
		if (currrentComponent->componentID == ComponentInfo.componentID &&
			currrentComponent->terminalNumber == ComponentInfo.terminalNumber &&
			currrentComponent->terminalType == ComponentInfo.terminalType) {
			connnectionInfo[ComponentInfo.componentID];
		}
	}
	return false;
}


