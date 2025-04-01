#include "init.h"

void init() {
	// Allegro 초기화
	al_init();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();

	// 입력 장치 활성화
	al_install_mouse();
	al_install_keyboard();

	// 난수 생성기를 초기화
	srand(time(NULL));
}