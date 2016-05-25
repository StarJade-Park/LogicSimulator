#pragma once
#include "ComponentObject.h"
#include <vector>

#define NOT_GATE_INPUT_VALUE_SIZE 1
#define NOT_GATE_OUTPUT_VALUE_SIZE 1

class CNOTGateComponent :public CComponentObject {
#define NOT_GATE_INPUT_DEFAULT_VALUE false
#define NOT_GATE_OUTPUT_DEFAULT_VALUE false
private:
	std::vector < bool > inputValue;
	std::vector < bool > outputValue;
public:
	CNOTGateComponent();
	CNOTGateComponent(CNOTGateComponent& object);
	virtual ~CNOTGateComponent();

	//input value �� �����ϸ� output value �� ����Ǿ����� �˷��ش�
	bool setInputValue(int index, bool _value);
	bool getInputValue(int index);
	bool getOutputValue(int index);

	void updateOutputValue();
};