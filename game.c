#include "game.h"

void start_game() {
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / FPS);
    ALLEGRO_EVENT_QUEUE* game_event_queue = al_create_event_queue();

    al_register_event_source(game_event_queue, al_get_mouse_event_source());
    al_register_event_source(game_event_queue, al_get_timer_event_source(timer));
    al_register_event_source(game_event_queue, al_get_keyboard_event_source()); // 키보드 이벤트 등록

    al_start_timer(timer);

    // 이미지 로딩
    ALLEGRO_BITMAP* planet_img1 = load_bitmap_resized("images/planet_1.png", 30, 30);
    ALLEGRO_BITMAP* planet_img2 = load_bitmap_resized("images/planet_2.png", 50, 50);
    ALLEGRO_BITMAP* planet_img3 = load_bitmap_resized("images/planet_3.png", 70, 70);
    ALLEGRO_BITMAP* planet_img4 = load_bitmap_resized("images/planet_4.png", 100, 100);
    ALLEGRO_BITMAP* planet_img5 = load_bitmap_resized("images/planet_5.png", 140, 140);
    ALLEGRO_BITMAP* center = load_bitmap_resized("images/center.png", 30, 30);
    ALLEGRO_BITMAP* startpoint = load_bitmap_resized("images/ShootStartingPoint.png", 150, 150);
    ALLEGRO_BITMAP* gravityfield = load_bitmap_resized("images/GravityField.png", 700, 700);
    ALLEGRO_BITMAP* home_icon = load_bitmap_resized("images/home.png", 50, 50);


    if (!planet_img1) printf("planet_1.png 로딩 실패\n");
    if (!startpoint) printf("출발지점 이미지 로딩 실패\n");

    Vector2 shootStart = { init_x, init_y };
    Vector2 gravityCenter = { center_x, center_y };

    Planet* planet_list[MAX_PLANET] = { 0 };
    int planet_num = 0;
    planet_list[planet_num++] = Create_Planet(shootStart, (Vector2) { 0, 0 }, rand() % 5 + 1);

    // 상태 변수들
    Vector2 dragStart, dragEnd;
    float dragThreshold = 30.0f;
    float gravityScale = 1.0f;
    float centerCoefficient = 0.003f;
    float deltaTime = 1.0f / FPS;
    float last_shot_time = 0.0f;
    bool isFired = false, redraw = true, playing = true, isDragging = false;

    while (playing) {
        ALLEGRO_EVENT event;
        al_wait_for_event(game_event_queue, &event);

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            playing = false;

        else if (event.type == ALLEGRO_EVENT_TIMER)
            redraw = true;

        else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (event.keyboard.keycode == ALLEGRO_KEY_R) {
                playing = false;
                // 리소스 정리 후 다시 시작
                for (int i = 0; i < planet_num; ++i) {
                    if (planet_list[i]) free(planet_list[i]);
                }
                al_destroy_bitmap(planet_img1);
                al_destroy_bitmap(planet_img2);
                al_destroy_bitmap(planet_img3);
                al_destroy_bitmap(planet_img4);
                al_destroy_bitmap(planet_img5);
                al_destroy_bitmap(center);
                al_destroy_bitmap(gravityfield);
                al_destroy_bitmap(startpoint);
                al_destroy_bitmap(home_icon);
                al_destroy_event_queue(game_event_queue);
                al_destroy_timer(timer);

                start_game(); // 재시작
                return;
            }
        }

        else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            int mx = event.mouse.x;
            int my = event.mouse.y;

            // home 버튼 위치 클릭됐는지 확인
            if (mx >= SCREEN_W - 60 && mx <= SCREEN_W - 10 &&
                my >= 10 && my <= 60) {

                playing = false;
                // 리소스 정리 후 메뉴로 복귀
                for (int i = 0; i < planet_num; ++i) {
                    if (planet_list[i]) free(planet_list[i]);
                }
                al_destroy_bitmap(planet_img1);
                al_destroy_bitmap(planet_img2);
                al_destroy_bitmap(planet_img3);
                al_destroy_bitmap(planet_img4);
                al_destroy_bitmap(planet_img5);
                al_destroy_bitmap(center);
                al_destroy_bitmap(gravityfield);
                al_destroy_bitmap(startpoint);
                al_destroy_bitmap(home_icon);
                al_destroy_event_queue(game_event_queue);
                al_destroy_timer(timer);

                return; // start_game() 종료 → main 메뉴 화면으로 복귀
            }
        }

        ALLEGRO_MOUSE_STATE mouse;
        al_get_mouse_state(&mouse);

        if (al_mouse_button_down(&mouse, 1) && !isFired) {
            if (!isDragging) {
                isDragging = true;
                dragStart.x = mouse.x;
                dragStart.y = mouse.y;
            }
            dragEnd.x = mouse.x;
            dragEnd.y = mouse.y;
        }
        else if (isDragging && !isFired) {
            isDragging = false;
            Vector2 dragVec = Vector2_Sub(dragEnd, dragStart);

            if (Vector2_Length(dragVec) > dragThreshold && planet_num < MAX_PLANET) {
                Vector2 force = Vector2_Clamp(Vector2_Scale(dragVec, -dragForce), maxForce);
                Planet* p = planet_list[planet_num - 1];
                p->velocity = force;
                p->isFlying = true;
            }

            isFired = true;
            last_shot_time = al_get_time();
        }

        for (int i = 0; i < planet_num;) {
            Planet* p = planet_list[i];
            if (!p) { ++i; continue; }

            if (p->position.x < -100 || p->position.x > SCREEN_W + 100 ||
                p->position.y < -100 || p->position.y > SCREEN_H + 100) {
                Destroy_Planet(planet_list, &planet_num, i);
                continue;
            }

            if (!p->isFlying || p->type == 0) { ++i; continue; }

            if (collision_check(p->position.x, p->position.y, p->radius, center_x, center_y, 15)) {
                Vector2 normal = Vector2_Normalize(Vector2_Sub(p->position, gravityCenter));
                p->velocity = Vector2_Sub(p->velocity,
                    Vector2_Scale(Vector2_Project(p->velocity, normal), (1 + RESTITUTION)));
            }

            for (int j = 0; j < planet_num; ++j) {
                Planet* q = planet_list[j];
                if (!q || q == p || !q->isFlying) continue;

                if (collision_check(p->position.x, p->position.y, p->radius,
                    q->position.x, q->position.y, q->radius)) {

                    if (p->type == q->type) {
                        merge_planets(p, q);
                        Destroy_Planet(planet_list, &planet_num, j);
                        if (j < i) i--;
                        continue;
                    }

                    Vector2 normal = Vector2_Normalize(Vector2_Sub(p->position, q->position));
                    p->velocity = Vector2_Sub(p->velocity, Vector2_Scale(Vector2_Project(p->velocity, normal), (1 + RESTITUTION)));
                    q->velocity = Vector2_Sub(q->velocity, Vector2_Scale(Vector2_Project(q->velocity, normal), (1 + RESTITUTION)));
                }
            }

            CalcGravity(p, gravityCenter, centerCoefficient, deltaTime);
            p->position = Vector2_Add(p->position, Vector2_Scale(p->velocity, deltaTime));
            ++i;
        }

        if (al_get_time() - last_shot_time > 5.0 && isFired) {
            if (planet_num < MAX_PLANET) {
                planet_list[planet_num++] = Create_Planet(shootStart, (Vector2) { 0, 0 }, rand() % 5 + 1);
            }
            isFired = false;
        }

        if (redraw) {
            al_clear_to_color(al_map_rgb(20, 20, 20));
            al_draw_bitmap(gravityfield, center_x - 350, center_y - 350, 0);
            al_draw_bitmap(startpoint, init_x - 75, init_y - 75, 0);
            al_draw_bitmap(center, center_x - 15, center_y - 15, 0);
            al_draw_bitmap(home_icon, SCREEN_W - 60, 10, 0);


            for (int i = 0; i < planet_num; ++i) {
                Planet* p = planet_list[i];
                if (!p || !p->isFlying) continue;

                ALLEGRO_BITMAP* planet_img = NULL;
                switch (p->type) {
                case 1: planet_img = planet_img1; break;
                case 2: planet_img = planet_img2; break;
                case 3: planet_img = planet_img3; break;
                case 4: planet_img = planet_img4; break;
                case 5: planet_img = planet_img5; break;
                }

                if (planet_img)
                    al_draw_bitmap(planet_img, p->position.x - p->radius, p->position.y - p->radius, 0);
            }

            if (isDragging) {
                Vector2 forceVec = Vector2_Clamp(Vector2_Scale(Vector2_Sub(dragEnd, dragStart), -line_length), maxForce);
                Vector2 endPoint = Vector2_Add(shootStart, forceVec);
                al_draw_line(shootStart.x, shootStart.y, endPoint.x, endPoint.y, al_map_rgb(255, 255, 0), 2);
            }

            al_flip_display();
            redraw = false;
        }
    }

    for (int i = 0; i < planet_num; ++i) {
        if (planet_list[i]) free(planet_list[i]);
    }

    al_destroy_bitmap(planet_img1);
    al_destroy_bitmap(planet_img2);
    al_destroy_bitmap(planet_img3);
    al_destroy_bitmap(planet_img4);
    al_destroy_bitmap(planet_img5);
    al_destroy_bitmap(center);
    al_destroy_bitmap(gravityfield);
    al_destroy_bitmap(startpoint);
    al_destroy_event_queue(game_event_queue);
    al_destroy_timer(timer);
}

// 충돌 검사
bool collision_check(int x1, int y1, int size1, int x2, int y2, int size2) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    float distance = sqrt(dx * dx + dy * dy);
    return distance < size1 + size2;
}

// 중력 + 회전 보정
void CalcGravity(Planet* rb, Vector2 center, float centerCoefficient, float deltaTime) {
    Vector2 gravityDir = Vector2_Normalize(Vector2_Sub(center, rb->position));
    Vector2 gravity = Vector2_Scale(gravityDir, GRAVITY);

    Vector2 vel = rb->velocity;
    Vector2 nextPos = Vector2_Add(rb->position, vel);

    Vector2 parallelVel = Vector2_Project(vel, gravityDir);
    Vector2 perpendicularVel = Vector2_Sub(vel, parallelVel);

    Vector2 correctionDir = Vector2_Project((Vector2) { -perpendicularVel.x, -perpendicularVel.y }, Vector2_Sub(nextPos, center));
    Vector2 newPerpendicularVel = Vector2_Add(perpendicularVel, correctionDir);

    perpendicularVel.x = (1 - centerCoefficient) * perpendicularVel.x + centerCoefficient * newPerpendicularVel.x;
    perpendicularVel.y = (1 - centerCoefficient) * perpendicularVel.y + centerCoefficient * newPerpendicularVel.y;

    rb->velocity = Vector2_Add(Vector2_Add(parallelVel, perpendicularVel), Vector2_Scale(gravity, deltaTime));
}

Planet* Create_Planet(Vector2 pos, Vector2 vel, int type) {
    Planet* p = (Planet*)calloc(1, sizeof(Planet));
    if (!p) {
        printf("행성 생성 실패 : 메모리 부족\n");
        return NULL;
    }
    p->position = pos;
    p->velocity = vel;
    p->type = type;
    p->radius = get_radius(type);
    p->isFlying = true;
    return p;
}

void Destroy_Planet(Planet** planet_list, int* count, int index) {
    if (!planet_list[index]) return;
    free(planet_list[index]);
    for (int i = index; i < (*count) - 1; ++i) {
        planet_list[i] = planet_list[i + 1];
    }
    planet_list[*count - 1] = NULL;
    (*count)--;
}

int get_radius(int type) {
    switch (type) {
    case 1: return 15;
    case 2: return 25;
    case 3: return 35;
    case 4: return 50;
    case 5: return 70;
    default: return 10;
    }
}

void merge_planets(Planet* a, Planet* b) {
    a->type += 1;
    a->radius = get_radius(a->type);
    a->velocity = Vector2_Scale(Vector2_Add(a->velocity, b->velocity), 0.5f);
    b->isFlying = false;
    b->type = 0;
    b->velocity = (Vector2){ 0, 0 };
}
