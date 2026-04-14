#include "pch.h"
#include "TronManager.h"


TronManager::TronManager(int width, int height) 
    : m_IsRunning(false), m_Player1(nullptr), m_Player2(nullptr) 
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

int TronManager::Run()
{
    
    m_IsRunning = true;
    int winner = 0;

    while (m_IsRunning)
    {
        // 1. Сначала управление. 
        // Если GetCell в поле защищен (см. выше), бот не уронит программу.
        ProcessInput();

        // 2. Движение
        m_Player1->Move();
        m_Player2->Move();

        int x1 = m_Player1->GetX();
        int y1 = m_Player1->GetY();
        int x2 = m_Player2->GetX();
        int y2 = m_Player2->GetY();

        // 3. Проверка стен (Чистая математика, без обращения к массиву)
        bool p1Wall = (x1 < 0 || x1 >= m_Field->GetWidth() || y1 < 0 || y1 >= m_Field->GetHeight());
        bool p2Wall = (x2 < 0 || x2 >= m_Field->GetWidth() || y2 < 0 || y2 >= m_Field->GetHeight());

        if (p1Wall || p2Wall)
        {
            m_IsRunning = false;
            if (p1Wall && p2Wall)
                winner = 0;
            else if (p1Wall)
                winner = 2;
            else 
                winner = 1;
            break;
        }

        // 4. Отрисовка следа (Только если мы внутри поля!)
        m_Field->SetCell(x1, y1, m_Player1->GetColor());
        m_Field->SetCell(x2, y2, m_Player2->GetColor());

        Render();
        Sleep(70);
    }
    return winner;
    
}

void TronManager::ProcessInput()
{
    m_Player1->UpdateDirection(m_Field);
    m_Player2->UpdateDirection(m_Field);
}

void TronManager::Update()
{
}

void TronManager::Render() {
    m_Field->Draw();
}