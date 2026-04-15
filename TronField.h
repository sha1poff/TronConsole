#pragma once


class TronField
{
private:
    int m_Width;
    int m_Height;
    int** m_Grid;

public:
    TronField(int width, int height);
    ~TronField();

    void Init();
    void Draw() const;

    void SetCell(int x, int y, int value);
    int GetCell(int x, int y) const;

    int GetWidth() const { return m_Width; }
    int GetHeight() const { return m_Height; }
};