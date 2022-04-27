#include <Levels.h>
#include <MapParser.h>
Levels *Levels::s_Instance = nullptr;
void Levels::Init() { m_levels = MapParser::GetInstance()->GetMap("levels"); }
void Levels::Clear() { m_levels = nullptr; }
void Levels::Render() { m_levels->Render(); }
void Levels::Update(float dt) { m_levels->Update(); }