#ifndef SETTING_H
#define SETTING_H
#include <GameMap.h>
#include <GameObject.h>
class Setting {
private:
  static Setting *s_Instance;
  GameMap *m_setting;

public:
  static Setting *GetInstance() {
    return s_Instance = (s_Instance != nullptr) ? s_Instance : new Setting();
  }
  Setting(){};
  void Init();
  void Update(float dt);
  void Render();
  inline GameMap *GetMenu() { return m_setting; }
  void Clear();
};
#endif