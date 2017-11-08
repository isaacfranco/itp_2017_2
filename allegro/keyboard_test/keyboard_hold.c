#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 480;

typedef struct keyboard_s Keyboard;
struct keyboard_s {
	short up, down, left, right;
};

int keyboard_clear(Keyboard *keyboard) {
	keyboard->up = 0;
	keyboard->down = 0;
	keyboard->up = 0;
	keyboard->up = 0;
}

int main(int argc, char * argv[]) {
	ALLEGRO_DISPLAY *tela;
	ALLEGRO_TIMER *timer;
	ALLEGRO_EVENT_QUEUE *fila_eventos;
	float fps = 60.0;
	float frame_time = 1.0 / fps;
	int sair = 0;
	Keyboard teclado;
	ALLEGRO_COLOR vermelho, branco;

	float circulo_x, circulo_y, circulo_step;
	circulo_x = SCREEN_WIDTH / 2;
	circulo_y = SCREEN_HEIGHT / 2;
	circulo_step = 1;

	/* inicializar allegro */
	al_init();

	/* inicializar addons utilizados */
	al_init_primitives_addon();

	al_install_keyboard();

	keyboard_clear(&teclado);

	/* criar recursos */
	tela = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
	fila_eventos = al_create_event_queue();
	timer = al_create_timer(frame_time);

	vermelho = al_map_rgb(255, 0, 0);
	branco = al_map_rgb(255, 255, 255);


	/* registrar event_sources na fila_eventos */
	al_register_event_source( fila_eventos, al_get_display_event_source(tela) );
	al_register_event_source( fila_eventos, al_get_timer_event_source(timer) );
	al_register_event_source( fila_eventos, al_get_keyboard_event_source() );

	/* iniciar o timer para gerar eventos para a fila */
	al_start_timer(timer);

	while ( !sair ) {
		ALLEGRO_EVENT evento_atual;

		/* aguardar evento qualquer e salvar ele em "evento_atual" */
		al_wait_for_event(fila_eventos, &evento_atual);

		switch (evento_atual.type) {
			case ALLEGRO_EVENT_TIMER:
				/* timer ocorreu (1 por frame) */

				// fisica e movimentos
				if (teclado.up) {
					printf("\tUP segurado\n");
					circulo_y -= circulo_step;
				}

				if (teclado.down) {
					printf("\tDOWN segurado\n");
					circulo_y += circulo_step;
				} 

				if (teclado.left) {
					printf("\tLEFT segurado\n");
					circulo_x -= circulo_step;
				}

				if (teclado.right) {
					printf("\tRIGHT segurado\n");
					circulo_x += circulo_step;
				}

				// desenhar
				al_clear_to_color(branco);
				al_draw_circle(circulo_x, circulo_y, 10, vermelho, 5);

				// flip
				al_flip_display();

				break;
			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				/* clicar em fechar janela */
				sair = 1;
				break;
			case ALLEGRO_EVENT_KEY_DOWN:
				switch(evento_atual.keyboard.keycode) {
					case ALLEGRO_KEY_UP:
						teclado.up = 1;
						break;
					case ALLEGRO_KEY_DOWN:
						teclado.down = 1;
						break;
					case ALLEGRO_KEY_LEFT:
						teclado.left = 1;
						break;
					case ALLEGRO_KEY_RIGHT:
						teclado.right = 1;
						break;
					default:
						break;
				}
				break;
			case ALLEGRO_EVENT_KEY_UP:
				switch(evento_atual.keyboard.keycode) {
					case ALLEGRO_KEY_UP:
						teclado.up = 0;
						break;
					case ALLEGRO_KEY_DOWN:
						teclado.down = 0;
						break;
					case ALLEGRO_KEY_LEFT:
						teclado.left = 0;
						break;
					case ALLEGRO_KEY_RIGHT:
						teclado.right = 0;
						break;
					default:
						break;
				}
				break;
			case ALLEGRO_EVENT_DISPLAY_SWITCH_OUT:
				keyboard_clear(&teclado);
				break;
			default:
				//printf("Evento desconhecido encontrado tipo: %i\n", evento_atual.type);
				break;
		}
	}

	al_destroy_timer(timer);
	al_destroy_display(tela);

}