#include "pch.h"
#include "CellType.h"
#include "TronManager.h"


TronManager::TronManager(int width, int height) 
    : m_IsRunning(false),
      m_Player1(nullptr),
      m_Player2(nullptr) 
{
    m_Field = new TronField(width, height);
}

TronManager::~TronManager() 
{
    delete m_Field;
    if (m_Player1)
        delete m_Player1;
    if (m_Player2)
        delete m_Player2;
}

void TronManager::SetPlayer(int slot, TronPlayer* player)
{
    if (slot == 1)
        m_Player1 = player;
    else if (slot == 2)
        m_Player2 = player;
}

int TronManager::Run() {
    m_IsRunning = true;
    int winner = 0;

    while (m_IsRunning) {
        ProcessInput();

        // Запоминаем текущие позиции (где сейчас головы)
        int oldX1 = m_Player1->GetX(), oldY1 = m_Player1->GetY();
        int oldX2 = m_Player2->GetX(), oldY2 = m_Player2->GetY();

        // Совершаем движение
        m_Player1->Move();
        m_Player2->Move();

        int x1 = m_Player1->GetX(), y1 = m_Player1->GetY();
        int x2 = m_Player2->GetX(), y2 = m_Player2->GetY();

        // Проверка столкновений
        bool p1Hit = (x1 < 0 || x1 >= m_Field->GetWidth() || y1 < 0 || y1 >= m_Field->GetHeight() || m_Field->GetCell(x1, y1) != EMPTY);
        bool p2Hit = (x2 < 0 || x2 >= m_Field->GetWidth() || y2 < 0 || y2 >= m_Field->GetHeight() || m_Field->GetCell(x2, y2) != EMPTY);

        if (x1 == x2 && y1 == y2) p1Hit = p2Hit = true;

        if (p1Hit || p2Hit) {
            m_IsRunning = false;
            winner = (p1Hit && p2Hit) ? 0 : (p1Hit ? 2 : 1);
            break;
        }

        // Обновляем сетку: старая голова -> след, новая позиция -> голова
        m_Field->SetCell(oldX1, oldY1, P1_TRAIL);
        m_Field->SetCell(oldX2, oldY2, P2_TRAIL);
        m_Field->SetCell(x1, y1, P1_HEAD);
        m_Field->SetCell(x2, y2, P2_HEAD);

        Render();
        Sleep(60); // Скорость игры
    }
    return winner;
}

void TronManager::ProcessInput()
{
    m_Player1->UpdateDirection(m_Field);
    m_Player2->UpdateDirection(m_Field);
}

void TronManager::Render() {
    m_Field->Draw();
}