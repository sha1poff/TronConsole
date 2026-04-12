#pragma once
#include "pch.h"
#include "TronField.h"


enum class Direction {UP, RIGHT, DOWN, LEFT };

class TronPlayer
{
protected: // protected, чтобы наследники видели поля
    std::string m_Name;
    int m_X, m_Y;
    Direction m_Dir;
    int m_Color;
    bool m_IsAlive;

public:
    TronPlayer(std::string name, int x, int y, Direction dir, int color);
    virtual ~TronPlayer();  

    virtual void UpdateDirection(const TronField* field) = 0;

    void Move();

    std::string GetName() const;
    int GetColor() const;
    int GetX() const;
    int GetY() const;

    bool IsAlive() const;
    void Die();
};
