#include "pch.h"
#include "OthelloComputerPlayer.h"
#include "OthelloBoardMonteCarloEvaluator.h"
#include <vector>
OthelloComputerPlayer::OthelloComputerPlayer()
{

}

OthelloComputerPlayer::~OthelloComputerPlayer()
{

}

bool OthelloComputerPlayer::MakeMove(unsigned int col, unsigned int row)
{	
	// создание объектов вычислителя для каждого легального хода
	vector <OthelloBoardMonteCarloEvaluator*> evaluators;
	for (unsigned int i = 0; i < this->board->GetBoardSize(); i++)
		for (unsigned int j = 0; j < this->board->GetBoardSize(); j++)
			if (this->board->CheckLegal(j, i, this->cellType))
				evaluators.push_back(new OthelloBoardMonteCarloEvaluator(this->board, 1000, this->cellType, j, i));
	
	
	// вычислeние количества вероятных исходов для каждого  объекта
	for (auto evaluator = evaluators.begin(); evaluator != evaluators.end(); evaluator++)
		(*evaluator)->Evaluate();

	// определение значения максимального выигрыша
	int biggestVictories = -1;
	for (auto evaluator = evaluators.begin(); evaluator != evaluators.end(); evaluator++)
			if ((*evaluator)->GetVictores() > biggestVictories)
				biggestVictories = (*evaluator)->GetVictores();

	// создание массива объектов с максимальным выигрышем 
	vector <OthelloBoardMonteCarloEvaluator*> biggestWinEvaluators;
	for (auto evaluator = evaluators.begin(); evaluator != evaluators.end(); evaluator++)
	{
		int numVictories;
		numVictories = (*evaluator)->GetVictores();
		if (numVictories == biggestVictories)
			biggestWinEvaluators.push_back((*evaluator));
	}

	// делаем ход. данные берём из первого объекта массива с максимальным выигрышем 
	this->board->SetCells(biggestWinEvaluators[0]->GetXPos(), biggestWinEvaluators[0]->GetYPos(), this->cellType);

	// очистка динамически распределяемой памяти
	for (auto evaluator = evaluators.begin(); evaluator != evaluators.end(); evaluator++)
		delete (*evaluator);
	evaluators.clear();
	biggestWinEvaluators.clear();

	return true;
}

bool OthelloComputerPlayer::IsHuman()
{
	return false;
}