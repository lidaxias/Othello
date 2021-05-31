// CTicTacToeField.cpp: файл реализации
//

#include "pch.h"
#include "OthelloTest.h"
#include "OthelloField.h"
#include "OthelloTestDlg.h"

#define TICTACTOEFIELD_CLASSNAME L"OthelloField"
#define FIELDNUMBERSSPACE 20
#define TIMER_ID 101

// CTicTacToeField

IMPLEMENT_DYNAMIC(OthelloField, CWnd)

OthelloField::OthelloField()
{

	gameParent = nullptr;
	this->RegisterClass();
	nSelectedX = -1;
	nSelectedY = -1;
}

OthelloField::~OthelloField()
{
}


BEGIN_MESSAGE_MAP(OthelloField, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_DESTROY()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSELEAVE()
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// Обработчики сообщений OthelloField

bool OthelloField::RegisterClass()
{
	WNDCLASS wndcls;
	HINSTANCE hInst = AfxGetInstanceHandle();
	
	if (!(::GetClassInfo(hInst, TICTACTOEFIELD_CLASSNAME, &wndcls)))
	{
		wndcls.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
		wndcls.lpfnWndProc = ::DefWindowProc;
		wndcls.cbClsExtra = wndcls.cbWndExtra = 0;
		wndcls.hInstance = hInst;
		wndcls.hIcon = NULL;
		wndcls.hCursor = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
		wndcls.hbrBackground = (HBRUSH)(COLOR_3DFACE + 1);
		wndcls.lpszMenuName = NULL;
		wndcls.lpszClassName = TICTACTOEFIELD_CLASSNAME;

		if (!AfxRegisterClass(&wndcls))
		{
			AfxThrowResourceException();
			return FALSE;
		}

	}
	return TRUE;
}


void OthelloField::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: добавьте свой код обработчика сообщений
					   // Не вызывать CWnd::OnPaint() для сообщений рисования

	if ((this->gameParent == nullptr) || (this->gameParent->GetBoard() == nullptr))
		return;

	CRect rect;
	GetClientRect(&rect);

	int fieldSize = this->gameParent->GetBoard()->GetBoardSize();

	CPen ourPen;
	HGDIOBJ oldPen;
	ourPen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));

	oldPen= dc.SelectObject(ourPen);

	int hPartSize = (rect.right- FIELDNUMBERSSPACE) / fieldSize;
	int vPartSize = (rect.bottom - FIELDNUMBERSSPACE) / fieldSize;
	

	this->HighlightSelection(dc);

	for (int i = 0; i < fieldSize ; i++)
	{	// вертикальные линиии
		dc.MoveTo(FIELDNUMBERSSPACE + i * hPartSize, FIELDNUMBERSSPACE);
		dc.LineTo(FIELDNUMBERSSPACE + i * hPartSize, fieldSize * vPartSize + FIELDNUMBERSSPACE);
		// горизонтальные линиии
		dc.MoveTo(FIELDNUMBERSSPACE, i * vPartSize + FIELDNUMBERSSPACE);
		dc.LineTo(FIELDNUMBERSSPACE + fieldSize*hPartSize, i * vPartSize + FIELDNUMBERSSPACE);
	}
	// последняя вертикальная линия
	dc.MoveTo(FIELDNUMBERSSPACE + fieldSize * hPartSize, FIELDNUMBERSSPACE);
	dc.LineTo(FIELDNUMBERSSPACE + fieldSize * hPartSize, fieldSize * vPartSize + FIELDNUMBERSSPACE);
	// последняя горизонтальная линия - с коррекцией "хвостиков" на пересечении
	dc.MoveTo(FIELDNUMBERSSPACE, fieldSize * vPartSize + FIELDNUMBERSSPACE-1);
	dc.LineTo(FIELDNUMBERSSPACE + fieldSize * hPartSize, fieldSize * vPartSize + FIELDNUMBERSSPACE-1);

	dc.SetTextColor(RGB(255, 0, 0));
	dc.SetBkMode(TRANSPARENT);
	dc.SetTextAlign(TA_TOP | TA_LEFT);

	for (int i = 0; i < fieldSize; i++)
	{
		// обозначения ячеек на доске  1..  A..
		CString str;
		str.Format(L"%d", i+1);
		dc.TextOutW(3, FIELDNUMBERSSPACE/2 + vPartSize/2 +  i * vPartSize, str);
		str.Format(L"%c", 0x41+i);
		dc.TextOutW(FIELDNUMBERSSPACE / 2 + hPartSize / 2 + i * hPartSize, 1, str);
	}
	// перерисовка фишек
		for(int x=0; x< fieldSize; x++)
			for (int y = 0; y < fieldSize; y++)
			{
				if (this->gameParent->GetBoard()->GetCell(x,y) == CellType_X)
					this->DrawX(dc, this->GetRectFromField(x, y));
				if (this->gameParent->GetBoard()->GetCell(x, y) == CellType_O)
					this->DrawO(dc, this->GetRectFromField(x, y));
			}

	dc.SelectObject(oldPen);
	ourPen.DeleteObject();
}

void OthelloField::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	CString str;
	if ((bGameInProgress) && (this->gameParent->GetCurrentPlayer()->IsHuman()))
	{
		if ((this->gameParent == nullptr) || (this->gameParent->GetBoard() == nullptr))
			return;

		int x, o, y;
		this->GetFieldPosition(point, x, y);
		if (this->gameParent->GetCurrentPlayer()->MakeMove(x,y) == true)
		{
			// подсчёт фишек игроков
			this->gameParent->GetBoard()->GetChipCnt(x, o);
			str.Format(L"Чёрных: %i", x);
			this->gameParent->strPlayer1Cnt = str;
			str.Format(L"Белых:  %i", o);
			this->gameParent->strPlayer2Cnt = str;
			this->gameParent->UpdateData(FALSE);

			if (this->CheckEndCondition())
			{
				this->SetGameInProgress(false);
				this->gameParent->Invalidate();
			}
			else
			{
				CellType ct=this->gameParent->GetCurrentPlayer()->GetCellType();
				if (ct == CellType_O)ct = CellType_X; else ct = CellType_O;
				if (this->gameParent->GetBoard()->CheckMoveEn(ct))
					this->gameParent->TogglePlayer();
				else
				{
					str.Format(L"Игрок: %s. Дополнительный ход!", this->gameParent->GetCurrentPlayer() ->GetName());
					AfxMessageBox(str);
				}
				
				
			}
		}

		this->Invalidate();
	}
	CWnd::OnLButtonDown(nFlags, point);
}

// проверка завершения игры
bool OthelloField::CheckEndCondition()
{
	if (this->gameParent->GetBoard()->CheckEndCondition())
	{
		int x, o;
		this->gameParent->GetBoard()->GetChipCnt(x,o);
		CString str;
		if (x > o)
			str.Format(L"Игрок %s победил!", this->gameParent->GetPlayer1()->GetName());
		else if (o > x)
			str.Format(L"Игрок %s победил!", this->gameParent->GetPlayer2()->GetName());
		else  str="Ничья!";
		AfxMessageBox(str);
		// очистка статического текста
		this->gameParent->strPlayerTurn = L"";
		this->gameParent->strPlayer1Cnt = L"";
		this->gameParent->strPlayer2Cnt = L"";
		this->gameParent->UpdateData(FALSE);

		return true;
	}
	return false;
}

// определение ячейки на котрую указвает мышь
void OthelloField::GetFieldPosition(CPoint point, int& xpos, int& ypos)
{
	// TODO: Добавьте сюда код реализации.
	if ((this->gameParent == nullptr) || (this->gameParent->GetBoard() == nullptr))
		return;

	int fieldSize = this->gameParent->GetBoard()->GetBoardSize();
	CRect rect;
	GetClientRect(&rect);
	int hPartSize = (rect.right - FIELDNUMBERSSPACE) / fieldSize;
	int vPartSize = (rect.bottom - FIELDNUMBERSSPACE) / fieldSize;
	for (int i = 0; i < fieldSize; i++)
	{
		if ((point.x > FIELDNUMBERSSPACE + i * hPartSize) && (point.x < FIELDNUMBERSSPACE + (i + 1) * hPartSize))
			xpos = i;
		if((point.y > FIELDNUMBERSSPACE + i * vPartSize) && (point.y < FIELDNUMBERSSPACE + (i + 1) * vPartSize))
			ypos = i;
	}
}
// закрытие окна
void OthelloField::OnDestroy()
{
	CWnd::OnDestroy();
	// TODO: добавьте свой код обработчика сообщений
}

CRect OthelloField::GetRectFromField(int x, int y)
{
	// TODO: Добавьте сюда код реализации.
	if ((this->gameParent == nullptr) || (this->gameParent->GetBoard() == nullptr))
		return CRect(0,0,0,0);

	int fieldSize = this->gameParent->GetBoard()->GetBoardSize();
	CRect rect;
	CRect rectWnd;
	GetClientRect(&rectWnd);
	int hPartSize = (rectWnd.right - FIELDNUMBERSSPACE) / fieldSize;
	int vPartSize = (rectWnd.bottom - FIELDNUMBERSSPACE) / fieldSize;

	rect.left = FIELDNUMBERSSPACE + x * hPartSize + 1;
	rect.top = FIELDNUMBERSSPACE + y * vPartSize + 1;
	rect.right = FIELDNUMBERSSPACE + ((x + 1) * hPartSize) - 1;
	rect.bottom = FIELDNUMBERSSPACE + ((y + 1) * vPartSize) - 1;

	return rect;
}


void OthelloField::DrawX(CPaintDC& dc, CRect rect)
{
	// TODO: Добавьте сюда код реализации.
	// TODO: Добавьте сюда код реализации.
	CPen pen;
	CBrush brush;
	pen.CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
	brush.CreateSolidBrush(RGB(0, 0, 0));
	HGDIOBJ oldpen = dc.SelectObject(pen);
	HGDIOBJ oldbrush = dc.SelectObject(brush);
	dc.Ellipse(rect.left + 4, rect.top + 4, rect.right - 4, rect.bottom - 4);

	dc.SelectObject(oldpen);
	dc.SelectObject(oldbrush);
	pen.DeleteObject();
}


void OthelloField::DrawO(CPaintDC& dc, CRect rect)
{
	// TODO: Добавьте сюда код реализации.
	CPen pen;
	CBrush brush;
	pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	brush.CreateSolidBrush(RGB(255,255,255));
	HGDIOBJ oldpen = dc.SelectObject(pen);
	HGDIOBJ oldbrush = dc.SelectObject(brush);
	dc.Ellipse(rect.left + 4, rect.top + 4, rect.right - 4, rect.bottom - 4);

	dc.SelectObject(oldpen);
	dc.SelectObject(oldbrush);
	pen.DeleteObject();

}

void OthelloField::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	int x, y;

	GetFieldPosition(point, x, y);
	if ((nSelectedX != x) || (nSelectedY != y))
	{
		nSelectedX = x;
		nSelectedY = y;
		this->Invalidate();
	}

	TRACKMOUSEEVENT tme;
	tme.cbSize = sizeof(tme);
	tme.hwndTrack = this->m_hWnd;
	tme.dwFlags = TME_LEAVE;
	tme.dwHoverTime = HOVER_DEFAULT;


	TrackMouseEvent(&tme);

	CWnd::OnMouseMove(nFlags, point);
}

void OthelloField::HighlightSelection(CPaintDC& dc)
{
	// TODO: Добавьте сюда код реализации.
	if ((nSelectedX < 0) || (nSelectedY < 0))
		return;

	CRect rect = GetRectFromField(nSelectedX, nSelectedY);
	CBrush brush;
	brush.CreateSolidBrush(RGB(125, 249, 255));
	HGDIOBJ oldbrush = dc.SelectObject(brush);
	dc.Rectangle(rect);
	dc.SelectObject(oldbrush);
	brush.DeleteObject();
}

void OthelloField::OnMouseLeave()
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	nSelectedX = -1;
	nSelectedY = -1;
	this->Invalidate();
	CWnd::OnMouseLeave();
}

void OthelloField::SetGameParent(OthelloTestDlg* p)
{
	this->gameParent = p;
}


void OthelloField::SetGameInProgress(bool InProgress)
{
	if (bGameInProgress != InProgress)
	{
		this->bGameInProgress = InProgress;
		this->gameParent->SetGameInProgress(InProgress);
	}
	if (InProgress)
		SetTimer(TIMER_ID, 1000, NULL);
	else
		KillTimer(TIMER_ID); 
	

}

void OthelloField::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	CString str;
	if ((bGameInProgress) && (!this->gameParent->GetCurrentPlayer()->IsHuman()))
	{
		if ((this->gameParent == nullptr) || (this->gameParent->GetBoard() == nullptr))
			return;
		
		SetTimer(TIMER_ID, 0xFFFFFFFF, NULL);
		
		if (this->gameParent->GetCurrentPlayer()->MakeMove(0, 0) == true)
		{
			int x, o;
			this->gameParent->GetBoard()->GetChipCnt(x, o);
			str.Format(L"Чёрных: %i", x);
			this->gameParent->strPlayer1Cnt = str;
			str.Format(L"Белых:  %i", o);
			this->gameParent->strPlayer2Cnt = str;
			this->gameParent->UpdateData(FALSE);
			
			if (this->CheckEndCondition())
			{
				this->SetGameInProgress(false);
				this->gameParent->Invalidate();
			}
			else
			{
				CellType ct = this->gameParent->GetCurrentPlayer()->GetCellType();
				if (ct == CellType_O)ct = CellType_X; else ct = CellType_O;
				{
					if (this->gameParent->GetBoard()->CheckMoveEn(ct))
						this->gameParent->TogglePlayer();
				}

			}
		}

		SetTimer(TIMER_ID, 1000, NULL);
		this->Invalidate();
	}
	CWnd::OnTimer(nIDEvent);
}


BOOL OthelloField::OnEraseBkgnd(CDC* pDC)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного

	CBrush brush;
	brush.CreateSolidBrush(RGB(125, 249, 100));
	CRect rcClip;
	pDC->GetClipBox(rcClip);
	pDC->FillRect(rcClip, &brush);
	brush.DeleteObject();
	return true;
}
