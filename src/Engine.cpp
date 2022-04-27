#include <Engine.h>
#include <Input.h>
#include <Levels.h>
#include <Menu.h>
#include <Music.h>
#include <Play.h>
#include <Setting.h>
#include <Timer.h>
Engine *Engine::s_Instance = nullptr;
Engine::Engine() {
  m_IsMenu = true;
  m_IsPlay = false;
  m_IsSetting = false;
  m_IsLevels = false;
}
bool Engine::Init() {
  if (SDL_Init(SDL_INIT_EVERYTHING) == -1 &&
      IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) == -1)
    return false;
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    return false;
  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
    return false;
  if (!Music::GetInstance()->Init())
    return false;
  SDL_WindowFlags window_flags =
      (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
  m_Window = SDL_CreateWindow("GameEngine", SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,
                              SCREEN_HEIGHT, window_flags);
  if (m_Window == nullptr)
    return false;
  m_Renderer = SDL_CreateRenderer(
      m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (m_Renderer == nullptr)
    return false;
  if (!Menu::GetInstance()->Init())
    return false;
  if (!Play::GetInstance()->Init())
    return false;
  Setting::GetInstance()->Init();
  Levels::GetInstance()->Init();
  Music::GetInstance()->PlayBG();
  return m_IsRunning = true;
}

void Engine::Update() {

  float dt = Timer::GetInstance()->GetDelteTime();
  if (m_IsPlay)
    Play::GetInstance()->Update(dt);
  if (m_IsMenu)
    Menu::GetInstance()->Update(dt);
  if (m_IsLevels)
    Levels::GetInstance()->Update(dt);
  if (m_IsSetting)
    Setting::GetInstance()->Update(dt);
}
void Engine::Event() { Input::GetInstance()->Event(); }
void Engine::Render() {
  SDL_SetRenderDrawColor(m_Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderClear(m_Renderer);
  if (m_IsPlay)
    Play::GetInstance()->Render();
  if (m_IsMenu)
    Menu::GetInstance()->Render();
  if (m_IsLevels)
    Levels::GetInstance()->Render();
  if (m_IsSetting)
    Setting::GetInstance()->Render();

  SDL_RenderPresent(m_Renderer);
}
void Engine::Clear() {
  Menu::GetInstance()->Clear();
  Levels::GetInstance()->Clear();
  Setting::GetInstance()->Clear();
  Music::GetInstance()->Clear();
  SDL_DestroyRenderer(m_Renderer);
  m_Renderer = nullptr;
  SDL_DestroyWindow(m_Window);
  m_Window = nullptr;
  SDL_Quit();
  IMG_Quit();
}
void Engine::Quit() { m_IsRunning = false; }