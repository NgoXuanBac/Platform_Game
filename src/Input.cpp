#include <Engine.h>
#include <Input.h>
#include <iostream>

Input *Input::s_Instance = nullptr;
Input::Input() {
  m_KeyStates = SDL_GetKeyboardState(nullptr);
  m_ButtonMouse = (Uint8)0;
}
void Input::Event() {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    switch (e.type) {
    case SDL_QUIT:
      Engine::GetInstance()->Quit();
      break;
    case SDL_KEYDOWN:
      m_KeyStates = SDL_GetKeyboardState(nullptr);
      break;
    case SDL_KEYUP:
      m_KeyStates = SDL_GetKeyboardState(nullptr);
      break;
    case SDL_MOUSEMOTION: {
      m_MousePosition.X = e.button.x;
      m_MousePosition.Y = e.button.y;
    } break;

    case SDL_MOUSEBUTTONDOWN: {
      m_ButtonMouse = e.button.button;
    } break;
    case SDL_MOUSEBUTTONUP: {
      m_ButtonMouse = (Uint8)0;
    } break;
    }
  }
}

int Input::GetAxisKey(Axis axis) {
  switch (axis) {
  case HORIZONTAL:
    if (GetKeyDown(SDL_SCANCODE_D))
      return 1;
    if (GetKeyDown(SDL_SCANCODE_A))
      return -1;
    break;
  case VERTICAL:
    if (GetKeyDown(SDL_SCANCODE_W))
      return 1;
    if (GetKeyDown(SDL_SCANCODE_S))
      return -1;
    break;
  }
  return 0;
}
bool Input::GetKeyDown(SDL_Scancode key) {
  return (m_KeyStates[key] == 1) ? true : false;
}
bool Input::GetButton(Uint8 button) {
  return (m_ButtonMouse == button) ? true : false;
}