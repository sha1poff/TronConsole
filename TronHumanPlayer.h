#pragma once

#include "TronPlayer.h"
#include "TronField.h"


class TronHumanPlayer :
    public TronPlayer
{
private:
    // коды клавиш управления, инициализируемые в конструкторе
    int m_UpKey;
    int m_DownKey;
    int m_LeftKey;
    int m_RightKey;

    // флаг для определения спецсимволов (стрелок), требующих двойного вызова _getch()
    bool m_IsSpecialKey;

public:
    TronHumanPlayer(std::string name, int playerNum);
    virtual ~TronHumanPlayer();

    void UpdateDirection(const TronField* field) override;
};

