#include "pch.h"
#include "OthelloRandomPlayer.h"

OthelloRandomPlayer::OthelloRandomPlayer()
{

}

OthelloRandomPlayer::~OthelloRandomPlayer()
{

}

bool OthelloRandomPlayer::MakeMove(unsigned int c, unsigned int r)
{
	unsigned int row, col;
	int bs = this->board->GetBoardSize();
	row = (unsigned int)(rand() % bs);
	col = (unsigned int)(rand() % bs);
	if (this->board->CheckLegal(col, row, this->cellType))
	{
		this->board->SetCells(col, row, this->cellType);
		return true;
	}
	return false;
}

bool OthelloRandomPlayer::IsHuman()
{
	 return false;
}