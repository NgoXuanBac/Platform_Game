#include <TileLayer.h>
#define SPEED_FRAME 110
Tilelayer::Tilelayer(int tilesize, int rowcount, int colcount, TileMap tilemap,
                     TilesetList tilesets, std::string name)
    : m_TileSize(tilesize), m_Tilesets(tilesets), m_ColCount(colcount),
      m_RowCount(rowcount), m_Tilemap(tilemap) {
  m_Map = m_Tilemap;
  m_LayerName = name;
  Tileset tileset;
  for (unsigned int i = 0; i < m_Tilesets.size(); i++) {
    tileset = m_Tilesets.at(i);
    // static_Tile
    if (tileset.Name == "Terrain" || tileset.Name == "Front bottom tree" ||
        tileset.Name == "Grass" || tileset.Name == "Water_Tile" ||
        tileset.Name == "Sky_Tile") {
      int Row = tileset.RowCount;
      int Col = tileset.ColCount;
      int tileRow, tileCol, id;
      for (int tileID = tileset.FirstID; tileID <= tileset.LastID; tileID++) {
        id = tileID + tilesets.at(i).TileCount - tileset.LastID;
        tileRow = id / Col;
        tileCol = id - tileRow * Col - 1;
        if (id % Col == 0) {
          tileRow--;
          tileCol = Col - 1;
        }
        m_Tiles.push_back(
            new StaticTile(tileset.Name, m_TileSize, tileCol, tileRow));
      }
    }
    // menu_Tile
    else if (tileset.Name == "Game over" || tileset.Name == "Info") {
      m_Tiles.push_back(new SingleTile(
          tileset.Name, m_TileSize, tileset.TileHeight, tileset.TileWidth, 0));
    } else if (tileset.Name == "Big Banner" || tileset.Name == "Small Banner" ||
               tileset.Name == "Green Board" ||
               tileset.Name == "Yellow Board" ||
               tileset.Name == "Yellow Paper") {
      int Row = tileset.RowCount;
      int Col = tileset.ColCount;
      int tileRow, tileCol, id;
      for (int tileID = tileset.FirstID; tileID <= tileset.LastID; tileID++) {
        id = tileID + tilesets.at(i).TileCount - tileset.LastID;
        tileRow = id / Col;
        tileCol = id - tileRow * Col - 1;
        if (id % Col == 0) {
          tileRow--;
          tileCol = Col - 1;
        }
        m_Tiles.push_back(
            new StaticTile(tileset.Name, m_TileSize, tileCol, tileRow, 0));
      }
    } else if (tileset.Name == "Play button" ||
               tileset.Name == "Setting button" ||
               tileset.Name == "Quit button" || tileset.Name == "Menu button" ||
               tileset.Name == "Return button" ||
               tileset.Name == "Music button" ||
               tileset.Name == "Home button" ||
               tileset.Name == "Home_2 button" ||
               tileset.Name == "Close button" ||
               tileset.Name == "Continue button" ||
               tileset.Name == "Info button" || tileset.Name == "1 Button" ||
               tileset.Name == "2 Button" || tileset.Name == "3 Button" ||
               tileset.Name == "4 Button" || tileset.Name == "5 Button" ||
               tileset.Name == "6 Button") {
      m_Tiles.push_back(new ButtonTile(
          tileset.Name, m_TileSize, tileset.TileHeight, tileset.TileWidth, 0));

    }
    // animation_Tile
    else if (tileset.Name == "Flag") {
      std::vector<std::string> ids = {"Flag 01", "Flag 02", "Flag 03",
                                      "Flag 04", "Flag 05", "Flag 06",
                                      "Flag 07", "Flag 08", "Flag 09"};
      m_Tiles.push_back(new AnimationTile(ids, m_TileSize, tileset.TileHeight,
                                          tileset.TileWidth, SPEED_FRAME));
    } else if (tileset.Name == "Gold coin") {
      std::vector<std::string> ids = {"Gold coin 1", "Gold coin 2",
                                      "Gold coin 3", "Gold coin 4"};
      m_Tiles.push_back(new AnimationTile(ids, m_TileSize, tileset.TileHeight,
                                          tileset.TileWidth, SPEED_FRAME));
    } else if (tileset.Name == "Silver coin") {
      std::vector<std::string> ids = {"Silver coin 1", "Silver coin 2",
                                      "Silver coin 3", "Silver coin 4"};
      m_Tiles.push_back(new AnimationTile(ids, m_TileSize, tileset.TileHeight,
                                          tileset.TileWidth, SPEED_FRAME));
    } else if (tileset.Name == "Back tree") {
      std::vector<std::string> ids = {"Back tree 1", "Back tree 2",
                                      "Back tree 3", "Back tree 4"};
      m_Tiles.push_back(new AnimationTile(ids, m_TileSize, tileset.TileHeight,
                                          tileset.TileWidth, SPEED_FRAME));
    } else if (tileset.Name == "Front top tree") {
      std::vector<std::string> ids = {"Front tree Top 1", "Front tree Top 2",
                                      "Front tree Top 3", "Front tree Top 4"};
      m_Tiles.push_back(new AnimationTile(ids, m_TileSize, tileset.TileHeight,
                                          tileset.TileWidth, SPEED_FRAME));
    } else if (tileset.Name == "Water") {
      std::vector<std::string> ids = {"Water Top 1", "Water Top 2",
                                      "Water Top 3", "Water Top 4"};
      m_Tiles.push_back(new AnimationTile(ids, m_TileSize, tileset.TileHeight,
                                          tileset.TileWidth, SPEED_FRAME));
    } else if (tileset.Name == "Water-effect") {
      std::vector<std::string> ids = {"Water effect 1", "Water effect 2",
                                      "Water effect 3", "Water effect 4"};
      m_Tiles.push_back(new AnimationTile(ids, m_TileSize, tileset.TileHeight,
                                          tileset.TileWidth, SPEED_FRAME, 0.5));
    } else if (tileset.Name == "Sword") {
      std::vector<std::string> ids = {
          "Sword idle1", "Sword idle2", "Sword idle3", "Sword idle4",
          "Sword idle5", "Sword idle6", "Sword idle7", "Sword idle8"};
      m_Tiles.push_back(new AnimationTile(ids, m_TileSize, tileset.TileHeight,
                                          tileset.TileWidth, SPEED_FRAME));
    } else if (tileset.Name == "Treasure") {
      std::vector<std::string> ids = {"Treasure 1", "Treasure 2", "Treasure 3",
                                      "Treasure 4", "Treasure 5", "Treasure 6",
                                      "Treasure 7", "Treasure 8", "Treasure 9",
                                      "Treasure 10"};
      m_Tiles.push_back(new AnimationTile(ids, m_TileSize, tileset.TileHeight,
                                          tileset.TileWidth, SPEED_FRAME));

    } else if (tileset.Name == "Chains") {
      std::vector<std::string> ids = {
          "Chains Big 1", "Chains Big 2", "Chains Big 3", "Chains Big 4",
          "Chains Big 5", "Chains Big 6", "Chains Big 7", "Chains Big 8"};
      m_Tiles.push_back(new AnimationTile(ids, m_TileSize, tileset.TileHeight,
                                          tileset.TileWidth, SPEED_FRAME, 0));
    }
    // SingleTile
    else if (tileset.Name == "Skyline" || tileset.Name == "Chest") {
      m_Tiles.push_back(new SingleTile(tileset.Name, m_TileSize,
                                       tileset.TileHeight, tileset.TileWidth));
    }
    // sprite_Tile
    else if (tileset.Name == "Pixel") {
      m_Tiles.push_back(new SpriteTile());
    } else if (tileset.Name == "Cloud") {
      m_Tiles.push_back(new MoveTile("cloud 1", m_TileSize, 21, 46, 0.05));
      m_Tiles.push_back(new MoveTile("cloud 2", m_TileSize, 54, 147, 0.25));
      m_Tiles.push_back(new MoveTile("cloud 3", m_TileSize, 28, 55, 0.1));
      m_Tiles.push_back(new MoveTile("cloud 4", m_TileSize, 54, 161, 0.35));
      m_Tiles.push_back(new MoveTile("cloud 5", m_TileSize, 42, 100, 0.3));
      m_Tiles.push_back(new MoveTile("cloud 6", m_TileSize, 41, 79, 0.15));
      m_Tiles.push_back(new MoveTile("cloud 7", m_TileSize, 66, 181, 0.4));
      m_Tiles.push_back(new MoveTile("cloud 8", m_TileSize, 41, 79, 0.2));
    }
  }
}
void Tilelayer::Render() {
  for (unsigned int y = 0; y < m_RowCount; y++) {
    for (unsigned int x = 0; x < m_ColCount; x++) {
      int tileID = m_Map[y][x];
      if (tileID != 0) {
        m_Tiles.at(tileID - 1)->Render(x, y);
      }
    }
  }
}
void Tilelayer::Update() {
  for (int i = 0; i < m_Tiles.size(); i++) {
    m_Tiles[i]->Update();
  }
}
void Tilelayer::DeleteTile(const int &x, const int &y) { m_Map[x][y] = 0; }
