
// MFCLogicSimulator.h : MFCLogicSimulator ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CMFCLogicSimulatorApp:
// �� Ŭ������ ������ ���ؼ��� MFCLogicSimulator.cpp�� �����Ͻʽÿ�.
//

class CMFCLogicSimulatorApp : public CWinApp
{
public:
	CMFCLogicSimulatorApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	UINT  m_nAppLook;
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMFCLogicSimulatorApp theApp;
