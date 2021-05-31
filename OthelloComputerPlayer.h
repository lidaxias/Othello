#pragma once
#include "OthelloPlayer.h"
class OthelloComputerPlayer : public OthelloPlayer
{
public:
	OthelloComputerPlayer();
	virtual ~OthelloComputerPlayer();
	virtual bool MakeMove(unsigned int col, unsigned int row);
	virtual bool IsHuman();

};

