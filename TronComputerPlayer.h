#pragma once
#include "TronPlayer.h"
#include "TronField.h"

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
    void UpdateDirection(const TronField* field) override;
};