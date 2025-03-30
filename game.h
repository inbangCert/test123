#pragma once
#include "init.h"
#include "display.h"
#include "vector.h"
#include <stdlib.h>



// ������ ����
float line_length = 0.8f;

// �༺ �߻� ��ġ
#define init_x 300
#define init_y SCREEN_H / 2

// ��ǥ �༺ ��ġ
#define center_x SCREEN_W - 400
#define center_y SCREEN_H / 2

// ���� ���
double GRAVITY = 0.01f;  // �߷�
double RESTITUTION = 0.3f;      // ź�� ���
double dragForce = 500.0f;      // ���� ��
double maxForce = 500.0f;      // �ִ� ���� ��

// �ִ� �༺ ����
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
// �ٽ� �߷� + ȸ�� ���� �Լ�
void CalcGravity(Planet* rb, Vector2 center, float centerCoefficient, float deltaTime);
Planet* Create_Planet(Vector2 pos, Vector2 vel, int type);
void Destroy_Planet(Planet** planet_list, int* count, int index);
void merge_planets(Planet* a, Planet* b);