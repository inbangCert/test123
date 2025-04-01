#include "help.h"

void help_menu() {
    ALLEGRO_BITMAP* help_screen = al_load_bitmap("images/help.png");

    // �̺�Ʈ ť ����
    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    if (!help_screen) {
        printf("help.png �ε� ����!\n");
    }
    else {
        al_draw_scaled_bitmap(help_screen, 0, 0,
            al_get_bitmap_width(help_screen), al_get_bitmap_height(help_screen),
            0, 0, SCREEN_W, SCREEN_H, 0);
        al_flip_display();

        // ESC�� ���� ������ ��ٸ��� ����
        bool in_help = true;
        while (in_help) {
            ALLEGRO_EVENT help_event;
            al_wait_for_event(event_queue, &help_event);

            if (help_event.type == ALLEGRO_EVENT_KEY_DOWN &&
                help_event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                in_help = false; // ESC ������ ���� ����
            }
        }

        al_destroy_bitmap(help_screen);
    }
}