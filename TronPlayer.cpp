#include "pch.h"
#include "TronPlayer.h"


TronPlayer::TronPlayer(std::string name, int playerNum)
    : m_Name(name), m_PlayerNumber(playerNum) // инициализация
{
    if (m_PlayerNumber == 1)
    {
        m_X = 10;
        m_Y = 12;
        m_Dir = Direction::RIGHT;
        m_Color = 10; // зеленый
    }
    if (m_PlayerNumber == 2)
    {
        m_X = 60;
        m_Y = 12;
        m_Dir = Direction::LEFT;
        m_Color = 13; // фиолетовый
    }
}

TronPlayer::~TronPlayer()
{
}

void TronPlayer::Move()
{
    // Теперь используем переменные с префиксом m_
    switch (m_Dir)
    {
    case Direction::UP:
        m_Y--;
        break;
    case Direction::LEFT:
        m_X--;
        break;
    case Direction::RIGHT:
        m_X++;
        break;
    case Direction::DOWN:
        m_Y++;
        break;
    }
}

std::string TronPlayer::GetName() const
{
    return m_Name;
}

int TronPlayer::GetColor() const
{
    return m_Color;
}

int TronPlayer::GetX() const
{
    return m_X;
}

int TronPlayer::GetY() const
{
    return m_Y;
}

bool TronPlayer::IsAlive() const
{
    return m_IsAlive;
}

void TronPlayer::Die()
{
    m_IsAlive = false;
}