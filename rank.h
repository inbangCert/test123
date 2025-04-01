#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "font.h"

#define RANKING_FILE "ranking.txt"
#define MAX_RANKS 100

typedef struct {
    char username[100];  // ����� �̸�
    int score;           // ����
} Rank;

int load_score(Rank* ranks);
void save_score(char* username, int score);
void display_ranks();
ALLEGRO_FONT* get_rank_font();