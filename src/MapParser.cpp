#include <MapParser.h>
MapParser *MapParser::s_Instance = nullptr;
bool MapParser::Load() {
  if (!Parse("menu", "assets/level/menu.tmx"))
    return false;
  if (!Parse("setting", "assets/level/Setting.tmx"))
    return false;
  if (!Parse("over", "assets/level/GameOver.tmx"))
    return false;
  if (!Parse("info", "assets/level/Info.tmx"))
    return false;
  if (!Parse("levels", "assets/level/Levels.tmx"))
    return false;
  if (!Parse("level_0", "assets/level/level_0.tmx"))
    return false;
  if (!Parse("level_1", "assets/level/level_1.tmx"))
    return false;
  if (!Parse("level_2", "assets/level/level_2.tmx"))
    return false;
  if (!Parse("level_3", "assets/level/level_3.tmx"))
    return false;
  if (!Parse("level_4", "assets/level/level_4.tmx"))
    return false;
  if (!Parse("level_5", "assets/level/level_5.tmx"))
    return false;
  return true;
}
void MapParser::Clean() {
  std::map<std::string, GameMap *>::iterator it;
  for (it = m_MapDict.begin(); it != m_MapDict.end(); it++) {
    it->second = nullptr;
  }
  m_MapDict.clear();
}
bool MapParser::Parse(std::string id, std::string source) {
  TiXmlDocument xml;
  xml.LoadFile(source);

  if (xml.Error()) {
    return false;
  }
  TiXmlElement *root = xml.RootElement();
  int rowcount, colcount, tilesize = 0;
  root->Attribute("width", &colcount);
  root->Attribute("height", &rowcount);
  root->Attribute("tilewidth", &tilesize);
  TilesetList tilesets;
  for (TiXmlElement *e = root->FirstChildElement(); e != nullptr;
       e = e->NextSiblingElement()) {
    if (e->Value() == std::string("tileset")) {
      tilesets.push_back(ParseTileset(e));
    }
  }
  GameMap *gamemap = new GameMap();
  for (TiXmlElement *e = root->FirstChildElement(); e != nullptr;
       e = e->NextSiblingElement()) {
    if (e->Value() == std::string("layer")) {
      Tilelayer *tilelayer =
          ParseTileLayer(e, tilesets, tilesize, rowcount, colcount);
      gamemap->m_MapLayers.push_back(tilelayer);
    }
  }
  m_MapDict[id] = gamemap;
  return true;
}
Tileset MapParser::ParseTileset(TiXmlElement *xmlTileset) {
  Tileset tileset;
  tileset.Name = xmlTileset->Attribute("name");
  xmlTileset->Attribute("firstgid", &tileset.FirstID);
  xmlTileset->Attribute("tilecount", &tileset.TileCount);
  tileset.LastID = (tileset.FirstID + tileset.TileCount) - 1;
  xmlTileset->Attribute("columns", &tileset.ColCount);
  if (tileset.ColCount != 0) {
    tileset.RowCount = tileset.TileCount / tileset.ColCount;
  } else {
    tileset.RowCount = 0;
  }
  xmlTileset->Attribute("tilewidth", &tileset.TileWidth);
  xmlTileset->Attribute("tileheight", &tileset.TileHeight);
  return tileset;
}
Tilelayer *MapParser::ParseTileLayer(TiXmlElement *xmlLayer,
                                     TilesetList Tilesets, int tilesize,
                                     int rowcount, int colcount) {
  TiXmlElement *data;
  for (TiXmlElement *e = xmlLayer->FirstChildElement(); e != nullptr;
       e = e->NextSiblingElement()) {
    if (e->Value() == std::string("data")) {
      data = e;
      break;
    }
  }
  std::string matrix(data->GetText());
  std::istringstream iss(matrix);
  std::string id;

  TileMap tilemap(rowcount, std::vector<int>(colcount, 0));
  for (int row = 0; row < rowcount; row++) {
    for (int col = 0; col < colcount; col++) {
      getline(iss, id, ',');
      std::stringstream convertor(id);
      convertor >> tilemap[row][col];
      if (!iss.good())
        break;
    }
  }
  return (new Tilelayer(tilesize, rowcount, colcount, tilemap, Tilesets,
                        xmlLayer->Attribute("name")));
}