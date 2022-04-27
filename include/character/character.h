#ifndef CHARACTER_H
#define CHARACTER_H
#include <GameObject.h>
#include <Tranform.h>
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <Point.h>
class Character : public GameObject
{
public:
    Character(float x, float y, int width, int height, SDL_RendererFlip flip = SDL_FLIP_NONE) : m_Width(width), m_Height(height), m_Flip(flip)
    {
        m_Transform = new TranForm(x, y);
        float px = x + width / 2;
        float py = y + height / 2;
        m_Origin = new Point(px, py);
    }
    inline Point *GetOrigin() { return m_Origin; }
    virtual void Draw() = 0;
    virtual void Clear() = 0;
    virtual void Update(float dt) = 0;

protected:
    std::string m_Name;
    Point *m_Origin;
    TranForm *m_Transform;
    float m_Width, m_Height;
    SDL_RendererFlip m_Flip;
};
#endif