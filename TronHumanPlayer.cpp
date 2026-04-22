#include "TronHumanPlayer.h"


TronHumanPlayer::TronHumanPlayer(std::string name, int playerNum)
    : TronPlayer(name, playerNum) // вызов базового конструктора для позиции и цвета
{
    if (m_PlayerNumber == 1) {
        m_UpKey = 'W';
        m_DownKey = 'S';
        m_LeftKey = 'A';
        m_RightKey = 'D';
        m_IsSpecialKey = false;
    } 
    else {
        m_UpKey = VK_UP;
        m_DownKey = VK_DOWN;
        m_LeftKey = VK_LEFT;
        m_RightKey = VK_RIGHT;
        m_IsSpecialKey = true;
    }
}

TronHumanPlayer::~TronHumanPlayer()
{
}

void TronHumanPlayer::UpdateDirection(const TronField* field)
{
    int pressedKey = 0;

    // опрашиваем клавиши (универсально)
    if (GetAsyncKeyState(m_UpKey) & 0x8000)
        pressedKey = m_UpKey;
    else if (GetAsyncKeyState(m_DownKey) & 0x8000)
        pressedKey = m_DownKey;
    else if (GetAsyncKeyState(m_LeftKey) & 0x8000)
        pressedKey = m_LeftKey;
    else if (GetAsyncKeyState(m_RightKey) & 0x8000)
        pressedKey = m_RightKey;

    if (pressedKey == 0) return;

    switch (pressedKey)
    {
        // Работает и для WASD (коды букв), и для стрелок (VK коды)
        case 'W':
        case VK_UP:
            if (m_Dir != DOWN) m_Dir = UP;
            break;

        case 'S':
        case VK_DOWN:
            if (m_Dir != UP) m_Dir = DOWN;
            break;

        case 'A':
        case VK_LEFT:
            if (m_Dir != RIGHT) m_Dir = LEFT;
            break;

        case 'D':
        case VK_RIGHT:
            if (m_Dir != LEFT) m_Dir = RIGHT;
            break;
    }
}