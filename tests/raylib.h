#ifndef RAYLIB_H
#define RAYLIB_H
#include <cmath>
struct Texture2D { int id = 0; int width = 0; int height = 0; int mipmaps = 1; int format = 0; };
struct Vector2 { float x = 0.0f; float y = 0.0f; };
struct Rectangle { float x = 0.0f; float y = 0.0f; float width = 0.0f; float height = 0.0f; };
struct Color { unsigned char r=0,g=0,b=0,a=0; };
static const Color WHITE{255,255,255,255};
static const Color RED{255,0,0,255};
inline float GetFrameTime(){ return 0.016f; }
inline bool CheckCollisionRecs(Rectangle, Rectangle){ return false; }
inline void DrawRectangleLines(int,int,int,int,Color){}
inline void DrawTexturePro(Texture2D, Rectangle, Rectangle, Vector2, float, Color){}
#endif // RAYLIB_H
