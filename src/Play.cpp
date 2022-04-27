#include <Camera.h>
#include <CollisionHandler.h>
#include <Enemy.h>
#include <Index.h>
#include <MapParser.h>
#include <ObjectParser.h>
#include <Play.h>
#include <TextureManager.h>
#include <Warrior.h>
#include <iostream>
Play *Play::s_Instance = nullptr;
Play::Play() {
  m_Over = MapParser::GetInstance()->GetMap("over");
  m_IsOver = false;
}
void Play::Update(float dt) {
  m_levelmap->Update();
  for (auto &&i : m_GameObject)
    i->Update(dt);
  if (m_IsOver)
    m_Over->Update();

  Camera::GetInstance()->Update();
}
void Play::Render() {
  m_levelmap->Render();
  for (auto &&i : m_GameObject)
    i->Draw();
  if (m_IsOver)
    m_Over->Render();
}
void Play::Clear() {
  m_levelmap = nullptr;
  m_Over = nullptr;
  for (auto &&i : m_GameObject)
    i->Clear();
  TextureManager::GetInstance()->Clear();
  CollisionHandler::GetInstance()->Clear();
  ObjectParser::GetInstance()->Clear();
  MapParser::GetInstance()->Clean();
  Index::GetInstance()->Clear();
}
bool Play::Init(std::string id) {
  // map
  ObjectParser::GetInstance()->GetObject(id);
  MapParser::GetInstance()->GetMap(id)->Reset();
  m_levelmap = MapParser::GetInstance()->GetMap(id);
  SwitchOver(false);
  m_GameObject.resize(0);
  // enemy
  int k = 0;
  for (auto &&i : ObjectParser::GetInstance()->GetPositionEnemy1()) {
    m_GameObject.push_back(new Enemy("1", k, i.x, i.y, i.w, i.h));
    k++;
  }
  k = 0;
  for (auto &&i : ObjectParser::GetInstance()->GetPositionEnemy2()) {
    m_GameObject.push_back(new Enemy("2", k, i.x, i.y, i.w, i.h));
    k++;
  }
  k = 0;
  for (auto &&i : ObjectParser::GetInstance()->GetPositionEnemy3()) {
    m_GameObject.push_back(new Enemy("3", k, i.x, i.y, i.w, i.h));
    k++;
  }
  // warrior
  SDL_Rect rect = ObjectParser::GetInstance()->GetPositionWarrior();
  Warrior *warrior = new Warrior(rect.x, rect.y, rect.w, rect.h);
  m_GameObject.push_back(warrior);
  // camera player
  Camera::GetInstance()->SetTarget(warrior->GetOrigin());
  return true;
}