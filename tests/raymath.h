#ifndef RAYMATH_H
#define RAYMATH_H
#include <cmath>
#include "raylib.h"
inline Vector2 Vector2Add(Vector2 a, Vector2 b){ return {a.x+b.x, a.y+b.y}; }
inline Vector2 Vector2Scale(Vector2 a, float s){ return {a.x*s, a.y*s}; }
inline float Vector2Length(Vector2 v){ return std::sqrt(v.x*v.x + v.y*v.y); }
inline Vector2 Vector2Normalize(Vector2 v){ float l=Vector2Length(v); return l==0?Vector2{0,0}:Vector2{v.x/l, v.y/l}; }
#endif // RAYMATH_H
