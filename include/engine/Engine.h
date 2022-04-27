#ifndef ENGINE_H
#define ENGINE_H
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 320
class Engine {
public:
  static Engine *GetInstance() {
    return s_Instance = (s_Instance != nullptr) ? s_Instance : new Engine();
  }
  bool Init();
  void Quit();
  void Clear();

  void Render();
  void Update();
  void Event();

  inline bool IsRunning() { return m_IsRunning; }
  void Switch_Menu(bool BOOL) {
    m_IsMenu = BOOL;
    m_IsPlay = (m_IsMenu == true) ? false : true;
  }
  void Switch_Play(bool BOOL) {
    m_IsPlay = BOOL;
    m_IsMenu = (m_IsPlay == true) ? false : true;
  }
  inline void Switch_Levels(bool BOOL) { m_IsLevels = BOOL; }
  inline void Switch_Setting(bool BOOL) { m_IsSetting = BOOL; }
  inline bool GetMenu() { return m_IsMenu; }
  inline bool GetSetting() { return m_IsSetting; }
  inline bool GetLevels() { return m_IsLevels; }
  inline bool GetPlay() { return m_IsPlay; }
  inline SDL_Window *GetMainWindow() { return m_Window; }
  inline SDL_Renderer *GetRenderer() { return m_Renderer; }

private:
  Engine();
  bool m_IsRunning, m_IsMenu, m_IsPlay, m_IsSetting, m_IsLevels;
  static Engine *s_Instance;
  SDL_Window *m_Window;
  SDL_Renderer *m_Renderer;
};

#endif