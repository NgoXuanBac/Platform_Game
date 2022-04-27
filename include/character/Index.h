#ifndef INDEX_H
#define INDEX_H
#include <vector>
#include <string>
#include <map>
struct IdQuence
{
    std::vector<std::string> TextureIDs;
    int height, width, count;
};
class Index
{
private:
    Index();

private:
    //.....

    static Index *s_Instance;
    std::map<std::string, IdQuence> m_Indexs;
    IdQuence m_ColorIndex;

public:
    //....
    bool Parser(std::string source);
    void Update(float dt);
    void Clear();
    void RenderIndex(std::string Id, const int &x, const int &y, const int &hp, const int &color = 0, const int &length = 3);

    static Index *GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new Index(); }
};
#endif