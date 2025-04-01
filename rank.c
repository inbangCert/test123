#include "rank.h"

// 랭킹을 파일에서 읽어오는 함수
int load_score(Rank* ranks) {
    FILE* file = fopen(RANKING_FILE, "r");

    int rank_count = 0;

    if (file) {
        while (fscanf(file, "%s %d", ranks[rank_count].username, &ranks[rank_count].score) == 2) {
            rank_count++;
            if (rank_count >= MAX_RANKS) break;  // 최대 랭킹 개수 제한
        }
        fclose(file);
    }
    else {
        printf("fail to load ranks\n");
    }

    return rank_count;  // 불러온 랭킹의 개수 반환
}

// 새로운 점수를 파일에 저장하는 함수
void save_score(char* username, int score) {
    FILE* file = fopen(RANKING_FILE, "w");
    if (file) {
        fprintf(file, "%s %d", username, score);
        fclose(file);
    }
}

void display_ranks() {
    ALLEGRO_FONT* rank_font = get_rank_font();
    float x = 50, y = 50;  // 시작 위치 (좌측 상단)

    Rank* ranks[MAX_RANKS];

    int rank_count = load_score(ranks);

    printf("%d. %s - %d", 0, ranks[0]->username, ranks[0]->score);

    // 화면에 텍스트를 출력
    for (int i = 0; i < rank_count; i++) {
        // 점수와 이름을 표시
        al_draw_textf(rank_font, al_map_rgb(255, 255, 255), x, y, 0, "%d. %s - %d", i + 1, ranks[i]->username, ranks[i]->score);
        y += 30;  // 각 랭킹 사이 간격을 두기 위해 y 좌표 증가
    }

    // 화면 업데이트
    al_flip_display();
}