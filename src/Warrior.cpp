#include <Camera.h>
#include <CollisionHandler.h>
#include <Index.h>
#include <Input.h>
#include <Music.h>
#include <ObjectParser.h>
#include <Play.h>
#include <TextureManager.h>
#include <Warrior.h>
#include <iostream>
#define FORWARD -1.0f
#define BACKWARD 1.0f
#define UPWARD -1.0f
// time
#define JUMP_TIME 15.0f
#define DUST_TIME 15.0f
#define IDLE_TIME 100.0f
#define HIT_TIME 10.0f
#define HIT_TIME_DELAY 40.0f
#define DEAD_TIME 20.0f
// force
#define JUMP_FORCE 15.0f
#define RUN_FORCE 5.0f
#define RUN_AND_JUMP_FORCE 4.0f

#define ATTACK_TIME 20.0f
#define DUST_FOCUS_WARRIOR_X 16
#define DUST_FOCUS_WARRIOR_Y 12
#define COLLISION_WIDTH 15
#define COLLISION_HEIGHT 20
Warrior::Warrior(float x, float y, int width, int height, SDL_RendererFlip flip)
    : Character(x, y, width, height) {

  m_RunForce = RUN_FORCE;
  m_JumpForce = JUMP_FORCE;
  m_JumpTime = JUMP_TIME;
  m_DustFallTime = DUST_TIME;
  m_AttackTime = ATTACK_TIME;
  m_HitTimeDelay = 0;
  m_idleTime = 0;
  m_DeadTime = DEAD_TIME;
  m_blood = 9;
  m_IsHenshin = false;
  m_IsHit = false;
  m_IsDead = false;
  m_IsDeadGround = false;
  m_IsDeadHit = false;
  m_IsDying = false;

  m_Collider = new Collider();
  m_AttackCollider = new Collider();
  m_HitCollider = new Collider();
  m_HitCollider->SetBuffer(-40, -10, 0, 0);
  m_Warrior = new SeqAnimation();
  m_Warrior->Parse("assets/objects/Character/Warrior.tmx");

  m_DustParticles = new SeqAnimation();
  m_DustParticles->Parse("assets/objects/Character/DustParticles.tmx");
  m_DustParticles->SetCurrentSeq("Dust particles fall");

  m_Dialogue = new SeqAnimation();
  m_Dialogue->Parse("assets/objects/Character/Dialogue.tmx");
  m_Dialogue->SetCurrentSeq("Dialogue interrogation");

  m_AttackEffects = new SeqAnimation();
  m_AttackEffects->Parse("assets/objects/Character/AttackEffects.tmx");
  m_AttackEffects->SetCurrentSeq("Warrior Effect Attack_1");

  m_RigidBody = new RigidBody();
  m_RigidBody->SetGravity(7);
}
void Warrior::Draw() {
  if (!m_IsDead && m_IsDialogue)
    m_Dialogue->DrawFrame(m_Transform->X + 35, m_Transform->Y - 10, 1.0f, 1.0f);
  m_Warrior->DrawFrame(m_Transform->X, m_Transform->Y, 1.0f, 1.0f, m_Flip);
  if (!m_IsDead && (m_IsDustRun || m_IsDustJump || m_IsDustFall))
    m_DustParticles->DrawFrame(DustX, DustY, 0.5f, 0.5f, m_Flip);
  if (!m_IsDead && (m_IsAttacking1 || m_IsAttacking2 || m_IsAttacking3)) {
    m_AttackEffects->DrawFrame(EffectX, EffectY, 1.0f, 1.0f, m_Flip);
  }
  Index::GetInstance()->RenderIndex("WarriorHP", 0, 0, m_blood);
  // Rect
  // TextureManager::GetInstance()->DrawRect(m_Collider->Get());
  // TextureManager::GetInstance()->DrawRect(m_AttackCollider->Get());
  // TextureManager::GetInstance()->DrawRect(m_HitCollider->Get());
}
void Warrior::Update(float dt) {
  if (m_IsDead) {
    Play::GetInstance()->SwitchOver(true);
    return;
  }
  //=============================Init========================================
  m_IsRunning = false;
  m_IsCrouching = false;
  m_IsDustRun = false;
  m_IsDustJump = false;
  m_IsDustFall = false;
  m_IsDialogue = false;
  m_IsAttacking1 = false;
  m_IsAttacking2 = false;
  m_IsAttacking3 = false;
  m_Collider->SetBuffer(-25, -10, 0, 0);

  m_RigidBody->UnSetForce();
  //==================================Handle=================================
  // move left
  if (!m_IsDying) {
    if (Input::GetInstance()->GetAxisKey(HORIZONTAL) == FORWARD) {
      if (!m_IsFalling) {
        m_RunForce = RUN_FORCE * FORWARD;
      } else {
        m_RunForce = RUN_AND_JUMP_FORCE * FORWARD;
      }
      m_RigidBody->ApplyForceX(m_RunForce);
      m_Flip = SDL_FLIP_HORIZONTAL;
      m_IsRunning = true;
    }
    // move right
    if (Input::GetInstance()->GetAxisKey(HORIZONTAL) == BACKWARD) {
      if (!m_IsFalling) {
        m_RunForce = RUN_FORCE * BACKWARD;
      } else {
        m_RunForce = RUN_AND_JUMP_FORCE * BACKWARD;
      }

      m_RigidBody->ApplyForceX(m_RunForce);
      m_Flip = SDL_FLIP_NONE;
      m_IsRunning = true;
    }
    // crouch
    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_S)) {
      m_RigidBody->UnSetForce();
      //
      m_Collider->SetBuffer(-25, -15, 0, 5);
      //
      m_IsCrouching = true;
    }
    // attack no jump and fall
    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_J) && m_IsHenshin) {
      m_IsAttacking1 = true;
      if (m_Flip == SDL_FLIP_NONE)
        EffectX = m_Transform->X + 45;
      else
        EffectX = m_Transform->X - 10;
      EffectY = m_Transform->Y + 15;
      m_RigidBody->UnSetForce();
    }
    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_K) && m_IsHenshin) {
      m_IsAttacking2 = true;
      if (m_Flip == SDL_FLIP_NONE)
        EffectX = m_Transform->X + 35;
      else
        EffectX = m_Transform->X - 10;
      EffectY = m_Transform->Y;
      m_RigidBody->UnSetForce();
    }
    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_L) && m_IsHenshin) {
      m_IsAttacking3 = true;
      if (m_Flip == SDL_FLIP_NONE)
        EffectX = m_Transform->X + 35;
      else
        EffectX = m_Transform->X - 10;
      EffectY = m_Transform->Y;
      m_RigidBody->UnSetForce();
    }
    // jump
    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE) && m_IsGrounded) {
      m_IsJumping = true;
      m_IsGrounded = false;
      Music::GetInstance()->Stop();
      Music::GetInstance()->Play("Jump Sound");
    }
    // jump->fly
    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE) && m_IsJumping &&
        m_JumpTime > 0) {
      m_JumpTime -= dt;
      m_RigidBody->ApplyForceY(UPWARD * m_JumpForce);
    } else {
      m_IsJumping = false;
      m_JumpTime = JUMP_TIME;
    }
  }

  // fall
  if (m_RigidBody->Velocity().Y > 0 && !m_IsGrounded) {
    m_IsFalling = true;
  } else {
    m_IsFalling = false;
  }
  // hit
  m_HitCollider->Set(m_Transform->X, m_Transform->Y, 5, 20);
  if (CollisionHandler::GetInstance()->WarriorIsBeaten() &&
      m_HitTimeDelay <= 0) {
    m_blood--;
    if (m_blood != 0)
      m_IsHit = true;
    else {
      m_IsDying = true;
      m_IsDeadHit = true;
    }
    m_IsGrounded = false;
  }
  if ((m_IsHit || m_IsDeadHit) && m_HitTime > 0) {
    if (m_HitTime == HIT_TIME) {
      m_Dialogue->ResetFrame();
      m_Warrior->ResetFrame();
    }
    m_HitTime -= dt;
    m_HitTimeDelay = HIT_TIME_DELAY;
    if (CollisionHandler::GetInstance()->CheckRectEnemyAttack(
            m_HitCollider->Get()))
      m_RigidBody->ApplyForceX(-3);
    else
      m_RigidBody->ApplyForceX(+3);
    m_RigidBody->ApplyForceY(-10);
  } else {
    m_HitTime = HIT_TIME;
    m_IsHit = false;
    if (m_HitTimeDelay > 0)
      m_HitTimeDelay -= dt;
  }
  // DeadGround
  if (m_IsDeadHit && m_HitTime <= 0) {
    m_IsDeadGround = true;
    m_IsDeadHit = false;
  }
  if (m_IsDeadGround && m_DeadTime > 0) {
    if (m_IsGrounded)
      m_RigidBody->UnSetForce();
    if (m_DeadTime == HIT_TIME)
      m_Warrior->ResetFrame();
    m_DeadTime -= dt;
  }
  if (m_DeadTime <= 0 && m_IsGrounded)
    m_IsDead = true;

  //===============================ATTACK=================================
  if ((m_IsAttacking1 || m_IsAttacking2 || m_IsAttacking3) &&
      m_AttackTime > 0) {
    if (m_AttackTime == ATTACK_TIME) {
      m_Warrior->ResetFrame();
      m_AttackEffects->ResetFrame();
    }
    m_AttackTime -= dt;
    if (m_IsAttacking1) {
      if (m_Flip == SDL_FLIP_NONE) {
        m_AttackCollider->SetBuffer(-40, -10, 0, 0);
        m_AttackCollider->Set(m_Transform->X, m_Transform->Y, 25, 20);
      } else {
        m_AttackCollider->SetBuffer(0, -10, 0, 0);
        m_AttackCollider->Set(m_Transform->X, m_Transform->Y, 25, 20);
      }
    }
    if (m_IsAttacking2) {
      if (m_Flip == SDL_FLIP_NONE) {
        m_AttackCollider->SetBuffer(-40, -10, 0, 0);
        m_AttackCollider->Set(m_Transform->X, m_Transform->Y, 20, 30);
      } else {
        m_AttackCollider->SetBuffer(-5, -10, 0, 0);
        m_AttackCollider->Set(m_Transform->X, m_Transform->Y, 20, 30);
      }
    }
    if (m_IsAttacking3) {
      if (m_Flip == SDL_FLIP_NONE) {
        m_AttackCollider->SetBuffer(-40, 0, 0, 0);
        m_AttackCollider->Set(m_Transform->X, m_Transform->Y, 20, 30);
      } else {
        m_AttackCollider->SetBuffer(-5, 0, 0, 0);
        m_AttackCollider->Set(m_Transform->X, m_Transform->Y, 20, 30);
      }
    }
  } else {
    m_IsAttacking1 = false;
    m_IsAttacking2 = false;
    m_IsAttacking3 = false;
    m_AttackCollider->Set(0, 0, 0, 0);
    m_AttackTime = ATTACK_TIME;
    CollisionHandler::GetInstance()->WarriorStopAttack();
  }
  if (CollisionHandler::GetInstance()->WarriorIsAttacking(
          m_AttackCollider->Get())) {
  }
  //==================================Collision=================================
  m_RigidBody->Update(dt);
  m_LastSafePosition.X = m_Transform->X;
  m_Transform->X += m_RigidBody->Position().X;
  // check collision.
  m_Collider->Set(m_Transform->X, m_Transform->Y, COLLISION_WIDTH,
                  COLLISION_HEIGHT); // rect warrior
  if (CollisionHandler::GetInstance()->Static_Collision(m_Collider->Get()) ||
      CollisionHandler::GetInstance()->EnemyCollision(m_Collider->Get())) {
    m_Transform->X = m_LastSafePosition.X;
  }
  m_Collider->Set(m_Transform->X, m_Transform->Y, COLLISION_WIDTH,
                  COLLISION_HEIGHT);
  if (CollisionHandler::GetInstance()->CoinCollision(m_Collider->Get())) {
    Music::GetInstance()->Play("Coin Sound");
  }
  if (CollisionHandler::GetInstance()->SwordCollision(m_Collider->Get()))
    m_IsHenshin = true;
  if (CollisionHandler::GetInstance()->ChestCollision(m_Collider->Get())) {
    Engine::GetInstance()->Switch_Levels(true);
  }
  m_RigidBody->Update(dt);
  m_LastSafePosition.Y = m_Transform->Y;
  m_Transform->Y += m_RigidBody->Position().Y;
  // check collision
  m_Collider->Set(m_Transform->X, m_Transform->Y, COLLISION_WIDTH,
                  COLLISION_HEIGHT); // rect warrior

  if (CollisionHandler::GetInstance()->Static_Collision(m_Collider->Get()) ||
      CollisionHandler::GetInstance()->EnemyCollision(m_Collider->Get())) {
    m_IsGrounded = true;
    m_Transform->Y = m_LastSafePosition.Y;
  } else {
    m_IsGrounded = false;
  }
  m_Collider->Set(m_Transform->X, m_Transform->Y, COLLISION_WIDTH,
                  COLLISION_HEIGHT);
  if (CollisionHandler::GetInstance()->CoinCollision(m_Collider->Get())) {
    Music::GetInstance()->Play("Coin Sound");
  }
  if (CollisionHandler::GetInstance()->SwordCollision(m_Collider->Get()))
    m_IsHenshin = true;
  if (CollisionHandler::GetInstance()->WaterCollision(m_Collider->Get()) &&
      !m_IsDeadGround) {

    m_IsDeadHit = true;
    m_IsDying = true;
  }
  m_Origin->X = m_Transform->X + m_Width / 2;
  m_Origin->Y = m_Transform->Y + m_Height / 2;
  //=================================SAVE_POSIOTION==============================
  if (m_IsDeadHit || m_IsDeadGround)
    m_Collider->Set(0, 0, 0, 0);
  ObjectParser::GetInstance()->SetRectWarrior(m_Collider->Get());
  ObjectParser::GetInstance()->SetWarriorDirection(m_Flip);
  //==================================DIALOGUE===================================
  if (m_IsDeadHit || m_IsDeadGround)
    m_IsDialogue = true;
  else if (!m_IsFalling && !m_IsRunning && !m_IsJumping && !m_IsAttacking1 &&
           !m_IsAttacking2 && !m_IsAttacking3) {
    m_idleTime += dt;
    if (m_idleTime >= IDLE_TIME) {
      if (m_idleTime <= (IDLE_TIME + dt))
        m_Dialogue->ResetFrame();
      if (m_idleTime >= 2 * IDLE_TIME) {
        m_IsDialogue = false;
        m_idleTime = 0;
      } else
        m_IsDialogue = true;
    }
  } else {
    m_IsDialogue = false;
    m_idleTime = 0;
  }

  //==================================DUST_EFFECT=================================
  // dust-jump
  if (m_IsJumping) {
    m_IsDustJump = true;
    if (m_JumpTime == (JUMP_TIME - dt)) {
      m_DustParticles->ResetFrame();
      DustX = m_Transform->X + DUST_FOCUS_WARRIOR_X;
      DustY = m_Transform->Y + DUST_FOCUS_WARRIOR_Y;
    }
  }
  // dust-fall
  if (m_IsGrounded && m_DustFallTime > 0) {
    m_DustFallTime -= dt;
    m_IsDustFall = true;
    DustX = m_Transform->X + DUST_FOCUS_WARRIOR_X;
    DustY = m_Transform->Y + DUST_FOCUS_WARRIOR_Y;
  }
  if (!m_IsGrounded)
    m_DustFallTime = DUST_TIME;
  // dust-run
  if (m_IsGrounded && m_IsRunning) {
    m_IsDustRun = true;
    DustX = (m_Flip == SDL_FLIP_NONE)
                ? (m_Transform->X + DUST_FOCUS_WARRIOR_X - 6)
                : (m_Transform->X + DUST_FOCUS_WARRIOR_X + 6);
    DustY = m_Transform->Y + DUST_FOCUS_WARRIOR_Y;
  }
  if (!m_IsRunning && m_DustFallTime == DUST_TIME) {
    m_DustParticles->ResetFrame();
  }
  // if (m_idleTime > 0)
  //==================================Set_Current=================================
  AnimationState();
  //==================================Update_Frame=================================
  m_Dialogue->Update(dt);
  m_DustParticles->Update(dt);
  m_AttackEffects->Update(dt);
  m_Warrior->Update(dt);
}
void Warrior::AnimationState() {
  if (m_IsDustJump)
    m_DustParticles->SetCurrentSeq("Dust particles jump");
  if (m_IsDustFall)
    m_DustParticles->SetCurrentSeq("Dust particles fall");
  if (m_IsDustRun)
    m_DustParticles->SetCurrentSeq("Dust particles run");
  if (!m_IsHenshin) {
    m_Warrior->SetCurrentSeq("Warrior idle");
    if (m_IsRunning)
      m_Warrior->SetCurrentSeq("Warrior run");
    if (m_IsCrouching)
      m_Warrior->SetCurrentSeq("Warrior ground");
    if (m_IsJumping)
      m_Warrior->SetCurrentSeq("Warrior jump");
    if (m_IsFalling)
      m_Warrior->SetCurrentSeq("Warrior fall");
    if (m_IsHit)
      m_Warrior->SetCurrentSeq("Warrior hit");
  } else {
    m_Warrior->SetCurrentSeq("Warrior idle sword");
    if (m_IsRunning)
      m_Warrior->SetCurrentSeq("Warrior run sword");
    if (m_IsCrouching)
      m_Warrior->SetCurrentSeq("Warrior ground sword");
    if (m_IsJumping)
      m_Warrior->SetCurrentSeq("Warrior jump sword");
    if (m_IsFalling)
      m_Warrior->SetCurrentSeq("Warrior fall sword");
    if (m_IsHit)
      m_Warrior->SetCurrentSeq("Warrior hit sword");
    if (m_IsAttacking1) {
      m_Warrior->SetCurrentSeq("Warrior attack1");
      m_AttackEffects->SetCurrentSeq("Warrior Effect Attack_1");
    }
    if (m_IsAttacking2) {
      m_Warrior->SetCurrentSeq("Warrior attack2");
      m_AttackEffects->SetCurrentSeq("Warrior Effect Attack_2");
    }
    if (m_IsAttacking3) {
      m_Warrior->SetCurrentSeq("Warrior attack3");
      m_AttackEffects->SetCurrentSeq("Warrior Effect Attack_3");
    }
  }
  if (m_IsDeadHit) {
    m_Dialogue->SetCurrentSeq("Dialogue dead");
    m_Warrior->SetCurrentSeq("Warrior dead hit");
  }
  if (m_IsDeadGround) {
    m_Dialogue->SetCurrentSeq("Dialogue dead");
    m_Warrior->SetCurrentSeq("Warrior dead ground");
  }
}
void Warrior::Clear() {
  m_Warrior->Clear();
  m_Warrior = nullptr;
  m_AttackEffects->Clear();
  m_AttackEffects = nullptr;
  m_DustParticles->Clear();
  m_DustParticles = nullptr;
  m_Dialogue->Clear();
  m_Dialogue = nullptr;
  // clear collider
  m_Collider = nullptr;
  m_AttackCollider = nullptr;
  m_HitCollider = nullptr;
  // clear rigidBody
  m_RigidBody = nullptr;
}