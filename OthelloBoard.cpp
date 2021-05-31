#include "pch.h"
#include "OthelloBoard.h"

using namespace std;

OthelloBoard::OthelloBoard(unsigned int size)
{
	this->boardsize = size;
	cells = new CellType * [size];
	for (unsigned int i = 0; i < size; i++)
		cells[i] = new CellType[size];
	for (unsigned int i = 0; i < size; i++)
		for (unsigned int j = 0; j < size; j++)
			cells[i][j] = CellType_Empty;
}

OthelloBoard::OthelloBoard(OthelloBoard* board)
{
	this->boardsize = board->boardsize;
	cells = new CellType * [boardsize];
	for (unsigned int i = 0; i < boardsize; i++)
		cells[i] = new CellType[boardsize];
	for (unsigned int i = 0; i < boardsize; i++)
		for (unsigned int j = 0; j < boardsize; j++)
			cells[i][j] = board->cells[i][j];

}

OthelloBoard::~OthelloBoard()
{
	for (unsigned int i = 0; i < boardsize; i++)
		delete[]cells[i];
	delete[]cells;
}

// проверка, есть ли возможные ходы для текущего игрока
bool OthelloBoard::CheckMoveEn(CellType ct)
{
	for (unsigned int x=0;x< boardsize;x++)
		for (unsigned int y = 0; y < boardsize; y++)
			if (cells[y][x] == CellType_Empty)
				if (CheckLegal(x, y, ct))return true;		
	return false;
}
// проверка легален ли ход
bool OthelloBoard::CheckLegal(unsigned int xpos, unsigned int ypos, CellType ct)
{

	if((xpos>=boardsize)|| (ypos >= boardsize))
		return false;
	if (cells[ypos][xpos] != CellType_Empty) 
		return false;
	return (CheckLegalU(xpos, ypos, ct) || CheckLegalD(xpos, ypos, ct) || CheckLegalL(xpos, ypos, ct) || CheckLegalR(xpos, ypos, ct)
		|| CheckLegalUL(xpos, ypos, ct) || CheckLegalDR(xpos, ypos, ct) || CheckLegalDL(xpos, ypos, ct) || CheckLegalUR(xpos, ypos, ct));
}
//заполнение рядов выбраныным цветом по всем возможным направлениям
void OthelloBoard::SetCells(unsigned int xpos, unsigned int ypos, CellType ct)
{
	SetCellsU(xpos, ypos, ct);
	SetCellsD(xpos, ypos, ct);
	SetCellsL(xpos, ypos, ct);
	SetCellsR(xpos, ypos, ct);
	SetCellsUL(xpos, ypos, ct);
	SetCellsDR(xpos, ypos, ct);
	SetCellsUR(xpos, ypos, ct);
	SetCellsDL(xpos, ypos, ct);
	cells[ypos][xpos] = ct;
}
// заполнение ячейки
void OthelloBoard::SetCell(unsigned int xpos, unsigned int ypos, CellType ct)
{
	cells[ypos][xpos] = ct;
}
// заполнение возможных ячеек ряда в направлении вверх от текущей ячейки 
void OthelloBoard::SetCellsU(unsigned int xpos, unsigned int ypos, CellType ct)
{
	if (!CheckLegalU(xpos, ypos, ct)) return;
	for (unsigned int y = 1; y <= ypos; y++)
	{
		if (cells[ypos - y][xpos] == ct) return;
		if ((cells[ypos - y][xpos] != CellType_Empty) && (cells[ypos - y][xpos] != ct))
			cells[ypos - y][xpos] = ct;		
	}
	
}
// заполнение возможных ячеек диагонали в направлении вверх-влево от текущей ячейки 
void OthelloBoard::SetCellsUL(unsigned int xpos, unsigned int ypos, CellType ct)
{
	if (!CheckLegalUL(xpos, ypos, ct)) return;
	unsigned int e;
	if (xpos < ypos) e = xpos; else e = ypos;
	for (unsigned int x = 1; x <= e; x++)
	{
		if (cells[ypos - x][xpos - x] == ct) return;
		if ((cells[ypos - x][xpos - x] != CellType_Empty) && (cells[ypos - x][xpos - x] != ct))
			cells[ypos - x][xpos - x] = ct;
	}
}
// заполнение возможных ячеек диагонали в направлении вверх-вправо от текущей ячейки 
void OthelloBoard::SetCellsUR(unsigned int xpos, unsigned int ypos, CellType ct)
{
	if (!CheckLegalUR(xpos, ypos, ct)) return;
	unsigned int e;
	if (ypos < (boardsize -1- xpos)) e = ypos; else e = boardsize-1 - xpos;
	for (unsigned int x = 1; x <=e; x++)
	{
		if (cells[ypos - x][xpos + x] == ct) return;
		if ((cells[ypos - x][xpos + x] != CellType_Empty) && (cells[ypos - x][xpos + x] != ct))
			cells[ypos - x][xpos + x] = ct;
	}
}
// заполнение возможных ячеек диагонали в направлении вниз-влево от текущей ячейки 
void OthelloBoard::SetCellsDL(unsigned int xpos, unsigned int ypos, CellType ct)
{
	if (!CheckLegalDL(xpos, ypos, ct)) return;
	unsigned int e;
	if (xpos < (boardsize -1- ypos)) e = xpos; else e = boardsize -1- ypos;
	for (unsigned int x = 1; x <= e; x++)
	{
		if (cells[ypos + x][xpos - x] == ct) return;
		if ((cells[ypos + x][xpos - x] != CellType_Empty) && (cells[ypos + x][xpos - x] != ct))
			cells[ypos + x][xpos - x] = ct;
	}
}
// заполнение возможных ячеек ряда в направлении влево от текущей ячейки 
void OthelloBoard::SetCellsL(unsigned int xpos, unsigned int ypos, CellType ct)
{

	if (!CheckLegalL(xpos, ypos, ct)) return;
	for (unsigned int x = 1; x <= xpos; x++)
	{
		if (cells[ypos][xpos-x] == ct) return;
		if ((cells[ypos][xpos - x] != CellType_Empty) && (cells[ypos][xpos - x] != ct))
			cells[ypos][xpos - x] = ct;
	}

}
// заполнение возможных ячеек ряда в направлении вниз от текущей ячейки 
void OthelloBoard::SetCellsD(unsigned int xpos, unsigned int ypos, CellType ct)
{
	if (!CheckLegalD(xpos, ypos, ct)) return;
	for (unsigned int y = 1; y <= (boardsize - 1) - ypos; y++)
	{
		if (cells[ypos + y][xpos] == ct) return;
		if ((cells[ypos + y][xpos] != CellType_Empty) && (cells[ypos + y][xpos] != ct))
			cells[ypos + y][xpos] = ct;
	}
}
// заполнение возможных ячеек диагонали в направлении вниз-вправо от текущей ячейки 
void OthelloBoard::SetCellsDR(unsigned int xpos, unsigned int ypos, CellType ct)
{
	if (!CheckLegalDR(xpos, ypos, ct)) return;
	unsigned int e;
	if (xpos > ypos) e = boardsize -1- xpos; else e = boardsize -1- ypos;
	for (unsigned int x = 1; x <=e; x++)
	{
		if (cells[ypos + x][xpos + x] == ct) return;
		if ((cells[ypos + x][xpos + x] != CellType_Empty) && (cells[ypos + x][xpos + x] != ct))
			cells[ypos + x][xpos + x] = ct;
	}
}
// заполнение возможных ячеек ряда в направлении вправо от текущей ячейки 
void OthelloBoard::SetCellsR(unsigned int xpos, unsigned int ypos, CellType ct)
{
	if (!CheckLegalR(xpos, ypos, ct)) return;
	for (unsigned int x = 1; x <= (boardsize - 1) - xpos; x++)
	{
		if (cells[ypos][xpos+x] == ct) return;
		if ((cells[ypos][xpos+x] != CellType_Empty) && (cells[ypos][xpos+x] != ct))
			cells[ypos ][xpos+x] = ct;
	}
}

// проверка легальности хода для текущей ячейки  в направлении вверх от текущей ячейки 
bool OthelloBoard::CheckLegalU(unsigned int xpos, unsigned int ypos, CellType ct)
{
	if (ypos < 2) return false;
	int status = 0;
	for (unsigned int y = 1; y <=ypos; y++)
	{
		switch (status)
		{
			case 0:
				if ((cells[ypos - y][xpos] != CellType_Empty) && (cells[ypos - y][xpos] != ct))
				{
					status = 1; break;
				}
				else return false;
			case 1:
				if (cells[ypos - y][xpos] == ct) return true;
				if (cells[ypos - y][xpos] == CellType_Empty) return false;
				break;
		}
	}
	return false;
}
// проверка легальности хода для текущей ячейки  в направлении влево от текущей ячейки 
bool OthelloBoard::CheckLegalL(unsigned int xpos, unsigned int ypos, CellType ct)
{
	if (xpos < 2) return false;
	int status = 0;
	for (unsigned int x = 1; x <=xpos; x++)
	{
		switch (status)
		{
		case 0:
			if ((cells[ypos][xpos - x] != CellType_Empty) && (cells[ypos][xpos - x] != ct))
			{
				status = 1; break;
			}
			else return false;
		case 1:
			if (cells[ypos][xpos - x] == ct) return true;
			if (cells[ypos][xpos - x] == CellType_Empty) return false;
			break;
		}
	}
	return false;
}

// проверка легальности хода для текущей ячейки  в направлении вниз от текущей ячейки 
bool OthelloBoard::CheckLegalD(unsigned int xpos, unsigned int ypos, CellType ct)
{
	if (ypos > boardsize - 3) return false;
	int status = 0;
	for (unsigned int y = 1; y <= (boardsize - 1) - ypos; y++)
	{
		switch (status)
		{
		case 0:
			if ((cells[ypos+y][xpos] != CellType_Empty) && (cells[ypos + y][xpos] != ct))
			{
				status = 1; break;
			}
			else return false;
		case 1:
			if (cells[ypos + y][xpos] == ct) return true;
			if (cells[ypos + y][xpos] == CellType_Empty) return false;
			break;
		}
	}
	return false;
}
// проверка легальности хода для текущей ячейки  в направлении вправо от текущей ячейки 
bool OthelloBoard::CheckLegalR(unsigned int xpos, unsigned int ypos, CellType ct)
{
	if (xpos > boardsize - 3) return false;
	int status = 0;
	for (unsigned int x = 1; x <= (boardsize - 1) - xpos; x++)
	{
		switch (status)
		{
		case 0:
			if ((cells[ypos][xpos+x] != CellType_Empty) && (cells[ypos][xpos + x] != ct))
			{
				status = 1; break;
			}
			else return false;
		case 1:
			if (cells[ypos][xpos + x] == ct) return true;
			if (cells[ypos][xpos + x] == CellType_Empty) return false;
			break;
		}
	}
	return false;
}
// проверка легальности хода для текущей ячейки  в направлении вниз-вправо от текущей ячейки 
bool OthelloBoard::CheckLegalDR(unsigned int xpos, unsigned int ypos, CellType ct)
{
	if (xpos > boardsize - 3) return false;
	if (ypos > boardsize - 3) return false;
	int status = 0;
	unsigned int e;
	if (xpos> ypos) e = boardsize -1- xpos; else e = boardsize -1- ypos;
	for (unsigned int x =  1; x <=e; x++)
	{
		switch (status)
		{
		case 0:
			if ((cells[ypos + x][xpos + x] != CellType_Empty) && (cells[ypos + x][xpos + x] != ct))
			{
				status = 1; break;
			}
			else return false;
		case 1:
			if (cells[ypos+x][xpos+x] == ct) return true;
			if (cells[ypos + x][xpos + x] == CellType_Empty) return false;
			break;
		}
	}
	return false;
}
// проверка легальности хода для текущей ячейки  в направлении вниз-влево от текущей ячейки 
bool OthelloBoard::CheckLegalDL(unsigned int xpos, unsigned int ypos, CellType ct)
{
	CString str;
	if (xpos < 2) return false;
	if (ypos > boardsize - 3) return false;
	int status = 0;
	unsigned int e;
	if (xpos < (boardsize -1- ypos)) e = xpos; else e = boardsize -1- ypos;
	for (unsigned int x = 1; x <=e; x++)
	{
		switch (status)
		{
		case 0:
			if ((cells[ypos + x][xpos - x] != CellType_Empty) && (cells[ypos + x][xpos - x] != ct))
			{
				status = 1; break;
			}
			else return false;
		case 1:
			if (cells[ypos + x][xpos - x] == ct) return true;
			if (cells[ypos + x][xpos - x] == CellType_Empty) return false;
			break;
		}
	}
	return false;
}
// проверка легальности хода для текущей ячейки  в направлении вверх-вправо от текущей ячейки 
bool OthelloBoard::CheckLegalUR(unsigned int xpos, unsigned int ypos, CellType ct)
{
	if (ypos < 2) return false;
	if (xpos > boardsize - 3) return false;
	int status = 0;
	unsigned int e;
	if (ypos < (boardsize -1- xpos)) e = ypos; else e = boardsize -1- xpos;
	for (unsigned int x = 1; x <=e; x++)
	{
		switch (status)
		{
		case 0:
			if ((cells[ypos - x][xpos + x] != CellType_Empty) && (cells[ypos - x][xpos + x] != ct))
			{
				status = 1; break;
			}
			else return false;
		case 1:
			if (cells[ypos - x][xpos + x] == ct) return true;
			if (cells[ypos - x][xpos + x] == CellType_Empty) return false;
			break;
		}
	}
	return false;
}
// проверка легальности хода для текущей ячейки  в направлении вверх-влево от текущей ячейки 
bool OthelloBoard::CheckLegalUL(unsigned int xpos, unsigned int ypos, CellType ct)
{
	if (ypos < 2) return false;
	if (xpos < 2) return false;
	int status = 0;
	unsigned int e;
	if (xpos < ypos) e = xpos; else e = ypos;
	for (unsigned int x = 1; x <= e; x++)
	{
		switch (status)
		{
		case 0:
			if ((cells[ypos - x][xpos - x] != CellType_Empty) && (cells[ypos - x][xpos - x] != ct))
			{
				status = 1; break;
			}
			else return false;
		case 1:
			if (cells[ypos - x][xpos - x] == ct) return true;
			if (cells[ypos - x][xpos - x] == CellType_Empty) return false;
			break;
		}
	}
	return false;
}

// подсчёт количества фишек для каждого игрока
void OthelloBoard::GetChipCnt(int& ChipX, int& ChipO)
{
	int numX = 0, numO = 0;
	for ( int i = 0; i < boardsize; i++)
	{
		for ( int j = 0; j < boardsize; j++)
		{
			if (cells[i][j] == CellType_O)
				numO++;
			if (cells[i][j] == CellType_X)
				numX++;
		}
	}
	ChipX = numX; ChipO = numO;
}
// проверка завершения игры
bool OthelloBoard::CheckEndCondition()
{
	// игра не закончена, если  есть доступный ход хотя бы у одного игрока
	if (CheckMoveEn(CellType_O) || CheckMoveEn(CellType_X))
		return false;
	else
		return true;
}
// получение содержимого ячейки
CellType OthelloBoard::GetCell(unsigned int xpos, unsigned int ypos)
{
	return cells[ypos][xpos];
}
// получение размера доски
unsigned int OthelloBoard::GetBoardSize()
{
	return boardsize;
}
// очистка доски
void OthelloBoard::ClearBoard()
{
	for (unsigned int i = 0; i < boardsize; i++)
		for (unsigned int j = 0; j < boardsize; j++)
			cells[i][j] = CellType_Empty;
}




