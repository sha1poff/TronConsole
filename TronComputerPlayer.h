#pragma once
#include "TronPlayer.h"
#include "TronField.h"

class TronComputerPlayer : public TronPlayer
{
private:
	int m_Difficulty; // 1 - легкий, 2 - средний, 3 - сложный

public:
    TronComputerPlayer(
        std::string name,
        int playerNum
    );

    virtual ~TronComputerPlayer();

    void SetDifficulty(int diff);

    // искусственный интеллект
    void UpdateDirection(const TronField* field) override;
};