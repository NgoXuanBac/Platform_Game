#ifndef ENEMY_H
#define ENEMY_H
#include <Character.h>
#include <SeqAnimation.h>
#include <Collider.h>
#include <RigidBody.h>
#include <Vector2D.h>
class Enemy : public Character
{
public:
    Enemy(std::string id, int tt, float x, float y, int width, int height, SDL_RendererFlip flip = SDL_FLIP_NONE);
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
    bool m_IsAttacking;
    bool m_IsGrounded;
    bool m_IsHit;
    bool m_IsDead;
    bool m_IsDeadHit;
    bool m_IsDeadGround;
    bool m_IsDialogue;
    bool m_IsDustRun, m_IsDustFall, m_IsDustJump;
    float DustX, DustY, EffectX, EffectY;

    float m_RunForce, m_JumpForce;

    float m_JumpTime, m_idleTime, m_AttackTime, m_DustFallTime, m_HitTime, m_HitTimeDelay, m_W_HitTime, m_DeadTime;
    int m_BufferHeight, m_BufferWidth, m_BufferX, m_BufferY;
    SDL_Rect m_DeadBufferRect;
    // test thanh mau

    int m_blood;
    //
    float m_DustFocusX, m_DustFocusY;
    // quan ly hinh dang va thu may
    std::string m_id;
    int m_tt;

    Collider *m_Collider;
    Collider *m_AttackCollider;
    SeqAnimation *m_Enemy;
    SeqAnimation *m_AttackEffects;
    SeqAnimation *m_DustParticles;
    SeqAnimation *m_Dialogue;
    RigidBody *m_RigidBody;
    Vector2D m_LastSafePosition;
};

#endif