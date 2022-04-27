#ifndef TRANFORM_H
#define TRAMFORM_H
#include <Vector2D.h>
class TranForm
{
public:
    float X, Y;

public:
    TranForm(float x = 0, float y = 0) : X(x), Y(y) {}
    void log(std::string mag = "")
    {
        std::cout << mag << "(X,Y)={" << X << "," << Y << "}" << std::endl;
    };

public:
    inline void TranslateX(float x) { X += x; }
    inline void TranslateY(float y) { Y += y; }
    inline void Translate(Vector2D v)
    {
        X += v.X;
        Y += v.Y;
    }
};

#endif