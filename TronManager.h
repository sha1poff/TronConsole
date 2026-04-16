#pragma once
#include "TronField.h"
#include "TronPlayer.h"

/// <summary>
/// Класс игрового движка, связывает между собой игровое поле и игроков, управляет основным циклом игры, обработкой ввода, обновлением состояния и отрисовкой.
/// Реализует шаблон проектирования "Посредник" (Mediator), выступая центральным координатором между игроками и полем.
/// </summary>
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