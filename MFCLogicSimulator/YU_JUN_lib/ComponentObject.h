#pragma once

class CComponentObject {
private:
public:
	CComponentObject();
	CComponentObject(CComponentObject& object);
	virtual ~CComponentObject();
	//�����Լ���
	virtual bool setInputValue(int index, bool _value) = 0;
	virtual bool getInputValue(int index) = 0;
	virtual bool getOutputValue(int index) = 0;
	virtual bool update() = 0;
};
