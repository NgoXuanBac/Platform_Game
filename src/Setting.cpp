#include <MapParser.h>
#include <Setting.h>

Setting *Setting::s_Instance = nullptr;
void Setting::Init() {
  m_setting = MapParser::GetInstance()->GetMap("setting");
}
void Setting::Clear() { m_setting = nullptr; }
void Setting::Render() { m_setting->Render(); }
void Setting::Update(float dt) { m_setting->Update(); }