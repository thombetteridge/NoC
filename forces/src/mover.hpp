#ifndef MOVER_HPP
#define MOVER_HPP

#include <raylib.h>

class Mover
{
public:
  Mover(Vector2 pos, Vector2 vel);

  void update(float dt);
  void draw();
  void apply_force(Vector2 force);


private:
  Vector2 m_position;
  Vector2 m_velocity;
  Vector2 m_acceleration;

  float m_radius = 50;
  Color m_colour = GRAY;

  const float terminal_velocity = 100;
};


#endif