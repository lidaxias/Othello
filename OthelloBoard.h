#pragma once
#include "CellType.h"

class OthelloBoard
{
private:
	unsigned int boardsize;
	CellType** cells;

	bool CheckLegalU(unsigned int xpos, unsigned int ypos, CellType ct);
	bool CheckLegalD(unsigned int xpos, unsigned int ypos, CellType ct);
	bool CheckLegalL(unsigned int xpos, unsigned int ypos, CellType ct);
	bool CheckLegalR(unsigned int xpos, unsigned int ypos, CellType ct);
	bool CheckLegalUR(unsigned int xpos, unsigned int ypos, CellType ct);
	bool CheckLegalUL(unsigned int xpos, unsigned int ypos, CellType ct);
	bool CheckLegalDR(unsigned int xpos, unsigned int ypos, CellType ct);
	bool CheckLegalDL(unsigned int xpos, unsigned int ypos, CellType ct);
	void SetCellsU(unsigned int xpos, unsigned int ypos, CellType ct);
	void SetCellsD(unsigned int xpos, unsigned int ypos, CellType ct);
	void SetCellsL(unsigned int xpos, unsigned int ypos, CellType ct);
	void SetCellsR(unsigned int xpos, unsigned int ypos, CellType ct);
	void SetCellsUL(unsigned int xpos, unsigned int ypos, CellType ct);
	void SetCellsUR(unsigned int xpos, unsigned int ypos, CellType ct);
	void SetCellsDL(unsigned int xpos, unsigned int ypos, CellType ct);
	void SetCellsDR(unsigned int xpos, unsigned int ypos, CellType ct);
public:
	OthelloBoard(unsigned int size);
	OthelloBoard(OthelloBoard* board);
	virtual ~OthelloBoard();
	void SetCell(unsigned int xpos, unsigned int ypos, CellType ct);
	void SetCells(unsigned int xpos, unsigned int ypos, CellType ct);
	bool CheckMoveEn(CellType ct);
	bool CheckLegal(unsigned int xpos, unsigned int ypos, CellType ct);
	bool CheckEndCondition();
	CellType GetCell(unsigned int xpos, unsigned int ypos);
	unsigned int GetBoardSize();
	void ClearBoard();
	void GetChipCnt(int& ChipX , int& ChipO);
};

