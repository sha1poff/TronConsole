#include "TronComputerPlayer.h"
#include "TronField.h"


TronComputerPlayer::TronComputerPlayer(
    std::string name,
    int x, int y,
    Direction dir,
    int color)
    : TronPlayer(name, x, y, dir, color)
{
}

TronComputerPlayer::~TronComputerPlayer()
{
}

void TronComputerPlayer::UpdateDirection(const TronField* field)
{
    // 1. Вычисляем координаты клетки прямо перед нами
    int nextX = m_X;
    int nextY = m_Y;

    if (m_Dir == Direction::UP) nextY--;
    else if (m_Dir == Direction::DOWN) nextY++;
    else if (m_Dir == Direction::LEFT) nextX--;
    else if (m_Dir == Direction::RIGHT) nextX++;

    // 2. Если впереди опасность (не пустота)
    if (field->GetCell(nextX, nextY) != 0) {

        // Переменные для проверки соседних клеток
        int leftX = m_X, leftY = m_Y;
        int rightX = m_X, rightY = m_Y;
        Direction dirLeft, dirRight;

        // Определяем, где "лево" и "право" относительно нашего текущего движения
        if (m_Dir == Direction::UP || m_Dir == Direction::DOWN) {
            leftX = m_X - 1; dirLeft = Direction::LEFT;
            rightX = m_X + 1; dirRight = Direction::RIGHT;
        }
        else {
            leftY = m_Y - 1; dirLeft = Direction::UP;
            rightY = m_Y + 1; dirRight = Direction::DOWN;
        }

        // 3. Проверяем, куда безопаснее свернуть
        bool canGoLeft = (field->GetCell(leftX, leftY) == 0);
        bool canGoRight = (field->GetCell(rightX, rightY) == 0);

        if (canGoLeft && !canGoRight) {
            m_Dir = dirLeft;
        }
        else if (canGoRight && !canGoLeft) {
            m_Dir = dirRight;
        }
        else if (canGoLeft && canGoRight) {
            // Если свободны оба пути, выбираем случайно
            // Не забудь добавить #include <cstdlib> для rand()
            if (rand() % 2 == 0) m_Dir= dirLeft;
            else m_Dir = dirRight;
        }
        // Если оба пути закрыты — мы в тупике, ничего не меняем, игрок разобьется
    }
}