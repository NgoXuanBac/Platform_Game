#ifndef WARRIOR_H
#define WARRIOR_H
#include <Character.h>
#include <Collider.h>
#include <RigidBody.h>
#include <SeqAnimation.h>
#include <Vector2D.h>
class Warrior : public Character {
public:
  Warrior(float x, float y, int width, int height,
          SDL_RendererFlip flip = SDL_FLIP_NONE);
  virtual void Draw();
  virtual void Clear();
  virtual void Update(float dt);

private:
  void AnimationState();

private:
  bool m_IsJumping;   // nhay
  bool m_IsRunning;   // chay
  bool m_IsFalling;   // roi
  bool m_IsCrouching; // cui nguoi
  bool m_IsHit;
  bool m_IsDying;
  bool m_IsDeadHit;
  bool m_IsDeadGround;
  bool m_IsDead;
  // combo attack
  bool m_IsAttacking1;
  bool m_IsAttacking2;
  bool m_IsAttacking3;

  bool m_IsGrounded;
  bool m_IsDialogue;
  bool m_IsHenshin; // bien hinh
  bool m_IsDustRun, m_IsDustFall, m_IsDustJump;
  float DustX, DustY, EffectX, EffectY;

  float m_RunForce, m_JumpForce;

  float m_JumpTime, m_idleTime, m_AttackTime, m_DustFallTime, m_HitTime,
      m_HitTimeDelay, m_DeadTime;

  int m_blood;

  Collider *m_Collider;
  Collider *m_AttackCollider;
  Collider *m_HitCollider;
  SeqAnimation *m_Warrior;
  SeqAnimation *m_DustParticles;
  SeqAnimation *m_Dialogue;
  SeqAnimation *m_AttackEffects;
  RigidBody *m_RigidBody;
  Vector2D m_LastSafePosition;
};

#endif