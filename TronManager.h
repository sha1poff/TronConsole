#pragma once
#include "TronField.h"
#include "TronPlayer.h"


class TronManager
{
private:
    TronField* m_Field;
    TronPlayer* m_Player1; // указатель на первого игрока
    TronPlayer* m_Player2; // указатель на второго игрока
    bool m_IsRunning;

    void ProcessInput();
    void Update();
    void Render();

public:
    TronManager(int width, int height);
    ~TronManager();

    // теперь метод принимает конкретный номер игрока
    void SetPlayer(int slot, TronPlayer* player);
    int Run();
};