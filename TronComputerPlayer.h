#pragma once

#include "TronPlayer.h"
#include "TronField.h"

/// <summary>
/// Класс для управления игроком-компьютером. Реализует простую логику ИИ для выбора направления движения на основе текущего состояния игрового поля и уровня сложности.
/// Всего имеет 3 уровня сложности, которые влияют на глубину анализа возможных ходов и стратегию выбора направления.
/// </summary>
class TronComputerPlayer : public TronPlayer
{
private:
    // уровень сложности
	int m_Difficulty; // 1 - легкий, 2 - средний, 3 - сложный

public:
    TronComputerPlayer( std::string name, int playerNum);

    virtual ~TronComputerPlayer();

    // сеттер сложности
    void SetDifficulty(int diff);

    // искусственный интеллект
    void UpdateDirection(const TronField* field) override;
};