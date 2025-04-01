#include "menu.h"

// 버튼 생성
Button menu_buttons[MENU_COUNT] = {
    {SCREEN_W / 2 - 100, 250, 200, 50},  // Start
    {SCREEN_W / 2 - 100, 320, 200, 50},  // Rank
    {SCREEN_W / 2 - 100, 390, 200, 50},   // Setting
    {SCREEN_W / 2 - 100, 460, 200, 50}   // Help
};

void menu() {
    // Allegro 초기화
    init();

    // Display 생성
    ALLEGRO_DISPLAY* display = al_create_display(SCREEN_W, SCREEN_H);

    // 메뉴 화면 생성
    ALLEGRO_BITMAP* main_screen = load_bitmap_resized("images/menu.png", SCREEN_W, SCREEN_H);

    // 폰트
    ALLEGRO_FONT* title_font = get_title_font();
    ALLEGRO_FONT* menu_font = get_menu_font();

    // 이벤트 큐 생성
    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(display));

    al_draw_bitmap(main_screen, 0, 0, 0);

    MenuOption selected = MENU_START;
    bool running = true;

    while (running) {
        ALLEGRO_EVENT event;

        // 키보드 입력 처리
        while (al_get_next_event(event_queue, &event)) {
            if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
                switch (event.keyboard.keycode) {
                case ALLEGRO_KEY_UP:
                    selected = (selected - 1 + MENU_COUNT) % MENU_COUNT;
                    break;
                case ALLEGRO_KEY_DOWN:
                    selected = (selected + 1) % MENU_COUNT;
                    break;
                case ALLEGRO_KEY_ENTER:
                    if (selected == MENU_START) start_game();
                    else if (selected == MENU_RANK) display_ranks();
                    else if (selected == MENU_SETTING) printf("설정 화면\n");
                    else if (selected == MENU_HELP) {
                        help_menu();
                    }
                    break;
                case ALLEGRO_KEY_ESCAPE:
                    running = false;
                    break;
                }
            }
        }

        // 화면 그리기
        al_draw_scaled_bitmap(main_screen, 0, 0, al_get_bitmap_width(main_screen), al_get_bitmap_height(main_screen), 0, 0, SCREEN_W, SCREEN_H, 0);

        // 제목
        al_draw_text(title_font, al_map_rgb(181, 178, 255), SCREEN_W / 2, 300, ALLEGRO_ALIGN_CENTER, "SUPERNOVA");

        // 메뉴 옵션 출력 (선택된 메뉴는 노란색, 나머지는 흰색)
        al_draw_text(menu_font, (selected == MENU_START) ? al_map_rgb(255, 255, 0) : al_map_rgb(255, 255, 255),
            SCREEN_W / 2, 550, ALLEGRO_ALIGN_CENTER, "START");
        al_draw_text(menu_font, (selected == MENU_RANK) ? al_map_rgb(255, 255, 0) : al_map_rgb(255, 255, 255),
            SCREEN_W / 2, 620, ALLEGRO_ALIGN_CENTER, "RANK");
        al_draw_text(menu_font, (selected == MENU_SETTING) ? al_map_rgb(255, 255, 0) : al_map_rgb(255, 255, 255),
            SCREEN_W / 2, 690, ALLEGRO_ALIGN_CENTER, "SETTING");
        al_draw_text(menu_font, (selected == MENU_HELP) ? al_map_rgb(255, 255, 0) : al_map_rgb(255, 255, 255),
            SCREEN_W / 2, 780, ALLEGRO_ALIGN_CENTER, "HELP");

        al_flip_display();
    }

    // 리소스 해제
    al_destroy_bitmap(main_screen);
    al_destroy_font(menu_font);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
}