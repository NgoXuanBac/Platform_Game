#ifndef INPUT_H
#define INPUT_H
#include <SDL.h>
#include <Vector2D.h>
enum Axis { HORIZONTAL, VERTICAL };
class Input {
public:
  static Input *GetInstance() {
    return s_Instance = (s_Instance != nullptr) ? s_Instance : new Input();
  }
  void Event();
  inline Vector2D Get_MousePosition() { return m_MousePosition; }
  bool GetKeyDown(SDL_Scancode key);
  bool GetButton(Uint8 button);
  int GetAxisKey(Axis axis);

private:
  Input();
  void KeyUp();
  void KeyDown();

private:
  Vector2D m_MousePosition;
  const Uint8 *m_KeyStates;
  static Input *s_Instance;
  Uint8 m_ButtonMouse;
};
#endif
