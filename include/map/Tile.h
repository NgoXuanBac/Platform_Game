#ifndef TILE_H
#define TILE_H
#include <string>
#include <vector>
class Tile {
public:
  virtual void Render(const int &x, const int &y) = 0;
  virtual void Update() = 0;
};
class SpriteTile : public Tile {
public:
  SpriteTile(){};
  virtual void Render(const int &x, const int &y){};
  virtual void Update(){};
};
class SingleTile : public Tile {
private:
  int TileSize, TileHeight, TileWidth;
  int frame;
  float TileScoll;
  std::string TextureID;

public:
  SingleTile(std::string IDs, int size, int height, int width,
             float scoll = 1.0f)
      : TextureID(IDs), TileSize(size), TileHeight(height), TileWidth(width),
        TileScoll(scoll) {}
  virtual void Render(const int &x, const int &y);
  virtual void Update(){};
};
class MoveTile : public Tile {
private:
  int TileSize, TileHeight, TileWidth;
  int frame;
  float TileScoll, Displacement, speed;
  std::string TextureID;

public:
  MoveTile(std::string IDs, int size, int height, int width, float SPEED,
           float scoll = 1.0f)
      : TextureID(IDs), TileSize(size), TileHeight(height), TileWidth(width),
        TileScoll(scoll), speed(SPEED) {
    Displacement = 0;
  }
  virtual void Render(const int &x, const int &y);
  virtual void Update();
};
class ButtonTile : public Tile {
private:
  int TileSize, TileHeight, TileWidth;
  int frame;
  float TileScoll;
  std::string TextureID;

public:
  ButtonTile(std::string IDs, int size, int height, int width,
             float scoll = 1.0f)
      : TextureID(IDs), TileSize(size), TileHeight(height), TileWidth(width),
        TileScoll(scoll) {}
  virtual void Render(const int &x, const int &y);
  virtual void Update(){};
};
class StaticTile : public Tile {
private:
  int TileSize, TileCol, TileRow;
  float TileScoll;
  std::string TextureID;

public:
  StaticTile(std::string ID, int size, int col, int row, float scoll = 1.0f)
      : TextureID(ID), TileSize(size), TileCol(col), TileRow(row),
        TileScoll(scoll){};
  virtual void Render(const int &x, const int &y);
  virtual void Update(){};
};
class AnimationTile : public Tile {
private:
  int TileSize, TileHeight, TileWidth, TileSpeed;
  int frame;
  float TileScoll;
  std::vector<std::string> TextureIDs;

public:
  AnimationTile(std::vector<std::string> IDs, int size, int height, int width,
                int speed, float scoll = 1.0f)
      : TextureIDs(IDs), TileSize(size), TileHeight(height), TileWidth(width),
        TileSpeed(speed), TileScoll(scoll) {}
  virtual void Render(const int &x, const int &y);
  virtual void Update();
};
#endif