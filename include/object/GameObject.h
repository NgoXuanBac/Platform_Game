#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H
class GameObject
{
public:
    virtual void Draw() = 0;
    virtual void Update(float dt) = 0;
    virtual void Clear() = 0;
};
#endif