#ifndef CAMERA_H
#define CAMERA_H
#include <Engine.h>
#include <Point.h>
#include <SDL.h>
#include <Vector2D.h>
class Camera {
public:
  void Update();
  inline static Camera *GetInstance() {
    return s_Instance = (s_Instance != nullptr) ? s_Instance : new Camera();
  }
  inline SDL_Rect GetViewBox() { return m_ViewBox; }
  inline Vector2D GetPosition() { return m_Position; }
  inline void UnsetPosition() { m_Position = Vector2D(0, 0); }
  inline void SetTarget(Point *target) { m_Target = target; }

private:
  Camera() { m_ViewBox = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT}; }
  SDL_Rect m_ViewBox;
  Point *m_Target;
  Vector2D m_Position;
  static Camera *s_Instance;
};
#endif