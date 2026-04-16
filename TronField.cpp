#include "pch.h"
#include "TronField.h"


TronField::TronField(int width, int height)
    : m_Width(width), m_Height(height)
{
    m_Grid = new int* [m_Height];

    for (int i = 0; i < m_Height; ++i)
        m_Grid[i] = new int[m_Width];

    Init();
}

TronField::~TronField()
{
    for (int i = 0; i < m_Height; ++i) 
        delete[] m_Grid[i];
    delete[] m_Grid;

    m_Grid = nullptr;
}

void TronField::Init()
{
    for (int y = 0; y < m_Height; y++) {
        for (int x = 0; x < m_Width; x++) {
            if (y == 0 || y == m_Height - 1 || x == 0 || x == m_Width - 1)
                m_Grid[y][x] = 1; // стена
            else
                m_Grid[y][x] = 0; // пустота
        }
    }
}

void TronField::Draw() const
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD bufferSize = { (SHORT)m_Width, (SHORT)m_Height };
    COORD characterPos = { 0, 0 };
    SMALL_RECT writeRegion = { 0, 0, (SHORT)(m_Width - 1), (SHORT)(m_Height - 1) };

    // Создаем массив структур (символ + атрибуты цвета)
    CHAR_INFO* chipBuffer = new CHAR_INFO[m_Width * m_Height];

    for (int y = 0; y < m_Height; y++) {
        for (int x = 0; x < m_Width; x++) {
            int index = y * m_Width + x;
            int val = m_Grid[y][x];

            // Устанавливаем символ
            chipBuffer[index].Char.AsciiChar = (val == 0 ? ' ' : (val == 1 ? '#' : '@'));

            // Устанавливаем цвет
            if (val == 1) chipBuffer[index].Attributes = 8;
            else if (val == 0) chipBuffer[index].Attributes = 7;
            else chipBuffer[index].Attributes = (WORD)val;
        }
    }

    // ОДИН вызов функции на весь экран!
    WriteConsoleOutputA(hConsole, chipBuffer, bufferSize, characterPos, &writeRegion);

    delete[] chipBuffer;
}

void TronField::SetCell(int x, int y, int value)
{
    if (x >= 0 && x < m_Width && y >= 0 && y < m_Height)
        m_Grid[y][x] = value;
}

int TronField::GetCell(int x, int y) const
{
    if (x >= 0 && x < m_Width && y >= 0 && y < m_Height)
        return m_Grid[y][x];
    return 1;
}