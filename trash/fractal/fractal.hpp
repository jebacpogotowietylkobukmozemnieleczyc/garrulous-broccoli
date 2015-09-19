#ifndef FRACTAL_HPP
#define FRACTAL_HPP
#include<functional>

class Fractal
{
public:
    Fractal(std::function<void()> solid,int depth,float startx,float starty,float startz,float size) : solid_(solid),depth_(depth),startx_(startx),startz_(startz),size_(size) {};

void FractalStep (int depth,float startx, float starty,float startz,float size);
void DrawFractal();
private:
    std::function<void()> solid_;
    int depth_;
    float size_;
    float startx_;
    float starty_;
    float startz_;
};

#endif // FRACTAL_HPP
