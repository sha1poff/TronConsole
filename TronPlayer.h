#pragma once

#include "Direction.h"
#include "pch.h"
#include "TronField.h"

/// <summary>
/// Абстрактный базовый класс для игроков в игре Tron.
/// Содержит общие свойства и методы для управления, состоянием игрока, его позицией, направлением и цветом.
/// Конкретные типы игроков (человек или ИИ) будут наследовать от этого класса
/// и реализовывать логику изменения направления движения.
/// </summary>
class TronPlayer
{
protected:              // protected, чтобы наследники видели поля
    std::string m_Name; // имя
    int m_PlayerNumber; // номер игрока
    int m_X, m_Y;       // координаты
    Direction m_Dir;    // текущее направление
    int m_Color;        // цвет игрока
    bool m_IsAlive;     

public:
    TronPlayer(std::string name, int playerNum);
    virtual ~TronPlayer();  

    // реализация изменения координат
    virtual void UpdateDirection(const TronField* field) = 0;

    // движение
    void Move();

    // геттеры
    std::string GetName() const;
    int GetColor() const;
    int GetX() const;
    int GetY() const;
};
