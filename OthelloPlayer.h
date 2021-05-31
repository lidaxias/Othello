#pragma once
#include <iostream>
using namespace std;
#include "OthelloBoard.h"

class OthelloPlayer
{
protected:
	OthelloBoard* board;
	CellType cellType;
	CString name;

public:
	OthelloPlayer();
	virtual ~OthelloPlayer();
	void SetupPlayer(CString name, CellType celltype);
	void SetBoard(OthelloBoard* board);
	virtual bool MakeMove(unsigned int col, unsigned int row) = 0;
	CString GetName();
	CellType GetCellType();
	virtual bool IsHuman() = 0;
};




