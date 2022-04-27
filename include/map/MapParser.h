#ifndef MAPPARSER_H
#define MAPPARSER_H
#include <map>
#include <string>
#include <GameMap.h>
#include <tinyxml.h>
#include <TileLayer.h>
class MapParser
{
public:
    bool Load();
    void Clean();
    inline static MapParser *GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new MapParser(); }
    inline GameMap *GetMap(std::string id) { return m_MapDict[id]; }

private:
    bool Parse(std::string id, std::string source);
    Tileset ParseTileset(TiXmlElement *xmlTileset);
    Tilelayer *ParseTileLayer(TiXmlElement *xmlLayer, TilesetList Tilesets, int tilesize, int rowcount, int colcount);

protected:
    MapParser(){};
    static MapParser *s_Instance;
    std::map<std::string, GameMap *> m_MapDict;
};
#endif