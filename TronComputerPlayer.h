#pragma once
#include "TronPlayer.h"


class TronComputerPlayer : public TronPlayer
{
public:
    TronComputerPlayer(
        std::string name,
        int x, int y,
        Direction dir,
        int color
    );

    virtual ~TronComputerPlayer();

    // Искусственный интеллект
    virtual void UpdateDirection() override;
};