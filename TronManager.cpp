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
    int winner = 0; // 0 - ничья, 1 - игрок 1, 2 - игрок 2

    while (m_IsRunning)
    {
        // 1. Опрос ввода (изменение векторов движения)
        ProcessInput();

        // 2. Рассчитываем СЛЕДУЮЩИЕ координаты (не двигая игроков)
        int nextX1 = m_Player1->GetX();
        int nextY1 = m_Player1->GetY();
        int nextX2 = m_Player2->GetX();
        int nextY2 = m_Player2->GetY();

        // Симулируем движение для проверки
        auto getNextPos = [](int& x, int& y, Direction dir) {
            if (dir == Direction::UP) y--;
            else if (dir == Direction::DOWN) y++;
            else if (dir == Direction::LEFT) x--;
            else if (dir == Direction::RIGHT) x++;
            };

        // Внимание: здесь мы берем текущие направления игроков
        // (которые обновились в ProcessInput)
        // Но так как у вас Move() внутри игрока просто меняет координаты, 
        // мы реализуем проверку ПЕРЕД вызовом Move()

        // Для чистоты кода, предположим, что мы временно храним новые координаты
        int x1 = nextX1; int y1 = nextY1;
        int x2 = nextX2; int y2 = nextY2;

        // В вашем TronPlayer.h/cpp Move() меняет внутренние переменные.
        // Поэтому мы сначала вызываем Move(), а потом проверяем коллизии.
        m_Player1->Move();
        m_Player2->Move();

        x1 = m_Player1->GetX(); y1 = m_Player1->GetY();
        x2 = m_Player2->GetX(); y2 = m_Player2->GetY();

        // 3. ПРОВЕРКА СТОЛКНОВЕНИЙ

        // Проверка выхода за границы
        bool p1Out = (x1 < 0 || x1 >= m_Field->GetWidth() || y1 < 0 || y1 >= m_Field->GetHeight());
        bool p2Out = (x2 < 0 || x2 >= m_Field->GetWidth() || y2 < 0 || y2 >= m_Field->GetHeight());

        // Проверка столкновения со следами (только если не вылетели за границы)
        bool p1HitTrail = (!p1Out && m_Field->GetCell(x1, y1) != 0);
        bool p2HitTrail = (!p2Out && m_Field->GetCell(x2, y2) != 0);

        // Проверка "лобового" столкновения (оба в одной клетке)
        bool headOn = (x1 == x2 && y1 == y2);

        // Флаги смерти
        bool p1Dead = p1Out || p1HitTrail || headOn;
        bool p2Dead = p2Out || p2HitTrail || headOn;

        // 4. ОПРЕДЕЛЕНИЕ ПОБЕДИТЕЛЯ
        if (p1Dead || p2Dead)
        {
            m_IsRunning = false;
            if (p1Dead && p2Dead) winner = 0; // Оба погибли одновременно
            else if (p1Dead)      winner = 2; // Первый врезался -> второй выиграл
            else                  winner = 1; // Второй врезался -> первый выиграл
            break;
        }

        // 5. ОБНОВЛЕНИЕ ПОЛЯ
        // Если никто не умер, фиксируем их позиции на поле (оставляем след)
        m_Field->SetCell(x1, y1, m_Player1->GetColor());
        m_Field->SetCell(x2, y2, m_Player2->GetColor());

        // 6. ОТРИСОВКА И ПАУЗА
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

void TronManager::Render() {
    m_Field->Draw();
}