#include <Index.h>
#include <tinyxml.h>
#include <TextureManager.h>
#define WARRIOR_HP_X 16
#define WARRIOR_HP_Y 14
#define ENEMY_HP_X 3
#define ENEMY_HP_Y 3
Index *Index::s_Instance = nullptr;
Index::Index() {}
bool Index::Parser(std::string source)
{
    TiXmlDocument xml;
    xml.LoadFile(source);
    if (xml.Error())
        return false;
    TiXmlElement *root = xml.RootElement();
    for (TiXmlElement *e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
    {
        if (e->Value() == std::string("idquence"))
        {
            IdQuence index;
            std::string indexID = e->Attribute("id");

            if (indexID == "Colors")
            {
                e->Attribute("width", &m_ColorIndex.width);
                e->Attribute("height", &m_ColorIndex.height);
                e->Attribute("Count", &m_ColorIndex.count);
                for (TiXmlElement *texture = e->FirstChildElement(); texture != nullptr; texture = texture->NextSiblingElement())
                {
                    m_ColorIndex.TextureIDs.push_back(texture->Attribute("textureID"));
                }
            }
            else
            {
                e->Attribute("width", &index.width);
                e->Attribute("height", &index.height);
                e->Attribute("Count", &index.count);
                for (TiXmlElement *texture = e->FirstChildElement(); texture != nullptr; texture = texture->NextSiblingElement())
                {
                    index.TextureIDs.push_back(texture->Attribute("textureID"));
                }
                m_Indexs[indexID] = index;
            }
        }
    }
    return true;
}
void Index::RenderIndex(std::string Id, const int &x, const int &y, const int &hp, const int &color, const int &length)
{
    int width = m_Indexs[Id].width;
    int height = m_Indexs[Id].height;
    int IndexWidth = width * length + 16;
    int X = x;
    int Y = y;
    int scoll = 1;
    if (Id == "WarriorHP")
    {
        IndexWidth = width * length + 44;
        scoll = 0;
    }
    TextureManager::GetInstance()->Draw(m_Indexs[Id].TextureIDs[0], X, Y, width, height, 1, 1, scoll);
    for (int i = 1; i <= length; i++)
    {
        X += width;
        TextureManager::GetInstance()->Draw(m_Indexs[Id].TextureIDs[1], X, Y, width, height, 1, 1, scoll);
    }
    X += width;
    TextureManager::GetInstance()->Draw(m_Indexs[Id].TextureIDs.back(), X, Y, width, height, 1, 1, scoll);
    width = m_ColorIndex.width / 2;
    height = m_ColorIndex.height / 2;
    int LineWidth = width;
    X = x + ENEMY_HP_X;
    Y = y + ENEMY_HP_Y;
    if (Id == "WarriorHP")
    {
        X = x + WARRIOR_HP_X;
        Y = y + WARRIOR_HP_Y;
    }
    for (int i = 1; i <= hp; i++)
    {
        if (LineWidth >= IndexWidth)
        {
            width = width - (LineWidth - IndexWidth);
            width = (width <= 0) ? 0 : width;
        }
        TextureManager::GetInstance()->Draw(m_ColorIndex.TextureIDs[color], X, Y, width, height, 1, 1, scoll);
        LineWidth += width;

        X += width;
    }
}
void Index::Update(float dt)
{
}
void Index::Clear()
{
    std::map<std::string, IdQuence>::iterator it;
    for (it = m_Indexs.begin(); it != m_Indexs.end(); it++)
    {
        it->second.TextureIDs.clear();
    }
    m_Indexs.clear();
}
