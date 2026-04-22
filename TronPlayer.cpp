#include "pch.h"
#include "TronPlayer.h"


TronPlayer::TronPlayer(std::string name, int playerNum)
    : m_Name(name), m_PlayerNumber(playerNum) // инициализация
{
    if (m_PlayerNumber == 1)
    {
        this->m_X = 10;
        this->m_Y = 12;
        this->m_Dir = RIGHT;
        this->m_Color = 10; // зеленый
    }
    if (m_PlayerNumber == 2)
    {
        this->m_X = 60;
        this->m_Y = 12;
        this->m_Dir = LEFT;
        this->m_Color = 13; // фиолетовый
    }
}

TronPlayer::~TronPlayer()
{
}

void TronPlayer::Move()
{
    switch (m_Dir)
    {
    case UP:
        m_Y--;
        break;
    case LEFT:
        m_X--;
        break;
    case RIGHT:
        m_X++;
        break;
    case DOWN:
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