#include "pch.h"
#include "OthelloHumanPlayer.h"

OthelloHumanPlayer::OthelloHumanPlayer()
{

}

OthelloHumanPlayer::~OthelloHumanPlayer()
{

}

// игрок-человек делает ход
bool OthelloHumanPlayer::MakeMove(unsigned int col, unsigned int row)
{
	if (this->board->CheckLegal(col, row, this->cellType))
	{
		this->board->SetCells(col, row, this->cellType);
		return true;
	}
	return false;
}

bool OthelloHumanPlayer::IsHuman()
{
	return true;
}