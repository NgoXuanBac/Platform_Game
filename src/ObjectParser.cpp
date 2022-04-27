#include <ObjectParser.h>
#include <tinyxml.h>
ObjectParser *ObjectParser::s_Instance = nullptr;
bool ObjectParser::Load() {
  if (!Parse("level_0", "assets/level/object_0.tmx"))
    return false;
  if (!Parse("level_1", "assets/level/object_1.tmx"))
    return false;
  if (!Parse("level_2", "assets/level/object_2.tmx"))
    return false;
  if (!Parse("level_3", "assets/level/object_3.tmx"))
    return false;
  if (!Parse("level_4", "assets/level/object_4.tmx"))
    return false;
  if (!Parse("level_5", "assets/level/object_5.tmx"))
    return false;
  return true;
}
bool ObjectParser::Parse(std::string id, std::string source) {
  TiXmlDocument xml;
  xml.LoadFile(source);
  if (xml.Error())
    return false;

  TiXmlElement *data = xml.RootElement()->FirstChildElement();
  std::string matrix(data->GetText());
  std::istringstream iss(matrix);
  std::string i;

  Tilemap tilemap(20, std::vector<int>(60, 0));
  for (int row = 0; row < 20; row++) {
    for (int col = 0; col < 60; col++) {

      getline(iss, i, ',');
      std::stringstream convertor(i);
      convertor >> tilemap[row][col];

      switch (tilemap[row][col]) {
      case 1: {
        m_Objects[id].m_PositionWarrior = {col * 32 - 18,
                                           (row + 1) * 32 - 60 + 18, 64, 40};
      } break;
      case 2: {
        SDL_Rect r = {col * 32 - 15, (row + 1) * 32 - 72 + 9, 72, 32};
        m_Objects[id].m_PositionEnemy1.push_back(r);
      } break;
      case 3: {
        SDL_Rect r = {col * 32 - 15, (row + 1) * 32 - 72 + 9, 72, 32};
        m_Objects[id].m_PositionEnemy2.push_back(r);
      } break;
      case 4: {
        SDL_Rect r = {col * 32 - 15, (row + 1) * 32 - 72 + 9, 72, 32};
        m_Objects[id].m_PositionEnemy3.push_back(r);
      } break;
      }

      if (!iss.good())
        break;
    }
  }

  return true;
}
void ObjectParser::Clear() {
  std::map<std::string, Object>::iterator it;
  for (it = m_Objects.begin(); it != m_Objects.end(); it++) {
    it->second.m_PositionEnemy1.clear();
    it->second.m_PositionEnemy2.clear();
    it->second.m_PositionEnemy3.clear();
  }
  m_Objects.clear();
}
void ObjectParser::SetWarriorDirection(SDL_RendererFlip flip) {
  m_WarriorDirection = (flip == SDL_FLIP_NONE) ? 1 : -1;
}
void ObjectParser::SetRectEnemy(const SDL_Rect &r, const int &i,
                                const std::string &type) {
  if (type == "1")
    m_PositionEnemy1[i] = r;
  else if (type == "2")
    m_PositionEnemy2[i] = r;
  else if (type == "3")
    m_PositionEnemy3[i] = r;
}
void ObjectParser::GetObject(std::string id) {
  m_PositionWarrior = m_Objects[id].m_PositionWarrior;
  m_PositionEnemy1 = m_Objects[id].m_PositionEnemy1;
  m_PositionEnemy2 = m_Objects[id].m_PositionEnemy2;
  m_PositionEnemy3 = m_Objects[id].m_PositionEnemy3;
  m_WarriorDirection = 1;
  m_RectEnemyAttack = {0, 0, 0, 0};
}