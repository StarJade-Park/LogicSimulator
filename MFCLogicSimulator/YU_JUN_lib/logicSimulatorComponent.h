#pragma once

#include <string>

enum DIRECTION {DIRECTION_NORTH,DIRECTION_SOUTH,DIRECTION_EAST,DIRECTION_WEST};
class CLogicSimulatorComponent {

public:
	int x, y;
	std::string label;
	std::string componetName;
	bool inputValue1, inputValue2;
	bool outputValue;
	DIRECTION direction;


	CLogicSimulatorComponent();
	~CLogicSimulatorComponent();

	void setX(int newX);
	int getX();
	void setY(int newY);
	int getY();
	
	void setLabel(std::string newLabel);
	std::string getLabel();
	void setInputValue1(bool newInputValue1);
	bool getInputvalue1();
	void setInputValue2(bool newInputValue2);
	bool getInputValue2();
	void setOutputValue(bool newOutputValue);
	bool getOutputValue();
	void setDirection(DIRECTION newDirection);
	DIRECTION getDirection();
	virtual void updateOutputValue();

	


};