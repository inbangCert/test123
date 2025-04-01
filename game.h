#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include "init.h"
#include "menu.h"
#include "display.h"
#include "vector.h"
#include "rank.h"   
#include <stdlib.h>

// 유도선 설정
float line_length = 0.15f;

// 행성 발사 위치
#define init_x 300
#define init_y SCREEN_H / 2

//배경
#define SCROLL_FRAMES 80

//배경 전용 타이머
float background_timer = 0.0f;
float background_interval = 0.2f;

// 행성 대기 위치
#define wait_x 120
#define wait_y 120

// 목표 행성 위치
#define center_x SCREEN_W - 400
#define center_y SCREEN_H / 2

// 물리 계수 (수정 시 꼭 말하고 하기)
double GRAVITY = 9.8f;  // 중력
double centerCoefficient = 0.015f;
double RESTITUTION = 0.6f;      // 탄성 계수
double dragForce = 150.0f;      // 당기는 힘
double maxForce = 200.0f;      // 최대 당기는 힘

// 최대 행성 개수
#define MAX_PLANET 100
#define PLANET_TYPES 7

// 유저 이름 최대 길이
#define MAX_NAME_LENGTH 20

typedef struct {
    Vector2 position;
    Vector2 velocity;
    bool isFlying;
    int type;
    int radius;
    bool wasInGravityZone;
    bool isLeavingGravityZone;
    float rotation;         // 회전 각도
    float angularVelocity;  // 각속도
} Planet;

int get_radius(int type);

void start_game();
bool collision_check(int x1, int y1, int size1, int x2, int y2, int size2);
// 핵심 중력 + 회전 보정 함수
void CalcGravity(Planet* rb, Vector2 center, float centerCoefficient, float deltaTime);
Planet* Create_Planet(Vector2 pos, Vector2 vel, int type);
void Destroy_Planet(Planet** planet_list, int* count, int index);
void merge_planets(Planet* a, Planet* b);
void Win();
char* getUserName();