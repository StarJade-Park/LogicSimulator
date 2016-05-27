#include "ANDGateComponet.h"

CANDGateComponent::CANDGateComponent()
{
	outputValue =  AND_GATE_OUTPUT_DEFUALT_VALUE;
	inputValue[0] = AND_GATE_INPUT_DEFUALT_VALUE;
	inputValue[1] = AND_GATE_INPUT_DEFUALT_VALUE;
}

CANDGateComponent::CANDGateComponent(CANDGateComponent & object)
	:CComponentObject(object)
{
	outputValue = AND_GATE_OUTPUT_DEFUALT_VALUE;
	inputValue[0] = AND_GATE_INPUT_DEFUALT_VALUE;
	inputValue[1] = AND_GATE_INPUT_DEFUALT_VALUE;
}

CANDGateComponent::~CANDGateComponent()
{
}

//input�� �ٲ�� output ���� �ٲ������ �� ��ȯ����
bool CANDGateComponent::setInputValue(int index, bool _value)
{
	inputValue[index] = _value;
	return update();
}

bool CANDGateComponent::getInputValue(int index)
{
	return inputValue[index];
}

bool CANDGateComponent::getOutputValue(int index)
{
	return	outputValue;
}

bool CANDGateComponent::update()
{
	bool oldValue = outputValue;
	outputValue = (inputValue[0] & inputValue[1]);
	if (oldValue == outputValue) {
		return false;
	}
	return true;
}

int CANDGateComponent::numberOfInput()
{
	return 2;
}

int CANDGateComponent::numberOfOutput()
{
	return 1;
}

