#pragma once
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include "display.h"

typedef enum { MENU_START, MENU_RANK, MENU_SETTING, MENU_HELP, MENU_COUNT } MenuOption;

typedef struct {
    int x, y, width, height;
} Button;

// 버튼 생성
Button menu_buttons[MENU_COUNT] = {
    {SCREEN_W / 2 - 100, 250, 200, 50},  // Start
    {SCREEN_W / 2 - 100, 320, 200, 50},  // Rank
    {SCREEN_W / 2 - 100, 390, 200, 50},   // Setting
    {SCREEN_W / 2 - 100, 460, 200, 50 }   // Help
};