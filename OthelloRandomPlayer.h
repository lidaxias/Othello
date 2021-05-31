#pragma once
#include "OthelloPlayer.h"
class OthelloRandomPlayer :
    public OthelloPlayer
{
public:
    OthelloRandomPlayer();
    virtual ~OthelloRandomPlayer();
    virtual bool MakeMove(unsigned int col, unsigned int row);
    virtual bool IsHuman();

};


