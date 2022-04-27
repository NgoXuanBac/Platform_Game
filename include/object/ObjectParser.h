#ifndef OBJECT_PARSER_H
#define OBJECT_PARSER_H
#include <SDL.h>
#include <map>
#include <string>
#include <vector>
using Tilemap = std::vector<std::vector<int>>;
struct Object {
  SDL_Rect m_PositionWarrior;
  std::vector<SDL_Rect> m_PositionEnemy1;
  std::vector<SDL_Rect> m_PositionEnemy2;
  std::vector<SDL_Rect> m_PositionEnemy3;
};
class ObjectParser {
private:
  bool Parse(std::string id, std::string source);

private:
  static ObjectParser *s_Instance;
  // Phan khong bao gio thay do
  std::map<std::string, Object> m_Objects;
  // Phan thay doi lien tuc
  //-> Warrior
  SDL_Rect m_PositionWarrior;
  int m_WarriorDirection;
  //-> Enemy
  std::vector<SDL_Rect> m_PositionEnemy1;
  std::vector<SDL_Rect> m_PositionEnemy2;
  std::vector<SDL_Rect> m_PositionEnemy3;
  SDL_Rect m_RectEnemyAttack;

public:
  ObjectParser() {}
  inline static ObjectParser *GetInstance() {
    return s_Instance =
               (s_Instance != nullptr) ? s_Instance : new ObjectParser();
  }
  inline SDL_Rect GetPositionWarrior() { return m_PositionWarrior; }
  inline std::vector<SDL_Rect> GetPositionEnemy1() { return m_PositionEnemy1; }
  inline std::vector<SDL_Rect> GetPositionEnemy2() { return m_PositionEnemy2; }
  inline std::vector<SDL_Rect> GetPositionEnemy3() { return m_PositionEnemy3; }

  inline void SetRectWarrior(const SDL_Rect &r) { m_PositionWarrior = r; }
  void SetRectEnemy(const SDL_Rect &r, const int &i, const std::string &type);

  void SetWarriorDirection(SDL_RendererFlip flip);
  inline int WarriorDirection() { return m_WarriorDirection; }
  inline void SetRectEnemyAttack(const SDL_Rect &r) { m_RectEnemyAttack = r; }
  inline SDL_Rect GetRectEnemyAttack() { return m_RectEnemyAttack; }

  void GetObject(std::string id);
  bool Load();
  void Clear();
};
#endif