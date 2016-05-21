#include "ORGateComponent.h"

CORGateComponent::CORGateComponent()
{
	setComponentName(std::string("OR Gate"));
	inputValue1 = false;
	inputValue2 = false;
	outputValue = false;
	setNumberOfInputTerminal(OR_GATE_INPUT_TERMINAL_NUMBER);
	setNumberOfOutputTerminal(OR_GATE_OUTPUT_TERMINAL_NUMBER);
}

CORGateComponent::CORGateComponent(CORGateComponent & object)
	:CComponentObject(object)
{
	setComponentName(std::string("OR Gate"));
	inputValue1 = false;
	inputValue2 = false;
	outputValue = false;
	setNumberOfInputTerminal(OR_GATE_INPUT_TERMINAL_NUMBER);
	setNumberOfOutputTerminal(OR_GATE_OUTPUT_TERMINAL_NUMBER);
}

CORGateComponent::~CORGateComponent()
{
}

void CORGateComponent::setInputValue1(bool _inputValue1)
{
	inputValue1 = _inputValue1;
}

bool CORGateComponent::getInputValue1()
{
	return inputValue1;
}

void CORGateComponent::setInputValue2(bool _inputValue2)
{
	inputValue2 = _inputValue2;
}

bool CORGateComponent::getInputValue2()
{
	return inputValue2;
}

bool CORGateComponent::getOutputValue()
{
	return outputValue;
}

void CORGateComponent::updateOutputValue()
{
	outputValue = (inputValue1 | inputValue2);
}