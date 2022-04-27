#include <Camera.h>
#include <CollisionHandler.h>
#include <Enemy.h>
#include <Index.h>
#include <Input.h>
#include <ObjectParser.h>
#include <TextureManager.h>
#include <iostream>

#define FORWARD -1.0f
#define BACKWARD 1.0f
#define UPWARD -1.0f
// time
#define JUMP_TIME 15.0f
#define DUST_TIME_ENEMY 15.0f
#define IDLE_TIME 100.0f
#define HIT_TIME 10.0f
#define HIT_TIME_DELAY_ENEMY 30.0f
#define DEAD_TIME 20.0f
// force
#define JUMP_FORCE 15.0f
#define RUN_FORCE_ENEMY 2.0f
#define RUN_AND_JUMP_FORCE 4.0f

#define ATTACK_TIME 20.0f
#define WARRIOR_HIT_TIME 17.0f

#define DUST_FOCUS_ENEMY1_X 15
#define DUST_FOCUS_ENEMY1_Y 8
#define COLLISION_WIDTH_ENEMY1 25;
#define COLLISION_HEIGHT_ENEMY1 17;
#define COLLISION_X_ENEMY1 -25;
#define COLLISION_Y_ENEMY1 -10;

#define DUST_FOCUS_ENEMY2_X -3
#define DUST_FOCUS_ENEMY2_Y 8
#define COLLISION_WIDTH_ENEMY2 15;
#define COLLISION_HEIGHT_ENEMY2 21;
#define COLLISION_X_ENEMY2 -10;
#define COLLISION_Y_ENEMY2 -5;

#define DUST_FOCUS_ENEMY3_X -3
#define DUST_FOCUS_ENEMY3_Y 8
#define COLLISION_WIDTH_ENEMY3 15;
#define COLLISION_HEIGHT_ENEMY3 21;
#define COLLISION_X_ENEMY3 -10;
#define COLLISION_Y_ENEMY3 -5;

Enemy::Enemy(std::string id, int tt, float x, float y, int width, int height,
             SDL_RendererFlip flip)
    : Character(x, y, width, height) {
  m_RunForce = RUN_FORCE_ENEMY;
  m_JumpForce = JUMP_FORCE;
  m_JumpTime = JUMP_TIME;
  m_DustFallTime = DUST_TIME_ENEMY;
  m_HitTime = HIT_TIME;
  m_AttackTime = ATTACK_TIME;
  m_W_HitTime = 0;
  m_IsJumping = false;
  m_IsFalling = true;
  m_IsHit = false;
  m_IsDead = false;
  m_IsDeadGround = false;
  m_IsDeadHit = false;
  m_idleTime = 0;
  m_HitTimeDelay = 0;
  m_DeadTime = DEAD_TIME;
  m_blood = 4;
  m_id = id;
  m_tt = tt;
  m_Collider = new Collider();
  m_AttackCollider = new Collider();

  m_Enemy = new SeqAnimation();
  m_Enemy->Parse("assets/objects/Character/Enemy.tmx");
  m_AttackEffects = new SeqAnimation();
  m_AttackEffects->Parse("assets/objects/Character/E_AttackEffects.tmx");
  if (m_id == "1") {
    m_BufferX = COLLISION_X_ENEMY1;
    m_BufferY = COLLISION_Y_ENEMY1;
    m_BufferWidth = COLLISION_WIDTH_ENEMY1;
    m_BufferHeight = COLLISION_HEIGHT_ENEMY1;
    m_DeadBufferRect = {m_BufferX - 5, m_BufferY + 5, 10, -5};
    m_AttackCollider->SetBuffer(-10, -10, -55, -17);
    m_DustFocusX = DUST_FOCUS_ENEMY1_X;
    m_DustFocusY = DUST_FOCUS_ENEMY1_Y;
    m_AttackEffects->SetCurrentSeq("Enemy1 Effect Attack");
  }
  if (m_id == "2") {
    m_BufferX = COLLISION_X_ENEMY2;
    m_BufferY = COLLISION_Y_ENEMY2;
    m_BufferWidth = COLLISION_WIDTH_ENEMY2;
    m_BufferHeight = COLLISION_HEIGHT_ENEMY2;
    m_DeadBufferRect = {m_BufferX, m_BufferY - 5, 0, 5};
    m_AttackCollider->SetBuffer(-5, -5, -25, -21);
    m_DustFocusX = DUST_FOCUS_ENEMY2_X;
    m_DustFocusY = DUST_FOCUS_ENEMY2_Y;
    m_AttackEffects->SetCurrentSeq("Enemy2 Effect Attack");
  }
  if (m_id == "3") {
    m_BufferX = COLLISION_X_ENEMY3;
    m_BufferY = COLLISION_Y_ENEMY3;
    m_BufferWidth = COLLISION_WIDTH_ENEMY3;
    m_BufferHeight = COLLISION_HEIGHT_ENEMY3;
    m_DeadBufferRect = {m_BufferX, m_BufferY - 5, 0, 5};
    m_AttackCollider->SetBuffer(0, -5, -10, -17);
    m_DustFocusX = DUST_FOCUS_ENEMY3_X;
    m_DustFocusY = DUST_FOCUS_ENEMY3_Y;
    m_AttackEffects->SetCurrentSeq("Enemy3 Effect Attack");
  }
  m_DustParticles = new SeqAnimation();
  m_DustParticles->Parse("assets/objects/Character/DustParticles.tmx");
  m_DustParticles->SetCurrentSeq("Dust particles fall");

  // m_Dialogue = new SeqAnimation();
  // m_Dialogue->Parse("assets/objects/Character/Dialogue.tmx");
  // m_Dialogue->SetCurrentSeq("Dialogue interrogation");

  m_RigidBody = new RigidBody();
  m_RigidBody->SetGravity(7);
}
void Enemy::Draw() {
  if ((m_IsDustRun || m_IsDustJump || m_IsDustFall) && !m_IsDead) {
    if (m_Flip == SDL_FLIP_NONE)
      m_DustParticles->DrawFrame(DustX, DustY, 0.5f, 0.5f, SDL_FLIP_HORIZONTAL);
    else
      m_DustParticles->DrawFrame(DustX, DustY, 0.5f, 0.5f, SDL_FLIP_NONE);
  }
  // if (m_IsDialogue)
  //     m_Dialogue->DrawFrame(m_Transform->X + 35, m_Transform->Y -
  //     10, 1.0f, 1.0f);
  if (!m_IsDead && m_HitTimeDelay > 0)
    Index::GetInstance()->RenderIndex("EnemyHP", m_Collider->Get().x - 17,
                                      m_Collider->Get().y - 18, m_blood);
  m_Enemy->DrawFrame(m_Transform->X, m_Transform->Y, 1.0f, 1.0f, m_Flip);
  if (m_IsAttacking && !m_IsDead)
    m_AttackEffects->DrawFrame(EffectX, EffectY, 1.0f, 1.0f, m_Flip);
  // Rect
  // TextureManager::GetInstance()->DrawRect(m_Collider->Get());
  // TextureManager::GetInstance()->DrawRect(m_AttackCollider->Get());
}
void Enemy::Update(float dt) {
  //=============================Init========================================
  if (m_IsDead)
    return;
  m_IsRunning = false;
  m_IsCrouching = false;
  m_IsAttacking = false;
  m_IsDustRun = false;
  m_IsDustFall = false;
  m_IsDialogue = false;
  m_Collider->SetBuffer(m_BufferX, m_BufferY, 0, 0);
  m_RigidBody->UnSetForce();
  //==================================AI=====================================
  if (!m_IsDeadGround) {
    // move
    if (m_RunForce > 0)
      m_Flip = SDL_FLIP_HORIZONTAL;
    else
      m_Flip = SDL_FLIP_NONE;

    m_RigidBody->ApplyForceX(m_RunForce);
    m_IsRunning = true;
  }
  // fall
  if (m_RigidBody->Velocity().Y > 0 && !m_IsGrounded) {
    m_IsFalling = true;
  } else {
    m_IsFalling = false;
  }
  // attack
  m_AttackCollider->Set(m_Transform->X, m_Transform->Y, 0, 0);
  if (m_id == "3") {
    if (m_Flip == SDL_FLIP_NONE)
      m_AttackCollider->SetBuffer(0, -5, -15, -17);
    if (m_Flip == SDL_FLIP_HORIZONTAL)
      m_AttackCollider->SetBuffer(-20, -5, -15, -17);
  }
  if (CollisionHandler::GetInstance()->WarriorCollision(
          m_AttackCollider->Get())) {
    if (m_id == "1") {
      m_IsAttacking = true;
      EffectX = m_Transform->X - 22;
      EffectY = m_Transform->Y + 8;
      m_RigidBody->UnSetForce();
    } else if (m_id == "2") {
      m_IsAttacking = true;
      EffectX = (m_Flip == SDL_FLIP_HORIZONTAL)
                    ? (m_Transform->X + m_DustFocusX - 4)
                    : (m_Transform->X + m_DustFocusX + 12);
      EffectY = m_Transform->Y + m_DustFocusY;
      m_RigidBody->UnSetForce();
    } else if (m_id == "3") {
      m_IsAttacking = true;
      if (m_Flip == SDL_FLIP_NONE)
        EffectX = m_Transform->X - 11;
      if (m_Flip == SDL_FLIP_HORIZONTAL)
        EffectX = m_Transform->X + 25;
      EffectY = m_Transform->Y;
      m_RigidBody->UnSetForce();
    }
    m_W_HitTime += dt;
    if (m_W_HitTime >= WARRIOR_HIT_TIME) {
      CollisionHandler::GetInstance()->EnemyIsAttacking(m_tt, m_id);
      m_W_HitTime = 0;
    }
  }

  if (m_IsAttacking && m_AttackTime > 0 && !m_IsDeadHit && !m_IsDeadGround) {
    if (m_AttackTime == ATTACK_TIME) {
      m_Enemy->ResetFrame();
      while (!m_Enemy->CheckFrame(1)) {
        m_Enemy->Update(dt);
      }
      m_AttackEffects->ResetFrame();
    }
    m_AttackTime -= dt;
  } else {
    m_IsAttacking = false;
    CollisionHandler::GetInstance()->EnemyStopAttack(m_tt, m_id);
    m_AttackTime = ATTACK_TIME;
  }
  // hit
  if (CollisionHandler::GetInstance()->EnemyIsBeaten(m_tt, m_id) &&
      m_HitTimeDelay <= 0) {
    m_blood--;
    if (m_blood != 0)
      m_IsHit = true;
    else
      m_IsDeadHit = true;

    m_IsGrounded = false;
  }
  if ((m_IsHit || m_IsDeadHit) && m_HitTime > 0) {
    if (m_HitTime == HIT_TIME)
      m_Enemy->ResetFrame();
    m_HitTime -= dt;
    m_HitTimeDelay = HIT_TIME_DELAY_ENEMY;
    m_RigidBody->ApplyForceX(3 *
                             ObjectParser::GetInstance()->WarriorDirection());
    m_RigidBody->ApplyForceY(-10);
  } else {
    m_HitTime = HIT_TIME;
    m_IsHit = false;
    if (m_HitTimeDelay > 0) {
      m_HitTimeDelay -= dt;
      m_RigidBody->UnSetForce();
      m_IsRunning = false;
    }
  }
  // DeadHit
  if (m_IsDeadHit || m_IsDeadGround)
    m_Collider->SetBuffer(m_DeadBufferRect.x, m_DeadBufferRect.y,
                          m_DeadBufferRect.w, m_DeadBufferRect.h);
  // DeadGround
  if (m_IsDeadHit && m_HitTime <= 0) {
    m_IsDeadGround = true;
    m_IsDeadHit = false;
  }
  if (m_IsDeadGround && m_DeadTime > 0) {
    if (m_DeadTime == HIT_TIME)
      m_Enemy->ResetFrame();
    m_DeadTime -= dt;
    if (m_DeadTime <= 0 && m_IsGrounded)
      m_IsDead = true;
  }

  //==================================Collision================================

  m_RigidBody->Update(dt);
  m_LastSafePosition.X = m_Transform->X;
  m_Transform->X += m_RigidBody->Position().X;
  // check collision.
  m_Collider->Set(m_Transform->X, m_Transform->Y, m_BufferWidth,
                  m_BufferHeight); // rect warrior
  if (CollisionHandler::GetInstance()->Static_Collision(m_Collider->Get()) ||
      CollisionHandler::GetInstance()->PixelCollision(m_Collider->Get()) ||
      CollisionHandler::GetInstance()->WarriorCollision(m_Collider->Get())) {
    m_RunForce = m_RunForce * (-1);
    m_Transform->X = m_LastSafePosition.X;
  }
  m_RigidBody->Update(dt);
  m_LastSafePosition.Y = m_Transform->Y;
  m_Transform->Y += m_RigidBody->Position().Y;
  // check collision
  m_Collider->Set(m_Transform->X, m_Transform->Y, m_BufferWidth,
                  m_BufferHeight); // rect warrior
  if (CollisionHandler::GetInstance()->Static_Collision(m_Collider->Get()) ||
      CollisionHandler::GetInstance()->WarriorCollision(m_Collider->Get())) {
    m_IsGrounded = true;
    m_Transform->Y = m_LastSafePosition.Y;
  } else {
    m_IsGrounded = false;
  }
  m_Origin->X = m_Transform->X + m_Width / 2;
  m_Origin->Y = m_Transform->Y + m_Height / 2;
  // =================================SAVE_POSIOTION=============================
  m_Collider->Set(m_Transform->X, m_Transform->Y, m_BufferWidth,
                  m_BufferHeight);
  ObjectParser::GetInstance()->SetRectEnemy(m_Collider->Get(), m_tt, m_id);
  if (m_IsAttacking)
    ObjectParser::GetInstance()->SetRectEnemyAttack(m_AttackCollider->Get());

  // ==================================DIALOGUE===================================

  //==================================DUST_EFFECT=================================
  // dust-fall
  if (m_IsGrounded && m_DustFallTime > 0) {
    m_DustFallTime -= dt;
    m_IsDustFall = true;
    DustX = m_Transform->X + m_DustFocusX + 5;
    DustY = m_Transform->Y + m_DustFocusY;
  }
  if (!m_IsGrounded)
    m_DustFallTime = DUST_TIME_ENEMY;
  // dust-run
  if (m_IsGrounded && m_IsRunning && !m_IsAttacking) {
    m_IsDustRun = true;
    DustX = (m_Flip == SDL_FLIP_HORIZONTAL)
                ? (m_Transform->X + m_DustFocusX - 4)
                : (m_Transform->X + m_DustFocusX + 12);
    DustY = m_Transform->Y + m_DustFocusY;
  }
  if (!m_IsRunning && m_DustFallTime == DUST_TIME_ENEMY) {
    m_DustParticles->ResetFrame();
  }
  //==================================Set_Current=================================
  AnimationState();
  //==================================Update_Frame=================================
  // m_Dialogue->Update(dt);
  m_DustParticles->Update(dt);
  m_AttackEffects->Update(dt);
  m_Enemy->Update(dt);
}
void Enemy::AnimationState() {

  if (m_IsDustFall)
    m_DustParticles->SetCurrentSeq("Dust particles fall");
  if (m_IsDustRun)
    m_DustParticles->SetCurrentSeq("Dust particles run");
  if (m_id == "1") {
    m_Enemy->SetCurrentSeq("Enemy1 idle");
    if (m_IsRunning)
      m_Enemy->SetCurrentSeq("Enemy1 run");
    if (m_IsJumping)
      m_Enemy->SetCurrentSeq("Enemy1 jump");
    if (m_IsFalling)
      m_Enemy->SetCurrentSeq("Enemy1 fall");
    if (m_IsAttacking)
      m_Enemy->SetCurrentSeq("Enemy1 attack");
    if (m_IsHit)
      m_Enemy->SetCurrentSeq("Enemy1 hit");
    if (m_IsDeadHit)
      m_Enemy->SetCurrentSeq("Enemy1 dead hit");
    if (m_IsDeadGround)
      m_Enemy->SetCurrentSeq("Enemy1 dead ground");
  } else if (m_id == "2") {
    m_Enemy->SetCurrentSeq("Enemy2 idle");
    if (m_IsRunning)
      m_Enemy->SetCurrentSeq("Enemy2 run");
    if (m_IsJumping)
      m_Enemy->SetCurrentSeq("Enemy2 jump");
    if (m_IsFalling)
      m_Enemy->SetCurrentSeq("Enemy2 fall");
    if (m_IsAttacking)
      m_Enemy->SetCurrentSeq("Enemy2 attack");
    if (m_IsHit)
      m_Enemy->SetCurrentSeq("Enemy2 hit");
    if (m_IsDeadHit)
      m_Enemy->SetCurrentSeq("Enemy2 dead hit");
    if (m_IsDeadGround)
      m_Enemy->SetCurrentSeq("Enemy2 dead ground");
  } else if (m_id == "3") {
    m_Enemy->SetCurrentSeq("Enemy3 idle");
    if (m_IsRunning)
      m_Enemy->SetCurrentSeq("Enemy3 run");
    if (m_IsJumping)
      m_Enemy->SetCurrentSeq("Enemy3 jump");
    if (m_IsFalling)
      m_Enemy->SetCurrentSeq("Enemy3 fall");
    if (m_IsAttacking)
      m_Enemy->SetCurrentSeq("Enemy3 attack");
    if (m_IsHit)
      m_Enemy->SetCurrentSeq("Enemy3 hit");
    if (m_IsDeadHit)
      m_Enemy->SetCurrentSeq("Enemy3 dead hit");
    if (m_IsDeadGround)
      m_Enemy->SetCurrentSeq("Enemy3 dead ground");
  }
}
void Enemy::Clear() {
  // clear animation
  m_Enemy->Clear();
  m_Enemy = nullptr;
  m_AttackEffects->Clear();
  m_AttackEffects = nullptr;
  m_DustParticles->Clear();
  m_DustParticles = nullptr;
  m_Dialogue->Clear();
  m_Dialogue = nullptr;
  // clear collider
  m_Collider = nullptr;
  m_AttackCollider = nullptr;
  // clear rigidBody
  m_RigidBody = nullptr;
}