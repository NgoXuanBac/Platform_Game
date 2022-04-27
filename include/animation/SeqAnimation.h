#ifndef SEQANIMATION_H
#define SEQANIMATION_H
#include <map>
#include <string>
#include <vector>
#include <SDL.h>
#include <Animation.h>
struct Sequence
{
    int Speed;
    int FrameCount;
    int width, height;
    std::vector<std::string> TextureIDs;
};
class SeqAnimation : public Animation
{
public:
    SeqAnimation(bool repeat = true);
    virtual void Update(float dt);

    void Parse(std::string source);
    void Clear();

    void SetCurrentSeq(std::string seqID);
    void SetRepeat(bool repeat) { m_Repeat = repeat; }
    void DrawFrame(float X, float Y, float xScale = 1.0f, float yScale = 1.0f, SDL_RendererFlip flip = SDL_FLIP_NONE);
    inline void ResetFrame() { m_TimeFrame = 0; };
    bool CheckFrame(const int &frame);

private:
    Sequence m_CurrentSeq;
    float m_TimeFrame;
    std::map<std::string, Sequence> m_SeqMap;
};

#endif