#ifndef TEXTURE_H
#define TEXTURE_H
#include <SDL.h>
#include <SDL_image.h>
#include <map>
#include <string>
class TextureManager {
public:
  static TextureManager *GetInstance() {
    return s_Instance =
               (s_Instance != nullptr) ? s_Instance : new TextureManager();
  }
  void Draw(std::string id, int x, int y, int width, int height,
            float scaleX = 1.0f, float scaleY = 1.0f, float scollratio = 1.0f,
            SDL_RendererFlip flip = SDL_FLIP_NONE, int Color = 0);
  void DrawFrame(std::string id, int x, int y, int width, int height, int row,
                 int frame, SDL_RendererFlip flip = SDL_FLIP_NONE);
  void DrawTile(std::string tilesetID, int tileSize, int x, int y, int row,
                int frame, float scollratio = 1.0f,
                SDL_RendererFlip flip = SDL_FLIP_NONE);

  void DrawRect(SDL_Rect box, SDL_RendererFlip Flip = SDL_FLIP_NONE);
  bool Load(std::string id, std::string FileName);
  bool ParseTextures(std::string source);

  void Drop(std::string id);
  void Clear();

private:
  static TextureManager *s_Instance;
  std::map<std::string, SDL_Texture *> m_TextureMap;
};
#endif