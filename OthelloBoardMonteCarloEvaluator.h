#pragma once
#include "OthelloBoard.h"
#include "OthelloPlayer.h"


class OthelloBoardMonteCarloEvaluator
{
private:
	OthelloBoard* board;
	int numGames;
	int numVictories;
	int numLosses;
	int numDraws;
	unsigned int xpos, ypos;
	CellType startCellType;
public:
	OthelloBoardMonteCarloEvaluator(OthelloBoard* board, int numIterations, CellType startCellType, unsigned int xpos, unsigned int ypos);
	~OthelloBoardMonteCarloEvaluator();
	void EvaluateBoard();
	void Evaluate();
	int GetVictores() { return numVictories; };
	int GetLosses() { return numLosses; };
	int GetDraws() { return numDraws; };
	int GetXPos() { return xpos; };
	int GetYPos() { return ypos; };

};


