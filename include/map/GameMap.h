#ifndef GAMEMAP_H
#define GAMEMAP_H
#include <Layer.h>
#include <vector>
class GameMap {
private:
  std::vector<Layer *> m_MapLayers;
  friend class MapParser;

public:
  void Render() {
    for (int i = 0; i < m_MapLayers.size(); i++)
      m_MapLayers.at(i)->Render();
  }
  void Update() {
    for (int i = 0; i < m_MapLayers.size(); i++)
      m_MapLayers.at(i)->Update();
  }
  void Reset() {
    for (int i = 0; i < m_MapLayers.size(); i++)
      m_MapLayers.at(i)->Reset();
  }
  std::vector<Layer *> GetMapLayers() { return m_MapLayers; }
};

#endif