#include "Canvas.h"
#include "stb_image_write.h"
#include <cstring>
#include <fstream>
Canvas::Canvas()
{

}

Canvas::~Canvas()
{

}

void Canvas::Init(int w, int h, unsigned int color)
{
    m_w = w;
    m_h = h;
    m_data.resize(m_w * m_h * 4);
    if(!m_data.empty())
    {
        std::fill_n(reinterpret_cast<unsigned int*>(m_data.data()), m_w * m_h, ToFillColor(color));
    }
}

void Canvas::Draw(int x, int y, unsigned int color)
{
    if(x >= 0 && x < m_w && y >= 0 && y < m_h)
    {
        size_t pos = (x + y * m_w) * 4;
        if(pos < m_data.size())
        {
            unsigned int fillColor = ToFillColor(color);
            std::memcpy(&m_data[pos], &fillColor, 4);
        }
    }
}

void Canvas::OutputFile(const char *file)
{
    std::ofstream outputFile(file, std::ios::binary | std::ios::trunc);
    if(outputFile.is_open() && !m_data.empty())
    {
        auto doWrite = [](void *context, void *data, int size)
        {
            auto des = static_cast<std::vector<unsigned char>*>(context);
            if(des != nullptr)
            {
                des->assign((unsigned char*)data, (unsigned char*)data + size);
            }
        };
        std::vector<unsigned char> fileData;
        stbi_write_png_to_func(doWrite, static_cast<void*>(&fileData), m_w, m_h, 4, static_cast<void*>(m_data.data()), 0);
        if(!fileData.empty())
        {
            outputFile.write(reinterpret_cast<char*>(fileData.data()), fileData.size());
        }
        outputFile.close();
    }
}

unsigned int Canvas::ToFillColor(unsigned int color)
{
    unsigned char r = (color & 0x00ff0000) >> 16;
    unsigned char g = (color & 0x0000ff00) >> 8;
    unsigned char b = (color & 0x000000ff);
    unsigned char a = (color & 0xff000000) >> 24;
    unsigned int fillColor = r | (g << 8) | ( b << 16) | (a << 24);
    return fillColor;
}
