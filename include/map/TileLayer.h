#ifndef TILELAYER_H
#define TILELAYER_H
#include <Layer.h>
#include <Tile.h>
#include <vector>
// Tileset
struct Tileset {
  std::string Name, Source;
  int FirstID, LastID, RowCount, ColCount, TileCount, TileWidth, TileHeight;
};
using Tiles = std::vector<Tile *>;
using TilesetList = std::vector<Tileset>;
using TileMap = std::vector<std::vector<int>>;
class Tilelayer : public Layer {
public:
  // modun
  virtual void Render();
  virtual void Update();
  virtual void DeleteTile(const int &x, const int &y);
  virtual void Reset() { m_Map = m_Tilemap; }
  Tilelayer(int tilesize, int rowcount, int colcount, TileMap tilemap,
            TilesetList tilesets, std::string name);
  inline TileMap GetTileMap() { return m_Map; }

private:
  int m_TileSize;
  int m_RowCount, m_ColCount;
  Tiles m_Tiles;
  TileMap m_Tilemap, m_Map;
  TilesetList m_Tilesets;
};
#endif