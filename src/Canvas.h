#pragma once
#include <vector>

class Canvas
{
public:
    Canvas();
    ~Canvas();
    void Init(int w, int h, unsigned int color);
    void Draw(int x, int y, unsigned int color);
    void OutputFile(const char* file);
public:
    static unsigned int ToFillColor(unsigned int color);
private:
    int m_w {0};
    int m_h {0};
    std::vector<unsigned char> m_data;
};
