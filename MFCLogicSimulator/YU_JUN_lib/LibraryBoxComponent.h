#pragma once
//���� Ŭ���� �߰�
#include "ComponentObject.h"
//�� ����Ʈ ��� ����߰�
#include "ANDGateComponet.h"
#include "ORGateComponent.h"
#include "NANDGateComponent.h"
#include "NORGateComponent.h"
#include "NOTGateComponent.h"
#include "XORGateComponent.h"
//���̾� ��� �߰�
#include "WireComponet.h"
#include <vector>


class CLibraryBox : CComponentObject {

private:
	vector<CComponentObject> componentList;
	vetor<CComponentObject>input
public:
	CLibraryBox();
	CLibraryBox(CLibraryBox& object);
	~CLibraryBox();
	








};