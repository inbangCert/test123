#include "vector.h"

Vector2 Vector2_Add(Vector2 a, Vector2 b) { return (Vector2) { a.x + b.x, a.y + b.y }; }
Vector2 Vector2_Sub(Vector2 a, Vector2 b) { return (Vector2) { a.x - b.x, a.y - b.y }; }
Vector2 Vector2_Scale(Vector2 v, float s) { return (Vector2) { v.x* s, v.y* s }; }
float Vector2_Length(Vector2 v) { return sqrtf(v.x * v.x + v.y * v.y); }
Vector2 Vector2_Normalize(Vector2 v) {
    float mag = Vector2_Length(v);
    return (mag > 0) ? Vector2_Scale(v, 1.0f / mag) : (Vector2) { 0, 0 };
}
float Vector2_Dot(Vector2 a, Vector2 b) { return a.x * b.x + a.y * b.y; }
Vector2 Vector2_Project(Vector2 v, Vector2 onto) {
    float dot = Vector2_Dot(v, onto);
    float ontoMagSq = Vector2_Dot(onto, onto);
    if (ontoMagSq == 0.0f) return (Vector2) { 0.0f, 0.0f };
    float scale = dot / ontoMagSq;
    return Vector2_Scale(onto, scale);
}
Vector2 Vector2_Clamp(Vector2 v, float maxLength) {
    float len = Vector2_Length(v);
    if (len > maxLength) return Vector2_Scale(Vector2_Normalize(v), maxLength);
    return v;
}