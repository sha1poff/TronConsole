#include "TronComputerPlayer.h"
#include "TronField.h"


TronComputerPlayer::TronComputerPlayer(std::string name, int playerNum)
    : TronPlayer(name, playerNum)
{
    m_Difficulty = 1;
}

TronComputerPlayer::~TronComputerPlayer()
{
}

void TronComputerPlayer::SetDifficulty(int diff)
{
    m_Difficulty = diff;
}

void TronComputerPlayer::UpdateDirection(const TronField* field)
{
    Direction dirs[] = { Direction::UP, Direction::DOWN, Direction::LEFT, Direction::RIGHT };
    Direction bestDir = m_Dir;
    int maxScore = -1;

    for (Direction d : dirs) {
        // проверка на разворот 180
        if ((m_Dir == Direction::UP && d == Direction::DOWN) ||
            (m_Dir == Direction::DOWN && d == Direction::UP) ||
            (m_Dir == Direction::LEFT && d == Direction::RIGHT) ||
            (m_Dir == Direction::RIGHT && d == Direction::LEFT))
            continue;

        int score = 0;

        // В зависимости от сложности меняем глубину анализа    
        int depth = (m_Difficulty == 1) ? 1 : (m_Difficulty == 2 ? 10 : 15);

        for (int i = 1; i <= depth; i++) {
            int tx = m_X, ty = m_Y;

            switch (d)
            {
                case Direction::UP:    ty -= i; break;
                case Direction::DOWN:  ty += i; break;
                case Direction::LEFT:  tx -= i; break;
                case Direction::RIGHT: tx += i; break;
            }

            if (field->GetCell(tx, ty) == 0) {
                score++;

                // Дополнительная логика для Уровня 3 (анализ пространства вокруг)
                if (m_Difficulty == 3)
                {
                    switch (d)
                    {
                        case Direction::UP:
                        case Direction::DOWN:
                            if (field->GetCell(tx - 1, ty) == 0)
                                score++;
                            if (field->GetCell(tx + 1, ty) == 0)
                                score++;
                            break;
                        case Direction::LEFT:
                        case Direction::RIGHT:
                            if (field->GetCell(tx, ty - 1) == 0)
                                score++;
                            if (field->GetCell(tx, ty + 1) == 0)
                                score++;
                            break;
                    }
                }
            }
            else
                break; // Стена — прекращаем сканирование в этом направлении
        }

        if (score > maxScore)
        {
            maxScore = score;
            bestDir = d;
        }
    }

    m_Dir = bestDir;
}