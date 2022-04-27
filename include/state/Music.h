#ifndef MUSIC_H
#define MUSIC_H
#include <SDL_mixer.h>
#include <map>
#include <string>
class Music {
private:
  static Music *s_Instance;
  std::map<std::string, Mix_Chunk *> m_Musics;
  Mix_Music *m_MusicBG;

public:
  static Music *GetInstance() {
    return s_Instance = (s_Instance != nullptr) ? s_Instance : new Music();
  }
  bool Load(std::string id, std::string source);
  bool Init();
  inline void Stop() { Mix_HaltChannel(-1); }
  void Play(std::string id);
  void PlayBG();
  void Clear();
};
#endif