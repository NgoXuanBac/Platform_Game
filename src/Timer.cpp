#include <Timer.h>
#include <SDL.h>
Timer *Timer::s_Instance = nullptr;
void Timer::Update()
{
    m_DeltaTime = (SDL_GetTicks() - m_LastTime) * (TARGET_FPS / 1000.0f);
    if (m_DeltaTime > TARGET_DELTATINE)
        m_DeltaTime = TARGET_DELTATINE;
    m_LastTime = SDL_GetTicks();
}
