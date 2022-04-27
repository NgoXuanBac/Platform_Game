#include <Music.h>
#include <tinyxml.h>
Music *Music::s_Instance = nullptr;
bool Music::Init() {
  TiXmlDocument xml;
  xml.LoadFile("assets/music/music.tmx");
  if (xml.Error()) {
    return false;
  }
  TiXmlElement *root = xml.RootElement();
  for (TiXmlElement *e = root->FirstChildElement(); e != nullptr;
       e = e->NextSiblingElement()) {
    if (e->Value() == std::string("music")) {
      std::string id = e->Attribute("id");
      std::string src = e->Attribute("source");
      Load(id, src);
    }
  }
  return true;
}
bool Music::Load(std::string id, std::string source) {
  if (id != "Bg Sound") {
    Mix_Chunk *chunk = Mix_LoadWAV(source.c_str());
    m_Musics[id] = chunk;
  } else {
    m_MusicBG = Mix_LoadMUS(source.c_str());
  }

  return true;
}
void Music::Play(std::string id) {
  Mix_Volume(-1, MIX_MAX_VOLUME / 5);
  Mix_PlayChannel(-1, m_Musics[id], 0);
}
void Music::Clear() {
  std::map<std::string, Mix_Chunk *>::iterator it;
  for (it = m_Musics.begin(); it != m_Musics.end(); it++) {
    it->second = nullptr;
  }
  m_Musics.clear();
}
void Music::PlayBG() {
  Mix_VolumeMusic(MIX_MAX_VOLUME / 15);
  Mix_PlayMusic(m_MusicBG, 1);
}