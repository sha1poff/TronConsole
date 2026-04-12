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
    if (m_Player1) delete m_Player1;
    if (m_Player2) delete m_Player2;
}

void TronManager::SetPlayer(int slot, TronPlayer* player) {
    if (slot == 1) m_Player1 = player;
    else if (slot == 2) m_Player2 = player;
}

void TronManager::Run() {
    // Проверка: можем ли мы начать без игроков?
    if (!m_Player1 || !m_Player2) {
        std::cout << "Ошибка: не все игроки созданы!" << std::endl;
        return;
    }

    m_IsRunning = true;
    while (m_IsRunning) {
        ProcessInput();
        Update();
        Render();
        Sleep(80);
    }
}

void TronManager::ProcessInput() {
    m_Player1->UpdateDirection();
    m_Player2->UpdateDirection();
}

void TronManager::Update() {
    // Массив для удобного обхода двух игроков в цикле внутри метода
    TronPlayer* players[] = { m_Player1, m_Player2 };

    for (TronPlayer* p : players) {
        // 1. Оставляем след
        m_Field->SetCell(p->GetX(), p->GetY(), p->GetColor());

        // 2. Двигаемся
        p->Move();

        // 3. Проверка столкновения
        int cell = m_Field->GetCell(p->GetX(), p->GetY());
        if (cell != 0) {
            m_IsRunning = false;
            m_Field->Draw(); // Последний кадр
            std::cout << "\nБАБАХ! Игрок " << p->GetName() << " проиграл!" << std::endl;
            system("pause");
            break;
        }
    }
}

void TronManager::Render() {
    m_Field->Draw();
}