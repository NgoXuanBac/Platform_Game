#ifndef COLLISION_HANDLER_H
#define COLLISION_HANDER_H
#include <GameMap.h>
#include <SDL.h>
#include <TileLayer.h>
#include <Vector2D.h>
#include <map>
#include <string>

class CollisionHandler {
public:
  bool CheckCollision(SDL_Rect a, SDL_Rect b);
  bool Static_Collision(SDL_Rect a);
  bool Point_Collision(Vector2D point, SDL_Rect a);
  // Screen
  bool ScreenCollision(SDL_Rect a);
  bool WaterCollision(SDL_Rect a);
  // Object-Character
  bool EnemyCollision(SDL_Rect a);
  bool WarriorCollision(SDL_Rect a);
  void EnemyIsAttacking(const int &tt, const std::string &type);
  bool WarriorIsBeaten();
  void EnemyStopAttack(const int &tt, const std::string &type);
  bool CheckRectEnemyAttack(SDL_Rect a);
  bool WarriorIsAttacking(SDL_Rect a);
  bool EnemyIsBeaten(const int &tt, const std::string &type);
  void WarriorStopAttack();

  // Object-Tile
  bool PixelCollision(SDL_Rect a);
  bool TerrainCollision(SDL_Rect a);
  bool ChestCollision(SDL_Rect b);
  bool FrontTreeTopCollision(SDL_Rect a);

  // Object-Item
  bool CoinCollision(SDL_Rect a);
  bool SwordCollision(SDL_Rect a);

  void Clear();
  void Update();
  inline static CollisionHandler *GetInstance() {
    return s_Instance =
               (s_Instance != nullptr) ? s_Instance : new CollisionHandler();
  }

private:
  CollisionHandler();
  int m_Enemy1IsBeaten;
  int m_Enemy2IsBeaten;
  int m_Enemy3IsBeaten;

  int m_Enemy1IsAttacking;
  int m_Enemy2IsAttacking;
  int m_Enemy3IsAttacking;

  TileMap m_CollisionTerrain;
  TileMap m_CollisionPixel;
  TileMap m_CollisionFrontTree;
  TileMap m_CollisionCoin;
  TileMap m_CollisionSword;
  TileMap m_CollisionChest;

  Tilelayer *m_TerrainLayer;
  Tilelayer *m_PixelLayer;
  Tilelayer *m_FrontTreeTopLayer;
  Tilelayer *m_CoinLayer;
  Tilelayer *m_SwordLayer;
  Tilelayer *m_ChestLayer;

  std::vector<SDL_Rect> m_PositionEnemy;
  SDL_Rect m_PositionWarrior;
  SDL_Rect m_RectEnemyAttack;
  std::map<std::string, int> LAYER;
  static CollisionHandler *s_Instance;
};
#endif