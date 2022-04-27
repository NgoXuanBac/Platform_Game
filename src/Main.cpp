#include <Engine.h>
#include <Timer.h>
int main(int argc, char **argv)
{
    Engine::GetInstance()->Init();
    while (Engine::GetInstance()->IsRunning())
    {
        Engine::GetInstance()->Event();
        Engine::GetInstance()->Update();
        Engine::GetInstance()->Render();
        Timer::GetInstance()->Update();
    }
    Engine::GetInstance()->Clear();
    return 0;
}