#include "TronComputerPlayer.h"


TronComputerPlayer::TronComputerPlayer(
    std::string name,
    int x, int y,
    Direction dir,
    int color)
    : TronPlayer(name, x, y, dir, color)
{
}

TronComputerPlayer::~TronComputerPlayer()
{
}

void TronComputerPlayer::UpdateDirection()
{
}