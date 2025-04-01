#include "help.h"

void help_menu() {
    ALLEGRO_BITMAP* help_screen = al_load_bitmap("images/help.png");

    // 이벤트 큐 생성
    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    if (!help_screen) {
        printf("help.png 로딩 실패!\n");
    }
    else {
        al_draw_scaled_bitmap(help_screen, 0, 0,
            al_get_bitmap_width(help_screen), al_get_bitmap_height(help_screen),
            0, 0, SCREEN_W, SCREEN_H, 0);
        al_flip_display();

        // ESC가 눌릴 때까지 기다리는 루프
        bool in_help = true;
        while (in_help) {
            ALLEGRO_EVENT help_event;
            al_wait_for_event(event_queue, &help_event);

            if (help_event.type == ALLEGRO_EVENT_KEY_DOWN &&
                help_event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                in_help = false; // ESC 누르면 루프 종료
            }
        }

        al_destroy_bitmap(help_screen);
    }
}