#include "init.h"

void init() {
	// Allegro �ʱ�ȭ
	al_init();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();

	// �Է� ��ġ Ȱ��ȭ
	al_install_mouse();
	al_install_keyboard();

	// ���� �����⸦ �ʱ�ȭ
	srand(time(NULL));
}