#pragma once
#include "stdbool.h"
#include "math.h"

typedef struct {
    float x, y;
} Vector2;

Vector2 Vector2_Add(Vector2 a, Vector2 b);
Vector2 Vector2_Sub(Vector2 a, Vector2 b);
Vector2 Vector2_Scale(Vector2 v, float s);
float Vector2_Length(Vector2 v);
Vector2 Vector2_Normalize(Vector2 v);
float Vector2_Dot(Vector2 a, Vector2 b);
Vector2 Vector2_Project(Vector2 v, Vector2 onto);
Vector2 Vector2_Clamp(Vector2 v, float maxLength);
