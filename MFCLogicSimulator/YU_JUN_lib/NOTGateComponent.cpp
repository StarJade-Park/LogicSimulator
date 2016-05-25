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
bool CNOTGateComponent::setInputValue(bool _value)
{
	bool oldOutputValue;
	oldOutputValue = outputValue;
	inputValue = _value;
	updateOutputValue();
	if (oldOutputValue == outputValue) {
		return false;
	}
	return true;
}

bool CNOTGateComponent::getInputValue()
{
	return inputValue;
}

bool CNOTGateComponent::getOutputValue()
{
	return outputValue;
}

void CNOTGateComponent::updateOutputValue()
{
	outputValue = !inputValue;
}
