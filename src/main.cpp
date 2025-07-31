#include "Canvas.h"

int main()
{
    Canvas canvas;
    canvas.Init(11, 11, 0xffff0000);
    canvas.Draw(5, 5, 0xff00ff00);
    canvas.OutputFile("canvas.png");

    return 0;
}
