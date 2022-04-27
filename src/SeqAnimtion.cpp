#include <SeqAnimation.h>
#include <tinyxml.h>
#include <TextureManager.h>
SeqAnimation::SeqAnimation(bool repeat) : Animation(repeat)
{
    m_TimeFrame = 0;
}
void SeqAnimation::DrawFrame(float X, float Y, float xScale, float yScale, SDL_RendererFlip flip)
{
    TextureManager::GetInstance()->Draw(m_CurrentSeq.TextureIDs[m_Currentframe], X, Y, m_CurrentSeq.width, m_CurrentSeq.height, xScale, yScale, 1, flip);
}
void SeqAnimation::Update(float dt)
{
    if (dt < 0 || dt > 20)
        dt = 0;
    m_TimeFrame = m_TimeFrame + dt;
    m_Currentframe = ((int)m_TimeFrame / m_CurrentSeq.Speed) % m_CurrentSeq.FrameCount;
}
bool SeqAnimation::CheckFrame(const int &frame)
{
    if (m_Currentframe == frame)
        return true;
    return false;
}
void SeqAnimation::SetCurrentSeq(std::string seqID)
{
    if (m_SeqMap.count(seqID) > 0)
    {
        m_CurrentSeq = m_SeqMap[seqID];
    }
}
void SeqAnimation::Parse(std::string source)
{
    TiXmlDocument xml;
    xml.LoadFile(source);
    if (!xml.Error())
    {
        TiXmlElement *root = xml.RootElement();
        for (TiXmlElement *e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
        {
            if (e->Value() == std::string("sequence"))
            {
                Sequence seq;
                std::string seqID = e->Attribute("id");
                e->Attribute("speed", &seq.Speed);
                e->Attribute("width", &seq.width);
                e->Attribute("height", &seq.height);
                e->Attribute("frameCount", &seq.FrameCount);
                for (TiXmlElement *frame = e->FirstChildElement(); frame != nullptr; frame = frame->NextSiblingElement())
                {
                    seq.TextureIDs.push_back(frame->Attribute("textureID"));
                }
                m_SeqMap[seqID] = seq;
            }
        }
    }
}
void SeqAnimation::Clear()
{
    std::map<std::string, Sequence>::iterator it;
    for (it = m_SeqMap.begin(); it != m_SeqMap.end(); it++)
    {
        it->second.TextureIDs.clear();
    }
    m_SeqMap.clear();
}