
#include "mover.hpp"
#include <raylib.h>
#include <raymath.h>

Mover::Mover(Vector2 pos, Vector2 vel)
: m_position(pos)
, m_velocity(vel)
, m_acceleration(Vector2{0, 0})
{}


void Mover::apply_force(Vector2 force)
{
  m_acceleration = Vector2Add(m_acceleration, force);
}

void Mover::draw()
{
  const float scale_factor = 0.90; // for black outline

  DrawCircle(m_position.x, m_position.y, m_radius, BLACK);
  DrawCircle(m_position.x, m_position.y, m_radius * scale_factor, m_colour);
}


void Mover::update(float dt)
{
  m_velocity = Vector2Add(m_velocity, m_acceleration);

  const auto vel = Vector2Scale(m_velocity, dt);
  m_position     = Vector2Add(m_position, vel);

  // Clear acceleration after it’s been applied.
  m_acceleration = Vector2{0, 0};
}