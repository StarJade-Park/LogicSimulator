#include "NOTGateComponent.h"

CNOTGateComponent::CNOTGateComponent()
{
	inputValue =  NOT_GATE_INPUT_DEFAULT_VALUE;
	outputValue = NOT_GATE_OUTPUT_DEFAULT_VALUE;
}

CNOTGateComponent::CNOTGateComponent(CNOTGateComponent & object)
	:CComponentObject(object)
{
	inputValue = NOT_GATE_INPUT_DEFAULT_VALUE;
	outputValue = NOT_GATE_OUTPUT_DEFAULT_VALUE;
}

CNOTGateComponent::~CNOTGateComponent()
{
}

//input value �� �����ϸ� output value �� ����Ǿ����� �˷��ش�
bool CNOTGateComponent::setInputValue(int index,bool _value)
{
	inputValue = _value;
	return update();
}

bool CNOTGateComponent::getInputValue(int index)
{
	return inputValue;
}

bool CNOTGateComponent::getOutputValue(int index)
{
	return outputValue;
}

bool CNOTGateComponent::update()
{
	bool oldvalue = outputValue;
	outputValue = !inputValue;
	if (oldvalue == outputValue) {
		return false;
	}
	return true;
}

int CNOTGateComponent::numberOfInput()
{
	return 1;
}

int CNOTGateComponent::numberOfOutput()
{
	return 1;
}

