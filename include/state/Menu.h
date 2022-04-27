#ifndef MENU_H
#define MENU_H
#include <GameMap.h>
#include <GameObject.h>
class Menu {
private:
  static Menu *s_Instance;
  bool m_IsInfo;
  GameMap *m_Info;
  GameMap *m_menu;

public:
  static Menu *GetInstance() {
    return s_Instance = (s_Instance != nullptr) ? s_Instance : new Menu();
  }
  Menu() { m_IsInfo = false; };
  bool Init();
  inline void SwitchInfo(bool BOOL) { m_IsInfo = BOOL; }
  void Update(float dt);
  void Render();
  inline GameMap *GetMenu() { return m_menu; }
  void Clear();
};
#endif