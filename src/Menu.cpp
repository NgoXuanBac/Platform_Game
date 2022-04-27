#include <Camera.h>
#include <CollisionHandler.h>
#include <Index.h>
#include <MapParser.h>
#include <Menu.h>
#include <ObjectParser.h>
#include <TextureManager.h>
#include <iostream>
Menu *Menu::s_Instance = nullptr;
bool Menu::Init() {
  if (!TextureManager::GetInstance()->ParseTextures(
          "assets/objects/objects.tmx"))
    return false;
  if (!MapParser::GetInstance()->Load())
    return false;
  if (!ObjectParser::GetInstance()->Load())
    return false;
  if (!Index::GetInstance()->Parser("assets/objects/Character/Index.tmx"))
    return false;

  m_Info = MapParser::GetInstance()->GetMap("info");
  m_menu = MapParser::GetInstance()->GetMap("menu");
  return true;
}
void Menu::Clear() { m_menu = nullptr; }
void Menu::Render() {
  m_menu->Render();
  if (m_IsInfo)
    m_Info->Render();
}
void Menu::Update(float dt) {
  Camera::GetInstance()->UnsetPosition();
  m_menu->Update();
  if (m_IsInfo)
    m_Info->Update();
}