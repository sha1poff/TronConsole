#include "TronHumanPlayer.h"


TronHumanPlayer::TronHumanPlayer(
    std::string name,
    int x, int y,
    Direction dir,
    int color,
    bool useArrows
)
    : TronPlayer(name, x, y, dir, color),
    m_UseArrows(useArrows)
{
}

TronHumanPlayer::~TronHumanPlayer()
{
}

void TronHumanPlayer::UpdateDirection() {
    int pressedKey = 0;

    if (m_UseArrows)
    {
        if (GetAsyncKeyState(VK_UP) & 0x8000)         pressedKey = VK_UP;
        else if (GetAsyncKeyState(VK_DOWN) & 0x8000)  pressedKey = VK_DOWN;
        else if (GetAsyncKeyState(VK_LEFT) & 0x8000)  pressedKey = VK_LEFT;
        else if (GetAsyncKeyState(VK_RIGHT) & 0x8000) pressedKey = VK_RIGHT;
    }
    else
    {
        if (GetAsyncKeyState('W') & 0x8000)      pressedKey = 'W';
        else if (GetAsyncKeyState('S') & 0x8000) pressedKey = 'S';
        else if (GetAsyncKeyState('A') & 0x8000) pressedKey = 'A';
        else if (GetAsyncKeyState('D') & 0x8000) pressedKey = 'D';
    }

    switch (pressedKey)
    {
        case VK_UP:
        case 'W':
            if (m_Dir != Direction::DOWN) m_Dir = Direction::UP;
            break;

        case VK_DOWN:
        case 'S':
            if (m_Dir != Direction::UP) m_Dir = Direction::DOWN;
            break;

        case VK_LEFT:
        case 'A':
            if (m_Dir != Direction::RIGHT) m_Dir = Direction::LEFT;
            break;

        case VK_RIGHT:
        case 'D':
            if (m_Dir != Direction::LEFT) m_Dir = Direction::RIGHT;
            break;

        default:
            break;
    }
}