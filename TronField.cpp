#include "pch.h"
#include "CellType.h"
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

void TronField::Init() {
    for (int y = 0; y < m_Height; y++) {
        for (int x = 0; x < m_Width; x++) {
            if (y == 0 || y == m_Height - 1 || x == 0 || x == m_Width - 1)
                m_Grid[y][x] = WALL;
            else
                m_Grid[y][x] = EMPTY;
        }
    }
}

void TronField::Draw() const
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD bufferSize = { (SHORT)m_Width, (SHORT)m_Height };
    COORD characterPos = { 0, 0 };
    SMALL_RECT writeRegion = { 0, 0, (SHORT)(m_Width - 1), (SHORT)(m_Height - 1) };

    CHAR_INFO* chipBuffer = new CHAR_INFO[m_Width * m_Height];

    for (int y = 0; y < m_Height; y++) {
        for (int x = 0; x < m_Width; x++) {
            int index = y * m_Width + x;
            int val = m_Grid[y][x];

            // Рисуем всё тем же символом блока, но через unsigned char
            unsigned char block = 219;

            switch (val) {
            case WALL:
                chipBuffer[index].Char.AsciiChar = '#';
                chipBuffer[index].Attributes = 8; // Темно-серый
                break;
            case P1_HEAD:
                chipBuffer[index].Char.AsciiChar = block;
                chipBuffer[index].Attributes = 10; // Ярко-зеленый
                break;
            case P1_TRAIL:
                chipBuffer[index].Char.AsciiChar = block;
                chipBuffer[index].Attributes = 2;  // Тускло-зеленый
                break;
            case P2_HEAD:
                chipBuffer[index].Char.AsciiChar = block;
                chipBuffer[index].Attributes = 13; // Ярко-розовый
                break;
            case P2_TRAIL:
                chipBuffer[index].Char.AsciiChar = block;
                chipBuffer[index].Attributes = 5;  // Тускло-пурпурный
                break;
            default: // EMPTY
                chipBuffer[index].Char.AsciiChar = ' ';
                chipBuffer[index].Attributes = 7;
                break;
            }
        }
    }

    // Используем WriteConsoleOutputA (ASCII версию)
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