#include "pch.h"
#include "TronPlayer.h"


TronPlayer::TronPlayer(std::string name, int x, int y, Direction dir, int color) :
    m_Name(name),
    m_X(x),
    m_Y(y),
    m_Dir(dir),
    m_Color(color),
    m_IsAlive(true)
{
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