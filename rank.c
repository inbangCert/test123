#include "rank.h"

// ��ŷ�� ���Ͽ��� �о���� �Լ�
int load_score(Rank* ranks) {
    FILE* file = fopen(RANKING_FILE, "r");

    int rank_count = 0;

    if (file) {
        while (fscanf(file, "%s %d", ranks[rank_count].username, &ranks[rank_count].score) == 2) {
            rank_count++;
            if (rank_count >= MAX_RANKS) break;  // �ִ� ��ŷ ���� ����
        }
        fclose(file);
    }
    else {
        printf("fail to load ranks\n");
    }

    return rank_count;  // �ҷ��� ��ŷ�� ���� ��ȯ
}

// ���ο� ������ ���Ͽ� �����ϴ� �Լ�
void save_score(char* username, int score) {
    FILE* file = fopen(RANKING_FILE, "w");
    if (file) {
        fprintf(file, "%s %d", username, score);
        fclose(file);
    }
}

void display_ranks() {
    ALLEGRO_FONT* rank_font = get_rank_font();
    float x = 50, y = 50;  // ���� ��ġ (���� ���)

    Rank* ranks[MAX_RANKS];

    int rank_count = load_score(ranks);

    printf("%d. %s - %d", 0, ranks[0]->username, ranks[0]->score);

    // ȭ�鿡 �ؽ�Ʈ�� ���
    for (int i = 0; i < rank_count; i++) {
        // ������ �̸��� ǥ��
        al_draw_textf(rank_font, al_map_rgb(255, 255, 255), x, y, 0, "%d. %s - %d", i + 1, ranks[i]->username, ranks[i]->score);
        y += 30;  // �� ��ŷ ���� ������ �α� ���� y ��ǥ ����
    }

    // ȭ�� ������Ʈ
    al_flip_display();
}