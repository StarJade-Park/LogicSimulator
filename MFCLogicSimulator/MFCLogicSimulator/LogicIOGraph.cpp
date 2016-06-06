#include "stdafx.h"
#include "LogicIOGraph.h"

//http://unikys.tistory.com/43
//http://www.tipssoft.com/bulletin/board.php?bo_table=update&wr_id=1069

LogicIOGraph::LogicIOGraph()
{
	m_xPos = 10;
	m_yPos = 15;
	m_xRatio = 10;

	m_nShiftPoint = 10;

	m_clockCount = 20;
	m_clockIn = 0;
}


LogicIOGraph::~LogicIOGraph()
{
}

void LogicIOGraph::drawPoint(CDC* pDC, CPoint point)
{
	CPaintDC dc(this);

	dc.FillSolidRect(m_clientRect, RGB(255, 255, 255));

	// �׷����� �׷��� �׷��� ������ ���������� ä���.
	dc.FillSolidRect(m_graphRect, RGB(0, 0, 0));

	// �׷��� ������ �簢�� �Ӽ��� �����Ѵ�.
	dc.Draw3dRect(m_graphRect, RGB(192, 192, 192), RGB(255, 255, 255));

	int i = 0;
	CRect r;
	CString str;
	// ��Ʈ�� �����Ѵ�.
	CFont *p_oldFont = dc.SelectObject(&m_font);

	// �׷����� �׸� �� ����� ��ν��� ���� �����Ѵ�.
	CBrush dataBrush(RGB(255, 255, 0)), *p_oldBrush = NULL;
	CPen scalePen(PS_SOLID, 1, RGB(0, 128, 255)), /* �׷��� ���� �׸� ��(��) */ *p_oldPen = NULL;
	CPen gridPen(PS_SOLID, 1, RGB(64, 64, 64)); /* �׷��� ���� �׸� ��(��) */
	CPen dataPen(PS_SOLID, 2, RGB(0, 255, 0));
	CPen pointPen(PS_SOLID, 1, RGB(255, 255, 0));

	// ���ڻ��� �����Ѵ�.
	dc.SetTextColor(RGB(0, 128, 255));
	// ������ ������ �����Ѵ�.
	dc.SetBkColor(RGB(232, 232, 208));

	m_clockIn = m_graphRect.Width() / (m_clockCount + 1);
	// x�� ���� �׸���.
	for (i = 0; i < m_clockCount; i++) {
		// ���ݰ� ��ġ���� �׸� x��ǥ�� �����Ѵ�.
		m_xPos = m_graphRect.left + m_clockIn*(i + 1);

		// ������ �׸� ���� �����Ѵ�.
		p_oldPen = dc.SelectObject(&scalePen);

		// x���� ������ �׸���.
		dc.MoveTo(int(m_xPos), m_graphRect.left + 1);
		dc.LineTo(int(m_xPos), m_graphRect.left + 5);

		// ���μ��� �׸� ���� �����Ѵ�.
		dc.SelectObject(&gridPen);
		// �׷��� ������ ��ġ�� ��Ÿ���� ���μ��� �׸���.
		dc.MoveTo(int(m_xPos), m_graphRect.right + 2);
		dc.LineTo(int(m_xPos), m_graphRect.left - 2);

		// ������ ������ ��ü�Ѵ�.
		dc.SelectObject(p_oldPen);
		// ������ ��ġ(Ƚ��)�� ���ڷ� ����Ѵ�.
		str.Format(_T("%d��"), i + 1);
		r.SetRect(int(m_xPos - 40), m_graphRect.left + 10, int(m_xPos + 40), m_graphRect.left + 30);
		dc.DrawText(str, r, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	}

	m_clockIn = m_graphRect.Height() / (m_clockCount + 1);
	// y�� ���� �׸���.
	for (i = 0; i <= 1 /* ����� 0, 1���� ������.*/; i++) {
		// ���ݰ� ��ġ���� �׸� y��ǥ�� �����Ѵ�.
		m_yPos = m_graphRect.bottom + m_clockIn*(i + 1);

		// ������ �׸� ���� �����Ѵ�.
		p_oldPen = dc.SelectObject(&scalePen);

		// y���� ������ �׸���.
		dc.MoveTo(int(m_yPos), m_graphRect.bottom + 1);
		dc.LineTo(int(m_yPos), m_graphRect.bottom + 5);

		// ���μ��� �׸� ���� �����Ѵ�.
		dc.SelectObject(&gridPen);
		// �׷��� ������ ��ġ�� ��Ÿ���� ���μ��� �׸���.
		dc.MoveTo(int(m_yPos), m_graphRect.top + 2);
		dc.LineTo(int(m_yPos), m_graphRect.bottom - 2);

		// ������ ������ ��ü�Ѵ�.
		dc.SelectObject(p_oldPen);
		// ������ ��ġ(Ƚ��)�� ���ڷ� ����Ѵ�.
		str.Format(_T("%d val"), i);
		r.SetRect(int(m_yPos - 40), m_graphRect.bottom + 10, int(m_yPos + 40), m_graphRect.bottom + 30);
		dc.DrawText(str, r, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	}

	// ������ �޾Ƽ� �׷��� �׸���.


	// ������ ��� �귯���� ��ü�Ѵ�.
	dc.SelectObject(p_oldPen);
	dc.SelectObject(p_oldBrush);

	// ������ ��Ʈ�� ��ü�Ѵ�.
	dc.SelectObject(p_oldFont);

	// ������ ��� �귯���� �����Ѵ�.
	scalePen.DeleteObject();
	gridPen.DeleteObject();
	dataPen.DeleteObject();
	dataBrush.DeleteObject();
	pointPen.DeleteObject();


}

void LogicIOGraph::ResetGraph()
{

}

void LogicIOGraph::setRangeXY(int _minY, int _maxY, int X_ratio)
{
	m_minY = _minY;
	m_maxY = _maxY;
	m_xRatio = X_ratio;
}

void LogicIOGraph::setGraphLabel(CString _XUnits, CString _YUnits)
{
	XUnits = _XUnits;
	YUnits = _YUnits;
}
