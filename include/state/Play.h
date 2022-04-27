#ifndef PLAY_H
#define PLAY_H
#include <GameMap.h>
#include <GameObject.h>
class Play {
private:
  static Play *s_Instance;
  GameMap *m_Over;
  GameMap *m_levelmap;
  bool m_IsOver;
  std::vector<GameObject *> m_GameObject;

public:
  static Play *GetInstance() {
    return s_Instance = (s_Instance != nullptr) ? s_Instance : new Play();
  }
  Play();
  inline void SwitchOver(bool BOOL) { m_IsOver = BOOL; }
  inline bool GetOver() { return m_IsOver; }
  bool Init(std::string id = "level_0");
  void Update(float dt);
  void Render();
  inline GameMap *GetMap() { return m_levelmap; }
  void Clear();
};
#endif