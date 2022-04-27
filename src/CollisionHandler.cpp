#include <CollisionHandler.h>
#include <MapParser.h>
#include <Menu.h>
#include <ObjectParser.h>
#include <Play.h>
// Parameter of tilemap
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 320
#define TILE_SIZE 32
#define ROW_COUNT 9
#define COL_COUNT 59
CollisionHandler *CollisionHandler::s_Instance = nullptr;
CollisionHandler::CollisionHandler() { Update(); }
void CollisionHandler::Update() {
  std::vector<Layer *> layers = Play::GetInstance()->GetMap()->GetMapLayers();
  for (int i = 0; i < layers.size(); i++) {
    LAYER[layers.at(i)->GetName()] = i;
  }
  m_Enemy1IsBeaten = -1;
  m_Enemy2IsBeaten = -1;
  m_Enemy3IsBeaten = -1;

  m_Enemy1IsAttacking = -1;
  m_Enemy2IsAttacking = -1;
  m_Enemy3IsAttacking = -1;
  m_TerrainLayer = (Tilelayer *)layers.at(LAYER["Terrain"]);
  m_CollisionTerrain = m_TerrainLayer->GetTileMap();

  m_FrontTreeTopLayer = (Tilelayer *)layers.at(LAYER["Front tree top"]);
  m_CollisionFrontTree = m_FrontTreeTopLayer->GetTileMap();

  m_CoinLayer = (Tilelayer *)layers.at(LAYER["Coin"]);
  m_CollisionCoin = m_CoinLayer->GetTileMap();

  m_SwordLayer = (Tilelayer *)layers.at(LAYER["Sword"]);
  m_CollisionSword = m_SwordLayer->GetTileMap();

  m_PixelLayer = (Tilelayer *)layers.at(LAYER["Pixel"]);
  m_CollisionPixel = m_PixelLayer->GetTileMap();

  m_ChestLayer = (Tilelayer *)layers.at(LAYER["Chest"]);
  m_CollisionChest = m_ChestLayer->GetTileMap();
}
void CollisionHandler::Clear() {
  m_TerrainLayer = nullptr;
  m_FrontTreeTopLayer = nullptr;
  m_CoinLayer = nullptr;
  m_PixelLayer = nullptr;
  m_SwordLayer = nullptr;
}
bool CollisionHandler::Point_Collision(Vector2D point, SDL_Rect a) {
  if (point.X < a.x || point.X > (a.x + a.w))
    return false;
  if (point.Y < a.y || point.Y > (a.y + a.h))
    return false;
  return true;
}
void CollisionHandler::EnemyIsAttacking(const int &tt,
                                        const std::string &type) {
  if (type == "1")
    m_Enemy1IsAttacking = tt;
  if (type == "2")
    m_Enemy2IsAttacking = tt;
  if (type == "3")
    m_Enemy3IsAttacking = tt;
}
void CollisionHandler::WarriorStopAttack() {
  m_Enemy1IsBeaten = -1;
  m_Enemy2IsBeaten = -1;
  m_Enemy3IsBeaten = -1;
}

bool CollisionHandler::WarriorIsBeaten() {
  if (m_Enemy1IsAttacking != -1) {
    return true;
  }
  if (m_Enemy2IsAttacking != -1) {
    return true;
  }
  if (m_Enemy3IsAttacking != -1) {
    return true;
  }
  return false;
}
void CollisionHandler::EnemyStopAttack(const int &tt, const std::string &type) {
  if (type == "1" && m_Enemy1IsAttacking == tt) {
    m_Enemy1IsAttacking = -1;
  }
  if (type == "2" && m_Enemy2IsAttacking == tt) {
    m_Enemy2IsAttacking = -1;
  }
  if (type == "3" && m_Enemy3IsAttacking == tt) {
    m_Enemy3IsAttacking = -1;
  }
}

bool CollisionHandler::EnemyCollision(SDL_Rect a) {
  m_PositionEnemy = ObjectParser::GetInstance()->GetPositionEnemy1();
  for (auto &&i : m_PositionEnemy) {
    if (CheckCollision(a, i))
      return true;
  }
  m_PositionEnemy = ObjectParser::GetInstance()->GetPositionEnemy2();
  for (auto &&i : m_PositionEnemy) {
    if (CheckCollision(a, i))
      return true;
  }
  m_PositionEnemy = ObjectParser::GetInstance()->GetPositionEnemy3();
  for (auto &&i : m_PositionEnemy) {
    if (CheckCollision(a, i))
      return true;
  }
  return false;
}
bool CollisionHandler::WarriorIsAttacking(SDL_Rect a) {
  m_PositionEnemy = ObjectParser::GetInstance()->GetPositionEnemy1();
  int k = 0;
  for (auto &&i : m_PositionEnemy) {
    if (CheckCollision(a, i)) {
      m_Enemy1IsBeaten = k;
      return true;
    }
    k++;
  }
  m_PositionEnemy = ObjectParser::GetInstance()->GetPositionEnemy2();
  k = 0;
  for (auto &&i : m_PositionEnemy) {
    if (CheckCollision(a, i)) {
      m_Enemy2IsBeaten = k;
      return true;
    }
    k++;
  }
  m_PositionEnemy = ObjectParser::GetInstance()->GetPositionEnemy3();
  k = 0;
  for (auto &&i : m_PositionEnemy) {
    if (CheckCollision(a, i)) {
      m_Enemy3IsBeaten = k;
      return true;
    }
    k++;
  }
  return false;
}
bool CollisionHandler::EnemyIsBeaten(const int &tt, const std::string &type) {
  if (type == "1" && m_Enemy1IsBeaten == tt) {
    return true;
  }
  if (type == "2" && m_Enemy2IsBeaten == tt) {
    return true;
  }
  if (type == "3" && m_Enemy3IsBeaten == tt) {
    return true;
  }
  return false;
}
bool CollisionHandler::WarriorCollision(SDL_Rect a) {
  m_PositionWarrior = ObjectParser::GetInstance()->GetPositionWarrior();
  if (CheckCollision(a, m_PositionWarrior))
    return true;
  return false;
}
bool CollisionHandler::PixelCollision(SDL_Rect a) {
  int left_tile = a.x / TILE_SIZE;
  int right_tile = (a.x + a.w) / TILE_SIZE;
  int top_tile = a.y / TILE_SIZE;
  int bottom_tile = (a.y + a.h) / TILE_SIZE;

  if (left_tile < 0)
    left_tile = 0;
  if (right_tile > COL_COUNT)
    right_tile = COL_COUNT;
  if (top_tile < 0)
    top_tile = 0;
  if (bottom_tile > ROW_COUNT)
    bottom_tile = ROW_COUNT;
  for (int j = top_tile; j <= bottom_tile; j++) {
    for (int i = left_tile; i <= right_tile; i++) {
      if (m_CollisionPixel[j][i] > 0) {
        return true;
      }
    }
  }

  return false;
}
bool CollisionHandler::SwordCollision(SDL_Rect a) {
  int left_tile = (a.x + 12) / TILE_SIZE;
  int right_tile = (a.x + a.w - 1) / TILE_SIZE;
  int top_tile = (a.y + 6) / TILE_SIZE;
  int bottom_tile = (a.y + a.h - 19) / TILE_SIZE;

  if (left_tile < 0)
    left_tile = 0;
  if (right_tile > COL_COUNT)
    right_tile = COL_COUNT;
  if (top_tile < 0)
    top_tile = 0;
  if (bottom_tile > ROW_COUNT)
    bottom_tile = ROW_COUNT;

  for (int j = top_tile; j <= bottom_tile; j++) {
    for (int i = left_tile; i <= right_tile; i++) {
      if (m_CollisionSword[j][i] > 0) {
        m_SwordLayer->DeleteTile(j, i);
        m_CollisionSword[j][i] = 0;
        return true;
      }
    }
  }
  return false;
}
bool CollisionHandler::CoinCollision(SDL_Rect a) {
  int left_tile = (a.x + 18) / TILE_SIZE;
  int right_tile = (a.x + a.w - 3) / TILE_SIZE;
  int top_tile = (a.y + 2) / TILE_SIZE;
  int bottom_tile = (a.y + a.h - 19) / TILE_SIZE;

  if (left_tile < 0)
    left_tile = 0;
  if (right_tile > COL_COUNT)
    right_tile = COL_COUNT;
  if (top_tile < 0)
    top_tile = 0;
  if (bottom_tile > ROW_COUNT)
    bottom_tile = ROW_COUNT;

  for (int j = top_tile; j <= bottom_tile; j++) {
    for (int i = left_tile; i <= right_tile; i++) {
      if (m_CollisionCoin[j][i] > 0) {
        m_CoinLayer->DeleteTile(j, i);
        m_CollisionCoin[j][i] = 0;
        return true;
      }
    }
  }
  return false;
}
bool CollisionHandler::Static_Collision(SDL_Rect a) {
  if (FrontTreeTopCollision(a) || TerrainCollision(a) || ScreenCollision(a))
    return true;
  return false;
}
bool CollisionHandler::CheckCollision(SDL_Rect a, SDL_Rect b) {
  bool x_overlaps = (a.x < b.x + b.w) && (a.x + a.w > b.x);
  bool y_overlaps = (a.y < b.y + b.h) && (a.y + a.h > b.y);
  return (x_overlaps && y_overlaps);
}
bool CollisionHandler::ChestCollision(SDL_Rect a) {
  int left_tile = a.x / TILE_SIZE;
  int right_tile = (a.x + a.w) / TILE_SIZE;
  int top_tile = a.y / TILE_SIZE;
  int bottom_tile = (a.y + a.h - 8) / TILE_SIZE;

  if (left_tile < 0)
    left_tile = 0;
  if (right_tile > COL_COUNT)
    right_tile = COL_COUNT;
  if (top_tile < 0)
    top_tile = 0;
  if (bottom_tile > ROW_COUNT)
    bottom_tile = ROW_COUNT;
  // kiem tra collision
  for (int j = top_tile; j <= bottom_tile; j++) {
    for (int i = left_tile; i <= right_tile; i++) {
      if (m_CollisionChest[j][i] > 0)
        return true;
    }
  }
  return false;
}
bool CollisionHandler::FrontTreeTopCollision(SDL_Rect a) {
  int left_tile = (a.x - 5) / TILE_SIZE;
  int right_tile = (a.x + a.w - 2) / TILE_SIZE;
  int top_tile = a.y / TILE_SIZE;
  int bottom_tile = (a.y + a.h) / TILE_SIZE;

  if (left_tile < 0)
    left_tile = 0;
  if (right_tile > COL_COUNT)
    right_tile = COL_COUNT;
  if (top_tile < 0)
    top_tile = 0;
  if (bottom_tile > ROW_COUNT)
    bottom_tile = ROW_COUNT;

  for (int j = top_tile; j <= bottom_tile; j++) {
    for (int i = left_tile; i <= right_tile; i++) {
      if (m_CollisionFrontTree[j][i] > 0)
        return true;
    }
  }
  return false;
}
bool CollisionHandler::TerrainCollision(SDL_Rect a) {

  int left_tile = a.x / TILE_SIZE;
  int right_tile = (a.x + a.w) / TILE_SIZE;
  int top_tile = a.y / TILE_SIZE;
  int bottom_tile = (a.y + a.h) / TILE_SIZE;

  if (left_tile < 0)
    left_tile = 0;
  if (right_tile > COL_COUNT)
    right_tile = COL_COUNT;
  if (top_tile < 0)
    top_tile = 0;
  if (bottom_tile > ROW_COUNT)
    bottom_tile = ROW_COUNT;
  // kiem tra collision
  for (int j = top_tile; j <= bottom_tile; j++) {
    for (int i = left_tile; i <= right_tile; i++) {
      if (m_CollisionTerrain[j][i] > 0)
        return true;
    }
  }
  return false;
}
bool CollisionHandler::CheckRectEnemyAttack(SDL_Rect a) {
  m_RectEnemyAttack = ObjectParser::GetInstance()->GetRectEnemyAttack();
  return CheckCollision(a, m_RectEnemyAttack);
}
bool CollisionHandler::ScreenCollision(SDL_Rect a) {
  if (a.x < 0 || (a.x + a.w) > SCREEN_WIDTH)
    return true;
  if (a.y < 0 || (a.y + a.h) > SCREEN_HEIGHT)
    return true;
  return false;
}
bool CollisionHandler::WaterCollision(SDL_Rect a) {
  if ((a.y + a.h + 5) >= SCREEN_HEIGHT)
    return true;
  return false;
}