#ifndef LEVELS_H
#define LEVELS_H
#include <GameMap.h>
#include <GameObject.h>
class Levels {
private:
  static Levels *s_Instance;
  GameMap *m_levels;

public:
  static Levels *GetInstance() {
    return s_Instance = (s_Instance != nullptr) ? s_Instance : new Levels();
  }
  Levels(){};
  void Init();
  void Update(float dt);
  void Render();
  inline GameMap *GetMenu() { return m_levels; }
  void Clear();
};
#endif