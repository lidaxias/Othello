#include "pch.h"
#include "OthelloBoardMonteCarloEvaluator.h"
#include "OthelloRandomPlayer.h"
OthelloBoardMonteCarloEvaluator::OthelloBoardMonteCarloEvaluator(OthelloBoard* board, int numIterations, CellType startCellType, unsigned int xpos, unsigned int ypos)
{
	this->board = board;
	this->numGames = numIterations;
	this->numDraws = 0;
	this->numLosses = 0;
	this->xpos = xpos;
	this->ypos = ypos;
	this->startCellType = startCellType;

}

OthelloBoardMonteCarloEvaluator::~OthelloBoardMonteCarloEvaluator()
{

}

// исход для доски с заданным ходом
void   OthelloBoardMonteCarloEvaluator::EvaluateBoard()
{
	OthelloBoard* b = new (OthelloBoard)(this->board);
	OthelloRandomPlayer* player1 = new OthelloRandomPlayer();
	OthelloRandomPlayer* player2 = new OthelloRandomPlayer();
	OthelloRandomPlayer* currentPlayer;
	bool bGameFinished = false;
	player1->SetupPlayer(L"RandomBlack", CellType_X);
	player2->SetupPlayer(L"RandomWhite", CellType_O);
	player1->SetBoard(b);
	player2->SetBoard(b);
	//делаем первый ход
	b->SetCells(xpos, ypos, startCellType);
	currentPlayer = (this->startCellType == CellType_X) ? player2 : player1;
	if (b->CheckEndCondition())
	{
		int x, o;
		b->GetChipCnt(x, o);
		if (x > o)
			if (startCellType == CellType_X)
				numVictories++;
			else
				numLosses++;
		else if (o > x)
			if (startCellType == CellType_O)
				numVictories++;
			else
				numLosses++;
		else  numDraws++;
		bGameFinished = true;

		delete b;
		delete player1;
		delete player2;
		return;
	}

	int k = 0,d=0;
	CString str;
	
	while (!bGameFinished)
	{
		if (!b->CheckMoveEn(currentPlayer->GetCellType()))
			currentPlayer = (currentPlayer == player2) ? player1 : player2;
		while (currentPlayer->MakeMove(0, 0));
		if (b->CheckEndCondition())
		{
			int x, o;
			b->GetChipCnt(x, o);
			if (x > o)
				if (startCellType == CellType_X)
					numVictories++;
				else
					numLosses++;
			else if (o > x)
				if (startCellType == CellType_O)
					numVictories++;
				else
					numLosses++;
			else  numDraws++;

			bGameFinished = true;
		}
		currentPlayer = (currentPlayer == player2) ? player1 : player2;
		k++;
	}
	
	delete b;
	delete player1;
	delete player2;

}
// вычисление всех игр
void   OthelloBoardMonteCarloEvaluator::Evaluate()
{
	for (int i = 0; i < numGames; i++)
		EvaluateBoard();

}
