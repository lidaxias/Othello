#include "pch.h"
#include "OthelloPlayer.h"


OthelloPlayer::OthelloPlayer()
{

}

OthelloPlayer::~OthelloPlayer()
{

}

void OthelloPlayer::SetupPlayer(CString name, CellType cellType)
{
	this->name = name;
	this->cellType = cellType;
}

void OthelloPlayer::SetBoard(OthelloBoard* board)
{
	this->board = board;
}

CString OthelloPlayer::GetName()
{
	return this->name;
}

CellType OthelloPlayer::GetCellType()
{
	return this->cellType;
}