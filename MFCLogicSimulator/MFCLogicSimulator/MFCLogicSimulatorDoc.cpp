// �� MFC ���� �ҽ� �ڵ�� MFC Microsoft Office Fluent ����� �������̽�("Fluent UI")�� 
// ����ϴ� ����� ���� �ָ�, MFC C++ ���̺귯�� ����Ʈ��� ���Ե� 
// Microsoft Foundation Classes Reference �� ���� ���� ������ ���� 
// �߰������� �����Ǵ� �����Դϴ�.  
// Fluent UI�� ����, ��� �Ǵ� �����ϴ� �� ���� ��� ����� ������ �����˴ϴ�.  
// Fluent UI ���̼��� ���α׷��� ���� �ڼ��� ������ 
// http://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// MFCLogicSimulatorDoc.cpp : CMFCLogicSimulatorDoc Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "MFCLogicSimulator.h"
#endif

#include "MFCLogicSimulatorDoc.h"
#include "MainFrm.h"

#include <propkey.h>



#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMFCLogicSimulatorDoc

IMPLEMENT_DYNCREATE(CMFCLogicSimulatorDoc, CDocument)

BEGIN_MESSAGE_MAP(CMFCLogicSimulatorDoc, CDocument)
END_MESSAGE_MAP()


// CMFCLogicSimulatorDoc ����/�Ҹ�


//������ ����鼭 ���̺귯�� ������ �ִ´�
CMFCLogicSimulatorDoc::CMFCLogicSimulatorDoc()
{
	// TODO: ���⿡ ��ȸ�� ���� �ڵ带 �߰��մϴ�.
	component_data.resize(10);
	currentSelectedItem = -1;
}

int CMFCLogicSimulatorDoc::itemSelectedInDoc()
{	
	// mainframe���� fileview�� Ʈ�� ���� ��ȸ
	// http://www.dreamy.pe.kr/zbxe/CodeClip/18117

	CMainFrame* p_MainFrm = (CMainFrame*)AfxGetMainWnd();

	CFileView* p_FileViewInDoc = p_MainFrm->getCFileView();

	CViewTree* p_ToolboxInDoc = p_FileViewInDoc->getCFileViewTree();

	// Ʈ�� ��Ʈ�� ������ �ε���
	// goo.gl/mdFKLz
	int indexOfItem = 0;

	HTREEITEM hItem = p_ToolboxInDoc->GetSelectedItem();
	HTREEITEM hComp = p_ToolboxInDoc->GetChildItem(NULL);

	while (hComp)
	{
		if (hComp == hItem) break;
		hComp = p_ToolboxInDoc->GetNextItem(hComp, TVGN_NEXTVISIBLE);
		++indexOfItem;
	}


	return indexOfItem;
}

CMFCLogicSimulatorDoc::~CMFCLogicSimulatorDoc()
{
}

BOOL CMFCLogicSimulatorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ���⿡ ���ʱ�ȭ �ڵ带 �߰��մϴ�.
	// SDI ������ �� ������ �ٽ� ����մϴ�.

	return TRUE;
}




// CMFCLogicSimulatorDoc serialization

void CMFCLogicSimulatorDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	}
	else
	{
		// TODO: ���⿡ �ε� �ڵ带 �߰��մϴ�.


	}
}

#ifdef SHARED_HANDLERS

// ����� �׸��� �����մϴ�.
void CMFCLogicSimulatorDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// ������ �����͸� �׸����� �� �ڵ带 �����Ͻʽÿ�.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// �˻� ó���⸦ �����մϴ�.
void CMFCLogicSimulatorDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ������ �����Ϳ��� �˻� �������� �����մϴ�.
	// ������ �κ��� ";"�� ���еǾ�� �մϴ�.

	// ��: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CMFCLogicSimulatorDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMFCLogicSimulatorDoc ����

#ifdef _DEBUG
void CMFCLogicSimulatorDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMFCLogicSimulatorDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMFCLogicSimulatorDoc ���

/*
int indexOfItem = 0;
CFileView* p_FileViewInDoc;
p_FileViewInDoc = (CFileView*) &m_FileViewInDoc;
ASSERT_VALID(p_FileViewInDoc);


HTREEITEM hItem = p_FileViewInDoc->getItemSelected();
HTREEITEM hComp = p_FileViewInDoc->getChildItem(NULL);

while (hComp)
{
if (hComp == hItem) break;
hComp = p_FileViewInDoc->getNextItem(hComp, TVGN_NEXT);
++indexOfItem;
}

switch (indexOfItem)
{
case 1:
AfxMessageBox(_T("item num 1"));
case 2:
AfxMessageBox(_T("item num 2"));
case 3:
AfxMessageBox(_T("item num 3"));
case 4:
AfxMessageBox(_T("item num 4"));
case 5:
AfxMessageBox(_T("item num 5"));
case 6:
AfxMessageBox(_T("item num 6"));
default:
AfxMessageBox(_T("item select switch err"));
break;
}
*/