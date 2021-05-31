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
	// �������� �������� ����������� ��� ������� ���������� ����
	vector <OthelloBoardMonteCarloEvaluator*> evaluators;
	for (unsigned int i = 0; i < this->board->GetBoardSize(); i++)
		for (unsigned int j = 0; j < this->board->GetBoardSize(); j++)
			if (this->board->CheckLegal(j, i, this->cellType))
				evaluators.push_back(new OthelloBoardMonteCarloEvaluator(this->board, 1000, this->cellType, j, i));
	
	
	// ������e��� ���������� ��������� ������� ��� �������  �������
	for (auto evaluator = evaluators.begin(); evaluator != evaluators.end(); evaluator++)
		(*evaluator)->Evaluate();

	// ����������� �������� ������������� ��������
	int biggestVictories = -1;
	for (auto evaluator = evaluators.begin(); evaluator != evaluators.end(); evaluator++)
			if ((*evaluator)->GetVictores() > biggestVictories)
				biggestVictories = (*evaluator)->GetVictores();

	// �������� ������� �������� � ������������ ��������� 
	vector <OthelloBoardMonteCarloEvaluator*> biggestWinEvaluators;
	for (auto evaluator = evaluators.begin(); evaluator != evaluators.end(); evaluator++)
	{
		int numVictories;
		numVictories = (*evaluator)->GetVictores();
		if (numVictories == biggestVictories)
			biggestWinEvaluators.push_back((*evaluator));
	}

	// ������ ���. ������ ���� �� ������� ������� ������� � ������������ ��������� 
	this->board->SetCells(biggestWinEvaluators[0]->GetXPos(), biggestWinEvaluators[0]->GetYPos(), this->cellType);

	// ������� ����������� �������������� ������
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