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

// Оценка доступного пространства (очень упрощенный Flood Fill)
int TronComputerPlayer::EvaluateArea(const TronField* field, int startX, int startY)
{
    int area = 0;
    int scanRange = (m_Difficulty == 3) ? 8 : 5; // Чем выше сложность, тем глубже видит

    for (int ix = -scanRange; ix <= scanRange; ix++)
    {
        for (int iy = -scanRange; iy <= scanRange; iy++)
        {
            if (field->GetCell(startX + ix, startY + iy) == 0)
            {
                // Считаем клетки, но чем они дальше, тем меньше их вес
                area += 1;
            }
        }
    }
    return area;
}

// Проверка: не заходим ли мы в узкий тупик шириной в 1 клетку
bool TronComputerPlayer::IsNarrowPassage(const TronField* field, int x, int y, Direction d)
{
    if (d == UP || d == DOWN)
    {
        return (field->GetCell(x - 1, y) != 0 && field->GetCell(x + 1, y) != 0);
    }
    else
    {
        return (field->GetCell(x, y - 1) != 0 && field->GetCell(x, y + 1) != 0);
    }
}

void TronComputerPlayer::UpdateDirection(const TronField* field)
{
    Direction dirs[] = { UP, DOWN, LEFT, RIGHT };
    Direction bestDir = m_Dir;
    float maxScore = -1000000.0f;

    for (Direction d : dirs)
    {
        // 1. Запрет разворота на 180 градусов
        if ((m_Dir == UP && d == DOWN) || (m_Dir == DOWN && d == UP) ||
            (m_Dir == LEFT && d == RIGHT) || (m_Dir == RIGHT && d == LEFT))
            continue;

        int nextX = m_X, nextY = m_Y;
        switch (d)
        {
            case UP:    nextY--; break;
            case DOWN:  nextY++; break;
            case LEFT:  nextX--; break;
            case RIGHT: nextX++; break;
        }

        // 2. Базовая проверка на мгновенное столкновение
        if (field->GetCell(nextX, nextY) != 0) continue;

        // 3. Оценка хода
        float currentScore = 0;

        if (m_Difficulty == 1)
        {
            // Легкий: просто считаем свободные клетки впереди (ваш старый метод)
            for (int i = 1; i <= 5; i++)
            {
                int tx = m_X, ty = m_Y;
                if (d == UP) ty -= i; else if (d == DOWN) ty += i;
                else if (d == LEFT) tx -= i; else if (d == RIGHT) tx += i;
                if (field->GetCell(tx, ty) == 0) currentScore++; else break;
            }
        }
        else {
            // Средний и Сложный: Оценка доступной площади (Flood Fill)
            int area = EvaluateArea(field, nextX, nextY);
            currentScore += area * 10;

            // На сложном уровне добавляем "инстинкт самосохранения" и позиционирование
            if (m_Difficulty == 3) {
                // Бонус за близость к центру (чтобы не прижиматься к краям раньше времени)
                int centerX = field->GetWidth() / 2;
                int centerY = field->GetHeight() / 2;
                int distToCenter = abs(nextX - centerX) + abs(nextY - centerY);
                currentScore -= distToCenter * 0.5f;

                // Штраф за движение в узкие проходы
                if (IsNarrowPassage(field, nextX, nextY, d)) currentScore -= 50;
            }
        }

        if (currentScore > maxScore) {
            maxScore = currentScore;
            bestDir = d;
        }
    }

    m_Dir = bestDir;
}