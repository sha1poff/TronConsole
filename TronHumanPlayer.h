#pragma once
#include "TronPlayer.h"


class TronHumanPlayer :
    public TronPlayer
{
private:
    bool m_UseArrows;

public:
    TronHumanPlayer(
        std::string name,
        int x, int y,
        Direction dir,
        int color,
        bool m_UseArrows
    );
    virtual ~TronHumanPlayer();

    virtual void UpdateDirection() override;
};

