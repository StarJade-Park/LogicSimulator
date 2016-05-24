#pragma once
#include "ComponentObject.h"
#include <vector>

#define AND_GATE_OUTPUT_DEFUALT_VALUE false
#define AND_GATE_OUTPUT_VALUE_SIZE 1

#define AND_GATE_INPUT_DEFUALT_VALUE false
#define AND_GATE_INPUT_VALUE_SIZE 2

class CANDGateComponent :public CComponentObject{
private:
	std::vector<bool>outputValue;
	std::vector<bool>inputValue;

public:
	CANDGateComponent();
	CANDGateComponent(CANDGateComponent& object);
	virtual ~CANDGateComponent();

	//input�� �ٲ�� output ���� �ٲ������ �� ��ȯ����
	bool setInputValue(int index, bool _value);
	bool getInputValue(int index);
	bool getOutputValue(int index);
	void updateOutputValue();
};