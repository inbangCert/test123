#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include "init.h"
#include "menu.h"
#include "display.h"
#include "vector.h"
#include "rank.h"   
#include <stdlib.h>

// ������ ����
float line_length = 0.15f;

// �༺ �߻� ��ġ
#define init_x 300
#define init_y SCREEN_H / 2

//���
#define SCROLL_FRAMES 80

//��� ���� Ÿ�̸�
float background_timer = 0.0f;
float background_interval = 0.2f;

// �༺ ��� ��ġ
#define wait_x 120
#define wait_y 120

// ��ǥ �༺ ��ġ
#define center_x SCREEN_W - 400
#define center_y SCREEN_H / 2

// ���� ��� (���� �� �� ���ϰ� �ϱ�)
double GRAVITY = 9.8f;  // �߷�
double centerCoefficient = 0.015f;
double RESTITUTION = 0.6f;      // ź�� ���
double dragForce = 150.0f;      // ���� ��
double maxForce = 200.0f;      // �ִ� ���� ��

// �ִ� �༺ ����
#define MAX_PLANET 100
#define PLANET_TYPES 7

// ���� �̸� �ִ� ����
#define MAX_NAME_LENGTH 20

typedef struct {
    Vector2 position;
    Vector2 velocity;
    bool isFlying;
    int type;
    int radius;
    bool wasInGravityZone;
    bool isLeavingGravityZone;
    float rotation;         // ȸ�� ����
    float angularVelocity;  // ���ӵ�
} Planet;

int get_radius(int type);

void start_game();
bool collision_check(int x1, int y1, int size1, int x2, int y2, int size2);
// �ٽ� �߷� + ȸ�� ���� �Լ�
void CalcGravity(Planet* rb, Vector2 center, float centerCoefficient, float deltaTime);
Planet* Create_Planet(Vector2 pos, Vector2 vel, int type);
void Destroy_Planet(Planet** planet_list, int* count, int index);
void merge_planets(Planet* a, Planet* b);
void Win();
char* getUserName();