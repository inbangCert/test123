#pragma once
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>

#define SCREEN_W 1600
#define SCREEN_H 900
#define FPS 120

#define GRID_SIZE 100
#define GRID_WIDTH (SCREEN_W / GRID_SIZE + 1)
#define GRID_HEIGHT (SCREEN_H / GRID_SIZE + 1)

void init();