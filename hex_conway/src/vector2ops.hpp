#ifndef RAYLIB_VEC2_OP_OVERLOADS
#define RAYLIB_VEC2_OP_OVERLOADS

#include <raylib.h>
#include <raymath.h>

#include <iostream>

inline Vector2 operator+(const Vector2& a, const Vector2& b)
{
  return Vector2Add(a, b);
}

inline Vector2& operator+=(Vector2& a, const Vector2& b)
{
  a = a + b;
  return a;
}

inline Vector2& operator-(Vector2& a)
{
  a = Vector2Negate(a);
  return a;
}

inline Vector2 operator-(const Vector2& a, const Vector2& b)
{
  return Vector2Subtract(a, b);
}


inline Vector2& operator-=(Vector2& a, const Vector2& b)
{
  a = a - b;
  return a;
}

inline Vector2 operator*(const Vector2& a, float b)
{
  return Vector2Scale(a, b);
}

inline Vector2& operator*=(Vector2& a, const float b)
{
  a = a * b;
  return a;
}

inline Vector2 operator/(const Vector2& a, const float b)
{
  if (b == 0.0) {
    std::cerr << "Division by zero error." << std::endl;
    throw std::domain_error("Division by zero error");
  }
  float recip = 1.0 / b;
  return a * recip;
}

inline Vector2& operator/=(Vector2& a, const float b)
{
  a = a / b;
  return a;
}

inline bool operator==(const Vector2& a, const Vector2& b)
{
  if ((a.x == b.x) && (a.y == b.y))
    return true;
  return false;
}

inline std::ostream& operator<<(std::ostream& os, Vector2 a)
{
  os << "(" << a.x << "," << a.y << ")";
  return os;
}

inline float length_Vector2(const Vector2& v)
{
  return std::sqrt(v.x * v.x + v.y * v.y);
}

inline Vector2 normalize_Vector2(const Vector2& v)
{
  const float len = length_Vector2(v);
  if (len != 0) {
    return Vector2{v.x / len, v.y / len};
  }
  return v; // Return the zero vector if length is zero
}

inline float distance_between_Vector2(const Vector2& v1, const Vector2& v2)
{
  return length_Vector2(v1 - v2);
}

inline Vector2 magnitude_Vector2(const Vector2& v, float new_magnitude)
{
  if (new_magnitude < 0) {
    throw std::invalid_argument("Magnitude cannot be negative.");
  }

  const float current_length = length_Vector2(v);

  if (current_length == 0.0f) {
    // Handle the zero vector case if needed
    return Vector2{0.0f, 0.0f}; // or set directionally to the desired magnitude
  }

  const float scale = new_magnitude / current_length;

  return Vector2{v.x * scale, v.y * scale};
}

inline Vector2 limit_Vector2(const Vector2& v, float max_magnitude)
{
  if (max_magnitude < 0) {
    throw std::invalid_argument("Maximum magnitude cannot be negative.");
  }

  auto x = v.x;
  auto y = v.y;

  const float current_length = length_Vector2(v);
  if (current_length > max_magnitude) {
    float scale = max_magnitude / current_length;
    x *= scale;
    y *= scale;
  }

  return Vector2{x, y};
}

#endif