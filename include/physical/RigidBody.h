#ifndef RIGID_BODY_H
#define RIGID_BODY_H
#include <Vector2D.h>
#define UNI_MASS 1.0f
#define GRAVITY 9.8f
class RigidBody
{
public:
    RigidBody()
    {
        m_Mass = UNI_MASS;
        m_Gravity = GRAVITY;
    }
    // set mass & gravity
    inline void SetMass(float mass) { m_Mass = mass; }
    inline void SetGravity(float gravity) { m_Gravity = gravity; }
    // force
    inline void ApplyForce(Vector2D F) { m_Force = F; }
    inline void ApplyForceX(float Fx) { m_Force.X = Fx; }
    inline void ApplyForceY(float Fy) { m_Force.Y = Fy; }
    inline void UnSetForce() { m_Force = Vector2D(0, 0); }
    // Getter
    inline float GetMass() { return m_Mass; };
    inline Vector2D Position() { return m_Position; }
    inline Vector2D Velocity() { return m_Velocity; }
    inline Vector2D Acceleration() { return m_Acceleration; }
    // Update methods
    void Update(float dt)
    {
        if (dt > 2 || dt < 0)
            dt = 0;
        m_Acceleration.X = (m_Force.X + m_Friction.X) / m_Mass;
        m_Acceleration.Y = m_Gravity + m_Force.Y / m_Mass;
        m_Velocity = m_Acceleration * dt;
        m_Position = m_Velocity * dt;
    }

private:
    float m_Mass;            // khoi luong
    float m_Gravity;         // trong luc
    Vector2D m_Force;        // luc
    Vector2D m_Friction;     // ma sat
    Vector2D m_Position;     // vi tri
    Vector2D m_Velocity;     // van toc
    Vector2D m_Acceleration; // gia toc
};

#endif