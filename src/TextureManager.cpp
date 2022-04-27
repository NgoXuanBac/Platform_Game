#include <Camera.h>
#include <Engine.h>
#include <TextureManager.h>
#include <tinyxml.h>

TextureManager *TextureManager::s_Instance = nullptr;
bool TextureManager::Load(std::string id, std::string FileName) {
  SDL_Surface *loadedSurface = IMG_Load(FileName.c_str());
  if (loadedSurface == nullptr) {
    return false;
  }
  SDL_Texture *texture = SDL_CreateTextureFromSurface(
      Engine::GetInstance()->GetRenderer(), loadedSurface);
  if (texture == nullptr) {
    return false;
  }
  m_TextureMap[id] = texture;
  return true;
}
void TextureManager::Draw(std::string id, int x, int y, int width, int height,
                          float scaleX, float scaleY, float scollratio,
                          SDL_RendererFlip flip, int Color) {
  SDL_Rect srcrect = {0, 0, width, height};
  Vector2D cam = Camera::GetInstance()->GetPosition() * scollratio;
  x = x - cam.X;
  y = y - cam.Y;
  width = width * scaleX;
  height = height * scaleY;
  SDL_Rect dstrect = {x, y, width, height};
  SDL_SetTextureColorMod(m_TextureMap[id], 255, 255, 255);
  if (Color != 0)
    SDL_SetTextureColorMod(m_TextureMap[id], 128, 128, 128);
  SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[id],
                   &srcrect, &dstrect, 0, nullptr, flip);
}
void TextureManager::DrawFrame(std::string id, int x, int y, int width,
                               int height, int row, int frame,
                               SDL_RendererFlip flip) {
  SDL_Rect srcRect = {width * frame, height * row, width, height};
  Vector2D cam = Camera::GetInstance()->GetPosition();
  x = x - cam.X;
  y = y - cam.Y;
  SDL_Rect dstRect = {x, y, width, height};
  SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[id],
                   &srcRect, &dstRect, 0, nullptr, flip);
}
void TextureManager::DrawTile(std::string tilesetID, int tileSize, int x, int y,
                              int row, int frame, float scollratio,
                              SDL_RendererFlip flip) {
  SDL_Rect srcRect = {tileSize * frame, tileSize * row, tileSize, tileSize};
  Vector2D cam = Camera::GetInstance()->GetPosition() * scollratio;
  x = x - cam.X;
  y = y - cam.Y;
  SDL_Rect dstRect = {x, y, tileSize, tileSize};
  SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(),
                   m_TextureMap[tilesetID], &srcRect, &dstRect, 0, 0, flip);
}
void TextureManager::DrawRect(SDL_Rect box, SDL_RendererFlip Flip) {
  Vector2D cam = Camera::GetInstance()->GetPosition();
  box.x -= cam.X;
  box.y -= cam.Y;
  SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box);
}
bool TextureManager::ParseTextures(std::string source) {
  TiXmlDocument xml;
  xml.LoadFile(source);
  if (xml.Error()) {
    return false;
  }
  TiXmlElement *root = xml.RootElement();
  for (TiXmlElement *e = root->FirstChildElement(); e != nullptr;
       e = e->NextSiblingElement()) {
    if (e->Value() == std::string("texture")) {
      std::string id = e->Attribute("id");
      std::string src = e->Attribute("source");
      Load(id, src);
    }
  }
  return true;
}
void TextureManager::Drop(std::string id) {
  SDL_DestroyTexture(m_TextureMap[id]);
  m_TextureMap.erase(id);
}
void TextureManager::Clear() {
  for (std::map<std::string, SDL_Texture *>::iterator it;
       it != m_TextureMap.end(); it++) {
    SDL_DestroyTexture(it->second);
  }
  m_TextureMap.clear();
}