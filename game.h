#pragma once
#include "init.h"
#include "display.h"
#include "vector.h"
#include <stdlib.h>



// 유도선 설정
float line_length = 0.8f;

// 행성 발사 위치
#define init_x 300
#define init_y SCREEN_H / 2

// 목표 행성 위치
#define center_x SCREEN_W - 400
#define center_y SCREEN_H / 2

// 물리 계수
double GRAVITY = 0.01f;  // 중력
double RESTITUTION = 0.3f;      // 탄성 계수
double dragForce = 500.0f;      // 당기는 힘
double maxForce = 500.0f;      // 최대 당기는 힘

// 최대 행성 개수
#define MAX_PLANET 100

typedef struct {
    Vector2 position;
    Vector2 velocity;
    bool isFlying;
    int type;
    int radius;
} Planet;

int get_radius(int type);

void start_game();
bool collision_check(int x1, int y1, int size1, int x2, int y2, int size2);
// 핵심 중력 + 회전 보정 함수
void CalcGravity(Planet* rb, Vector2 center, float centerCoefficient, float deltaTime);
Planet* Create_Planet(Vector2 pos, Vector2 vel, int type);
void Destroy_Planet(Planet** planet_list, int* count, int index);
void merge_planets(Planet* a, Planet* b);