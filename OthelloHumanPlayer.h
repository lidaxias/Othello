#pragma once
#include <iostream>
using namespace std;
#include "OthelloBoard.h"
#include "OthelloPlayer.h"
#include <conio.h>


class OthelloHumanPlayer : public OthelloPlayer
{
public:
	OthelloHumanPlayer();
	virtual ~OthelloHumanPlayer();
	virtual bool MakeMove(unsigned int col, unsigned int row);
	virtual bool IsHuman();

};
