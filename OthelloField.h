#pragma once
#include "OthelloTestDlg.h"

// OthelloField
class OthelloTestDlg;

class OthelloField : public CWnd
{
	DECLARE_DYNAMIC(OthelloField)

public:
	OthelloField();
	virtual ~OthelloField();

protected:
	DECLARE_MESSAGE_MAP()
private:
	bool RegisterClass();
public:
	afx_msg void OnPaint();
public:
	// Установка размера игрового поля
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
private:
	void GetFieldPosition(CPoint point, int& xpos, int& ypos);

public:
	afx_msg void OnDestroy();
	
private:
	CRect GetRectFromField(int x, int y);
public:
	void DrawX(CPaintDC& dc, CRect rect);
private:
	void DrawO(CPaintDC& dc, CRect rect);
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
private:
	int nSelectedX;
	int nSelectedY;
	OthelloTestDlg* gameParent;
	bool bGameInProgress = false;
	void HighlightSelection(CPaintDC& dc);
public:
	afx_msg void OnMouseLeave();
	void SetGameParent(OthelloTestDlg* p);
	void  SetGameInProgress(bool InProgress);
	bool CheckEndCondition();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};


