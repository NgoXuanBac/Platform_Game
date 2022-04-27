#include <CollisionHandler.h>
#include <Engine.h>
#include <Input.h>
#include <Menu.h>
#include <Play.h>
#include <TextureManager.h>
#include <Tile.h>
#define MAX_MAP 1920
void StaticTile::Render(const int &x, const int &y) {
  TextureManager::GetInstance()->DrawTile(TextureID, TileSize, x * TileSize,
                                          y * TileSize, TileRow, TileCol,
                                          TileScoll);
}
void SingleTile::Render(const int &x, const int &y) {
  int TileX = x * TileSize;
  int TileY = (y + 1) * TileSize - TileHeight;
  TextureManager::GetInstance()->Draw(TextureID, TileX, TileY, TileWidth,
                                      TileHeight, 1, 1, TileScoll);
}
void MoveTile::Render(const int &x, const int &y) {
  int TileX = x * TileSize - (int)Displacement;
  int TileY = (y + 1) * TileSize - TileHeight;
  if ((TileX + TileWidth) < 0) {
    Displacement = x * TileSize - MAX_MAP;
  }
  TextureManager::GetInstance()->Draw(TextureID, TileX, TileY, TileWidth,
                                      TileHeight, 1, 1, TileScoll);
}
void MoveTile::Update() { Displacement += speed; }
void ButtonTile::Render(const int &x, const int &y) {
  int Color = 0;
  int TileX = x * TileSize;
  int TileY = (y + 1) * TileSize - TileHeight;
  SDL_Rect rect = {TileX, TileY, TileWidth, TileHeight};
  // Menu
  Menu::GetInstance()->SwitchInfo(false);
  if (CollisionHandler::GetInstance()->Point_Collision(
          Input::GetInstance()->Get_MousePosition(), rect)) {
    Color = 1;
    if (TextureID == "Info button") {
      Menu::GetInstance()->SwitchInfo(true);
    }
    if (Input::GetInstance()->GetButton(SDL_BUTTON_LEFT)) {
      if (!Engine::GetInstance()->GetSetting() &&
          !Engine::GetInstance()->GetLevels()) {
        if (TextureID == "Play button")
          Engine::GetInstance()->Switch_Levels(true);
        else if (TextureID == "Quit button")
          Engine::GetInstance()->Quit();
        else if (TextureID == "Setting button")
          Engine::GetInstance()->Switch_Setting(true);
        else if (TextureID == "Home button") {
          Engine::GetInstance()->Switch_Setting(true);
        } else if (TextureID == "Home_2 button") {
          Engine::GetInstance()->Switch_Setting(true);
        } else if (TextureID == "Continue button") {
          Engine::GetInstance()->Switch_Levels(true);
        } else if (TextureID == "Close button") {
          Engine::GetInstance()->Switch_Levels(true);
        }
      } else if (Engine::GetInstance()->GetSetting()) {
        if (TextureID == "Return button")
          Engine::GetInstance()->Switch_Setting(false);
        else if (TextureID == "Menu button") {
          Engine::GetInstance()->Switch_Play(false);
          Engine::GetInstance()->Switch_Setting(false);
          Engine::GetInstance()->Switch_Menu(true);
        }
      } else if (Engine::GetInstance()->GetLevels()) {
        if (TextureID == "Return button") {
          Engine::GetInstance()->Switch_Levels(false);
        } else if (TextureID == "1 Button") {
          Play::GetInstance()->Init("level_0");
          Engine::GetInstance()->Switch_Play(true);
          CollisionHandler::GetInstance()->Update();
          Engine::GetInstance()->Switch_Levels(false);
        } else if (TextureID == "2 Button") {
          Play::GetInstance()->Init("level_1");
          Engine::GetInstance()->Switch_Play(true);
          CollisionHandler::GetInstance()->Update();
          Engine::GetInstance()->Switch_Levels(false);
        } else if (TextureID == "3 Button") {
          Play::GetInstance()->Init("level_2");
          Engine::GetInstance()->Switch_Play(true);
          CollisionHandler::GetInstance()->Update();
          Engine::GetInstance()->Switch_Levels(false);
        } else if (TextureID == "4 Button") {
          Play::GetInstance()->Init("level_3");
          Engine::GetInstance()->Switch_Play(true);
          CollisionHandler::GetInstance()->Update();
          Engine::GetInstance()->Switch_Levels(false);
        } else if (TextureID == "5 Button") {
          Play::GetInstance()->Init("level_4");
          Engine::GetInstance()->Switch_Play(true);
          CollisionHandler::GetInstance()->Update();
          Engine::GetInstance()->Switch_Levels(false);
        } else if (TextureID == "6 Button") {
          Play::GetInstance()->Init("level_5");
          Engine::GetInstance()->Switch_Play(true);
          CollisionHandler::GetInstance()->Update();
          Engine::GetInstance()->Switch_Levels(false);
        }
      }
    }
  }
  TextureManager::GetInstance()->Draw(TextureID, TileX, TileY, TileWidth,
                                      TileHeight, 1, 1, TileScoll,
                                      SDL_FLIP_NONE, Color);
}
void AnimationTile::Render(const int &x, const int &y) {
  int TileX = x * TileSize;
  int TileY = (y + 1) * TileSize - TileHeight;
  TextureManager::GetInstance()->Draw(TextureIDs[frame], TileX, TileY,
                                      TileWidth, TileHeight, 1, 1, TileScoll);
}
void AnimationTile::Update() {
  frame = (SDL_GetTicks() / TileSpeed) % TextureIDs.size();
}
